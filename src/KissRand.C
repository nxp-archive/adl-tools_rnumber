//
// Implements the KISS random number generator.  This is a simple,
// but quite good, random number generator with a period of 2^127.
// The function is not reversible (that I know of).  It requires 
// five words to store state.
//
// $Id$
//

#include <iostream>

#include "rnumber_exceptions.h"
#include "KissRand.h"

using namespace rnumber;

void KissState::save(ostream &os) const
{
  for (int i = 0; i != Size; ++i) {
    os.write(&_d[i],sizeof(_d[i]));
  }
}

void KissState::load(istream &is) 
{
  for (int i = 0; i != Size; ++i) {
    is.read(&_d[i],sizeof(_d[i]));
  }
}

// Resets the generator back to the initial state,
// using the given seed.
KissRand::KissRand(unsigned seed)
{
  sgenrand(seed);
}

// Specify a seed and init the generator.
void KissRand::sgenrand (unsigned long seed)
{
  _x = seed | 1;
  _y = seed | 2;
  _z = seed | 4;
  _w = seed | 8;
  _carry = 0;
  _count = 0;
}

// Save/load state from a binary stream.
void KissRand::save(ostream &os) const
{
  os.write(&_x,sizeof(_x));
  os.write(&_y,sizeof(_y));
  os.write(&_z,sizeof(_z));
  os.write(&_w,sizeof(_w));
  os.write(&_carry,sizeof(_carry));
  os.write(&_count,sizeof(_count));
}

void KissRand::load(istream &is)
{
  is.read(&_x,sizeof(_x));
  is.read(&_y,sizeof(_y));
  is.read(&_z,sizeof(_z));
  is.read(&_w,sizeof(_w));
  is.read(&_carry,sizeof(_carry));
  is.read(&_count,sizeof(_count));
}

// Get/set state of generator.
KissState KissRand::getState() const
{
  KissState s;
  s._d[0] = _x;
  s._d[1] = _y;
  s._d[2] = _z;
  s._d[3] = _w;
  s._d[4] = _carry;
  s._d[5] = _count;
  return s;
}

void KissRand::setState(const KissState &s)
{
  _x = s._d[0];
  _y = s._d[1];
  _z = s._d[2];
  _w = s._d[3];
  _carry = s._d[4];
  _count = s._d[5];
}

