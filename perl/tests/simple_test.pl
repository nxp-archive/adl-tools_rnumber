#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

use FindBin;
use lib "../src";
use lib "$FindBin::RealBin/../src";
use rnumber;

print RNumber::rnumber_cstr(RNumber::rnumber_create_from_unsigned(10)) . "\n";
