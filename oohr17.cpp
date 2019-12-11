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

class Hr {
	int cols;
	const char *str;

public:
	Hr(int cols = -1, const char * str = "#") : str(str) {
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

	void print(const char * str = nullptr) {
		if(str == nullptr)
			str = this->str;

		auto len = strlen(str);

		for(auto i = 0; i < cols; ++i)
			cout.put(str[i%len]);
		endl(cout);
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
