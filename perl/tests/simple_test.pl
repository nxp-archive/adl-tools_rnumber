#!/usr/bin/env perl -w

use lib '../src/';
use pl_rnumber;

print pl_rnumber::rnumber_cstr(pl_rnumber::rnumber_create_from_unsigned(10)) . "\n";
