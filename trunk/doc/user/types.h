
  const unsigned NIBBLE_BITS  = 4;
  const unsigned NIBBLE_RADIX = ( (unsigned) 0x1 ) << NIBBLE_BITS;
  const unsigned NIBBLE_MASK  = NIBBLE_RADIX - 1;

  /// Attributes of a byte.
  const unsigned BYTE_BITS  = 8;
  const unsigned BYTE_RADIX = ( (unsigned) 0x1 ) << BYTE_BITS;
  const unsigned BYTE_MASK  = BYTE_RADIX - 1;

  /// Attributes of a word.
  const unsigned WORD_BYTES = sizeof( unsigned );
  const unsigned WORD_BITS  = WORD_BYTES * BYTE_BITS;
  const unsigned WORD_MASK  = (unsigned) ((int) -1);
  /// Make sure that WORD_BYTES = ceil(WORD_BITS / BYTE_BITS).

  /// Attributes of a half word.
  const unsigned HALF_WORD_BYTES = WORD_BYTES / 2;
  const unsigned HALF_WORD_BITS  = HALF_WORD_BYTES * BYTE_BITS;
  const unsigned HALF_WORD_RADIX = ( (unsigned) 0x1 ) << HALF_WORD_BITS;
  const unsigned HALF_WORD_MASK  = HALF_WORD_RADIX - 1;

  /// Attributes of a digit.
  const unsigned DIGIT_BYTES = sizeof( unsigned );
  const unsigned DIGIT_BITS  = ( DIGIT_BYTES * BYTE_BITS ) - 2;
  const unsigned DIGIT_RADIX = ( (unsigned) 0x1 ) << DIGIT_BITS;
  const unsigned DIGIT_MASK  = DIGIT_RADIX - 1;
  /// Make sure that DIGIT_BYTES = ceil(DIGIT_BITS / BYTE_BITS).

  /// Similar attributes for the half of a digit.
  const unsigned HALF_DIGIT_BYTES = DIGIT_BYTES / 2;
  const unsigned HALF_DIGIT_BITS  = DIGIT_BITS / 2;
  const unsigned HALF_DIGIT_RADIX = ( (unsigned) 0x1 ) << HALF_DIGIT_BITS;
  const unsigned HALF_DIGIT_MASK  = HALF_DIGIT_RADIX - 1;

  /// Various integer types.
  typedef unsigned long long int   uint64;
  typedef signed long long int     int64;
  typedef unsigned short int       uint16;
  typedef signed short int         int16;

  typedef unsigned char            uint8;
  typedef signed char              int8;

