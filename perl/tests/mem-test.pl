#!/usr/local/bin/perl -w

use strict;
#use lib '/local1/work/lib/rnumber';
#use lib '/cad/tools/rnumber/1.11.2/lib/rnumber';
use lib '../src';
use rnumber;

# without memory management in rnumber, this quickly takes over
# 50M of memory
for my $i (0..100000) {
  rn_plus(rn_ctor ("10"), rn_ctor(5));
}
