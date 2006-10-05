#!/usr/bin/env perl
#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

use FindBin;

use lib "../perl/src"; # this needs to point to where RNumber.pm and stuff from rnumber/perl/src was
                       # installed.
use lib "$FindBin::RealBin/../src";
use rnumber;

#sub rnumber_cstr {
#  return RNumber::rnumber_cstr ($_[0]);
#}

#   /* rnumbers can be created from integers */
my $a = RNumber::rnumber_create_from_unsigned (0x10);

#    /* rnumbers can be created from strings */
my $b = RNumber::rnumber_create_from_string ("0x102344356553");

#    /* underscores may be placed into strings to increase readability */
my $c = RNumber::rnumber_create_from_string ("0x1023_4435_6553");

#    /* rnumbers can be created with a specified size. */
my $d = RNumber::rnumber_create_from_unsigned_of_size (0, 128); 

#    /* rnumbers can be allowed to grow instead of wrap. */
my $e = RNumber::rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);

#    /*   V0 ("rnumbers use the radix of the ostream used to print them when they are printed");
#         V0 (" a " << a << " (" << hex << a << ")"); */
   
printf ("%s:%d :Use rnumber_cstr and rnumber_cstr_radix to print rnumbers\n",
            __FILE__, __LINE__);

printf ("%s:%d :a %s (%s)\n",  __FILE__, __LINE__, RNumber::rnumber_cstr ($a), 
	RNumber::rnumber_cstr_radix ($a, 16, 0));

printf ("%s:%d b %s %s %s\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr ($b), RNumber::rnumber_cstr_radix ($b, 16, 0), 
	RNumber::rnumber_cstr_radix ($b, 16, 1));

#    /* the underscores in the ctor are not remembered by the number. This gives the
#       same output as b. */
printf ("%s:%d c %s %s %s\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr ($c), RNumber::rnumber_cstr_radix ($c, 16, 0), 
	RNumber::rnumber_cstr_radix ($c, 16, 1));

#    // rnumber_cstr_radix supports radix or 2, 10, and 16
printf ("%s:%d a %s %s %s\n",  __FILE__, __LINE__, RNumber::rnumber_cstr_radix ($a, 10, 1), 
	RNumber::rnumber_cstr_radix ($a, 2, 1), RNumber::rnumber_cstr_radix ($a, 16, 1));

#    // d is a wide number
printf ("%s:%d d %s %s\n", __FILE__, __LINE__, 
	RNumber::rnumber_cstr ($d), RNumber::rnumber_cstr_radix ($d, 16, 1));

#    // set all of the bits in d and e.
# rnumber_set_all will cause a core dump. don't use it.
# RNumber::rnumber_set_all ($d);
$d = $d - 1;
#RNumber::rnumber_set_all ($e);
$e = $e - 1;

printf ("%s:%d d %s e %s\n", __FILE__, __LINE__, RNumber::rnumber_cstr_radix ($d, 16, 1), 
	RNumber::rnumber_cstr_radix($e, 16, 1));

#    // The normal overloaded operators currently always wrap.
#    RNumber * t = rnumber_rn_plus_ui (d, 1);
#    rnumber_destroy (d);
#    d = t;
$d = $d + 1;
#    t = rnumber_rn_plus_ui (e, 1);
#    rnumber_destroy (e);
#    e = t;
$e = $e + 1;

printf ("%s:%d d %s e %s\n", __FILE__, __LINE__, RNumber::rnumber_cstr_radix ($d, 16, 1), 
	RNumber::rnumber_cstr_radix ($e, 16, 1));
   
#    // operator equal does not copy the size for fixed numbers or sizing for either. Howevery, the
#    // assign method does
   
my $f_fixed = RNumber::rnumber_create_from_unsigned_of_size (0, 32);
my $f_dynamic = RNumber::rnumber_create_from_unsigned_of_size_variable_sizing (0, 32);
my $g = RNumber::rnumber_create_from_unsigned_of_size (0, 64);

    printf ("%s:%d f_fixed %d %d f_fdynamic %d %d\n", __FILE__, __LINE__,
            RNumber::rnumber_size ($f_fixed), RNumber::rnumber_sizing ($f_fixed),
            RNumber::rnumber_size ($f_dynamic), RNumber::rnumber_sizing ($f_dynamic));

#    /* the operator= is not available in C. */
# rnumber_assign does not work for perl. Do no use it. It will cause a core dump
$f_fixed = $g;
$f_dynamic = $g;

printf ("%s:%d f_fixed %d %d f_dynamic %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_size ($f_fixed), RNumber::rnumber_sizing ($f_fixed),
	RNumber::rnumber_size ($f_dynamic), RNumber::rnumber_sizing ($f_dynamic));

#    // the add function can be used with the extend parameter to have 'growing' numbers
#    rnumber_destroy (d);
#    rnumber_destroy (e);

$d = RNumber::rnumber_create_from_unsigned_of_size (0, 128);
$e = RNumber::rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);

$d = $d - 1;
$e = $e - 1;

#    rnumber_set_all (d);
#    rnumber_set_all (e);

    printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
            RNumber::rnumber_cstr_radix ($d, 16, 1), RNumber::rnumber_size ($d),
	    RNumber::rnumber_sizing ($d));
    printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
            RNumber::rnumber_cstr_radix ($e, 16, 1), RNumber::rnumber_size ($e), 
	    RNumber::rnumber_sizing ($e));

$d = RNumber::rnumber_rn_add_ext_ui ($d, 1);
$e = RNumber::rnumber_rn_add_ext_ui ($e, 1);

printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($d, 16, 1), RNumber::rnumber_size ($d),
	RNumber::rnumber_sizing ($d));
printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($e, 16, 1), RNumber::rnumber_size ($e), 
	RNumber::rnumber_sizing ($e));
   
#    // assign assigns state, but will not shrink numbers.
$d = RNumber::rnumber_create_from_unsigned_of_size (0, 128);
$e = RNumber::rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);

printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($d, 16, 1), RNumber::rnumber_size ($d),
	RNumber::rnumber_sizing ($d));
printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($e, 16, 1), RNumber::rnumber_size ($e), 
	RNumber::rnumber_sizing ($e));
   
# RNumber::rnumber_copy  doesn't work. It will cause a core dump. Do not use it.
#    // copy copies all state.
$d = RNumber::rnumber_create_from_unsigned_of_size (0, 128);
$e = RNumber::rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);
#    rnumber_destroy (t);

printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($d, 16, 1), RNumber::rnumber_size ($d),
	RNumber::rnumber_sizing ($d));
printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($e, 16, 1), RNumber::rnumber_size ($e), 
	RNumber::rnumber_sizing ($e));
   
$d = $d - 1;
$e = $e - 1;

printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($d, 16, 1), RNumber::rnumber_size ($d),
	RNumber::rnumber_sizing ($d));
printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($e, 16, 1), RNumber::rnumber_size ($e), 
	RNumber::rnumber_sizing ($e));
   
#    // the add function can be used with the extend parameter to have 'growing' numbers
#    // Notice that since 'd' is not dynamically sized, it will wrap. 
$d = RNumber::rnumber_rn_add_ext_ui ($d, 1);
$e = RNumber::rnumber_rn_add_ext_ui ($e, 1);

printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($d, 16, 1), RNumber::rnumber_size ($d),
	RNumber::rnumber_sizing ($d));
printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
	RNumber::rnumber_cstr_radix ($e, 16, 1), RNumber::rnumber_size ($e), 
	RNumber::rnumber_sizing ($e));
   
