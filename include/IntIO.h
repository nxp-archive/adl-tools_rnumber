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

  uint64_t readInt64(std::istream &is);
  void writeInt64(std::ostream &os,uint64_t d);

  uint32_t readInt(std::istream &is);
  void writeInt(std::ostream &os,uint32_t d);

  uint16_t readShort(std::istream &is);
  void writeShort(std::ostream &os,uint16_t d);

  uint8_t readByte(std::istream &is);
  void writeByte(std::ostream &os,uint8_t d);

}

#endif
