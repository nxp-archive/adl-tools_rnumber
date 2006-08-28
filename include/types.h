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

  // Various integer types.
  typedef unsigned long long int	uint64;
  typedef signed long long int	   int64;

  typedef unsigned short int	      uint16;
  typedef signed short int	      int16;

  typedef unsigned char		      uint8;
  typedef signed char		         int8;

}

#endif
