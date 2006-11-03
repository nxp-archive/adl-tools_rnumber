//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//


#include <iostream>

#include "RNumber.h"

using namespace std;
using namespace rnumber;

int main ( int argc, char ** argv) {
  cout << "10 << rn 35" << ( 10 << RNumber(static_cast<unsigned int>(0x35))) << endl;
  cout << "10 >> rn 35" << ( 10 >> RNumber(0x35)) << endl;
}
