#include <stdio.h>
#include <unistd.h>
#include <strstream.h>
#include <stl_algobase.h>

#include "rnumber_exceptions.h"
#include "RNumber.h"
#include "Random.h"

#include "trace.h"

unsigned maxIter = 100;

const int Verbose = 0;
using namespace rnumber;

int main ( int argc, char ** argv) {
  cout << "10 << rn 35" << ( 10 << RNumber(0x35)) << endl;
  cout << "10 >> rn 35" << ( 10 >> RNumber(0x35)) << endl;
}
