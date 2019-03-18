# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -ansi -O2

all:
	@$(CC) $(CFLAGS) hr.c -o hr

clean:
	@rm hr
