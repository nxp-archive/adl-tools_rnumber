#!/usr/bin/env perl

##  -w              enable many useful warnings (RECOMMENDED)
##  -S              look for programfile using PATH environment variable

use strict;

my $srcdir = (exists $ENV{srcdir}) ? $ENV{srcdir} : ".";

system ("$srcdir/rnumber-example.pl > output");
if (system ("diff $srcdir/rnumber-example.output output")) {
  die "Failed diff.";
}

0;
