#!/usr/local/bin/perl -w

use strict;
#use lib '/local1/work/lib/rnumber';
#use lib '/cad/tools/rnumber/1.11.2/lib/rnumber';
use lib '../src';
use rnumber;

print "create a\n";
predicates ("10", 10);
my $a = rn_ctor(10,64);
print "</a>\n";
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
