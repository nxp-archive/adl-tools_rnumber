/* A C-program for MT19937: Integer     version                   */
/*  genrand() generates one pseudorandom unsigned integer (32bit) */
/* which is uniformly distributed among 0 to 2^32-1  for each     */
/* call. sgenrand(seed) set initial values to the working area    */
/* of 624 words. Before genrand(), sgenrand(seed) must be         */
/* called once. (seed is any 32-bit integer except for 0).        */
/*   Coded by Takuji Nishimura, considering the suggestions by    */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.              */

/* This library is free software; you can redistribute it and/or   */
/* modify it under the terms of the GNU Library General Public     */
/* License as published by the Free Software Foundation; either    */
/* version 2 of the License, or (at your option) any later         */
/* version.                                                        */
/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
/* See the GNU Library General Public License for more details.    */
/* You should have received a copy of the GNU Library General      */
/* Public License along with this library; if not, write to the    */
/* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */ 
/* 02111-1307  USA                                                 */

/* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
/* When you use this, send an email to: matumoto@math.keio.ac.jp   */
/* with an appropriate reference to your work.                     */

#include "rnumber_exceptions.h"
#include "MtRand.h"

using namespace std;

namespace rnumber {

  /* Period parameters */  
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

  /* Tempering parameters */   
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

  MtRand::MtRand(unsigned seed)
  {
    reset();
    sgenrand(seed);
  }

  // Resets the random number generator.
  void MtRand::reset()
  {
    _mti = N + 1; // mti==N+1 means mt[N] is not initialized.
  }

  // Initializing the array with a NONZERO seed.
  void MtRand::sgenrand(unsigned long seed)
  {
    // setting initial seeds to _mt[N] using
    // the generator Line 25 of Table 1 in
    // [KNUTH 1981, The Art of Computer Programming
    //    Vol. 2 (2nd Ed.), pp102]
    _mt[0]= seed & 0xffffffff;
    for (_mti=1; _mti<N; _mti++)
		_mt[_mti] = (69069 * _mt[_mti-1]) & 0xffffffff;
  }

  // Generates a new random integer.  The system updates its
  // entire array of 624 words at once.
  unsigned long MtRand::genrand()
  {
    unsigned long y;
    static unsigned long mag01[2]={0x0, MATRIX_A};
    // mag01[x] = x * MATRIX_A  for x=0,1

    if (_mti >= N) { // generate N words at one time
		int kk;

		if (_mti == N+1)   // if sgenrand() has not been called,
		  sgenrand(4357);  // a default initial seed is used.

		for (kk=0;kk<N-M;kk++) {
		  y = (_mt[kk]&UPPER_MASK)|(_mt[kk+1]&LOWER_MASK);
		  _mt[kk] = _mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for (;kk<N-1;kk++) {
		  y = (_mt[kk]&UPPER_MASK)|(_mt[kk+1]&LOWER_MASK);
		  _mt[kk] = _mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (_mt[N-1]&UPPER_MASK)|(_mt[0]&LOWER_MASK);
		_mt[N-1] = _mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

		_mti = 0;
    }
  
    y = _mt[_mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    return y; 
  }

  // Save state to a binary stream.
  void MtRand::save(ostream &os) const
  {
    // We compute a simple checksum by xoring the elements together.
    unsigned cs = 0xa5a5a5a5;
    for (int i = 0; i != N; ++i) {
      os.write((char*)&_mt[i],sizeof(_mt[i]));
      cs ^= _mt[i];
    }
    os.write((char*)&_mti,sizeof(_mti));
    cs ^= _mti;
    os.write((char*)&cs,sizeof(cs));
  }

  // Load state from a binary stream.
  void MtRand::load(istream &is)
  {
    unsigned ics;
    unsigned cs = 0xa5a5a5a5;
    for (int i = 0; i != N; ++i) {
      is.read((char*)&_mt[i],sizeof(_mt[i]));
      cs ^= _mt[i];
    }
    is.read((char*)&_mti,sizeof(_mti));
    cs ^= _mti;
    is.read((char*)&ics,sizeof(ics));
    if (ics != cs) {
      throw runtime_error ("Bad checksum when reading Mersenne Twist info.");
    }
  }

}
