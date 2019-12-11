#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019 Bartosz Mierzynski
'''

__author__    = "Bartosz Mierzynski"
__copyright__ = "(c) Copyright 2019 Bartosz Mierzynski"

def main():
        from sys import argv, stdout
        from os  import getenv 
        cols = getenv("COLUMNS")
        if cols == None or cols == "":
                try:
                        from os import get_terminal_size
                        cols = get_terminal_size().columns
                except OSError:
                        cols = 80
        else:
                cols = int(cols)
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
    from sys import exit
    exit(main())
