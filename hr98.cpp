/* hr.cpp - writes horizontal bar to terminal
 * (c) Copyright 2019-2020 Bartosz Mierzynski
 * Written in C++98
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#ifdef __WIN32__
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif /* __WIN32__ */

using std::cout;
using std::endl;
using std::strlen;

void get_columns(int &n) {
#ifdef __WIN32__
	const char                 *columns;
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	if((columns = getenv("COLUMNS")) && (strlen(columns)))
		n = atoi(columns);
	else
		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			n = csbi.dwSize.X;
		else
			n = 80;
#else
	const char *columns;
	struct winsize w;

	if((columns = getenv("COLUMNS")) && (strlen(columns))) {
		n = atoi(columns);
	} else {
		ioctl(0, TIOCGWINSZ, &w);
		n = w.ws_col > 0 ? w.ws_col : 80;
	}
#endif /* __WIN32__ */
}

void hr1(int n = 80) {
	while(n--)
		cout.put('#');
	endl(cout);
}

void hr2(int n = 80, const char *s = "#") {
	int len = strlen(s);
	for(int i = 0; i < n; ++i)
		cout.put(s[i%len]);
	endl(cout);
}

int main(int argc, char *argv[]) {
	int n;

	get_columns(n);
	
	if(argc < 2)
		hr1(n);
	else
		for(--argc, ++argv; argc; --argc, ++argv)
			hr2(n, *argv);
}
