#!/usr/bin/env python2
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019 Bartosz Mierzynski
'''

from sys import argv, exit, stdout
from fcntl import ioctl
from struct import pack, unpack
from termios import TIOCGWINSZ

__author__    = "Bartosz Mierzynski"
__copyright__ = "(c) Copyright 2019 Bartosz Mierzynski"

def main():
	rows, cols, rowsp, colsp = unpack('HHHH', ioctl(0, TIOCGWINSZ, pack('HHHH', 0, 0, 0, 0)))
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
