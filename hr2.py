#!/usr/bin/env python2
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019-2020 Bartosz Mierzynski
'''

__author__    = "Bartosz Mierzynski"
__copyright__ = "(c) Copyright 2019-2020 Bartosz Mierzynski"

def get_columns(): 
    from platform import system
    from struct   import pack, unpack
    from os       import getenv
    n = getenv("COLUMNS")
    if n == None or n == "":
        if system() == 'Windows':
            try:
                from ctypes     import windll, create_string_buffer
                from subprocess import STD_OUTPUT_HANDLE
                h    = windll.kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
                csbi = create_string_buffer(22)
                res  = windll.kernel32.GetConsoleScreenBufferInfo(h, csbi)
                if res:
                    (bufx, bufy, curx, cury, wattr,
                    left, top, right, bottom,
                    maxx, maxy) = struct.unpack("hhhhHhhhhhh", csbi.raw)
                    n = right  - left + 1
                    rows = bottom - top  + 1
            except:
                pass
        else:
            try:
                from fcntl   import ioctl
                from termios import TIOCGWINSZ
                rows, n, rowspx, colspx \
                = unpack('HHHH', ioctl(0, TIOCGWINSZ, pack('HHHH', 0, 0, 0, 0)))
            except:
                pass

        if not n:
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
