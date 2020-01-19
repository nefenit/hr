/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019-2020 Bartosz Mierzynski
 * Written in C99
 */
 
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#ifdef __WIN32__
#include <windows.h>
  #if WINVER >= _WIN32_WINNT_WINXP  || _WIN32_WINNT >= _WIN32_WINNT_WINXP 
    #define AMAX 8191
  #else
    #define AMAX 2047
  #endif /* WINVER >= _WIN32_WINNT_WINXP  || _WIN32_WINNT >= _WIN32_WINNT_WINXP */
#else
#include <sys/ioctl.h>
  #ifdef ARG_MAX
    #define AMAX ARG_MAX
  #else
    #ifdef _POSIX_ARG_MAX
      #define AMAX _POSIX_ARG_MAX
    #else
      #define AMAX 4096
    #endif /* _POSIX_ARG_MAX */
  #endif /* ARG_MAX */
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
		putwchar(L'#');
	putwchar(L'\n');
}

void hr2(int n, const char *s) {
	wchar_t arg[AMAX];
	size_t  len;

	mbstowcs(arg, s, AMAX);
	len = wcslen(arg);
	for(int i = 0; i < n; ++i)
		putwchar(arg[i%len]);
	putwchar(L'\n');
}

int main(int argc, char *argv[]) {
	int n;

	setlocale(LC_ALL, "");

	get_columns(&n);

	if(argc < 2)
		hr1(n);
	else
		for(--argc, ++argv; argc; --argc, ++argv)
			hr2(n, *argv);
 }
