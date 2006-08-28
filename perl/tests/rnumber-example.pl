#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

##  -w              enable many useful warnings (RECOMMENDED)
##  -S              look for programfile using PATH environment variable

use strict;
use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
use rnumber;

sub predicates {
  print 
      "rnumberp(". $_[0] . ")=" . rnumberp($_[1]) . 
      " integerp(". $_[0]. ")=" . integerp($_[1]) . 
      " numbericp(".$_[0]. ")=" . numericp($_[1]) . 
      " stringp(". $_[0]. ")="  . stringp($_[1]) . 
      "\n";
}
my $a = rn_ctor(0x10);
print "0) a is rnumberp " . rnumberp($a) . "\n";

print "1) a is ". $a ."\n";

my $b = rn_ctor("0xdeadb0f0babe");
print "2) b is " . $b ."\n";

my $c = $a + $b;
#this one works
print "3) a + b is " . $c . "\n";

#this one doens't work
print "doesn't work, precedence problem \n";
print "4) a + b is " . $a + $b . "\n";

#try this
print "works\n";
print "5) a + b is " . ($a + $b) . "\n";

my $an_rnumber = rn_ctor(0x100);
my $another_rnumber = rn_ctor(0x35);
my $an_integer = 10;

my @operations = ('+', '-', '%', '*', '/', '&', '|', '==', '!=', '<', '<=', '>', 
                  '>=', '<<', '>>');

foreach my $i (@operations) {
  if ($i eq '%') {
    print "0x$an_rnumber \% 0x$another_rnumber = ";
  } else {
    print "0x$an_rnumber $i 0x$another_rnumber = ";
  }
  my $q = eval ("rn_ctor(0x$an_rnumber) $i rn_ctor(0x$another_rnumber)");
  if (rnumberp($q)) {
    print rn_cstr($q, 16, 1), "\n";
  } else {
    print $q, "\n";
  }
}
print rn_ctor("10") + 10, "\n";
my $i = '+';
print eval("rn_ctor(10) $i 10"),"\n";

print "hardcoded 10<<35 ", rn_ls(rn_ctor(10,64),rn_ctor(35)), "\n";
print "hardcoded 10<<35 ", eval ("10<<rn_ctor(35)") , "\n";

foreach my $i (@operations) {
  if ($i eq '%') {
    print "0x$an_rnumber \% $an_integer = ";
  } else {
    print "0x$an_rnumber $i $an_integer = ";
  }
  my $q = eval ("rn_ctor(0x$an_rnumber) $i $an_integer");
  if (rnumberp($q)) {
    print rn_cstr($q, 16, 1), "\n";
  } else {
    print $q, "\n";
  }
}
foreach my $i (@operations) {
  print "operation $i\n";
  print "$an_integer $i 0x$another_rnumber = ";
  my $q = eval ("$an_integer $i rn_ctor(0x$another_rnumber)");
  if (rnumberp($q)) {
    print rn_cstr($q, 16, 1), "\n";
  } else {
    print $q, "\n";
  }
}
