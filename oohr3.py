#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
 hr - horizontal bar for your terminal
 (c) Copyright 2019 Bartosz Mierzynski
'''

__author__    = "Bartosz Mierzynski"
__copyright__ = "(c) Copyright 2019 Bartosz Mierzynski"

class Hr:
    def __init__(self, cols = -1, string = "#"):
        from os import getenv
        self.string = string
        if(cols < 0):
            self.cols = getenv("COLUMNS")
            if self.cols == None or self.cols == "":
                from os import get_terminal_size
                try:
                    self.cols = get_terminal_size().columns
                except OSError:
                    self.cols = 80
            else:
                self.cols = int(cols)
        else:
            self.cols = cols

    def print(self, string = None):
        from sys import stdout
        if string == None:
            string = self.string

        length = len(string)
        for i in range(0, self.cols):
            stdout.write(string[i%length])
        stdout.write('\n');

def main():
    from sys import argv
    hr = Hr()
    if len(argv) < 2:
        hr.print()
    else:
        for i in range(1, len(argv)):
            hr.print(argv[i])
    return 0

if __name__ == "__main__":
    from sys import exit
    exit(main())
