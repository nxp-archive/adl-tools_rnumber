#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#


use strict;
#use lib '/local1/work/lib/rnumber';
#use lib '/cad/tools/rnumber/1.11.2/lib/rnumber';
use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
use rnumber;

# without memory management in rnumber, this quickly takes over
# 50M of memory
for my $i (0..10000) {
  rn_plus(rn_ctor ("10"), rn_ctor(5));
}
