/* hr.cpp - writes horizontal bar to terminal
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C++98
 */

#include <iostream>
#include <cstring>
#include <sys/ioctl.h>

using std::cout, std::endl, std::strlen;

int main(int argc, char *argv[]) {
	winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	auto cols = w.ws_col > 0 ? w.ws_col : 80;
	
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
