# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -ansi -O2 -g

.PHONY: all
all:
	@$(CC) hr89w.c -o hr $(CFLAGS) 

.PHONY: clean
clean:
	@rm hr
