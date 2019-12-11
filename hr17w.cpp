/* hr.cpp - writes horizontal bar to terminal
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C++17
 */

#include <climits>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <iostream>
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

using std::wcout, std::endl, std::wcslen, std::mbstowcs;

int main(int argc, char *argv[]) {
	auto cols = 0;
	const char *columns;
	wchar_t arg[AMAX];

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

	setlocale(LC_ALL, "");

	if(argc < 2) {
		while(cols--)
			wcout.put(L'#');
		endl(wcout);
	} else {
		for(auto j = 1; j < argc; ++j) {
			mbstowcs(arg, argv[j], AMAX);
			auto len = wcslen(arg);
			for(auto i = 0; i < cols; ++i)
				wcout.put(arg[i%len]);
			endl(wcout);
		}
	}
}
