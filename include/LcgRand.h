//
// Implements a lineaer congruential pseudo-random
// number generator.  This is a simple generator of the
// form x(n+1) = x(n)*a mod m.  In this case, m is prime,
// so the result is a group with the above as its function.
// The function visits all elements in the group before repeating,
// i.e. it orbits the entire group.
// Since it's a group, it has an inverse, which is essentially
// The function itself is simply x(n-1) = x(n)*b mod m, where
// b is computed as b = a^(m-2) mod m, i.e. "go through the entire orbit but 1".  
// The end result is that this function is reversible, requires one
// 32-bit integer to represent state, and has a period of 2^32-1.
// Note that if a larger period is desired, it's possible to simply create
// another lcg and combine the two results using addition- this creates a
// fairly good distribution with about double the period.
//
// $Id$
//

#ifndef _LCGRAND_H_
#define _LCGRAND_H_

#include <iosfwd>

namespace rnumber {

// KISS random number generator.
class LcgRand {
public:
  LcgRand (unsigned seed = 4937) { sgenrand(seed); };
  // Specify a seed (initial state).
  void sgenrand (unsigned long seed) { _x = seed & 0xffffffff; };
  // Generate the next value.
  unsigned long genrand ();
  // Generate the previous value.
  unsigned long rgenrand ();
  // Access the state element.
  unsigned long state() const { return _x; };
  // Save/load state from a binary stream.
  void save(std::ostream &) const;
  void load(std::istream &);
private:   
  // This is the state element of the generator.
  unsigned _x;
};
}

#endif
