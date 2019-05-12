#!/usr/bin/env perl6
use v6;

=begin comment
hr.c - writes horizontal bar to standard output
(c) Copyright 2019 Bartosz Mierzynski
=end comment

multi sub MAIN() {
	my $cols = 80;
	put '#' x $cols;
}

multi sub MAIN(*@args) {
	my $cols = 80;
	for @args -> $arg {
		for 0..($cols - 1) {
			print $arg.comb[$_ % $arg.comb.elems];
		}
		put '';
	}
}
