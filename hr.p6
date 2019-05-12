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
		my @chars = $arg.comb;
		my $len = @chars.elems;
		loop (my $i = 0; $i < $cols; ++$i) {
			print @chars[$i % $len];
		}
		put '';
	}
}
