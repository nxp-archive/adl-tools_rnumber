#!/usr/local/bin/perl -w
##!/usr/local/bin/perl -w

use strict;
#use lib '/local1/work/lib/rnumber';
#use lib '/cad/tools/rnumber/1.11.2/lib/rnumber';
use lib '../src';
use rnumber;

sub predicates {
  print 
      "rnumberp(". $_[0] . ")=" . rnumberp($_[1]) . 
      " integerp(". $_[0]. ")=" . integerp($_[1]) . 
      " numbericp(".$_[0]. ")=" . numericp($_[1]) . 
      " stringp(". $_[0]. ")="  . stringp($_[1]) . 
      "\n";
}

#see what happens with floats.
predicates ("integer 10", 10);
predicates ("float 10.5", 10.5);

print rn_cstr(rn_plus ( rn_ctor ("10"), 10.54),10) . "\n";
