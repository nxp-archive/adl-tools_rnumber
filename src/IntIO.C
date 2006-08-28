//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

//
// Helper routines for reading and writing integers
// to or from a stream.  This is done in an endian-neutral
// way so that it will work on different platforms.
//
// $Id$
//

#include <iostream>

#include "IntIO.h"

using namespace std;
using namespace rnumber_t;

namespace rnumber {

  uint64 readInt64(istream &is)
  {
    unsigned char t[sizeof(uint64)];
    is.read((char*)t,sizeof(uint64));
    return ( ((uint64)t[0] << 56) | 
             ((uint64)t[1] << 48) | 
             ((uint64)t[2] << 40) | 
             ((uint64)t[3] << 32) | 
             ((uint64)t[4] << 24) | 
             ((uint64)t[5] << 16) | 
             ((uint64)t[6] << 8 ) | 
             (t[7]) );
  }

  void writeInt64(ostream &os,uint64 d)
  {
    unsigned char t[sizeof(uint64)] = { ((d >> 56)&0xff),
                                        ((d >> 48)&0xff),
                                        ((d >> 40)&0xff),
                                        ((d >> 32)&0xff),
                                        ((d >> 24)&0xff),
                                        ((d >> 16)&0xff),
                                        ((d >> 8 )&0xff),
                                        ((d)         &0xff) };
    os.write((char*)t,sizeof(uint64));
  }

  unsigned readInt(istream &is)
  {
    unsigned char t[sizeof(unsigned)];
    is.read((char*)t,sizeof(unsigned));
    return ( (t[0] << 24) | (t[1] << 16) | (t[2] << 8) | (t[3]));
  }

  void writeInt(ostream &os,unsigned d)
  {
    unsigned char t[sizeof(unsigned)] = { ((d >> 24)&0xff),
                                          ((d >> 16)&0xff),
                                          ((d >> 8)&0xff),
                                          (d & 0xff) };
    os.write((char*)t,sizeof(unsigned));
  }

  unsigned short readShort(istream &is)
  {
    unsigned char t[sizeof(unsigned short)];
    is.read((char*)t,sizeof(unsigned short));
    return ( (t[0] << 8) | (t[1]));
  }

  void writeShort(ostream &os,unsigned short d)
  {
    unsigned char t[sizeof(unsigned short)] = { ((d >> 8)&0xff),
                                                (d & 0xff) };
    os.write((char*)t,sizeof(unsigned short));
  }

  unsigned char readByte(istream &is)
  {
    unsigned char c;
    is.read((char *)&c,sizeof(unsigned char));
    return c;
  }

  void writeByte(ostream &os,unsigned char d)
  {
    os.write((char*)&d,sizeof(unsigned char));
  }

}
