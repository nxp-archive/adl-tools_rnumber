//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
** ===========================================================================
*/
#ifdef _MSC_VER
# include <time.h>
#else
# include <sys/time.h>
#endif
#include <stdexcept>
#include <cassert>

#include "Random.h"

//#define VERBOSE1

#ifdef VERBOSE1
#  define V1(x) { cout << __FILE__ << ":" << __LINE__ << ":  " << x << endl; }
#else
# define V1(x)
#endif

using namespace std;
using namespace rnumber;

// We always install a default random object.
unsigned Random::_currentGen = 0;
vector<RandomObj> Random::_generators(1,RandomObj());

// This is here to make sure that repeated seed generations don't repeat.
unsigned RandomObj::_count = 0;

RandomObj::RandomObj()
{
  init();
};

RandomObj::RandomObj(unsigned seed)
{
  init( seed );
};

RandomObj::RandomObj(const RandomObj &x) : 
  _rand(x._rand),
  _gated(x._gated)
{
};

// Initializes the generator to a specified seed.
unsigned RandomObj::init( unsigned seed )
{
  _gated = false;
  if (!seed) {
#   ifdef _MSC_VER
	  time_t ltime;
	  time( &ltime );
	  seed = ltime + ++_count;
#   else
    struct timeval t;
    gettimeofday( &t, NULL );
    seed =  t . tv_sec + ++_count;
#   endif
  }
  _rand.sgenrand(seed);
  V1("Seed = " << seed << ", Count = " << _count);
  return seed;
}

// Get a random number of a specified number of bits.
RNumber RandomObj::getRNumber( unsigned int size = 32 )
{
  if ( _gated ) 
    throw runtime_error ( "RandomObj::getRNumber - Random number was generated while generator was gated." );

  unsigned i;
  unsigned count = (size + 31) / 32;
  unsigned shift = (size & 0x1f) ? (32 - (size & 0x1f)) : 0;
  unsigned v;
  RNumber res( 0, size );

  for (i = 0; i < count; i++)
    {
      v = _rand.genrand();
      v >>= shift;
      res <<= 32;
      res |= v;
      shift = 0;
    }

  return res;
}

// Get a random unsigned integer
unsigned RandomObj::getInteger()
{
  if ( _gated ) 
    throw runtime_error ( " RandomObj::getInteger - Random number was generated while generator was gated." );
  return _rand.genrand();
}

uint64_t RandomObj::getUint64()
{
  if ( _gated ) 
    throw runtime_error ( " RandomObj::getUint64 - Random number was generated while generator was gated." );
  uint64_t x = _rand.genrand();
  x <<= 32;
  return (x | _rand.genrand());
}

// Get a random unsigned integer from 0 to n
unsigned RandomObj::getInteger( unsigned n )
{
  if ( _gated ) 
    throw runtime_error ( "RandomObj::getInteger( unsigned n ) - Random number was generated while generator was gated." );
  return (n == 0) ? 0 : _rand.genrand() % n;
}

uint64_t RandomObj::getUint64( uint64_t n )
{
  if ( _gated ) 
    throw runtime_error ( "RandomObj::getUint64( uint64 n ) - Random number was generated while generator was gated." );
  return (n == 0) ? 0 : getUint64() % n;
}

// Get a double between 0 and 1
double RandomObj::getDouble()
{
  if ( _gated ) 
    throw runtime_error ( "RandomObj::getDouble() - Random number was generated while generator was gated." );
  unsigned v = _rand.genrand() & 0x7fffffff;
  return ((double) v) / ((double) 0x7fffffff);
}

// Unsigned range function- called by getFromRange, which does the job of figuring
// out if something is a signed or unsigned range.
inline RNumber RandomObj::fromRange(const RNumber &min,const RNumber &max) 
{
  RNumber diff(max - min + 1,max.size());
  return (min + (getRNumber(max.size()) % diff));
}

// Get a new random number within a given range.  This currently works
// for "signed" ranges.  These are these awful things that represent a noncontiguous
// range of numbers- they stretch from [0,max],[min,upper memory].  Eventually,
// we should eliminate that when the RSpan code is fully moved into Raptor.
RNumber RandomObj::getFromRange( const RNumber& min, const RNumber& max )
{
  if ( min <= max ) {
    // Normal, unsigned range.
    return fromRange(min,max);
  } else if ( min.signedLT(RNumber(0)) && max.signedGT(RNumber(0))) {
    // We're spanning from a neg number to a pos number.
    // Must break up range into two non-intersecting ranges.
    if (getInteger(2)) {
      return fromRange(RNumber(0,max.size()),max);
    } else {
      RNumber x(max);
      x.setAll();
      return fromRange(min,x);
    }
  } else if (max == 0) {
    RNumber x(0,max.size());
    x.setAll();
    RNumber length = x - min + 1;
    if (getInteger(length.uint32())) {
      return fromRange(min,x);
    }else{
      return RNumber(0);
    }
  } else {
    // Spans from a negative number to a negative number.
    return fromRange(max,min);
  }
}

// Get an unsigned integer within a given range
unsigned RandomObj::getFromRange( unsigned minimum, unsigned maximum )
{
  unsigned v = getInteger (maximum - minimum + 1);
  return (minimum + v);
}

// Save the generator's state.
void RandomObj::save(ostream &os)
{
  _rand.save(os);
}

// Load the generator's state.
void RandomObj::load(istream &is)
{
  _rand.load(is);
}

// Get the state of the generator.
RandState RandomObj::getState() const
{
  return _rand.getState();
}

// Set the state of the generator.
void RandomObj::setState(const RandState &rs)
{
  _rand.setState(rs);
}

// Return the current cyle of the generator
unsigned RandomObj::getCount()
{
  return _rand.count();
}

Random::Random()
{
}

void Random::set_gate   ( bool state_in,bool apply_to_all )
{
  if (apply_to_all) {
    for (vector<RandomObj>::iterator i = _generators.begin(); i != _generators.end(); ++i) {
      i->set_gate(state_in);
    }
  } else {
    _generators[_currentGen].set_gate(state_in);
  }
}

unsigned Random::init()
{
  return _generators[_currentGen].init();
}

unsigned Random::init( unsigned seed )
{
  return _generators[_currentGen].init(seed);
}

// Create a new generator and store its handle
int Random::addNewGen()
{
  _generators.push_back(RandomObj());
  return _generators.size()-1;
}

// Create a new generator and store its handle
int Random::addNewGen(unsigned seed)
{
  _generators.push_back(RandomObj(seed));
  return _generators.size()-1;
}

// Remove n generators from the end of the list.
void Random::popGen(int n)
{
  assert((int)_generators.size() >= n);
  _generators.erase(_generators.end()-n,_generators.end());
}

// Specify a new generator to use.
int Random::setCurGen(int g)
{
  V1("Setting random generator to " << dec << g);
  int cg = _currentGen;
  assert (g >= 0 && g < (int)_generators.size());
  _currentGen = g;
  return cg;
}

