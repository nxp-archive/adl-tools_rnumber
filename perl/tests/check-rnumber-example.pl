#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

##  -w              enable many useful warnings (RECOMMENDED)
##  -S              look for programfile using PATH environment variable

use strict;

my $srcdir = (exists $ENV{srcdir}) ? $ENV{srcdir} : ".";

system ("$srcdir/rnumber-example.pl > output");
if (system ("diff $srcdir/rnumber-example.output output")) {
  die "Failed diff.";
}

0;
