//
// Various tests of the random number generators.
//
// $Id$
//

#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

#include "LcgRand.h"
#include "KissRand.h"
#include "Random.h"

void revtest(unsigned);
void statetest(unsigned);
void rangetest(unsigned);

int main(int argc,const char *argv[])
{
  unsigned seed = 0;
  if (argc > 1) {
    seed = atoi(argv[1]);
    if (!seed) {
      cerr << "Error:  Expected a seed as a first argument." << endl;
      return 1;
    }
  }
  if (!seed) {
    struct timeval t;
    gettimeofday( &t, NULL );
    seed =  t . tv_sec;
  }
  cout << "\nSeed:  0x" << hex << seed << endl;
  revtest(seed);
  statetest(seed);
  rangetest(seed);
  return 0;
}

// Tests the getFromRange function.
void rangetest(unsigned seed)
{
  cout << "\nRange Test." << endl;

  Random::init(seed);
  
  // We'll process several sizes of data here.
  const int numSizes = 3;
  const int numTries = 10000;

  int typeu  = 0;
  int typen  = 0;
  int typesl = 0;
  int typesh = 0;
  int fails  = 0;

  int sizes[numSizes] = { 32,36,64 };
  for (int i = 0; i != numSizes; ++i) {
    int size = sizes[i];
    cout << " size:  " << dec << size << endl;
    for (int j = 0; j != numTries; ++j) {
      // cout << dec << j << endl;
      // We randomly generate the ranges and test to make
      // sure that the result is correct.
      RNumber min(Random::getRNumber(size));
      RNumber max(Random::getRNumber(size));
      //cout << "Range:  [" << min << ":" << max << "]" << endl;
      RNumber res = Random::getFromRange(min,max);
      if (min < max) {
        ++typeu;
        // Normal, unsigned range.
        if (!(res >= min && res <= max)) {
          cout << hex << "Unsigned Range Failure:  [" << min << ":" << max << "] and " << res << endl;
          ++fails;
        }
      } else {
        if (min.signedLT(0) && max.signedGT(0)) {
          // Signed range.
          if (res <= max) {
            ++typesl;
          } else if (res >= min) {
            ++typesh;
          } else {
            cout << hex << "Signed Range Failure:  [" << min << ":" << max << "] and " << res << endl;
            ++fails;
          }
        } else {
          // Fully negative range.
          if (min.signedGE(res) && max.signedLE(res)) {
            ++typen;
          } else {
            cout << hex << "Negative Signed Range Failure:  [" << min << ":" << max << "] and " << res << endl;
            ++fails;
          }
        }
      }
    }
  }
  if (fails) {
    cout << " " << dec << fails << " failures reported." << endl;
    exit (1);
  }
  if (!typeu) {
    cout << " Found no unsigned ranges.  This is probably a bug." << endl;
    exit (1);
  }
  if (!typesl) {
    cout << " Found no lower-half picks for signed ranges.  This is probably a bug." << endl;
    exit(1);
  }
  if (!typesh) {
    cout << " Found no upper-half picks for signed ranges.  This is probably a bug." << endl;
    exit(1);
  }
  if (!typen) {
    cout << " Found no negative range picks.  This is probably a bug." << endl;
    exit(1);
  }
}

// Tests the state saving feature of the KISS random
// number generator.
void statetest(unsigned seed)
{
  cout << "\nState Save/Load Test." << endl;
  const int size = 10000;
  unsigned v[size];
  KissRand rand(seed);
  KissState state;
  for (int i = 0 ; i != size; ++i) {
    if (i == (size/2)) {
      state = rand.getState();
    }
    v[i] = rand.genrand();
  }
  bool fail = false;
  rand.setState(state);
  for (int i = size/2; i != size; ++i) {
    unsigned k = rand.genrand();
    if (v[i] != k) {
      fail = true;
      cout << "  mismatch (" << dec << i << ")" << endl;
    }
  }

  cout << "Done." << endl;
  if (fail) {
    exit (1);
  }
}

// Tests reversability of the lcg random generator.
void revtest(unsigned seed)
{
  cout << "\nReverse Test." << endl;
  const int size = 10000;
  unsigned v[size];
  LcgRand rand(seed);
  for (int i = 0 ; i != size; ++i) {
    v[i] = rand.genrand();
  }
  bool fail = false;
  for (int i = size-1; i != -1; --i) {
    unsigned k = rand.rgenrand();
    if (v[i] != k) {
      fail = true;
      cout << "  mismatch (" << dec << i << ")" << endl;
    }
  }
  cout << "Done." << endl;
  if (fail) {
    exit (1);
  }
}
