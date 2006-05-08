#!/usr/bin/env perl

use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
use rnumber;

print RNumber::rnumber_cstr(RNumber::rnumber_create_from_unsigned(10)) . "\n";
