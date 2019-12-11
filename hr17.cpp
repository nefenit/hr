/* hr.cpp - writes horizontal bar to terminal
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C++17
 */

#include <iostream>
#include <cstring>
#ifdef __WIN32__
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif /* __WIN32__ */


using std::cout, std::endl, std::strlen;

int main(int argc, char *argv[]) {
	auto cols = 0;
	const char *columns;

	if((columns = getenv("COLUMNS")) && (strlen(columns))) {
		cols = atoi(columns);
	} else {
#ifdef __WIN32__
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		
		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			cols = csbi.dwSize.X;
		else
			cols = 80;
#else
		winsize w;
		
		ioctl(0, TIOCGWINSZ, &w);
		cols = w.ws_col > 0 ? w.ws_col : 80;
#endif /* __WIN32__ */
	}
	
	if(argc < 2) {
		while(cols--)
			cout.put('#');
		endl(cout);
	} else {
		for(auto j = 1; j < argc; ++j) {
			auto len = strlen(argv[j]);
			for(auto i = 0; i < cols; ++i)
				cout.put(argv[j][i%len]);
			endl(cout);
		}
	}
}
