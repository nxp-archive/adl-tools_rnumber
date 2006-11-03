//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

//
// This is a class which implements the Mersenne Twister 
// random number generator.  This is a really powerful
// linear pseudo-random number generator with a period of 2^19937-1.
// It is theoretically reversible, but the code that I found for
// the reverse function has a bug in it, so the reversability
// is not implemented.  Its state consists of 624 words, making it
// fairly expensive to save, but it gives you a great distribution.
//
// $Id$
//

#ifndef MTRANDOM_H
#define MTRANDOM_H

#include <iosfwd>

namespace rnumber {

  // Mersenne Twister random number generator class.
  class MtRand {
  public:
	 MtRand (unsigned seed);
    // Reset the generator.
    void reset();
    // Specify a seed.
	 void sgenrand (unsigned long seed);
    // Generate the next value.
	 unsigned long genrand ();
    // Save/load state from a binary stream.
    void save(std::ostream &) const;
    void load(std::istream &);
  private:
    enum { N=624 };
	 unsigned long _mt[N]; /* the array for the state vector  */
	 int _mti;
  };

}

#endif
