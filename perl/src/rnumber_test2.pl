#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#


use lib '.';
use FindBin;
use lib $FindBin::RealBin;
use rnumber;

print RNumber::rnumber_cstr(RNumber::rnumber_create_from_unsigned(10)) . "\n";
RNumber::random_create();
RNumber::random_init();
print RNumber::random_get_integer(), "\n";

my $a = RNumber::rnumber_create_from_unsigned(10);
my $b = 10;

print "ref a '", ref($a), "'\n";
print "ref b '", ref($b), "'\n";

my $string = "1234";
my $integer = 10;
my $rnumber = RNumber::rnumber_create_from_unsigned(10);

print "string  stringp ", stringp($string), " integerp ", integerp($string), " rnumberp ", 
    rnumberp($string), "\n";
print "integer stringp ", stringp($integer), " integerp ", integerp($integer), " rnumberp ",
    rnumberp($integer), "\n";
print "rnumber stringp ", stringp($rnumber), " integerp ", integerp($rnumber), " rnumberp ", 
    rnumberp($rnumber), "\n";
