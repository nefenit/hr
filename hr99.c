/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C99
 */
 
#include <stdio.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
#ifdef __WIN32__
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		cols = csbi.dwSize.X;
	else
		cols = 80;
#else
	struct winsize w;
	
	ioctl(0, TIOCGWINSZ, &w);
	cols = w.ws_col > 0 ? w.ws_col : 80;
#endif /* __WIN32__ */
	
	if(argc < 2) {
		while(cols--)
			putchar('#');
		putchar('\n');
	} else {
		for(int j = 1; j < argc; ++j) {
			int len = strlen(argv[j]);
			for(int i = 0; i < cols; ++i)
				putchar(argv[j][i%len]);
			putchar('\n');
		}
	}
	
 	return 0;
}
