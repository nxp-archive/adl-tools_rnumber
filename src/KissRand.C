//
// Implements the KISS random number generator.  This is a simple,
// but quite good, random number generator with a period of 2^127.
// The function is not reversible (that I know of).  It requires 
// five words to store state.
//
// $Id$
//

#include <stdexcept>
#include <iostream>

#include "KissRand.h"

using namespace std;

//#define VERBOSE1
//#define VERBOSE2

#ifdef VERBOSE1
#  define V1(x) { cout << __FILE__ << ":" << __LINE__ << ":  " << x << endl; }
#else
# define V1(x)
#endif


#ifdef VERBOSE2
#  define V2(x) { cout << __FILE__ << ":" << __LINE__ << ":  " << x << endl; }
#else
# define V2(x)
#endif

namespace rnumber {

  void KissState::save(ostream &os) const
  {
    V1("Kiss state:");
    for (int i = 0; i != Size; ++i) {
      V1("  " << dec << i << ":  " << hex << _d[i]);
      os.write((char *)&_d[i],sizeof(_d[i]));
    }
  }

  void KissState::load(istream &is) 
  {
    V1("Kiss state:");
    for (int i = 0; i != Size; ++i) {
      is.read((char *)&_d[i],sizeof(_d[i]));
      V1("  " << dec << i << ":  " << hex << _d[i]);
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
    os.write((char *)&_x,sizeof(_x));
    os.write((char *)&_y,sizeof(_y));
    os.write((char *)&_z,sizeof(_z));
    os.write((char *)&_w,sizeof(_w));
    os.write((char *)&_carry,sizeof(_carry));
    os.write((char *)&_count,sizeof(_count));
    V1("Kiss save:  \n" << hex << endl << 
       "x:      " << _x << endl << 
       "y:      " << _y << endl << 
       "z:      " << _z << endl << 
       "w:      " << _w << endl << 
       "carry:  " << _carry << endl << 
       "count:  " << _count);
  }

  void KissRand::load(istream &is)
  {
    is.read((char *)&_x,sizeof(_x));
    is.read((char *)&_y,sizeof(_y));
    is.read((char *)&_z,sizeof(_z));
    is.read((char *)&_w,sizeof(_w));
    is.read((char *)&_carry,sizeof(_carry));
    is.read((char *)&_count,sizeof(_count));
    V1("Kiss load:  \n" << hex << endl <<  
       "x:      " << _x << endl << 
       "y:      " << _y << endl << 
       "z:      " << _z << endl << 
       "w:      " << _w << endl << 
       "carry:  " << _carry << endl << 
       "count:  " << _count);
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

}
