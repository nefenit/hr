/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in ANSI C (C89)
 */
 
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <wchar.h>

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
 	int i, j, len, cols;
	struct winsize w;
	wchar_t arg[AMAX];
	
	ioctl(0, TIOCGWINSZ, &w);
	cols = w.ws_col > 0 ? w.ws_col : 80;

	setlocale(LC_ALL, "");
	
	if(argc < 2) {
		while(cols--)
			putwchar(L'#');
		putwchar(L'\n');
	} else {
		for(j = 1; j < argc; ++j) {
			mbstowcs(arg, argv[j], AMAX);
			len = wcslen(arg);
			for(i = 0; i < cols; ++i)
				putwchar(arg[i%len]);
			putwchar(L'\n');
		}
	}
	
 	return 0;
 }
