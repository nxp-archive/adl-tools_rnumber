/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** The Random class provides random number generation for Raptor.
** It contains a completely static interface, so the actual class need
** never be instantiated.
** ===========================================================================
*/
#ifndef RANDOM_H
#define RANDOM_H "$Id$"

#include <vector>
#include "KissRand.h"
#include "RNumber.h"

namespace rnumber {
typedef KissState RandState;

// Each of these items represents a random number generator.  
// The class is self contained, but they all share the same seed.
class RandomObj
{
private:
  friend class Random;

  KissRand _rand;
  // If we're gated, we cannot be used.
  bool     _gated;
  // This is used as a way of ensuring that no two 
  // seeds are the same- the count is incremented during
  // each usage so that even if the time value is the same,
  // the seeds will still be different.
  static unsigned _count;

  RNumber fromRange(const RNumber &min,const RNumber &max);

public:
  RandomObj();
  RandomObj(unsigned);
  RandomObj(const RandomObj &);

  // Initializes the random number generator.  
  // The seed is returned.
  unsigned init() { return init(0); };
  // Same as above, except that a seed is supplied.
  // If the seed is zero, we generate a new seed.
  unsigned init( unsigned seed );
  // Various functions for getting random data.
  RNumber  getRNumber( unsigned int size );
  unsigned getInteger();
  unsigned getInteger( unsigned n );
  double   getDouble();
  // Range-based gets.  Handles those awful signed ranges that are still
  // in Raptor.
  RNumber  getFromRange( const RNumber& minimum, const RNumber& maximum );
  // Simple unsigned range- min must be less than max.
  unsigned getFromRange( unsigned minimum, unsigned maximum );
  // Load/save the state of the random number generator.
  void save (ostream &os);
  void load (istream &is);
  // Get/set info about the random number generator.
  RandState getState() const;
  void setState(const RandState &);
  unsigned getCount();
  // Gate control.
  void set_gate(bool g) { _gated = g; };
};

// This class is never instantiated- it's purely static.  It contains
// multiple RandomObj generators which may be swapped in and out- the
// current generator is then used by the various get functions.
class Random
{
private:
  // Stores the various generators.
  static vector<RandomObj> _generators;
  // Stores the current generator that we're using.
  static unsigned _currentGen;
public:
  // By default, we set the seed based upon the time.
  Random();

  static void set_gate ( bool state_in,bool apply_to_all = true );
  // Generated seed (time based).
  static unsigned init();
  // Explicitly set seed.  If the value is 0, the time will be used.
  static unsigned init( unsigned seed );

  // Create a new generator and store its handle.
  // This does not select the generator for use.
  static int      addNewGen();
  static int      addNewGen(unsigned seed);
  // Remove n generators from the end of the list.
  static void     popGen(int);
  // Specify a new generator to use.
  static int      setCurGen(int);
  // Get the current generator handle.
  static int      getCurGen();
  // Return the number of generators that we currently have.
  static int      getNumGen();

  // Get a value from the current generator.
  static RNumber  getRNumber( int size );
  static unsigned getInteger();
  static unsigned getInteger( unsigned n );
  static double   getDouble();

  static RNumber  getFromRange( const RNumber& minimum, const RNumber& maximum );
  static unsigned getFromRange( unsigned minimum, unsigned maximum );

  // Load/save the state of the random number generator.
  static void save (ostream &os);
  static void load (istream &is);
  // Get/set info about the random number generator.
  static RandState getState();
  static void setState(const RandState &);
  // Return the offset that the current generator is at.
  static unsigned getCount();
};

// Functor for use with STL generic algorithms.
class RandomSTL
{
public:
  int operator()( int n )  { 
    return Random::getInteger( n ); 
  }
};

inline int Random::getCurGen()
{
  return _currentGen;
}

inline int Random::getNumGen()
{
  return _generators.size();
}

inline RNumber Random::getRNumber( int size )
{
  return _generators[_currentGen].getRNumber(size);
}

inline unsigned Random::getInteger()
{
  return _generators[_currentGen].getInteger();
}

inline unsigned Random::getInteger( unsigned n )
{
  return _generators[_currentGen].getInteger(n);
}

inline double Random::getDouble()
{
  return _generators[_currentGen].getDouble();
}

inline RNumber Random::getFromRange( const RNumber& minimum, const RNumber& maximum )
{
  return _generators[_currentGen].getFromRange(minimum,maximum);
}

inline unsigned Random::getFromRange( unsigned minimum, unsigned maximum )
{
  return _generators[_currentGen].getFromRange(minimum,maximum);
}

inline void Random::save(ostream &os)
{
  _generators[_currentGen].save(os);
}

inline void Random::load(istream &is)
{
  _generators[_currentGen].load(is);
}

inline RandState Random::getState()
{
  return _generators[_currentGen].getState();
}

inline void Random::setState(const RandState &rs)
{
  _generators[_currentGen].setState(rs);
}

inline unsigned Random::getCount()
{
  return _generators[_currentGen].getCount();
}

} // end namespace rnumber 

#endif
