/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C99
 */
 
 #include <stdio.h>
 #include <string.h>
 #include <sys/ioctl.h>
 
 int main(int argc, char *argv[]) {
	struct winsize w;
	
	ioctl(0, TIOCGWINSZ, &w);
	int cols = w.ws_col > 0 ? w.ws_col : 80;
	
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
