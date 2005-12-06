/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** C Wrapper for Random.h
** ===========================================================================
*/

#include "C-RNumber.h"
#include "C-Random.h"
#include "Random.h"

using namespace std;
using namespace rnumber;

// By default, we set the seed based upon the time.
void random_create () {
   Random();
}

void random_set_gate_all ( int state_in )
{
  Random::set_gate(state_in);
}

void random_set_gate ( int state_in, int apply_to_all )
{
  Random::set_gate(state_in, apply_to_all);
}

// Generated seed (time based).
unsigned random_init()
{
  return Random::init();
}

// Explicitly set seed.  If the value is 0, the time will be used.
unsigned random_init_from_seed( unsigned seed )
{
  return Random::init(seed);
}

// Create a new generator and store its handle.
// This does not select the generator for use.
int random_add_new_gen()
{
  return Random::addNewGen();
};

int random_add_new_gen_with_seed(unsigned seed)
{
  return Random::addNewGen(seed);
}
// Remove n generators from the end of the list.
void random_pop_gen(int x)
{
  Random::popGen(x);
}
// Specify a new generator to use.
int  random_set_cur_gen(int x)
{
  return Random::setCurGen(x);
}

// Get the current generator handle.
int random_get_cur_gen()
{
  return Random::getCurGen();
}
// Return the number of generators that we currently have.
int random_get_num_gen()
{
  return Random::getNumGen();
}

// Get a value from the current generator.
RNumber * random_get_rnumber( int size )
{
  return new RNumber(Random::getRNumber(size));
}

unsigned  random_get_integer()
{
  return Random::getInteger();
}

unsigned  random_get_integer_n( unsigned n )
{
  return Random::getInteger(n);
}
double    random_get_double()
{
  return Random::getDouble();
}

RNumber *  random_get_from_range_rnumber( RNumber * minimum, RNumber * maximum )
{
  return new RNumber(Random::getFromRange(*minimum, *maximum));
}

unsigned   random_get_from_range_unsigned( unsigned minimum, unsigned maximum )
{
  return Random::getFromRange(minimum, maximum);
}

// Load/save the state of the random number generator.
void random_save (void * os) 
{
  ostream * oos = reinterpret_cast<ostream *>(os);
  Random::save(*oos);
}

void random_load (void * is)
{
  istream * iis = reinterpret_cast<istream *>(is);
  Random::load(*iis);
}

// Get/set info about the random number generator.
void * random_get_state()
{
  return reinterpret_cast<void*> (new RandState(Random::getState()));
}
void random_set_state( void * state)
{
  RandState * random_state = reinterpret_cast<RandState*>(state);
  Random::setState(*random_state);
}

// Return the offset that the current generator is at.
unsigned random_get_count()
{
  return Random::getCount();
};
