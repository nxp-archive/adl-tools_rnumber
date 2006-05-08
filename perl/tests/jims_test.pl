#!/usr/bin/env perl

# you can use this code to find rnumber in client programs
# BEGIN {
#   $lib_dir = `rnumber-config --perl-libs`; 
#   $lib_dir =~ s/\s+//g;
#   unshift @INC, $lib_dir;
# }
# use rnumber;

use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
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

print "31:\n";
$c = rn_plus($a,$b);
print "33:\n";
print "b:  ", $b, "\n";
print "35:\n";

print "a:  ", rn_cstr($a,10), " ", rn_cstr($a,16), "\n";
print "38:\n";
printf "b:  $b 0x%x\n", $b;
print "40:\n";
predicates("c",$c);
print "42:\n";
print "c:  ", rn_cstr($c,16), "\n";
print "44:\n";
