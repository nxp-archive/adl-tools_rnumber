#!/usr/bin/env perl -w

use lib '.';
use rnumber;

print pl_rnumber::rnumber_cstr(pl_rnumber::rnumber_create_from_unsigned(10)) . "\n";
pl_rnumber::random_create();
pl_rnumber::random_init();
print pl_rnumber::random_get_integer(), "\n";

my $a = pl_rnumber::rnumber_create_from_unsigned(10);
my $b = 10;

print "ref a '", ref($a), "'\n";
print "ref b '", ref($b), "'\n";

my $string = "1234";
my $integer = 10;
my $rnumber = pl_rnumber::rnumber_create_from_unsigned(10);

print "string  stringp ", stringp($string), " integerp ", integerp($string), " rnumberp ", 
    rnumberp($string), "\n";
print "integer stringp ", stringp($integer), " integerp ", integerp($integer), " rnumberp ",
    rnumberp($integer), "\n";
print "rnumber stringp ", stringp($rnumber), " integerp ", integerp($rnumber), " rnumberp ", 
    rnumberp($rnumber), "\n";
