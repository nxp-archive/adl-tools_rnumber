#!/usr/local/bin/perl -w

use strict;
#use lib '/local1/work/lib/rnumber';
#use lib '/cad/tools/rnumber/1.10.4/lib/rnumber';
use lib '../src';
use rnumber;

my $a = rn_ctor(10,64);
my $b = 0xcd340000;
my $c = "3";
my $foo = "0xcd340000";

print "b:  ", $b, "\n";
#call predicates with name, variable
sub predicates {
  print 
      "rnumberp(". $_[0] . ")=" . rnumberp($_[1]) . 
      " integerp(". $_[0]. ")=" . integerp($_[1]) . 
      " numbericp(".$_[0]. ")=" . numericp($_[1]) . 
      " stringp(". $_[0]. ")="  . stringp($_[1]) . 
      "\n";
}
predicates("a", $a);
predicates("b", $b);
predicates("c", $c);
predicates("foo", $foo);

$c = rn_plus($a,$b);

print "a:  ", rn_cstr($a,10), " ", rn_cstr($a,16), "\n";
printf "b:  $b 0x%x\n", $b;
predicates("c",$c);
print "c:  ", rn_cstr($c,16), "\n";
