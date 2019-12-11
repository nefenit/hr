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

class Hr {
	int cols;
	wchar_t str[AMAX];

public:
	Hr(int cols = -1, const char * str = "#") {
		setlocale(LC_ALL, "");
		mbstowcs(this->str, str, AMAX);
		if((this->cols = cols) == -1)
			if((this->cols = Hr::get_environ_cols()) == -1)	
				if((this->cols = Hr::get_system_cols()) == -1)
					this->cols = 80;
	}

	static int get_environ_cols(void) {
		const char *columns;
		if((columns = getenv("COLUMNS")) && (strlen(columns)))
			return atoi(columns);
		else
			return -1;
		
	}

	static int get_system_cols(void) {
#ifdef __WIN32__
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		
		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return csbi.dwSize.X;
		else
			return -1;
#else
		winsize w;
		
		ioctl(0, TIOCGWINSZ, &w);
		return w.ws_col >= 0 ? w.ws_col : -1;
#endif /* __WIN32__ */
	}

	void print(const char * str = NULL) {
		if(str != NULL)
			mbstowcs(this->str, str, AMAX);

		auto len = wcslen(this->str);

		for(auto i = 0; i < cols; ++i)
			wcout.put(this->str[i%len]);
		endl(wcout);
	}
};

int main(int argc, char *argv[]) {
	Hr hr;

	if(argc < 2)
		hr.print();
	else
		for(auto i = 1; i < argc; ++i)
			hr.print(argv[i]);
}
