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

#ifndef _INTIO_H_
#define _INTIO_H_

#include <iosfwd>

#include "types.h"

namespace rnumber {

  rnumber_t::uint64 readInt64(std::istream &is);
  void writeInt64(std::ostream &os,rnumber_t::uint64 d);

  unsigned readInt(std::istream &is);
  void writeInt(std::ostream &os,unsigned d);

  unsigned short readShort(std::istream &is);
  void writeShort(std::ostream &os,unsigned short d);

  unsigned char readByte(std::istream &is);
  void writeByte(std::ostream &os,unsigned char d);

}

#endif
