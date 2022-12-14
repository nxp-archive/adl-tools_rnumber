#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#


use strict;
use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
use rnumber;

#with memory management this stays right at 48M.
#without memory management quickly (13 sec) reached 50M
#by 1 minute was 58M

#changed index to only go to 100000
#mm memory usage < 10M
#!mm memory usage 12M
for my $i (0..100000) {
  rn_ctor ("10");
}
