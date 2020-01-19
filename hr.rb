#!/usr/bin/env ruby
=begin
/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2019-2020 Bartosz Mierzynski
=end

def get_columns
  require 'io/console'
  n = ENV["COLUMNS"]
  if n.nil? or n == ""
    rows, n = IO.console.winsize	
  else
    n = n.to_i
  end
  return n
end

def hr1 n = 80
  while n > 0 do
    print "#"
    n -= 1
  end
  puts
end

def hr2 n = 80, s = "#"
  require 'pp'
  for i in 0..n-1
    print "#{s[i % s.length]}"
  end
  puts
end

def main
  n = get_columns
  case ARGV.length
    when 0
      hr1 n
    else
      for arg in ARGV
        hr2 n, arg
      end
  end
  #exit 0
end

if __FILE__ == $0
  main
end
