# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -ansi -O2 -g

all:
	@$(CC) $(CFLAGS) hr.c -o hr

.PHONY: clean

clean:
	@rm hr
