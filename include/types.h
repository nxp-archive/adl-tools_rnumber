//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
** ===========================================================================
*/

#ifndef TYPES_H
#define TYPES_H "$Id$"

#ifdef _MSC_VER

// Another example of how broken Windows is:  They don't include inttypes.h!
// I guess this is because they don't support C99.  After all, it's only been
// eight years and Microsoft is at least a decade behind on everything they do.

typedef __int64  int64_t;
typedef unsigned __int64 uint64_t;

typedef __int32  int32_t;
typedef unsigned __int32 uint32_t;

typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;

typedef __int8  int8_t;
typedef unsigned __int8 uint8_t;

#else
# include <inttypes.h>
#endif

namespace rnumber_t {

  // Attributes of a nibble.
  const unsigned NibbleBits  = 4;
  const unsigned NibbleRadix = ( (unsigned) 0x1 ) << NibbleBits;
  const unsigned NibbleMask  = NibbleRadix - 1;

  // Attributes of a byte.
  const unsigned ByteBits  = 8;
  const unsigned ByteRadix = ( (unsigned) 0x1 ) << ByteBits;
  const unsigned ByteMask  = ByteRadix - 1;

  // Attributes of a word.
  const unsigned WordBytes = sizeof( unsigned );
  const unsigned WordBits  = WordBytes * ByteBits;
  const unsigned WordMask  = (unsigned) ((int) -1);
  // Make sure that WordBytes = ceil(WordBits / ByteBits).

  // Attributes of a half word.
  const unsigned HalfWordBytes = WordBytes / 2;
  const unsigned HalfWordBits  = HalfWordBytes * ByteBits;
  const unsigned HalfWordRadix = ( (unsigned) 0x1 ) << HalfWordBits;
  const unsigned HalfWordMask  = HalfWordRadix - 1;

  // Attributes of a digit.
  const unsigned DigitBytes = sizeof( unsigned );
  const unsigned DigitBits  = ( DigitBytes * ByteBits ) - 2;
  const unsigned DigitRadix = ( (unsigned) 0x1 ) << DigitBits;
  const unsigned DigitMask  = DigitRadix - 1;
  // Make sure that DigitBytes = ceil(DigitBits / ByteBits).

  // Similar attributes for the half of a digit.
  const unsigned HalfDigitBytes = DigitBytes / 2;
  const unsigned HalfDigitBits  = DigitBits / 2;
  const unsigned HalfDigitRadix = ( (unsigned) 0x1 ) << HalfDigitBits;
  const unsigned HalfDigitMask  = HalfDigitRadix - 1;

}

#endif
