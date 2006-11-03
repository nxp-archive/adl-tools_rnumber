: # -*- perl -*-
eval 'exec perl -w -S $0 ${1+"$@"}'
    if 0;
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

use strict;

use example;

print example::fact(4) . "\n";
