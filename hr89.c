/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019-2020 Bartosz Mierzynski
 * Written in ANSI C (C89)
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __WIN32__
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif /* __WIN32__ */

void get_columns(int *n) {
#ifdef __WIN32__
	const char                 *columns;
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	if((columns = getenv("COLUMNS")) && (strlen(columns)))
		*n = atoi(columns);
	else
		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			*n = csbi.dwSize.X;
		else
			*n = 80;
#else
	const char *columns;
	struct winsize w;

	if((columns = getenv("COLUMNS")) && (strlen(columns))) {
		*n = atoi(columns);
	} else {
		ioctl(0, TIOCGWINSZ, &w);
		*n = w.ws_col > 0 ? w.ws_col : 80;
	}
#endif /* __WIN32__ */
}

void hr1(int n) {
	while(n--)
		putchar('#');
	putchar('\n');
}

void hr2(int n, const char *s) {
	int i, len = strlen(s);
	
	for(i = 0; i < n; ++i)
		putchar(s[i % len]);
	putchar('\n');
}

int main(int argc, char *argv[]) {
	int n;

	get_columns(&n);
	if(argc < 2)
		hr1(n);
	else
		for(--argc, ++argv; argc; --argc, ++argv)
			hr2(n, *argv);

 	return EXIT_SUCCESS;
 }
