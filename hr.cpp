/* hr.cpp - writes horizontal bar to terminal
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C++98
 */

#include <iostream>
#include <cstring>
#include <sys/ioctl.h>

using std::cout;
using std::endl;
using std::strlen;

int main(int argc, char *argv[]) {
	int cols;
	struct winsize w;
	
	ioctl(0, TIOCGWINSZ, &w);
	cols = w.ws_col > 0 ? w.ws_col : 80;
	
	if(argc < 2) {
		while(cols--)
			cout.put('#');
		endl(cout);
	} else {
		for(int j = 1; j < argc; ++j) {
			int len = strlen(argv[j]);
			for(int i = 0; i < cols; ++i)
				cout.put(argv[j][i%len]);
			endl(cout);
		}
	}
	
	return 0;
}
