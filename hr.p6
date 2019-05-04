#!/usr/bin/env perl6
=begin comment
hr.c - writes horizontal bar to standard output
(c) Copyright 2019 Bartosz Mierzynski
Written in Perl 6
=end comment

my $cols = 80;

if @*ARGS.elems == 0 {
	while $cols-- {
		print '#';
	}
	put '';
} else {
	for @*ARGS -> $arg {
		my @chars = $arg.comb;
		my $len = @chars.elems;
		loop (my $i = 0; $i < $cols; ++$i) {
			print @chars[$i % $len];
		}
		put '';
	}  
}
