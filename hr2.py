#!/usr/bin/env python2
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019 Bartosz Mierzynski
'''

from sys      import argv, exit, stdout
from struct   import pack, unpack
from platform import system

__author__    = "Bartosz Mierzynski"
__copyright__ = "(c) Copyright 2019 Bartosz Mierzynski"

def main():
        if system() == 'Windows':
            try:
                from ctypes import windll, create_string_buffer
                h    = windll.kernel32.GetStdHandle(-12)
                csbi = create_string_buffer(22)
                res  = windll.kernel32.GetConsoleScreenBufferInfo(h, csbi)
                if res:
                    (bufx, bufy, curx, cury, wattr,
                    left, top, right, bottom,
                    maxx, maxy) = struct.unpack("hhhhHhhhhhh", csbi.raw)
                    cols = right  - left + 1
                    rows = bottom - top  + 1
            except:
                pass
        else:
            try:
                from fcntl   import ioctl
                from termios import TIOCGWINSZ
	        rows, cols, rowspx, colspx \
	        = unpack('HHHH', ioctl(0, TIOCGWINSZ, pack('HHHH', 0, 0, 0, 0)))
            except:
                pass

        if cols == 0:
            cols = 80

	if len(argv) < 2:
		while cols:
			stdout.write('#');
			cols -= 1
		stdout.write('\n');
	else:
		for j in range(1, len(argv)):
			length = len(argv[j])
			for i in range(0, cols):
				stdout.write(argv[j][i%length])
			stdout.write('\n');
	return 0

if __name__ == "__main__":
	exit(main())
