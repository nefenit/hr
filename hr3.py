#!/usr/bin/python3
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019 Bartosz Mierzyński
'''

from sys import argv, exit, stdout
from os import get_terminal_size

__author__    = "Bartosz Mierzyński"
__copyright__ = "(c) Copyright 2019 Bartosz Mierzyński"

def main():
	try:
		cols = get_terminal_size().columns
	except OSError:
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
