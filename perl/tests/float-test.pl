#!/usr/bin/env perl

use strict;
use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
use rnumber;

sub predicates {
  my $x = $_[0];
  my $y = rnumberp($_[1]);
  print 
      "rnumberp(". $_[0] . ")=" . rnumberp($_[1]) .
      " integerp(". $_[0]. ")=" . integerp($_[1]) . 
      " numbericp(".$_[0]. ")=" . numericp($_[1]) . 
      " stringp(". $_[0]. ")="  . stringp($_[1]) . 
      "\n";
}

# See what happens with floats.
predicates ("integer 10 ", 10);
predicates ("float 10.5 ", 10.5);
predicates ("rn 10      ", rn_ctor("10"));

# This should work b/c 10.00 can be cast to an integer w/o losing precision.
print rn_cstr(rn_plus ( rn_ctor ("10"), 10.00),10) . "\n";
