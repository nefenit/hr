/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in ANSI C (C89)
 */
 
 #include <stdio.h>
 #include <string.h>
 #include <sys/ioctl.h>
 
 int main(int argc, char *argv[]) {
 	int i, j, len, cols;
	struct winsize w;
	
	ioctl(0, TIOCGWINSZ, &w);
	cols = w.ws_col > 0 ? w.ws_col : 80;
	
	if(argc < 2) {
		while(cols--)
			putchar('#');
		putchar('\n');
	} else {
		for(j = 1; j < argc; j++) {
			len = strlen(argv[j]);
			for(i = 0; i < cols; i++)
				putchar(argv[j][i%len]);
			putchar('\n');
		}
	}
	
 	return 0;
 }
