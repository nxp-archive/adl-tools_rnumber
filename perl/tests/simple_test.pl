#!/usr/local/bin/perl -w
##!/usr/bin/env perl -w

use lib '../src/';
use rnumber;

print RNumber::rnumber_cstr(RNumber::rnumber_create_from_unsigned(10)) . "\n";
