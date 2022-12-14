//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

//
// Implements a linear congruential generator.  This is a reversible
// function so you can cycle the generator backwards and forwards.
//
// $Id$
//

#include <iostream>

#include "LcgRand.h"

using namespace std;

// This LCG uses 64-bit arithmetic to ensure no loss
// of bits.  Otherwise, we can't reverse the generator.
// There should be a way to do a*x mod m using just
// 32-bit arithmetic, but I haven't tracked down the
// algorithm yet.  Thus, it may be necessary to modify
// this typedef when porting to other platforms.
typedef unsigned long long uint64;

// Good values for two generators.  Should you need to
// expand the period, simply combine these two LCGs together.
// a = { 1588635695UL,  279470273UL, };
// m = { 4294967291UL, 4294967291UL, };
// b = { 3870709308UL, 1815976680UL, };
static const uint64 a = 279470273UL;
static const uint64 m = 4294967291UL;
static const uint64 b = 1815976680UL;

using namespace rnumber;

unsigned long LcgRand::genrand ()
{
  _x = (a * _x) % m;
  return _x;
}

unsigned long LcgRand::rgenrand ()
{
  unsigned res = _x;
  _x = (b * _x) % m;
  return res;
}

void LcgRand::save(ostream &os) const
{
  os.write((char *)&_x,sizeof(_x));
}

void LcgRand::load(istream &is)
{
  is.read((char *)&_x,sizeof(_x));
}

