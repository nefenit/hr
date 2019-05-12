#!/usr/bin/env perl6
use v6;

=begin comment
hr.c - writes horizontal bar to standard output
(c) Copyright 2019 Bartosz Mierzynski
=end comment

unit sub MAIN(*@args) {
	my $cols = %*ENV<COLUMNS> || 80;
	if @args == 0 {
		put '#' x $cols;
	} else {
		for @args -> $arg {
			for 0..($cols - 1) {
				print $arg.comb[$_ % $arg.comb.elems];
			}
			put '';
		}
	}
}
