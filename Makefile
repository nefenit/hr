# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -ansi

all:
	@$(CC) $(CFLAGS) hr.c -o hr

clean:
	@rm hr
