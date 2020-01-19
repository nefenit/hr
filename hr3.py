#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019-2020 Bartosz Mierzynski
'''

__author__    = "Bartosz Mierzynski"
__copyright__ = "(c) Copyright 2019-2020 Bartosz Mierzynski"

def get_columns():
    from os import getenv 
    n = getenv("COLUMNS")
    if n == None or n == "":
        try:
            from os import get_terminal_size
            n = get_terminal_size().columns
        except OSError:
            n = 80
    else:
        n = int(n)
    return n

def hr1(n = 80):
    from sys import stdout
    while n:
        stdout.write('#');
        n -= 1
    stdout.write('\n');

def hr2(n = 80, s = "#"):
    from sys import stdout
    length = len(s)
    for i in range(0, n):
        stdout.write(s[i % length])
    stdout.write('\n');

def main():
    from sys import argv
    argc = len(argv)
    n    = get_columns()
    if argc < 2:
        hr1(n)
    else:
        for i in range(1, argc):
            hr2(n, argv[i])
    #from sys import exit
    #exit(0)

if __name__ == "__main__":
    main()
