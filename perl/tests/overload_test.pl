#!/usr/bin/env perl -w

use strict;
use lib "../src";
use rnumber;

my $an_rnumber = 0x100;
my $another_rnumber = 0x35;
my $an_integer = 10;

my @operations = ('+', '-', '%', '*', '/', '&', '|', '==', '!=', '<', '<=', '>', 
		  '>=', '<<', '>>');

sub predicates {
  print 
      "rnumberp(". $_[0] . ")=" . rnumberp($_[1]) . 
      " integerp(". $_[0]. ")=" . integerp($_[1]) . 
      " numbericp(".$_[0]. ")=" . numericp($_[1]) . 
      " stringp(". $_[0]. ")="  . stringp($_[1]) . 
      "\n";
}

foreach my $i (@operations) {
  printf "0x%x $i 0x%x = ", $an_rnumber, $another_rnumber;
  my $q = eval ("rn_ctor($an_rnumber) $i rn_ctor($another_rnumber)");
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
  printf "0x%x $i 0x%x = ", $an_rnumber, $an_integer;
  my $q = eval ("rn_ctor($an_rnumber) $i $an_integer");
  if (rnumberp($q)) {
    print rn_cstr($q, 16, 1), "\n";
  } else {
    print $q, "\n";
  }
}
foreach my $i (@operations) {
  printf "0x%x $i 0x%x = ", $an_integer, $another_rnumber;
  my $q = eval ("$an_integer $i rn_ctor($another_rnumber)");
  if (rnumberp($q)) {
    print rn_cstr($q, 16, 1), "\n";
  } else {
    print $q, "\n";
  }
}


