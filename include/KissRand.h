//
// Implements the KISS random number generator.  This is a simple,
// but quite good, random number generator with a period of 2^127.
// The function is not reversible (that I know of).  It requires 
// six words to store state (actually, just 5, but I include a count
// for debugging purposes).
//
// $Id$
//

#ifndef _KISSRAND_H_
#define _KISSRAND_H_

#include <iosfwd>

namespace rnumber {
// Momento object for storing state of the random number generator.
class KissState {
  friend class KissRand;
  enum { Size = 6 };
  int _d[Size];
public:
  void save(std::ostream &) const;
  void load(std::istream &);
};

// KISS random number generator.
class KissRand {
public:
  KissRand (unsigned seed = 4937);
  // Specify a seed.
  void sgenrand (unsigned long seed);
  // Generate the next value.
  unsigned long genrand ();
  // Save/load state from a binary stream.
  void save(std::ostream &) const;
  void load(std::istream &);
  unsigned count() const { return _count; };
  // Get/set state of generator.
  KissState getState() const;
  void setState(const KissState &);
private:
  unsigned _count;
  // These are the state variables for the function.
  // Note:  Using signed arithmetic increased the
  // quality of the random numbers.
  int _x, _y, _z, _w, _carry;
};

// Generate the next value.
inline unsigned long KissRand::genrand ()
{
  int k, m;
  _x = _x * 69069 + 1;
  _y ^= _y << 13;
  _y ^= _y >> 17;
  _y ^= _y << 5;
  k = (_z >> 2) + (_w >> 3) + (_carry >> 2);
  m = _w + _w + _z + _carry;
  _z = _w;
  _w = m;
  _carry = k >> 30;
  ++_count;
  return _x + _y + _w;
}
}
#endif
