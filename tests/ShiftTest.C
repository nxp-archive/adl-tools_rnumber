//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//


#include <iostream>
#include <iomanip>

#include "RNumber.h"

using namespace std;
using namespace rnumber;

int main ( int argc, char ** argv)
{
  cout << "10 << rn 35" << ( 10 << RNumber(static_cast<unsigned int>(0x35))) << endl;
  cout << "10 >> rn 35" << ( 10 >> RNumber(0x35)) << endl;

  // Other miscellaneous stuff.
  {
    RNumber v((uint64_t)0xdeadbeef12345678ull);
    unsigned char *bytes = v.bigEndianArrayOfBytes(0);
    cout << "Bytes from 0x" << hex << v << ": ";
    for (unsigned i = 0; i != v.size()/8; ++i) {
      cout << ' ' << setfill('0') << setw(2) << (unsigned)bytes[i];
    }
    cout << endl;
    delete bytes;
  }
}
