
#include <iostream>

#include "RNumber.h"

using namespace std;
using namespace rnumber;

int main ( int argc, char ** argv) {
  cout << "10 << rn 35" << ( 10 << RNumber(static_cast<unsigned int>(0x35))) << endl;
  cout << "10 >> rn 35" << ( 10 >> RNumber(0x35)) << endl;
}
