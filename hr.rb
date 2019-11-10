#!/usr/bin/env ruby
=begin
/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in Ruby
=end
require 'io/console'
require 'pp'

cols = ENV["COLUMNS"]
if cols.nil? or cols == ""
  rows, cols = IO.console.winsize	
else
  cols = cols.to_i
end

if ARGV.length == 0
  while cols > 0 do
    print "#"
    cols -= 1
  end
  puts;
else
  for arg in ARGV
    for i in 0..cols-1
      print "#{arg[i%arg.length]}"
    end
    puts
  end
end
