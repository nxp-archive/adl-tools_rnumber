#!/usr/local/bin/perl -w

use strict;
#use lib '/local1/work/lib/rnumber';
#use lib '/cad/tools/rnumber/1.11.2/lib/rnumber';
use lib '../src';
use rnumber;

#with memory management this stays right at 48M.
#without memory management quickly (13 sec) reached 50M
#by 1 minute was 58M

#changed index to only go to 100000
#mm memory usage < 10M
#!mm memory usage 12M
for my $i (0..100000) {
  rn_ctor ("10");
}
