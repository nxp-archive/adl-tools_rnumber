//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

// To compile this file use the command:
//
// g++ -o example1 `rnumber-config --cflags` example1.C `rnumber-config --libs`
//
// rnumber_config must be in your path and rnumber must be installed

#include <iostream>
#include <iomanip>

// You can use the tracing utilities to print with filename and linenumber
#include "rnumber/trace.h"
// You need to include the rnumber header file to use rnumber.
#include "rnumber/RNumber.h"


// RNumber is contained within the RNumber namespace. You need to either qualify types
// or use using to include the namespace. Most people don't recommend use of using within
// header files.
using namespace rnumber;
using namespace std;

int main () {
   RNumber a (0x10); // rnumbers can be created from integers
   RNumber b ("0x102344356553"); // rnumbers can be created from strings
   RNumber c ("0x1023_4435_6553"); // underscores may be placed into strings to increase readability
   RNumber d (0, 128); // rnumbers can be created with a specified size.
   RNumber e (0, 128, RNumber::dynamic); // rnumbers can be allowed to grow instead of wrap.

   V0 ("rnumbers use the radix of the ostream used to print them when they are printed");
   V0 (" a " << a << " (" << hex << a << ")");

   // you can use showbase to include the 0x
   V0 (" b " << b << hex << " " << b << " " << showbase << b << noshowbase);

   // the underscores in the ctor are not remembered by the number. This gives the
   // same output as b.
   V0 (" c " << c << hex << " " << c << " " << showbase << c);

   // you can print base 2 indirectly
   V0 (" a " << a << " " << a.str (RNumber::rprefix | RNumber::rbin) << " " << hex << a);
   
   // d is a wide number
   V0 (" d " << hex << d);

   // set all of the bits in d and e.
   d.setAll(); 
   e.setAll();
   V0 (" d " << hex << d << " e " << e);
   // The normal overloaded operators currently always wrap.
   d = d + 1;
   e = e + 1;
   V0 (" d " << hex << d << " e " << e);
   
   // operator equal does not copy the size for fixed numbers or
   // sizing for either. Howevery, the assign method does
   RNumber f_fixed (0, 32);
   RNumber f_dynamic (0, 32, RNumber::dynamic);
   RNumber g (0, 64);

   V0 (" f_fixed " << f_fixed.size () << " " << f_fixed.sizing () << "  " 
       " f_dynamic " << f_dynamic.size () << " " << f_dynamic.sizing ()); 
   f_fixed = g;
   f_dynamic = g;
   V0 (" f_fixed " << f_fixed.size () << " " << f_fixed.sizing () << "  " 
       " f_dynamic " << f_dynamic.size () << " " << f_dynamic.sizing ()); 
   f_fixed.assign (g);
   f_dynamic.assign (g);
   V0 (" f_fixed " << f_fixed.size () << " " << f_fixed.sizing () << "  " 
       " f_dynamic " << f_dynamic.size () << " " << f_dynamic.sizing ()); 

   // the add function can be used with the extend parameter to have 'growing' numbers
   d.assign (RNumber (0, 128));
   e.assign (RNumber (0, 128, RNumber::dynamic));

   d.setAll ();
   e.setAll ();

   V0 (" d (" << hex << d << ", " << dec << d.size() << ", " << d.sizing ());
   V0 (" e (" << hex << e << ", " << dec << e.size() << ", " << e.sizing ());

   bool extend = true;
   d.assign (add (d, 1, extend));
   e.assign (add (e, 1, extend));

   V0 (" d (" << hex << d << ", " << dec << d.size() << ", " << d.sizing ());
   V0 (" e (" << hex << e << ", " << dec << e.size() << ", " << e.sizing ());

   // assign assigns state, but will not shrink numbers.
   d.assign (RNumber (0, 128));
   e.assign (RNumber (0, 128, RNumber::dynamic));

   V0 (" d (" << hex << d << ", " << dec << d.size() << ", " << d.sizing ());
   V0 (" e (" << hex << e << ", " << dec << e.size() << ", " << e.sizing ());

   // copy copies all state
   d.copy (RNumber (0, 128));
   e.copy (RNumber (0, 128, RNumber::dynamic));

   V0 (" d (" << hex << d << ", " << dec << d.size() << ", " << d.sizing ());
   V0 (" e (" << hex << e << ", " << dec << e.size() << ", " << e.sizing ());

   d.setAll ();
   e.setAll ();

   V0 (" d (" << hex << d << ", " << dec << d.size() << ", " << d.sizing ());
   V0 (" e (" << hex << e << ", " << dec << e.size() << ", " << e.sizing ());

   // the add function can be used with the extend parameter to have 'growing' numbers
   // Notice that since 'd' is not dynamically sized, it will wrap. 
   d = add (d, 1, extend);
   e = add (e, 1, extend);

   V0 (" d (" << hex << d << ", " << dec << d.size() << ", " << d.sizing ());
   V0 (" e (" << hex << e << ", " << dec << e.size() << ", " << e.sizing ());
}
