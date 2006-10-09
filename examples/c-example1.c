//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

// To compile this file use the command:
//
// gcc -o c-example1 `rnumber-config --cflags` c-example1.c `rnumber-config --libs` -lstdc++
//
// rnumber_config must be in your path and rnumber must be installed

// The C++ tracing utilities are not available to C. 
// #include "rnumber/trace.h"

// You need to include the rnumber header file to use rnumber.
#include "rnumber/C-RNumber.h"

typedef struct RNumber RNumber;

int main () {
  /* rnumbers can be created from integers */
   RNumber * a = rnumber_create_from_unsigned (0x10);

   /* rnumbers can be created from strings */
   RNumber * b = rnumber_create_from_string ("0x102344356553");

   /* underscores may be placed into strings to increase readability */
   RNumber * c = rnumber_create_from_string ("0x1023_4435_6553");

   /* rnumbers can be created with a specified size. */
   RNumber * d = rnumber_create_from_unsigned_of_size (0, 128); 

   /* rnumbers can be allowed to grow instead of wrap. */
   RNumber * e = rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);

   /*   V0 ("rnumbers use the radix of the ostream used to print them when they are printed");
        V0 (" a " << a << " (" << hex << a << ")"); */
   
   printf ("%s:%d :Use rnumber_cstr and rnumber_cstr_radix to print rnumbers\n",
           __FILE__, __LINE__);

   printf ("%s:%d :a %s (%s)\n",  __FILE__, __LINE__, rnumber_cstr (a), rnumber_cstr_radix (a, 16, 0));

   printf ("%s:%d b %s %s %s\n", __FILE__, __LINE__,
           rnumber_cstr (b), rnumber_cstr_radix (b, 16, 0), rnumber_cstr_radix (b, 16, 1));

   /* the underscores in the ctor are not remembered by the number. This gives the
      same output as b. */
   printf ("%s:%d c %s %s %s\n", __FILE__, __LINE__,
           rnumber_cstr (c), rnumber_cstr_radix (c, 16, 0), rnumber_cstr_radix (c, 16, 1));

   // rnumber_cstr_radix supports radix or 2, 10, and 16
   printf ("%s:%d a %s %s %s\n",  __FILE__, __LINE__, rnumber_cstr_radix (a, 10, 1), 
           rnumber_cstr_radix (a, 2, 1), rnumber_cstr_radix (a, 16, 1));

   // d is a wide number
   printf ("%s:%d d %s %s\n", __FILE__, __LINE__, rnumber_cstr (d), rnumber_cstr_radix (d, 16, 1));

   // set all of the bits in d and e.
   rnumber_set_all (d);
   rnumber_set_all (e);

   printf ("%s:%d d %s e %s\n", __FILE__, __LINE__, rnumber_cstr_radix (d, 16, 1), 
           rnumber_cstr_radix(e, 16, 1));

   // The normal overloaded operators currently always wrap.
   RNumber * t = rnumber_rn_plus_ui (d, 1);
   rnumber_destroy (d);
   d = t;
   t = rnumber_rn_plus_ui (e, 1);
   rnumber_destroy (e);
   e = t;

   printf ("%s:%d d %s e %s\n", __FILE__, __LINE__, rnumber_cstr_radix (d, 16, 1), 
           rnumber_cstr_radix (e, 16, 1));
   
   // operator equal does not copy the size for fixed numbers or sizing for either. Howevery, the
   // assign method does
   
   RNumber * f_fixed = rnumber_create_from_unsigned_of_size (0, 32);
   RNumber * f_dynamic = rnumber_create_from_unsigned_of_size_variable_sizing (0, 32);
   RNumber * g = rnumber_create_from_unsigned_of_size (0, 64);

   printf ("%s:%d f_fixed %d %d f_fdynamic %d %d\n", __FILE__, __LINE__,
           rnumber_size (f_fixed), rnumber_sizing (f_fixed),
           rnumber_size (f_dynamic), rnumber_sizing (f_dynamic));

   /* the operator= is not available in C. */
   f_fixed = rnumber_assign (f_fixed, g);
   f_dynamic = rnumber_assign (f_dynamic, g);

   printf ("%s:%d f_fixed %d %d f_dynamic %d %d\n", __FILE__, __LINE__,
           rnumber_size (f_fixed), rnumber_sizing (f_fixed),
           rnumber_size (f_dynamic), rnumber_sizing (f_dynamic));

   // the add function can be used with the extend parameter to have 'growing' numbers
   rnumber_destroy (d);
   rnumber_destroy (e);

   d = rnumber_create_from_unsigned_of_size (0, 128);
   e = rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);

   rnumber_set_all (d);
   rnumber_set_all (e);

   printf ("%s:%d d %s %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (d, 16, 1), rnumber_size (d), rnumber_sizing (d));
   printf ("%s:%d e %s %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (e, 16, 1), rnumber_size (e), rnumber_sizing (e));

   d = rnumber_assign (d, rnumber_rn_add_ext_ui (d, 1));
   e = rnumber_assign (e, rnumber_rn_add_ext_ui (e, 1));

   printf ("%s:%d d (%s, %d %d\n", __FILE__, __LINE__, 
     rnumber_cstr_radix (d, 16, 1), rnumber_size (d), rnumber_sizing (d));
   printf ("%s:%d e (%s, %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (e, 16, 1), rnumber_size (e), rnumber_sizing (e));

   
   // assign assigns state, but will not shrink numbers.
   t = rnumber_create_from_unsigned_of_size (0, 128);
   d = rnumber_assign (d, t);
   rnumber_destroy (t);
   t = rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);
   e = rnumber_assign (e, t);
   rnumber_destroy (t);

   printf ("%s:%d d (%s, %d %d\n", __FILE__, __LINE__, 
           rnumber_cstr_radix (d, 16, 1), rnumber_size (d), rnumber_sizing (d));
   printf ("%s:%d e (%s, %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (e, 16, 1), rnumber_size (e), rnumber_sizing (e));

   // copy copies all state
   t = rnumber_create_from_unsigned_of_size (0, 128);
   d = rnumber_copy (d, t);
   rnumber_destroy (t);
   t = rnumber_create_from_unsigned_of_size_variable_sizing (0, 128);
   e = rnumber_copy (e, t);
   rnumber_destroy (t);

   printf ("%s:%d d (%s, %d %d\n", __FILE__, __LINE__, 
           rnumber_cstr_radix (d, 16, 1), rnumber_size (d), rnumber_sizing (d));
   printf ("%s:%d e (%s, %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (e, 16, 1), rnumber_size (e), rnumber_sizing (e));

   rnumber_set_all (d);
   rnumber_set_all (e);

   printf ("%s:%d d (%s, %d %d\n", __FILE__, __LINE__, 
           rnumber_cstr_radix (d, 16, 1), rnumber_size (d), rnumber_sizing (d));
   printf ("this number should have variable sizing set\n");
   printf ("%s:%d e (%s, %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (e, 16, 1), rnumber_size (e), rnumber_sizing (e));

   // the add function can be used with the extend parameter to have 'growing' numbers
   // Notice that since 'd' is not dynamically sized, it will wrap. 
   d = rnumber_assign (d, rnumber_rn_add_ext_ui (d, 1));
   e = rnumber_assign (e, rnumber_rn_add_ext_ui (e, 1));

   printf ("%s:%d d (%s, %d %d\n", __FILE__, __LINE__, 
           rnumber_cstr_radix (d, 16, 1), rnumber_size (d), rnumber_sizing (d));
   printf ("%s:%d e (%s, %d %d\n", __FILE__, __LINE__,
           rnumber_cstr_radix (e, 16, 1), rnumber_size (e), rnumber_sizing (e));

}
