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

namespace rnumber {

  uint64_t readInt64(istream &is)
  {
    unsigned char t[sizeof(uint64_t)];
    is.read((char*)t,sizeof(uint64_t));
    return ( ((uint64_t)t[0] << 56) | 
             ((uint64_t)t[1] << 48) | 
             ((uint64_t)t[2] << 40) | 
             ((uint64_t)t[3] << 32) | 
             ((uint64_t)t[4] << 24) | 
             ((uint64_t)t[5] << 16) | 
             ((uint64_t)t[6] << 8 ) | 
             (t[7]) );
  }

  void writeInt64(ostream &os,uint64_t d)
  {
    unsigned char t[sizeof(uint64_t)] = { ((d >> 56)&0xff),
                                        ((d >> 48)&0xff),
                                        ((d >> 40)&0xff),
                                        ((d >> 32)&0xff),
                                        ((d >> 24)&0xff),
                                        ((d >> 16)&0xff),
                                        ((d >> 8 )&0xff),
                                        ((d)         &0xff) };
    os.write((char*)t,sizeof(uint64_t));
  }

  uint32_t readInt(istream &is)
  {
    unsigned char t[sizeof(uint32_t)];
    is.read((char*)t,sizeof(uint32_t));
    return ( (t[0] << 24) | (t[1] << 16) | (t[2] << 8) | (t[3]));
  }

  void writeInt(ostream &os,uint32_t d)
  {
    unsigned char t[sizeof(uint32_t)] = { ((d >> 24)&0xff),
                                          ((d >> 16)&0xff),
                                          ((d >> 8)&0xff),
                                          (d & 0xff) };
    os.write((char*)t,sizeof(uint32_t));
  }

  uint16_t readShort(istream &is)
  {
    unsigned char t[sizeof(uint16_t)];
    is.read((char*)t,sizeof(uint16_t));
    return ( (t[0] << 8) | (t[1]));
  }

  void writeShort(ostream &os,uint16_t d)
  {
    unsigned char t[sizeof(uint16_t)] = { ((d >> 8)&0xff),
                                                (d & 0xff) };
    os.write((char*)t,sizeof(uint16_t));
  }

  uint8_t readByte(istream &is)
  {
    unsigned char c;
    is.read((char *)&c,sizeof(uint8_t));
    return c;
  }

  void writeByte(ostream &os,uint8_t d)
  {
    os.write((char*)&d,sizeof(uint8_t));
  }

}
