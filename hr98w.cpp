/* hr.cpp - writes horizontal bar to terminal
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C++98
 */

#include <climits>
#include <clocale>
#include <cstdlib>
#include <cwchar>
#include <iostream>

#ifdef __WIN32__
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif /* __WIN32__ */

#ifdef __WIN32__
  #if WINVER >= _WIN32_WINNT_WINXP  || _WIN32_WINNT >= _WIN32_WINNT_WINXP 
    #define AMAX 8191
  #else
    #define AMAX 2047
  #endif /* WINVER >= _WIN32_WINNT_WINXP  || _WIN32_WINNT >= _WIN32_WINNT_WINXP */
#else
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

using std::wcout;
using std::endl;
using std::wcslen;
using std::mbstowcs;

int main(int argc, char *argv[]) {
	int cols;
	wchar_t arg[AMAX];
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

	setlocale(LC_ALL, "");

	if(argc < 2) {
		while(cols--)
			wcout.put(L'#');
		endl(wcout);
	} else {
		for(int j = 1; j < argc; ++j) {
			mbstowcs(arg, argv[j], AMAX);
			int len = wcslen(arg);
			for(int i = 0; i < cols; ++i)
				wcout.put(arg[i%len]);
			endl(wcout);
		}
	}
}
