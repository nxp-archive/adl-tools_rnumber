/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** This number class provides arithmetic and boolean expression support for
** numeric data of arbitrary sizes.  The programmer is no longer constrained
** by the size of a platform's registers.  The number's sizing may be fixed
** or dynamic thus making it suitable for mimicking computer architecture
** components (such as registers) or for general purpose arithmetic. This
** particular implementation has limited support for signed numbers.
** ===========================================================================
*/
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "gccversion.h"
#ifdef STD_CPP
# include <sstream>
#else
# include <strstream.h>
# include <iomanip.h>
#endif

#include "RNumber.h"
#include "IntIO.h"
#include "trace.h"

using namespace std;
using namespace rnumber;
using namespace rnumber_t;

unsigned int RNumber::_defaultSize = 32;

//
// Function prototypes for static helper functions that are private to this class.
//
static inline unsigned int lowHalf( unsigned int n );
static inline unsigned int highHalf( unsigned int n );
static inline unsigned int highLowConcat( unsigned int nh, unsigned int nl );

static inline unsigned int* getTempBuffer( unsigned int wordCount );
static inline unsigned int countLeadingZeroWords( const unsigned int* n, unsigned int nLen );
static inline unsigned int skipLeadingZeroWords( const unsigned int* n, unsigned int nLen );
static inline unsigned int skipLeadingZeroBytes( const unsigned char* n, unsigned int nLen );
static inline unsigned int skipLeadingZeroBits( const unsigned int* n, unsigned int nLen );
static inline void convertToBytes( const unsigned int* wordBuffer, unsigned char* byteBuffer, unsigned int wordCount );

// General read function from strings, with radix specified
// by the prefix in the input.
void readstr(RNumber &,const string &);
// Read from a string, radix specified by caller.  No prefix
// is allowed.
void readstr(RNumber &,const string &,int format);

static void multiplyExtended( const unsigned int* vb1, unsigned int wc1, const unsigned int* vb2, unsigned int wc2, 
                              unsigned int* resValue0,bool extend );
static void divideExtended( unsigned char* xb, unsigned int xlen, unsigned char* yb, unsigned int ylen, unsigned char* q );


//
// Return the low half part of n.
//
static inline unsigned int lowHalf( unsigned int n )
{
  return n & HalfWordMask;
}


//
// Return the high half part of n.
//
static inline unsigned int highHalf( unsigned int n )
{
  return n >> HalfWordBits;
}


//
// Concatenate the high part nh and low part nl.
//
static inline unsigned int highLowConcat( unsigned int nh, unsigned int nl )
{
  return ( nh << HalfWordBits ) | ( nl & HalfWordMask );
}

class TempBuffer {
public:
  TempBuffer() : _size(4), _buf(new unsigned[_size]) {};
  ~TempBuffer() { delete [] _buf; };
  unsigned int *get(unsigned wc) {
    if (wc > _size) {
      delete [] _buf;
      _size *= 2;
      if (wc > _size) {
        _size = wc;
      }
      _buf = new unsigned[_size];
    }
    return _buf;
  }
private:
  unsigned  _size;
  unsigned *_buf;
};

//
// Return a static buffer for use in RNumber operators.
//
static inline unsigned int* getTempBuffer( unsigned int wordCount )
{
  static TempBuffer tempBuffer;
  return tempBuffer.get(wordCount);
}

//
// Returns the number of leading zero words.
//
static inline unsigned int countLeadingZeroWords( const unsigned int* n, unsigned int nLen )
{
  assert( nLen != 0 );

  unsigned int count = 0;
  const unsigned int* p = n;

  while ( ( --nLen > 0 ) && ( !*p ) ) {
    ++count;
    p++;
  }

  return count;
}

//
// Return the number of words in the number excluding leading zeros.
//
static inline unsigned int skipLeadingZeroWords( const unsigned int* n, unsigned int nLen )
{
  assert( nLen != 0 );

  const unsigned int* p = n;

  while ( ( --nLen > 0 ) && ( !*p ) )
    p++;

  return ( ++nLen );
}


//
// Return the number of bytes in the number excluding leading zeros.
//
static inline unsigned int skipLeadingZeroBytes( const unsigned char* n, unsigned int nLen )
{
  assert( nLen != 0 );

  const unsigned char* p = n;

  while ( ( --nLen > 0 ) && ( !*p ) )
    p++;

  return ( ++nLen );
}

//
// Return the number of bits in the number excluding leading zero bits.
//
static inline unsigned int skipLeadingZeroBits( const unsigned int* n, unsigned int nLen )
{
  assert( nLen != 0 );

  const unsigned int* p = n;
  const unsigned int START_BIT_POS = 0x1 << ( WordBits - 1 );
  unsigned off = ((nLen - 1) % WordBits) + 1;
  unsigned int bitPos = 0x1 << ( off - 1 );

  do
    {
      if (*p) {
        // Scan through the number, looking for a 1.
        while ( nLen-- && bitPos && !(*p & bitPos) )
          bitPos >>= 1;
          
        // Stop if we've found a 1 or we're 
        // at the end of the word.
        if ( !nLen || (*p & bitPos) )
          break;
      } else {
        nLen -= off;
        off = WordBits;
      }
      // Go to the next word.
      p++;
      bitPos = START_BIT_POS;
    } while ( 1 );
    
  return ( nLen + 1 );
}


//
// Convert word-based number representation to byte-based representation.
//
static inline void convertToBytes( const unsigned int* wordBuffer,
                                   unsigned char* byteBuffer,
                                   unsigned int wordCount )
{

  for ( unsigned int i = 0; i < wordCount; i++ )
    {
      *(byteBuffer++) = ( wordBuffer[i] >> ( 3 * ByteBits ) ) & ByteMask;
      *(byteBuffer++) = ( wordBuffer[i] >> ( 2 * ByteBits ) ) & ByteMask;
      *(byteBuffer++) = ( wordBuffer[i] >> ByteBits ) & ByteMask;
      *(byteBuffer++) = wordBuffer[i] & ByteMask;
    }
}

//
// Assign the specified number value but truncate it to fit our size.
//
inline void RNumber::assignAndTruncateNumber( const RNumber& number )
{

  assert( _size <= number._size );

  int diff = number._wordCount - _wordCount;
  unsigned int* nvb = number._valueBuffer + diff;

  for ( unsigned int i = 0; i < _wordCount; i++ )
    _valueBuffer[i] = nvb[i];

  truncateTop();
}


// Assign the specified number value. If we are too small in size to
// hold the new value, increase our size if our _sizing is dynamic;
// otherwise truncate. If we are bigger than the new value, keep the current
// size and prefix the value with zeros.
inline void RNumber::assignNumber( const RNumber& number )
{

  if ( _size == number._size )
    {
      // This loop will be tight but we do not incur the memcpy() function
      // call penalty.
      unsigned int* nvb = number._valueBuffer;

      for ( unsigned int i = 0; i < _wordCount; i++ )
        _valueBuffer[i] = nvb[i];
    }
  else if ( _size < number._size )
    {
      if ( _sizing == dynamic )
        {
          if ( _wordCount > WORD_THRESHOLD )
            delete [] _value.varValue;

          cloneNumber( number );
        }
      else
        assignAndTruncateNumber( number );
    }
  else
    {
      int wordDiff = _wordCount - number._wordCount;

      // This loop will be tight but we do not incur the memset() function
      // call penalty.
      if ( wordDiff > 0 )
        for ( int i = 0; i < wordDiff; i++ )
          _valueBuffer[i] = 0;

      unsigned int* vb  = _valueBuffer + wordDiff;
      unsigned int* nvb = number._valueBuffer;

      // This loop will be tight but we do not incur the memcpy() function
      // call penalty.
      for ( unsigned int i = 0; i < number._wordCount; i++ )
        vb[i] = nvb[i];
    }
}


//
// Truncate down to the specified bit size.
//
inline RNumber& RNumber::truncateTop()
{

  const unsigned int bitPos = _size % WordBits;

  if ( bitPos )
    _valueBuffer[0] &= ( 0x1 << bitPos ) - 1;

  return *this;
}


//
// Truncate down to the specified bit size.
//
inline RNumber& RNumber::truncateInt( unsigned int size )
{

  if ( size < WordBits )
    _valueBuffer[0] &= ( 0x1 << size ) - 1;

  return *this;
}


//
// Truncate down to the specified bit size.
//
inline RNumber& RNumber::truncateExtended( unsigned int size )
{

  if ( size < ( _wordCount * WordBits ) )
    {
      unsigned int n = _wordCount - ( size / WordBits );

      if ( size % WordBits )
        {
          unsigned int mask = ( 0x1 << ( size % WordBits ) ) - 1;

          _valueBuffer[n - 1] &= mask;
          n--;
        }

      for ( unsigned int i = 0; i < n; i++ )
        _valueBuffer[i] = 0;
    }

  return *this;
}


// ---------------------------------------------------------------------------

//
// Create a new RNumber with the specified value but constrained to the
// specified size.
//
RNumber::RNumber( unsigned int number, unsigned int size, Sizing sizing )
{
  initNumber( ( size ) ? size : _defaultSize, sizing );
  _valueBuffer[_wordCount - 1] = number;
  truncateTop();
}

RNumber::RNumber( int number, unsigned int size, Sizing sizing )
{
  initNumber( ( size ) ? size : _defaultSize, sizing );
  _valueBuffer[_wordCount - 1] = number;
  truncateTop();
}

RNumber::RNumber( long long number, unsigned int size, Sizing sizing ) {
   assert(size <= 64);
   initNumber( size, sizing );
   if (size <= 32) {
      _valueBuffer[0] = number & 0xffffffff;
   } else {
      _valueBuffer[0] = (number>>32)& 0xffffffff;
      _valueBuffer[1] = number & 0xffffffff;
   }
   truncateTop();
}

RNumber::RNumber( unsigned long long number, unsigned int size, Sizing sizing ) {
   assert(size <= 64);
   initNumber( size, sizing );
   if (size <= 32) {
      _valueBuffer[0] = number & 0xffffffff;
   } else {
      _valueBuffer[0] = (number>>32)& 0xffffffff;
      _valueBuffer[1] = number & 0xffffffff;
   }
   truncateTop();
}


//
// Create a new RNumber with the specified value but constrained to the
// specified size.
//
RNumber::RNumber( const RNumber& number, unsigned int size, Sizing sizing )
{
  // Initialize RNumber internals with the specified size.
  initNumber( ( size ) ? size : number._size, sizing );

  unsigned int* nvb = number._valueBuffer;

  if ( _size == number._size )
    {
      // The bit sizes match so just copy.
      for ( unsigned int i = 0; i < _wordCount; i++ )
        _valueBuffer[i] = nvb[i];
    }
  else if ( _size < number._size )
    {
      assignAndTruncateNumber( number );
    }
  else
    {
      // The specified size was larger than the value. Since the internals were
      // already initialized to zero from above, just copy the needed words.
      int diff = _wordCount - number._wordCount;
      unsigned int* vb = _valueBuffer + diff;

      for ( unsigned int i = 0, nwc = number._wordCount; i < nwc; i++ )
        vb[i] = nvb[i];
    }
}


//
// Create a new RNumber with the specified string value.
//
RNumber::RNumber( const string& number, Sizing sizing )
{
  Format radix = rios;
  
  unsigned size = getSizeWithRadix (number, radix);

  if (size < _defaultSize) size = _defaultSize;

  initNumber( size, sizing );

  readstr(*this,number);
}


//
// Create a new RNumber with the specified string value but constrained
// to the specified size.
//
RNumber::RNumber( const string& number, unsigned int size, Sizing sizing )
{
   Format radix = rios;

  // If a non-zero positive size is provided allocate space for it. Otherwise,
  // get the size and radix from the string contents and allocate space.
  initNumber( ( size ) ? size : getSizeWithRadix( number, radix ), sizing );

  readstr(*this,number);
}


//
// Create a new RNumber with the specified string value using the specified radix.
//
RNumber::RNumber (const string & number, Format radix, Sizing sizing) {
   initNumber (getSizeWithRadix (number, radix), sizing);

  // Read in the number based on the determined radix.
  readstr (*this,number,radix);
}


//
// Create a new RNumber with the specified string value but constrained
// to the specified size. If the size is 0, it will be determined by
// analyzing the string number for a prefix (such as 0x) or using the
// specified radix, in that order.
//
RNumber::RNumber( const string& number, unsigned int size, Format radix, Sizing sizing )
{
   Format r = radix;
  // If a non-zero positive size is provided allocate space for it. Otherwise,
  // get the size and radix from the string contents and allocate space.
  initNumber( ( size ) ? size : getSizeWithRadix( number, r ), sizing );

  // Read in the number based on the determined radix.
  readstr(*this,number,r);

  truncate( _size );
}

//
// Construct an RNumber taking an array of unsigned int values as data
//
RNumber::RNumber(const unsigned int* numVector, unsigned int wordCount, unsigned int size, Sizing sizing )
{
  // Update the RNumber internal members.
  _size = size;
  _wordCount = ( _size + WordBits - 1 ) / WordBits;
  _sizing = sizing;

  unsigned int i;

  if ( _wordCount <= WORD_THRESHOLD )
    {
      for ( i = 0; i < WORD_THRESHOLD; i++ )
        _value.fixedValue[i] = 0;

      _valueBuffer = _value.fixedValue + WORD_THRESHOLD - _wordCount;
    }
  else
    _valueBuffer = _value.varValue = new unsigned int[_wordCount];

  unsigned int* vb = _valueBuffer + _wordCount - 1;
  const unsigned int* nb = numVector + wordCount - 1;
  unsigned int n = ( wordCount < _wordCount ) ? wordCount : _wordCount;

  for ( i = 0; i < n; i++ )
    *(vb--) = *(nb--);

  if ( i < _wordCount )
    {
      while ( i < _wordCount )
        {
          *(vb--) = 0;
          i++;
        }
    }
  else
    truncateTop();
}

//
// The assignment operator takes only the value of the number and copies it.
// Our size is only modified if it needs to be enlarged to contain the 32-bit
// value and our _sizing is dynamic.
//
RNumber& RNumber::operator=( unsigned int number )
{

  // First clear out any most-significant words. Then assign the number to the
  // least significant word.
  for ( unsigned int i = 0; i < _wordCount - 1; i++ )
    _valueBuffer[i] = 0;

  _valueBuffer[_wordCount - 1] = number;

  // If assigning to a number of size less than an integer, resize the number
  // if it is too small to represent the value and the _sizing is dynamic.
  if ( _size < WordBits )
    {
      truncateInt( _size );

      if ( _valueBuffer[0] != number && _sizing == dynamic )
        {
          _size = WordBits;
          _valueBuffer[0] = number;
        }
    }

  return *this;
}


//
// The assignment operator takes only the value of the number and copies it.
// Our size is only modified if it needs to be extended to contain the value
// and the _sizing is dynamic.
//
RNumber& RNumber::operator=( const string& number )
{

   Format radix = rios;

  initNumber( getSizeWithRadix( number, radix ), _sizing );

  readstr(*this,number);

  return *this;
}


//
// The assignment operator takes only the value of the number and copies it.
// Our size is only modified if it needs to be extended to contain the value
// and the _sizing is dynamic.
//
RNumber& RNumber::operator=( const RNumber& number )
{

  assignNumber( number );

  return *this;
}


//
// Assign the value ignoring the _sizing state. Thus, a larger value will
// increase our size. This function will not change the _sizing state.
//
RNumber& RNumber::assign( const RNumber& number )
{

  Sizing oldSizing = _sizing;

  _sizing = dynamic;
  assignNumber( number );
  _sizing = oldSizing;

  return *this;
}


//
// Unlike the assignment operator, we copy the entire number's attributes.
//
RNumber& RNumber::copy( const RNumber& number )
{

  if ( _wordCount > WORD_THRESHOLD )
    delete [] _value.varValue;

  cloneNumber( number );

  return *this;
}


//
// Reset the RNumber back to initialized state with specified size and a value
// of zero. Note that because this function specifies a bit size, the RNumber
// will have its _sizing set to fixed, even if it was not set at construction.
//
void RNumber::resize( unsigned int size )
{

  // No sizes of zero for now.
  assert( size );

  const unsigned int nwc = ( size + WordBits - 1 ) / WordBits;
  unsigned int i = 0;

  if ( nwc == _wordCount )
    {
      // If the new size is smaller, truncate the top; otherwise, just assign
      // the new size.
      if ( size < _size )
        {
          _size = size;
          truncateTop();
        }
      else
        _size = size;
    }
  else if ( nwc < _wordCount )
    {
      // Since we are shrinking the size of the number, truncation will result.
      // Note that resizing requires special treatment if we are shrinking to a
      // size that crosses the WORD_THRESHOLD boundary. For this case, we need
      // to copy the contents into the fixed array and delete the memory that
      // was allocated.
      unsigned int wordDiff = _wordCount - nwc;

      if ( _wordCount > WORD_THRESHOLD && nwc <= WORD_THRESHOLD )
        {
          unsigned int* vb = _valueBuffer + wordDiff;
          unsigned int threshDiff = WORD_THRESHOLD - nwc;

          for ( i = 0; i < threshDiff; i++ )
            _value.fixedValue[i] = 0;

          for ( i = threshDiff; i < WORD_THRESHOLD; i++ )
            _value.fixedValue[i] = *vb++;

          delete [] _valueBuffer;
          _valueBuffer = _value.fixedValue + WORD_THRESHOLD - nwc;
        }
      else
        {
          if ( _wordCount <= WORD_THRESHOLD )
            for ( i = 0; i < wordDiff; i++ )
              _valueBuffer[i] = 0;

          _valueBuffer += wordDiff;
        }

      _wordCount = nwc;
      _size = size;
      truncateTop();
    }
  else
    {
      // In this final case, we need to enlarge the existing number. If the
      // resizing crosses over the WORD_THRESHOLD boundary, we need to copy from
      // the fixed array over to dynamically allocated memory.
      unsigned int wordDiff = nwc - _wordCount;

      if ( _wordCount <= WORD_THRESHOLD && nwc > WORD_THRESHOLD )
        {
          unsigned int* fv = _value.fixedValue + WORD_THRESHOLD - _wordCount;

          _valueBuffer = new unsigned int[nwc];

          for ( i = 0; i < wordDiff; i++ )
            _valueBuffer[i] = 0;

          for ( i = wordDiff; i < nwc; i++ )
            _valueBuffer[i] = *fv++;

          _value.varValue = _valueBuffer;
        }
      else if ( nwc <= WORD_THRESHOLD )
        _valueBuffer -= wordDiff;
      else
        {
          unsigned int* nvb = new unsigned int[nwc];
          unsigned int* vb = _valueBuffer;

          for ( i = 0; i < wordDiff; i++ )
            nvb[i] = 0;

          for ( i = wordDiff; i < nwc; i++ )
            nvb[i] = *vb++;

          delete [] _valueBuffer;
          _valueBuffer = _value.varValue = nvb;
        }

      _wordCount = nwc;
      _size = size;
      truncateTop();
    }

  _sizing = fixed;
}


//
// The minus sign unary operator.
//
const RNumber RNumber::operator-() const
{

  RNumber res( *this );
  res.negate();

  return res;
}


//
// Return an RNumber containing a bitwise inversion of our value.
//
const RNumber RNumber::operator~() const
{

  unsigned int* ivb = getTempBuffer( _wordCount );

  for ( unsigned int i = 0; i < _wordCount; i++ )
    ivb[i] = ~_valueBuffer[i];

  return RNumber( ivb, _wordCount, _size );
}


//
// Non-member function for adding two RNumbers.
//
inline const RNumber rnumber::add( const RNumber& n1, const RNumber& n2, bool extend )
{

  unsigned int maxs = max( n1._size, n2._size );
  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );
  unsigned int maxwc = max( n1wc, n2wc );

  // We add by traversing through each set of words, in parallel, adding as we go.
  // Thus, our starting position is the last word in each array (the lowest-order word).
  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  const unsigned int* numValue = n2._valueBuffer + n2wc - 1;
  // If we're extending, then the maximum we can grow is by one extra word.
  unsigned int* sumValue0 = getTempBuffer( ( extend ) ? maxwc + 1 : maxwc );
  // Position our sum pointer at the last word in the temporary buffer.
  unsigned int* sumValue = sumValue0 + ( ( extend ) ? maxwc : maxwc - 1 );

  unsigned int cin = 0;
  unsigned int a, b, c;
  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    {
      *sumValue = *value + *numValue + cin;
      a = *( value-- );
      b = *( numValue-- );
      c = *( sumValue-- );
      cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );
    }

  const unsigned int* leftOver = ( n1wc < n2wc ) ? numValue : value;

  for ( i = minwc; i < maxwc; i++ )
    {
      *sumValue = *leftOver + cin;
      a = *( leftOver-- );
      c = *( sumValue-- );
      cin = ( a & ~c ) >> ( WordBits - 1 );
    }

  if ( extend )
    {
      if ( cin && ( ( maxs - 1 ) % WordBits == WordBits - 1 ) )
        {
          // If we have a final carry-in, then this becomes a 1 
          // in the new word.  In this case, we have truly grown by
          // one word, so we make sure that we include it in the 
          // final RNumber.
          *sumValue = 1;
          maxwc++;
          maxs++;
        } else {
          if ( *( sumValue0 + 1 ) >> ( maxs % WordBits ) == 1 ) {
            // We've grown, but not into a new word, just by one bit
            // in the existing word.
            maxs++;
          }
          // We haven't grown by a whole word, so we make sure to 
          // ignore the extra word in our final RNumber.
          sumValue0++;
        }
    }

  return RNumber( sumValue0, maxwc, maxs );
}


//
// Non-member function for adding an RNumber and unsigned.
//
inline const RNumber rnumber::add( const RNumber& n1, unsigned int n2, bool extend )
{

  unsigned int maxs = max( n1._size, WordBits );
  unsigned int n1wc = n1._wordCount;

  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  unsigned int* sumValue0 = getTempBuffer( ( extend ) ? n1wc + 1 : n1wc );
  unsigned int* sumValue = sumValue0 + ( ( extend ) ? n1wc : n1wc - 1 );

  *sumValue = *value + n2;

  unsigned int a = *( value-- );
  unsigned int b = n2;
  unsigned int c = *( sumValue-- );
  unsigned int cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );

  for ( unsigned int i = 0; i < n1wc - 1; i++ )
    {
      *sumValue = *value + cin;
      a = *( value-- );
      c = *( sumValue-- );
      cin = ( a & ~c ) >> ( WordBits - 1 );
    }

  if ( extend )
    {
      if ( cin && ( ( maxs - 1 ) % WordBits == WordBits - 1 ) )
        {
          // If we have a final carry-in, then this becomes a 1 
          // in the new word.  In this case, we have truly grown by
          // one word, so we make sure that we include it in the 
          // final RNumber.
          *sumValue = 1;
          n1wc++;
          maxs++;
        } else {
          if ( *( sumValue0 + 1 ) >> ( maxs % WordBits ) == 1 ) {
            // We've grown, but not into a new word, just by one bit
            // in the existing word.
            maxs++;
          }
          // We haven't grown by a whole word, so we make sure to 
          // ignore the extra word in our final RNumber.
          sumValue0++;
        }
    }

  return RNumber( sumValue0, n1wc, maxs );
}


//
// Non-member function for the addition of two RNumbers.
//
const RNumber rnumber::operator+( const RNumber& n1, const RNumber& n2 )
{

  return add( n1, n2, false );
}


//
// Non-member function for the addition of an RNumber to an unsigned.
//
const RNumber rnumber::operator+( const RNumber& n1, unsigned int n2 )
{

  return add( n1, n2, false );
}


//
// Non-member function for the addition of an unsigned to an RNumber.
//
const RNumber rnumber::operator+( unsigned int n1, const RNumber& n2 )
{

  return add( n2, n1, false );
}


//
// Non-member function for the addition of two RNumbers. This add function
// will return a result that includes the carry.
//
const RNumber rnumber::addExt( const RNumber& n1, const RNumber& n2 )
{
  return add( n1, n2, true );
}


//
// Non-member function for the addition of an RNumber to an unsigned. This add
// function will return a result that includes the carry.
//
const RNumber rnumber::addExt( const RNumber& n1, unsigned int n2 )
{
  return add( n1, n2, true );
}


//
// Non-member function for the addition of an unsigned to an RNumber. This add
// function will return a result that includes the carry.
//
const RNumber rnumber::addExt( unsigned int n1, const RNumber& n2 )
{
  return add( n2, n1, true );
}


//
// The same as operator+ but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator+=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  unsigned int minwc = min( _wordCount, number._wordCount );
  unsigned int* value = _valueBuffer + _wordCount - 1;
  const unsigned int* numValue = number._valueBuffer + number._wordCount - 1;

  unsigned int cin = 0;
  unsigned int a, b, c;
  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    {
      a = *value;
      *value += *numValue + cin;
      b = *( numValue-- );
      c = *( value-- );
      cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );
    }

  for ( i = minwc; i < _wordCount; i++ )
    {
      a = *value;
      *value += cin;
      c = *( value-- );
      cin = ( a & ~c ) >> ( WordBits - 1 );
    }

  truncateTop();

  return *this;
}


//
// The same as operator+ but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator+=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  unsigned int* value = _valueBuffer + _wordCount - 1;
  unsigned int a = *value;

  *value += number;

  unsigned int b = number;
  unsigned int c = *( value-- );
  unsigned int cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );

  if ( cin )
    {
      for ( unsigned int i = 0; i < _wordCount - 1; i++ )
        {
          a = *value;
          *value += cin;
          c = *( value-- );
          cin = ( a & ~c ) >> ( WordBits - 1 );
        }
    }

  truncateTop();

  return *this;
}


//
// Non-member function for subtracting two RNumbers.
//
inline const RNumber rnumber::subtract( const RNumber& n1, const RNumber& n2 )
{

  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );
  const unsigned int maxwc = max( n1wc, n2wc );

  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  const unsigned int* numValue = n2._valueBuffer + n2wc - 1;
  unsigned int* diffValue0 = getTempBuffer( maxwc );
  unsigned int* diffValue = diffValue0 + maxwc - 1;

  unsigned int cin = 1;
  unsigned int inv;
  unsigned int a, b, c;
  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    {
      inv = ~( *( numValue-- ) );
      *diffValue = *value + inv + cin;
      a = *( value-- );
      b = inv;
      c = *( diffValue-- );
      cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );
    }

  if ( n1wc < n2wc )
    {
      for ( i = minwc; i < maxwc; i++ )
        {
          inv = ~( *( numValue-- ) );
          *diffValue = inv + cin;
          b = inv;
          c = *( diffValue-- );
          cin = ( b & ~c ) >> ( WordBits - 1 );
        }
    }
  else
    {
      for ( i = minwc; i < maxwc; i++ )
        {
          *diffValue = *value + cin - 1;
          a = *( value-- );
          c = *( diffValue-- );
          cin = ( a | ~c ) >> ( WordBits - 1 );
        }
    }

  return RNumber( diffValue0, maxwc, max( n1._size, n2._size ) );
}


//
// Non-member function for subtracting an unsigned from an RNumber.
//
inline const RNumber rnumber::subtract( const RNumber& n1, unsigned int n2 )
{

  const unsigned int n1wc = n1._wordCount;

  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  unsigned int* diffValue0 = getTempBuffer( n1wc );
  unsigned int* diffValue = diffValue0 + n1wc - 1;

  *diffValue = *value + ~n2 + 1;

  unsigned int a = *( value-- );
  unsigned int b = ~n2;
  unsigned int c = *( diffValue-- );
  unsigned int cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );

  for ( unsigned int i = 0; i < n1wc - 1; i++ )
    {
      *diffValue = *value + cin - 1;
      a = *( value-- );
      c = *( diffValue-- );
      cin = ( a | ~c ) >> ( WordBits - 1 );
    }

  return RNumber( diffValue0, n1wc, max( n1._size, WordBits ) );
}


//
// Non-member function for subtracting an RNumber from an unsigned.
//
inline const RNumber rnumber::subtract( unsigned int n1, const RNumber& n2 )
{

  const unsigned int n2wc = n2._wordCount;

  const unsigned int* numValue = n2._valueBuffer + n2wc - 1;
  unsigned int* diffValue0 = getTempBuffer( n2wc );
  unsigned int* diffValue = diffValue0 + n2wc - 1;

  unsigned int inv = ~( *( numValue-- ) );
  *diffValue = n1 + inv + 1;

  unsigned int a = n1;
  unsigned int b = inv;
  unsigned int c = *( diffValue-- );
  unsigned int cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );

  for ( unsigned int i = 0; i < n2wc - 1; i++ )
    {
      *diffValue = *numValue + cin - 1;
      a = *( numValue-- );
      c = *( diffValue-- );
      cin = ( a | ~c ) >> ( WordBits - 1 );
    }

  return RNumber( diffValue0, n2wc, max( n2._size, WordBits ) );
}


//
// Non-member function for the subtraction of two RNumbers.
//
const RNumber rnumber::operator-( const RNumber& n1, const RNumber& n2 )
{

  return subtract( n1, n2 );
}


//
// Non-member function for the subtraction of an unsigned from
// an RNumber.
//
const RNumber rnumber::operator-( const RNumber& n1, unsigned int n2 )
{

  return subtract( n1, n2 );
}


//
// Non-member function for the subtraction of an RNumber from
// an unsigned.
//
const RNumber rnumber::operator-( unsigned int n1, const RNumber& n2 )
{

  return subtract( n1, n2 );
}


//
// The same as operator- but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator-=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  unsigned int minwc = min( _wordCount, number._wordCount );
  unsigned int* value = _valueBuffer + _wordCount - 1;
  const unsigned int* numValue = number._valueBuffer + number._wordCount - 1;

  unsigned int cin = 1;
  unsigned int inv;
  unsigned int a, b, c;
  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    {
      a = *value;
      inv = ~( *( numValue-- ) );
      *value += inv + cin;
      b = inv;
      c = *( value-- );
      cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );
    }

  for ( i = minwc; i < _wordCount; i++ )
    {
      a = *value;
      *value += cin - 1;
      c = *( value-- );
      cin = ( a | ~c ) >> ( WordBits - 1 );
    }

  truncateTop();

  return *this;
}


//
//
// The same as operator- but the assignment allows us to optimize the code to
// not create temporary objects.
//
//
RNumber& RNumber::operator-=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  unsigned int* value = _valueBuffer + _wordCount - 1;
  unsigned int a = *value;

  *value += ~number + 1;

  unsigned int b = ~number;
  unsigned int c = *( value-- );
  unsigned int cin = ( ( a & b ) | ( ( a | b ) & ~c ) ) >> ( WordBits - 1 );

  for ( unsigned int i = 0; i < _wordCount - 1; i++ )
    {
      a = *value;
      *value += cin - 1;
      c = *( value-- );
      cin = ( a | ~c ) >> ( WordBits - 1 );
    }

  truncateTop();

  return *this;
}


//
// Non-member function for multiplying two RNumbers. It computes w = u * v,
// where u and v are arbitrarily sized numbers and w is the larger sized.
//
// Cases considered when computing u * v:
// 1. if u and v are <= word bits, use native multiply.
// 2. if u or v is = 0, result is 0.
// 3. if u or v is = 1, result is other operand.
// 4. extended multiply is necessary.
//
inline const RNumber rnumber::multiply( const RNumber& n1, const RNumber& n2, bool extend )
{

  unsigned int maxs = max( n1._size, n2._size );
  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  unsigned int maxwc = max( n1wc, n2wc );

  const unsigned int* n1vb = n1._valueBuffer;
  const unsigned int* n2vb = n2._valueBuffer;

  if ( n1wc == 1 && n2wc == 1 && !extend)
    return RNumber( n1vb[0] * n2vb[0],maxs );
  else if ( !n1 || !n2 )
    return RNumber( 0, maxs );
  else if ( n1 == 1 )
    return RNumber( n2, maxs );
  else if ( n2 == 1 )
    return RNumber( n1, maxs );

  unsigned int* resultValue0 = getTempBuffer( ( extend ) ? n1wc + n2wc : maxwc );

  // If the top operand is smaller than the bottom, swap them for speed.
  if ( n1wc < n2wc )
    multiplyExtended( n2vb, n2wc, n1vb, n1wc, resultValue0, extend );
  else
    multiplyExtended( n1vb, n1wc, n2vb, n2wc, resultValue0, extend );

  if ( extend )
    {
      maxs = skipLeadingZeroBits( resultValue0, (n1wc+n2wc)*WordBits );
      maxwc = ( maxs + WordBits - 1 ) / WordBits;
      resultValue0 += ((n1wc + n2wc) - maxwc );
    }

  return RNumber( resultValue0, maxwc, maxs );
}


//
// Non-member function for multiplying an RNumber and unsigned. It computes
// w = u * v, where u and v are arbitrarily sized numbers and w is the
// larger sized.
//
// Cases considered when computing u * v:
// 1. if u and v are <= word bits, use native multiply.
// 2. if u or v is = 0, result is 0.
// 3. if u or v is = 1, result is other operand.
// 4. extended multiply is necessary.
//
inline const RNumber rnumber::multiply( const RNumber& n1, unsigned int n2, bool extend )
{

  unsigned int maxs = max( n1._size, WordBits );
  unsigned int n1wc = n1._wordCount;
  const unsigned int* n1vb = n1._valueBuffer;

  if ( n1wc == 1 && !extend)
    return RNumber( n1vb[0] * n2, maxs );
  else if ( !n1 || !n2 )
    return RNumber( 0, maxs );
  else if ( n1 == 1 )
    return RNumber( n2, maxs );
  else if ( n2 == 1 )
    return RNumber( n1, maxs );

  int wc = (extend) ? n1wc + 1 : n1wc;
  unsigned int* resultValue0 = getTempBuffer( wc );

  multiplyExtended( n1vb, n1wc, &n2, 1, resultValue0, extend );

  if ( extend )
    {
      maxs = skipLeadingZeroBits( resultValue0, (wc)*WordBits );
      wc = ( maxs + WordBits - 1 ) / WordBits;
      resultValue0 += ((n1wc + 1) - wc );
    }

  return RNumber( resultValue0, wc, maxs );
}


//
// Non-member function for the multiplication of two RNumbers.
//
const RNumber rnumber::operator*( const RNumber& n1, const RNumber& n2 )
{

  return multiply( n1, n2, false );
}


//
// Non-member function for the multiplication of an RNumber and unsigned.
//
const RNumber rnumber::operator*( const RNumber& n1, unsigned int n2 )
{

  return multiply( n1, n2, false );
}


//
// Non-member function for the multiplication of an unsigned and RNumber.
//
const RNumber rnumber::operator*( unsigned int n1, const RNumber& n2 )
{

  return multiply( RNumber(n1), n2, false );
}


//
// Non-member function for the multiplication of two RNumbers. This multiply
// function will return the complete result.
//
const RNumber rnumber::multiplyExt( const RNumber& n1, const RNumber& n2 )
{

  return multiply( n1, n2, true );
}


//
// Non-member function for the multiplication of an RNumber and unsigned.
// This multiply function will return the complete result.
//
const RNumber rnumber::multiplyExt( const RNumber& n1, unsigned int n2 )
{

  return multiply( n1, n2, true );
}


//
// Non-member function for the multiplication of an unsigned and RNumber.
// This multiply function will return the complete result.
//
const RNumber rnumber::multiplyExt( unsigned int n1, const RNumber& n2 )
{

  return multiply( RNumber(n1), n2, true );
}


//
// The same as operator* but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator*=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  const unsigned int nwc = number._wordCount;
  const unsigned int maxwc = max( _wordCount, nwc );

  const unsigned int* nvb = number._valueBuffer;

  if ( _wordCount == 1 && nwc == 1 )
    {
      _valueBuffer[0] *= nvb[0];
      truncateTop();
    }
  else if ( !*this || !number )
    clearAll();
  else if ( *this == 1 )
    *this = number;
  else if ( number == 1 )
    ;
  else
    {
      unsigned int* resultValue0 = getTempBuffer( maxwc );
      unsigned int* resultValue = resultValue0;

      multiplyExtended( _valueBuffer, _wordCount, nvb, nwc, resultValue0, false );

      if ( _wordCount < number._wordCount )
        resultValue += number._wordCount - _wordCount;

      for ( unsigned int i = 0; i < _wordCount; i++ )
        _valueBuffer[i] = resultValue[i];

      truncateTop();
    }

  return *this;
}


//
// The same as operator* but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator*=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  if ( _wordCount == 1 )
    {
      _valueBuffer[0] *= number;
      truncateTop();
    }
  else if ( !*this || !number )
    clearAll();
  else if ( *this == 1 )
    *this = number;
  else if ( number == 1 )
    ;
  else
    {
      unsigned int* resultValue0 = getTempBuffer( _wordCount );

      multiplyExtended( _valueBuffer, _wordCount, &number, 1, resultValue0, false );

      for ( unsigned int i = 0; i < _wordCount; i++ )
        _valueBuffer[i] = resultValue0[i];

      truncateTop();
    }

  return *this;
}


//
// The extended multiply algorithm works as follows.
//   Each number can be represented as a sum of 16-bit coefficients times a power of 2**16:
//     a0 + a1*2**16 + a2*2**32 + a3*2**48 + ...
//     b0 + b1*2**16 + b2*2**32 + b3*2**48 + ...
//   The result of the multiplication can be written as:
//     a0*b0 + (a0*b1 + a1*b0)*2**16 + (a0*b2+a1*b1+a2*b0)*2**32 + (a0*b3+a1*b2+a2*b1+a3*b0)*2**48 + ...
//   Each of these multiplications can be performed by a native 32-bit multiply without
//   losing any output bits, and each result word can be computed by adding the multiplication
//   results appropriately so that carry-outs are propagated.
//
//   result words (order from least significant word on the left) as sums of products:
//         res0      |        res1          ...
//    ------------------------------------
//   |    a0*b0      |
//    ---------------------- 
//           |     a0*b1    |
//           |     a1*b0    |
//            ---------------------
//                   |    a0*b2    |
//                   |    a1*b1    |
//                   |    a2*b0    |
//                    --------------------
//                          |    a0*b3    |
//                          |    a1*b2    |
//                          |    a2*b1    |
//                          |    a3*b0    |
//                           -------------
//
// Following is pseudocode for the actual computation.  Note that for simplicity, the
// result array is written with the least significant word first.  In the actual code,
// the representation is most significant word first.
//
//    carry = 0
//    for (i = 0; i < 2*wordCount; i += 2)
//      lw = lowHalf (carry)
//      hw = highHalf (carry)
//      carry = 0
//      for (j = 0; j <= i; j++)
//        mult1 = a[j]*b[i-j]
//        mult2 = a[j]*b[i-j+1]
//        lw += lowHalf (mult1)
//        hw += lowHalf (mult2) + highHalf (mult1)
//        carry += highHalf (mult2)
//      mult2 = a[j+1]*b[0]
//      hw += lowHalf (mult2)
//      carry += highHalf (mult2)
//      hw += highHalf (lw)
//      carry += highHalf (hw)
//      result[i/2] = highLowConcat (lowHalf (hw), lowHalf (lw))
//
// Note1: This algorithm will not work on arbitrarily large numbers; at around
//        32768 words, carryouts from the adds will be lost.
//
// Note2: The word size of vb1 must *always* be >= the word size of vb2.
//
static void multiplyExtended( const unsigned int* vb1, unsigned int wc1,
                              const unsigned int* vb2, unsigned int wc2,
                              unsigned int* resValue0, bool extend )
{
  const unsigned int* valEnd = vb1 + wc1 - 1;
  const unsigned int* numEnd = vb2 + wc2 - 1;
  unsigned int maxwc = (extend) ? (wc1+wc2) : max( wc1, wc2 );
  unsigned int* resValue = resValue0 + maxwc - 1;
  const unsigned int* u;
  const unsigned int* v;
  unsigned int uj, vij, vij1;
  unsigned int lw, hw;
  unsigned int mult1, mult2;
  unsigned int carry = 0;
  unsigned int i2;

  for ( unsigned int i = 0; i < maxwc * 2; i += 2 )
    {
      i2 = i / 2;
      lw = lowHalf( carry );
      hw = highHalf( carry );
      carry = 0;
      // This is 'a' above.  It sweeps from least-significant to most-significant.
      // In the above algorithm, this is 0..n, but here, the word ordering is
      // swapped, so it's the reverse.
      u = valEnd;
      // This is 'b' above.  It sweeps from most-significant to least.  It's
      // possible that this number is smaller than the first, hence the various
      // checks below for v>=vb2- at first, we'll be referencing most-significant
      // words which don't exist, hence our pointer will be less than the start pointer.
      v = numEnd - i2;

      for ( unsigned int j = 0; j < i; j += 2 )
        {
          // If we're in extending-arithmetic mode, we might pass the
          // most-significant word.  In that case, we use 0.
          unsigned uval = (u < vb1) ? 0 : *u;
          // This does the first half of the word we're processing;
          // i.e. even indices in the pseudo code above.
          if ( v >= vb2 )
            {
              uj = lowHalf( uval );
              vij = lowHalf( *v );
              vij1 = highHalf( *v );

              mult1 = uj * vij;
              mult2 = uj * vij1;
              lw += lowHalf( mult1 );
              hw += highHalf( mult1 ) + lowHalf( mult2 );
              carry += highHalf( mult2 );
            }

          // This does the second half- the odd indices in the
          // pseudo code algorithm.
          if ( ( v + 1 ) >= vb2 )
            {
              uj = highHalf( uval );
              // We'll use 0 on the boundary condition.
              vij1 = ( v >= vb2 ) ? lowHalf( *v ) : 0;
              v++;
              vij = highHalf( *v );

              mult1 = uj * vij;
              mult2 = uj * vij1;
              lw += lowHalf( mult1 );
              hw += highHalf( mult1 ) + lowHalf( mult2 );
              carry += highHalf( mult2 );
            }
          else
            {
              // The sizes of the two items are not equal,
              // so we advance towards lower-sig words.
              v++;
            }
          // We advance towards more-significant bytes.
          u--;
        }

      unsigned uval = (u < vb1) ? 0 : *u;
      if ( v >= vb2 )
        {
          uj = lowHalf( uval );
          vij = lowHalf( *v );
          vij1 = highHalf( *v );

          mult1 = uj * vij;
          mult2 = uj * vij1;
          lw += lowHalf( mult1 );
          hw += highHalf( mult1 ) + lowHalf( mult2 );
          carry += highHalf( mult2 );
        }

      mult2 = highHalf( uval ) * lowHalf( *numEnd );
      hw += lowHalf( mult2 );
      carry += highHalf( mult2 );

      hw += highHalf( lw );
      carry += highHalf( hw );

      *( resValue-- ) = highLowConcat( lowHalf( hw ), lowHalf( lw ) );
      //cout << "res:  0x" << hex << highLowConcat( lowHalf( hw ), lowHalf( lw ) ) << endl;
    }
}


//
// Non-member function for dividing two RNumbers. It computes w = u / v,
// where u and v are arbitrarily sized numbers and w is the larger sized.
//
// Cases considered when computing u / v:
// 1. if u and v are <= word bits, use native divide.
// 2. if v is = 0, result is max word bits.
// 3. if v is = 1, result is u.
// 4. if v byte size is > u byte size after leading 0's are ignored,
//    result is 0.
// 5. if size of u and v are <= word bits after leading 0's are skipped,
//    use native divide on low words.
// 6. extended divide is necessary.
//
inline const RNumber rnumber::divide( const RNumber& n1, const RNumber& n2 )
{

  const unsigned int maxs = max( n1._size, n2._size );
  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int maxwc = max( n1wc, n2wc );

  const unsigned int* n1vb = n1._valueBuffer;
  const unsigned int* n2vb = n2._valueBuffer;

  if ( n1wc == 1 && n2wc == 1 )
    {
      unsigned int result = 0xffffffff;

      if ( n2vb[0] )
        result = n1vb[0] / n2vb[0];

      return RNumber( result, maxs );
    }
  else if ( n2 == 0 )
    {
      RNumber result( 0, maxs );
      result.setAll();

      return result;
    }
  else if ( n2 == 1 )
    return RNumber( n1, maxs );

  // Convert word-based representation to byte-based representation.  A separate
  // buffer is used so that it will work correctly on a little endian architecture.
  unsigned char* y = new unsigned char[n2wc * sizeof( unsigned int ) + 1];
  unsigned char* x = new unsigned char[n1wc * sizeof( unsigned int ) + 1];
  unsigned char* p = x;

  *( x++ ) = 0;
  convertToBytes( n1vb, x, n1wc );
  convertToBytes( n2vb, y, n2wc );

  // Skip leading zeros in both numbers.
  unsigned int xlen = skipLeadingZeroBytes( x, n1wc * sizeof( unsigned int ) );
  unsigned int ylen = skipLeadingZeroBytes( y, n2wc * sizeof( unsigned int ) );

  // Case 4.
  if ( xlen < ylen )
    {
      delete [] p;
      delete [] y;
      return RNumber( 0, maxs );
    }

  // Case 5.
  if ( xlen <= WordBytes && ylen <= WordBytes )
    {
      delete [] p;
      delete [] y;

      unsigned int v = n2vb[n2wc - 1];
      
      if ( v )
        return RNumber( n1vb[n1wc - 1] / v, maxs );
      else
        {
          RNumber result( 0, maxs );
          result.setAll();

          return result;
        }
    }

  unsigned char* xb = x + n1wc * sizeof( unsigned int ) - xlen;
  unsigned char* yb = y + n2wc * sizeof( unsigned int ) - ylen;
  unsigned char* q = (unsigned char*) getTempBuffer( maxwc * 2 );
  yb[ylen] = 0;   // in case ylen < 2

  divideExtended( xb, xlen, yb, ylen, q );

  delete [] p;
  delete [] y;

  // Convert byte-based result to word-based result.
  unsigned int* r = (unsigned int*) ( q + maxwc * sizeof( unsigned int ) );
  unsigned int* s = r + maxwc - 1;
  unsigned int shift = 0;

  p = q + xlen - ylen;
  *s = 0;

  for ( unsigned int i = 0; i <= xlen - ylen; i++ )
    {
      *s |= ( *( p-- ) << shift );
      shift = ( shift + 8 ) % 32;

      if ( shift == 0 )
        {
          s--;

          if ( s >= r )
            *s = 0;
        }
    }

  s--;

  while ( s >= r )
    *( s-- ) = 0;

  return RNumber( (unsigned int*) r, maxwc, maxs );
}


//
// Non-member function for dividing an RNumber and integer. It computes
// w = u / v, where u and v are arbitrarily sized numbers and w is the
// larger sized.
//
// Cases considered when computing u / v:
// 1. if u and v are <= word bits, use native divide.
// 2. if v is = 0, result is max word bits.
// 3. if v is = 1, result is u.
// 4. if v byte size is > u byte size after leading 0's are ignored,
//    result is 0.
// 5. if size of u and v are <= word bits after leading 0's are skipped,
//    use native divide on low words.
// 6. extended divide is necessary.
//
inline const RNumber rnumber::divide( const RNumber& n1, unsigned int n2 )
{

  const unsigned int maxs = max( n1._size, WordBits );
  const unsigned int n1wc = n1._wordCount;

  const unsigned int* n1vb = n1._valueBuffer;

  if ( n1wc == 1 )
    {
      unsigned int result = 0xffffffff;

      if ( n2 )
        result = n1vb[0] / n2;

      return RNumber( result, maxs );
    }
  else if ( n2 == 0 )
    {
      RNumber result( 0, maxs );
      result.setAll();

      return result;
    }
  else if ( n2 == 1 )
    return RNumber( n1, maxs );

  // Convert word-based representation to byte-based representation.  A separate
  // buffer is used so that it will work correctly on a little endian architecture.
  unsigned char* y = new unsigned char[sizeof( unsigned int ) + 1];
  unsigned char* x = new unsigned char[n1wc * sizeof( unsigned int ) + 1];
  unsigned char* p = x;

  *( x++ ) = 0;
  convertToBytes( n1vb, x, n1wc );
  convertToBytes( &n2, y, 1 );

  // Skip leading zeros in both numbers.
  unsigned int xlen = skipLeadingZeroBytes( x, n1wc * sizeof( unsigned int ) );
  unsigned int ylen = skipLeadingZeroBytes( y, sizeof( unsigned int ) );

  // Case 4.
  if ( xlen < ylen )
    {
      delete [] p;
      delete [] y;
      return RNumber( 0, maxs );
    }

  // Case 5.
  if ( xlen <= WordBytes )
    {
      delete [] p;
      delete [] y;
      
      if ( n2 )
        return RNumber( n1vb[n1wc - 1] / n2, maxs );
      else
        {
          RNumber result( 0, maxs );
          result.setAll();

          return result;
        }
    }

  unsigned char* xb = x + n1wc * sizeof( unsigned int ) - xlen;
  unsigned char* yb = y + sizeof( unsigned int ) - ylen;
  unsigned char* q = (unsigned char*) getTempBuffer( n1wc * 2 );
  yb[ylen] = 0;   // in case ylen < 2

  divideExtended( xb, xlen, yb, ylen, q );

  delete [] p;
  delete [] y;

  // Convert byte-based result to word-based result.
  unsigned int* r = (unsigned int*) ( q + n1wc * sizeof( unsigned int ) );
  unsigned int* s = r + n1wc - 1;
  unsigned int shift = 0;

  p = q + xlen - ylen;
  *s = 0;

  for ( unsigned int i = 0; i <= xlen - ylen; i++ )
    {
      *s |= ( *( p-- ) << shift );
      shift = ( shift + 8 ) % 32;

      if ( shift == 0 )
        {
          s--;

          if ( s >= r )
            *s = 0;
        }
    }

  s--;

  while ( s >= r )
    *( s-- ) = 0;

  return RNumber( (unsigned int*) r, n1wc, maxs );
}


//
// Non-member function for dividing an RNumber and integer. It computes
// w = u / v, where u and v are arbitrarily sized numbers and w is the
// larger sized.
//
// Cases considered when computing u / v:
// 1. if u and v are <= word bits, use native divide.
// 2. if v is = 0, result is max word bits.
// 3. if v is = 1, result is u.
// 4. if v byte size is > u byte size after leading 0's are ignored,
//    result is 0.
// 5. if size of u and v are <= word bits after leading 0's are skipped,
//    use native divide on low words.
// 6. extended divide is necessary.
//
inline const RNumber rnumber::divide( unsigned int n1, const RNumber& n2 )
{

  const unsigned int maxs = max( WordBits, n2._size );
  const unsigned int n2wc = n2._wordCount;

  const unsigned int* n2vb = n2._valueBuffer;

  if ( n2wc == 1 )
    {
      unsigned int result = 0xffffffff;

      if ( n2vb[0] )
        result = n1 / n2vb[0];

      return RNumber( result, maxs );
    }
  else if ( n2 == 0 )
    {
      RNumber result( 0, maxs );
      result.setAll();

      return result;
    }
  else if ( n2 == 1 )
    return RNumber( n1, maxs );

  // Convert word-based representation to byte-based representation.  A separate
  // buffer is used so that it will work correctly on a little endian architecture.
  unsigned char* y = new unsigned char[n2wc * sizeof( unsigned int ) + 1];
  unsigned char* x = new unsigned char[sizeof( unsigned int ) + 1];
  unsigned char* p = x;

  *( x++ ) = 0;
  convertToBytes( &n1, x, 1 );
  convertToBytes( n2vb, y, n2wc );

  // Skip leading zeros in both numbers.
  unsigned int xlen = skipLeadingZeroBytes( x, sizeof( unsigned int ) );
  unsigned int ylen = skipLeadingZeroBytes( y, n2wc * sizeof( unsigned int ) );

  // Case 4.
  if ( xlen < ylen )
    {
      delete [] p;
      delete [] y;
      return RNumber( 0, maxs );
    }

  // Case 5.
  if ( ylen <= WordBytes )
    {
      delete [] p;
      delete [] y;

      unsigned int v = n2vb[n2wc - 1];
      
      if ( v )
        return RNumber( n1 / v, maxs );
      else
        {
          RNumber result( 0, maxs );
          result.setAll();

          return result;
        }
    }

  unsigned char* xb = x + sizeof( unsigned int ) - xlen;
  unsigned char* yb = y + n2wc * sizeof( unsigned int ) - ylen;
  unsigned char* q = (unsigned char*) getTempBuffer( n2wc * 2 );
  yb[ylen] = 0;   // in case ylen < 2

  divideExtended( xb, xlen, yb, ylen, q );

  delete [] p;
  delete [] y;

  // Convert byte-based result to word-based result.
  unsigned int* r = (unsigned int*) ( q + n2wc * sizeof( unsigned int ) );
  unsigned int* s = r + n2wc - 1;
  unsigned int shift = 0;

  p = q + xlen - ylen;
  *s = 0;

  for ( unsigned int i = 0; i <= xlen - ylen; i++ )
    {
      *s |= ( *( p-- ) << shift );
      shift = ( shift + 8 ) % 32;

      if ( shift == 0 )
        {
          s--;

          if ( s >= r )
            *s = 0;
        }
    }

  s--;

  while ( s >= r )
    *( s-- ) = 0;

  return RNumber( (unsigned int*) r, n2wc, maxs );
}


//
// Non-member function for the division of two RNumbers.
//
const RNumber rnumber::operator/( const RNumber& n1, const RNumber& n2 )
{

  return divide( n1, n2 );
}


//
// Non-member function for the division of an RNumber and unsigned.
//
const RNumber rnumber::operator/( const RNumber& n1, unsigned int n2 )
{

  return divide( n1, n2 );
}


//
// Non-member function for the division of an unsigned and RNumber.
//
const RNumber rnumber::operator/( unsigned int n1, const RNumber& n2 )
{

  return divide( n1, n2 );
}


//
// The same as operator/ but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator/=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  const unsigned int nwc = number._wordCount;
  const unsigned int maxwc = max( _wordCount, number._wordCount );
  const unsigned int* nvb = number._valueBuffer;

  if ( _wordCount == 1 && nwc == 1 )
    {
      // Case 1.
      if ( nvb[0] )
        _valueBuffer[0] /= nvb[0];
      else
        _valueBuffer[0] = 0xffffffff;

      truncateTop();

      return *this;
    }
  else if ( number <= 1 )
    {
      // Cases 2 and 3.
      if ( !number )
        setAll();

      return *this;
    }

  // Convert word-based representation to byte-based representation.  A separate
  // buffer is used so that it will work correctly on a little endian architecture.
  unsigned char* y = new unsigned char[nwc * sizeof( unsigned int ) + 1];
  unsigned char* x = new unsigned char[_wordCount * sizeof( unsigned int ) + 1];
  unsigned char* p = x;

  *( x++ ) = 0;
  convertToBytes( _valueBuffer, x, _wordCount );
  convertToBytes( nvb, y, nwc );

  // Skip leading zeros in both numbers.
  unsigned int xlen = skipLeadingZeroBytes( x, _wordCount * sizeof( unsigned int ) );
  unsigned int ylen = skipLeadingZeroBytes( y, nwc * sizeof( unsigned int ) );

  // Case 4.
  if ( xlen < ylen )
    {
      delete [] p;
      delete [] y;

      clearAll();

      return *this;
    }

  // Case 5.
  if ( xlen <= WordBytes && ylen <= WordBytes )
    {
      delete [] p;
      delete [] y;

      unsigned int v = nvb[nwc - 1];

      if ( v )
        _valueBuffer[_wordCount - 1] /= v;
      else
        setAll( );

      return *this;
    }

  unsigned char* xb = x + _wordCount * sizeof( unsigned int ) - xlen;
  unsigned char* yb = y + nwc * sizeof( unsigned int ) - ylen;
  unsigned char* q = (unsigned char*) getTempBuffer( maxwc );
  yb[ylen] = 0;   // in case ylen < 2

  divideExtended( xb, xlen, yb, ylen, q );

  delete [] p;
  delete [] y;

  // Convert byte-based result to word-based result
  unsigned int* s = _valueBuffer + _wordCount - 1;
  unsigned int shift = 0;
  p = q + xlen - ylen;
  *s = 0;

  for ( unsigned int i = 0; i <= xlen - ylen; i++ )
    {
      *s |= ( *( p-- ) << shift );
      shift = ( shift + 8 ) % 32;

      if ( shift == 0 )
        {
          s--;

          if ( s >= _valueBuffer )
            *s = 0;
        }
    }

  s--;

  while ( s >= _valueBuffer )
    *( s-- ) = 0;

  return *this;
}


//
// The same as operator/ but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator/=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  if ( _wordCount == 1 )
    {
      // Case 1.
      if ( number )
        _valueBuffer[0] /= number;
      else
        _valueBuffer[0] = 0xffffffff;

      truncateTop();

      return *this;
    }
  else if ( number <= 1 )
    {
      // Cases 2 and 3.
      if ( !number )
        setAll();

      return *this;
    }

  // Convert word-based representation to byte-based representation.  A separate
  // buffer is used so that it will work correctly on a little endian architecture.
  unsigned char* y = new unsigned char[sizeof( unsigned int ) + 1];
  unsigned char* x = new unsigned char[_wordCount * sizeof( unsigned int ) + 1];
  unsigned char* p = x;

  *( x++ ) = 0;
  convertToBytes( _valueBuffer, x, _wordCount );
  convertToBytes( &number, y, 1 );

  // Skip leading zeros in both numbers.
  unsigned int xlen = skipLeadingZeroBytes( x, _wordCount * sizeof( unsigned int ) );
  unsigned int ylen = skipLeadingZeroBytes( y, sizeof( unsigned int ) );

  // Case 4.
  if ( xlen < ylen )
    {
      delete [] p;
      delete [] y;

      clearAll();

      return *this;
    }

  // Case 5.
  if ( xlen <= WordBytes )
    {
      delete [] p;
      delete [] y;

      if ( number )
        _valueBuffer[_wordCount - 1] /= number;
      else
        setAll();

      return *this;
    }

  unsigned char* xb = x + _wordCount * sizeof( unsigned int ) - xlen;
  unsigned char* yb = y + sizeof( unsigned int ) - ylen;
  unsigned char* q = (unsigned char*) getTempBuffer( _wordCount );
  yb[ylen] = 0;   // in case ylen < 2

  divideExtended( xb, xlen, yb, ylen, q );

  delete [] p;
  delete [] y;

  // Convert byte-based result to word-based result
  unsigned int* s = _valueBuffer + _wordCount - 1;
  unsigned int shift = 0;
  p = q + xlen - ylen;
  *s = 0;

  for ( unsigned int i = 0; i <= xlen - ylen; i++ )
    {
      *s |= ( *( p-- ) << shift );
      shift = ( shift + 8 ) % 32;

      if ( shift == 0 )
        {
          s--;

          if ( s >= _valueBuffer )
            *s = 0;
        }
    }

  s--;

  while ( s >= _valueBuffer )
    *( s-- ) = 0;

  return *this;
}


//
// The extended divide algorithm is the following:
//   The algorithm works on a byte buffer representation of the inputs and
//   computes a single byte of the output at a time.  Each byte is computed
//   from most significant to least by dividing the top 3 bytes of the current
//   dividend by the top 2 bytes of the divisor.  The resultant byte is either
//   the correct value for the current byte of the result, or is 1 higher than
//   the correct value.  The current dividend is adjusted for the next step by
//   a multiplication of the computed byte by the divisor, then a subtraction.
//   If this results in a negative dividend, then the computed byte is 1 too high
//   and is adjusted, and the dividend is readjusted to the correct value for the
//   next iteration:
//       for (i = 0; i < result_bytes; i++)
//         byte[i] = dividend[i-1:i+1] / divisor[0:1]
//         dividend = dividend - divisor * byte[i] (with appropriate shifting)
//         if dividend negative
//            byte[i]--
//            dividend = dividend + divisor
//
static void divideExtended( unsigned char* xb, unsigned int xlen, unsigned char* yb, unsigned int ylen,
                            unsigned char* q )
{
  unsigned int qk;    // qk is a guess for q[k] such that q[k] = qk or qk - 1.
  unsigned int x3;    // most significant 3 bytes of x
  unsigned int y2;    // most significant 2 bytes of y.

  y2 = ( yb[0] << ByteBits ) + yb[1];

  // Find each q[k]. qk is a guess for q[k] such that q[k] = qk or qk - 1.
  // Find qk by just using 2 bytes of y and 3 bytes of x.
  for ( unsigned int k = 0; k <= xlen - ylen; k++ )
    {
      x3 = ( xb[k - 1] << ( 2 * ByteBits ) ) + ( xb[k] << ByteBits ) + xb[k + 1];
      qk = x3 / y2;

      // qk cannot be larger than the largest value in ByteRadix.
      if ( qk >= ByteRadix )
        qk = ByteRadix - 1;

      // Determine if q[k] = qk or qk - 1.
      if ( qk )
        {
          int carry;
          int carry2;
          int diff;
          unsigned char* xk;

          // A shortcut for x[k].
          xk = xb + k;

          // adjust dividend based on divisor byte:
          //   x = x - y * qk;
          carry = 0;

          for ( int i = ylen - 1; i >= 0; i-- )
            {
              carry += yb[i] * qk;
              diff = ( xk[i] + ByteRadix ) - ( carry & ByteMask );
              xk[i] = (unsigned char) ( diff & ByteMask );
              carry = ( carry >> ByteBits ) + ( 1 - ( diff >> ByteBits ) );
            }

          if ( carry )
            {
              // extend the carry out to the most significant byte.
              carry = ( xk[-1] + ByteRadix ) - carry;
              xk[-1] = (unsigned char) ( carry & ByteMask );
              carry = 1 - ( carry >> ByteBits );
        
              if ( carry )
                {
                  // qk was one too large, so decrement it.
                  --qk;
        
                  // re-adjust dividend for correct divisor byte:
                  //    x = x - y * (qk - 1) 
                  //      = x - y * qk + y 
                  //      = x_above + y.
                  carry2 = 0;

                  for ( int i = ylen - 1; i >= 0; i-- )
                    {
                      carry2 += xk[i] + yb[i];
                      xk[i] = (unsigned char) ( carry2 & ByteMask );
                      carry2 >>= ByteBits;
                    }

                  if ( carry2 )
                    xk[-1] = (unsigned char) ( ( xk[-1] + 1 ) & ByteMask );

                }
            }
        }
      q[k] = (unsigned char) qk;
    }
}


//
// Non-member function for the modulus of two RNumbers.
//
inline const RNumber rnumber::mod( const RNumber& n1, const RNumber& n2 )
{

  RNumber result( 0, n2._size );

  result = n1 - ( n1 / n2 ) * n2;

  return result;
}


//
// Non-member function for the modulus of an RNumber using an unsigned.
//
inline const RNumber rnumber::mod( const RNumber& n1, unsigned int n2 )
{

  RNumber result( 0, WordBits );

  result = n1 - ( n1 / n2 ) * n2;

  return result;
}


//
// Non-member function for the modulus of an unsigned using an RNumber.
//
inline const RNumber rnumber::mod( unsigned int n1, const RNumber& n2 )
{

  RNumber result( 0, n2._size );

  result = n1 - ( n1 / n2 ) * n2;

  return result;
}


//
// Non-member function for the modulus of two RNumbers.
//
const RNumber rnumber::operator%( const RNumber& n1, const RNumber& n2 )
{

  return mod( n1, n2 );
}


//
// Non-member function for the modulus of an RNumber and unsigned.
//
const RNumber rnumber::operator%( const RNumber& n1, unsigned int n2 )
{

  return mod( n1, n2 );
}


//
// Non-member function for the modulus of an unsigned and RNumber.
//
const RNumber rnumber::operator%( unsigned int n1, const RNumber& n2 )
{

  return mod( n1, n2 );
}


//
// The same as operator% but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator%=( const RNumber& number )
{

  *this -= ( *this / number ) * number;

  return *this;
}


//
// The same as operator% but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator%=( unsigned int number )
{

  *this -= ( *this / number ) * number;

  return *this;
}


//
// Non-member function for bit-wise ANDing two RNumbers.
//
inline const RNumber rnumber::bitWiseAnd( const RNumber& n1, const RNumber& n2 )
{

  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );
  const unsigned int maxwc = max( n1wc, n2wc );

  const unsigned int* value    = n1._valueBuffer + n1wc - 1;
  const unsigned int* numValue = n2._valueBuffer + n2wc - 1;
  unsigned int* resValue0 = getTempBuffer( maxwc );
  unsigned int* resValue = resValue0 + maxwc - 1;

  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    *( resValue-- ) = *( value-- ) & *( numValue-- );

  for ( i = minwc; i < maxwc; i++ )
    *( resValue-- ) = 0;

  return RNumber( resValue0, maxwc, max( n1._size, n2._size ) );
}


//
// Non-member function for bit-wise ANDing an RNumber and unsigned.
//
inline const RNumber rnumber::bitWiseAnd( const RNumber& n1, unsigned int n2 )
{

  const unsigned int n1wc = n1._wordCount;

  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  unsigned int* resValue0 = getTempBuffer( n1wc );
  unsigned int* resValue = resValue0 + n1wc - 1;

  *( resValue-- ) = *value & n2;

  for ( unsigned int i = 1; i < n1wc; i++ )
    *( resValue-- ) = 0;

  return RNumber( resValue0, n1wc, max( n1._size, WordBits ) );
}


//
// Non-member function for bit-wise ANDing two RNumbers.
//
const RNumber rnumber::operator&( const RNumber& n1, const RNumber& n2 )
{

  return bitWiseAnd( n1, n2 );
}


//
// Non-member function for bit-wise ANDing an RNumber and unsigned.
//
const RNumber rnumber::operator&( const RNumber& n1, unsigned int n2 )
{

  return bitWiseAnd( n1, n2 );
}


//
// Non-member function for bit-wise ANDing an unsigned and RNumber.
//
const RNumber rnumber::operator&( unsigned int n1, const RNumber& n2 )
{

  return bitWiseAnd( n2, n1 );
}


//
// The same as operator& but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator&=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  unsigned int minwc = min( _wordCount, number._wordCount );
  unsigned int* value = _valueBuffer + _wordCount - 1;
  const unsigned int* numValue = number._valueBuffer + number._wordCount - 1;

  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    *( value-- ) &= *( numValue-- );

  for ( i = minwc; i < _wordCount; i++ )
    *( value-- ) = 0;

  return *this;
}


//
// The same as operator& but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator&=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  unsigned int* value = _valueBuffer;

  for ( unsigned int i = 0; i < _wordCount - 1; i++ )
    *( value++ ) = 0;

  *value &= number;

  return *this;
}


//
// Non-member function for bit-wise ORing two RNumbers.
//
inline const RNumber rnumber::bitWiseOr( const RNumber& n1, const RNumber& n2 )
{

  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );
  const unsigned int maxwc = max( n1wc, n2wc );

  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  const unsigned int* numValue = n2._valueBuffer + n2wc - 1;
  unsigned int* resValue0 = getTempBuffer( maxwc );
  unsigned int* resValue = resValue0 + maxwc - 1;

  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    *( resValue-- ) = *( value-- ) | *( numValue-- );

  if ( n1wc < n2wc )
    for ( i = minwc; i < maxwc; i++ )
      *( resValue-- ) = *( numValue-- );
  else
    for ( i = minwc; i < maxwc; i++ )
      *( resValue-- ) = *( value-- );

  return RNumber( resValue0, maxwc, max( n1._size, n2._size ) );
}


//
// Non-member function for bit-wise ORing two RNumbers.
//
inline const RNumber rnumber::bitWiseOr( const RNumber& n1, unsigned int n2 )
{

  const unsigned int n1wc = n1._wordCount;

  const unsigned int* value = n1._valueBuffer;
  unsigned int* resValue0 = getTempBuffer( n1wc );
  unsigned int* resValue = resValue0;

  for ( unsigned int i = 0; i < n1wc - 1; i++ )
    *( resValue++ ) = *( value++ );

  *resValue = *value | n2;

  return RNumber( resValue0, n1wc, max( n1._size, WordBits ) );
}


//
// Non-member function for bit-wise ORing two RNumbers.
//
const RNumber rnumber::operator|( const RNumber& n1, const RNumber& n2 )
{

  return bitWiseOr( n1, n2 );
}


//
// Non-member function for bit-wise ORing an RNumber and unsigned.
//
const RNumber rnumber::operator|( const RNumber& n1, unsigned int n2 )
{

  return bitWiseOr( n1, n2 );
}


//
// Non-member function for bit-wise ORing an unsigned and RNumber.
//
const RNumber rnumber::operator|( unsigned int n1, const RNumber& n2 )
{

  return bitWiseOr( n2, n1 );
}


//
// The same as operator| but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator|=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  unsigned int minwc = min( _wordCount, number._wordCount );
  unsigned int* value = _valueBuffer + _wordCount - 1;
  const unsigned int* numValue = number._valueBuffer + number._wordCount - 1;

  for ( unsigned int i = 0; i < minwc; i++ )
    *( value-- ) |= *( numValue-- );

  truncateTop();

  return *this;
}


//
// The same as operator| but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator|=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  unsigned int* value = _valueBuffer + _wordCount - 1;

  *value |= number;

  if ( _wordCount == 1 )
    truncateTop();

  return *this;
}

//
// Non-member function for bit-wise XORing two RNumbers.
//
inline const RNumber rnumber::bitWiseXor( const RNumber& n1, const RNumber& n2 )
{

  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );
  const unsigned int maxwc = max( n1wc, n2wc );

  const unsigned int* value = n1._valueBuffer + n1wc - 1;
  const unsigned int* numValue = n2._valueBuffer + n2wc - 1;
  unsigned int* resValue0 = getTempBuffer( maxwc );
  unsigned int* resValue = resValue0 + maxwc - 1;

  unsigned int i;

  for ( i = 0; i < minwc; i++ )
    *( resValue-- ) = *( value-- ) ^ *( numValue-- );

  if ( n1wc < n2wc )
    for ( i = minwc; i < maxwc; i++ )
      *( resValue-- ) = *( numValue-- );
  else
    for ( i = minwc; i < maxwc; i++ )
      *( resValue-- ) = *( value-- );

  return RNumber( resValue0, maxwc, max( n1._size, n2._size ) );
}


//
// Non-member function for bit-wise XORing an RNumber and an unsigned.
//
inline const RNumber rnumber::bitWiseXor( const RNumber& n1, unsigned int n2 )
{

  const unsigned int n1wc = n1._wordCount;

  const unsigned int* value = n1._valueBuffer;
  unsigned int* resValue0 = getTempBuffer( n1wc );
  unsigned int* resValue = resValue0;

  for ( unsigned int i = 0; i < n1wc - 1; i++ )
    *( resValue++ ) = *( value++ );

  *resValue = *value ^ n2;

  return RNumber( resValue0, n1wc, max( n1._size, WordBits ) );
}


//
// Non-member function for bit-wise XORing two RNumbers.
//
const RNumber rnumber::operator^( const RNumber& n1, const RNumber& n2 )
{

  return bitWiseXor( n1, n2 );
}


//
// Non-member function for bit-wise XORing an RNumber and unsigned.
//
const RNumber rnumber::operator^( const RNumber& n1, unsigned int n2 )
{

  return bitWiseXor( n1, n2 );
}


//
// Non-member function for bit-wise XORing an unsigned and RNumber.
//
const RNumber rnumber::operator^( unsigned int n1, const RNumber& n2 )
{

  return bitWiseXor( n2, n1 );
}


//
// The same as operator^ but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator^=( const RNumber& number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < number._size )
    resize( number._size );

  unsigned int minwc = min( _wordCount, number._wordCount );
  unsigned int* value = _valueBuffer + _wordCount - 1;;
  const unsigned int* numValue = number._valueBuffer + number._wordCount - 1;

  for ( unsigned int i = 0; i < minwc; i++ )
    *( value-- ) ^= *( numValue-- );

  truncateTop();

  return *this;
}


//
// The same as operator^ but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator^=( unsigned int number )
{

  // If the right operand is larger than us and our sizing is dynamic,
  // enlarge our size to match the right operand.
  if ( _sizing == dynamic && _size < WordBits )
    resize( WordBits );

  unsigned int* value = _valueBuffer + _wordCount - 1;

  *value ^= number;

  if ( _wordCount == 1 )
    truncateTop();

  return *this;
}


//
// Non-member function for left shifting an RNumber using an RNumber.
//
inline const RNumber rnumber::leftShift( const RNumber& n, const RNumber& shift, bool extend )
{
  unsigned int ns = n._size;
  const unsigned int totals = ns + shift.uint32();
  unsigned int nwc = n._wordCount;
  const unsigned int totalwc = nwc + ( shift.uint32() / WordBits ) + 1;

  const unsigned int* value = n._valueBuffer + nwc - 1;
  unsigned alloc  = (extend) ? totalwc : nwc;
  unsigned adjust = (extend) ? (totalwc - nwc) : 0;
  unsigned int* resValue0 = getTempBuffer( alloc );
  unsigned int* resValue = resValue0 + alloc - 1;

  unsigned int i;

  if ( shift < n._size || extend )
    {
      if ( shift == 0 )
        {
          for ( i = 0; i < nwc; i++ )
            *( resValue-- ) = *( value-- );
          // We didn't use the extra space, so we 
          // make sure that we don't count it in the
          // final result.
          resValue0 += adjust;
        }
      else if ( shift < WordBits )
        {
          unsigned int intShift = shift.uint32();
          int invShift = WordBits - intShift;
          unsigned int mask = ( 0x1 << intShift ) - 1;
          unsigned int cin = 0;

          if ( extend )
            {
              nwc = totalwc;
              ns = totals;
            }

          for ( i = 0; i < nwc; i++ )
            {
              *( resValue-- ) = ( *value << intShift ) | cin;
              cin = ( *( value-- ) >> invShift ) & mask;
            }
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int offset = shift.uint32() / WordBits;

          if ( extend )
            {
              nwc = totalwc;
              ns = totals;
            }

          for ( i = 0; i < offset; i++ )
            *( resValue-- ) = 0;

          for ( i = offset; i < nwc; i++ )
            *( resValue-- ) = *( value-- );
        }
      else if ( extend )
        return leftShiftExt( leftShiftExt( n, shift % WordBits ), shift - ( shift % WordBits ) );
      else
        return ( n << ( shift % WordBits ) ) << ( shift - ( shift % WordBits ) );
    }
  else
    {
      for ( i = 0; i < nwc; i++ )
        *( resValue-- ) = 0;
    }

  return RNumber( resValue0, nwc, ns );
}


//
// Non-member function for left shifting an RNumber using an unsigned.
//
inline const RNumber rnumber::leftShift( const RNumber& n, unsigned int shift, bool extend )
{
  unsigned int ns = n._size;
  const unsigned int totals = ns + shift;
  unsigned int nwc = n._wordCount;
  const unsigned int totalwc = nwc + ( shift / WordBits ) + 1;

  const unsigned int* value = n._valueBuffer + nwc - 1;
  unsigned alloc  = (extend) ? totalwc : nwc;
  unsigned adjust = (extend) ? (totalwc - nwc) : 0;
  unsigned int* resValue0 = getTempBuffer( alloc );
  unsigned int* resValue = resValue0 + alloc - 1;

  unsigned int i;

  if ( shift < n._size || extend )
    {
      if ( shift == 0 )
        {
          for ( i = 0; i < nwc; i++ )
            *( resValue-- ) = *( value-- );
          // We didn't use the extra space, so we 
          // make sure that we don't count it in the
          // final result.
          resValue0 += adjust;
        }
      else if ( shift < WordBits )
        {
          int invShift = WordBits - shift;
          unsigned int mask = ( 1 << shift ) - 1;
          unsigned int cin = 0;

          if ( extend )
            {
              nwc = totalwc;
              ns = totals;
            }

          for ( i = 0; i < nwc; i++ )
            {
              *( resValue-- ) = ( *value << shift ) | cin;
              cin = ( *( value-- ) >> invShift ) & mask;
            }
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int offset = shift / WordBits;

          if ( extend )
            {
              nwc = totalwc;
              ns = totals;
            }

          for ( i = 0; i < offset; i++ )
            *( resValue-- ) = 0;

          for ( i = offset; i < nwc; i++ )
            *( resValue-- ) = *( value-- );
        }
      else if ( extend )
        {
          return leftShiftExt( leftShiftExt( n, shift % WordBits ), shift - ( shift % WordBits ) );
        }
      else
        {
          return ( n << ( shift % WordBits ) ) << ( shift - ( shift % WordBits ) );
        }
    }
  else
    {
      for ( i = 0; i < nwc; i++ )
        *( resValue-- ) = 0;
    }

  return RNumber( resValue0, nwc, ns );
}


//
// Non-member function for left shifting an unsigned using an RNumber.
//
inline const RNumber rnumber::leftShift( unsigned int n, const RNumber& shift, bool extend )
{

  unsigned int* resValue0 = getTempBuffer( 1 );

  if ( shift == 0 )
    *resValue0 = n;
  else if ( shift < WordBits )
    *resValue0 = n << shift.uint32();
  else
    *resValue0 = 0;

  return RNumber( resValue0, 1, WordBits );
}


//
// Non-member function for left shifting an RNumber with an RNumber.
//
const RNumber rnumber::operator<<( const RNumber& n1, const RNumber& n2 )
{

  return leftShift( n1, n2, false );
}


//
// Non-member function for left shifting an RNumber with an unsigned.
//
const RNumber rnumber::operator<<( const RNumber& n1, unsigned int n2 )
{
  return leftShift( n1, n2, false );
}


//
// Non-member function for left shifting an unsigned with an RNumber.
//
const RNumber rnumber::operator<<( unsigned int n1, const RNumber& n2 )
{

  return leftShift( n1, n2, false );
}


//
// Non-member function for left shifting an RNumber with an RNumber.
//
const RNumber rnumber::leftShiftExt( const RNumber& n1, const RNumber& n2 )
{

  return leftShift( n1, n2, true );
}


//
// Non-member function for left shifting an RNumber with an unsigned.
//
const RNumber rnumber::leftShiftExt( const RNumber& n1, unsigned int n2 )
{

  return leftShift( n1, n2, true );
}


//
// Non-member function for left shifting an unsigned with an RNumber.
//
const RNumber rnumber::leftShiftExt( unsigned int n1, const RNumber& n2 )
{

  return leftShift( n1, n2, true );
}


//
// The same as operator<< but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator<<=( const RNumber& shift )
{

  unsigned int i;

  if ( shift < _size )
    {
      if ( shift < WordBits )
        {
          unsigned int* value = _valueBuffer + _wordCount - 1;
          unsigned int intShift = shift.uint32();
          int invShift = WordBits - intShift;
          unsigned int mask = ( 1 << intShift ) - 1;
          unsigned int cin = 0;
          unsigned int old;

          for ( i = 0; i < _wordCount; i++ )
            {
              old = *value;
              *value = ( *value << intShift ) | cin;
              value--;
              cin = ( old >> invShift ) & mask;
            }

          truncateTop();
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int* value = _valueBuffer;
          unsigned int offset = shift.uint32() / WordBits;

          for ( i = offset; i < _wordCount; i++ )
            {
              *value = *( value + offset );
              value++;
            }

          for ( i = 0; i < offset; i++ )
            *( value++ ) = 0;

          truncateTop();
        }
      else if ( shift != 0 )
        *this = ( *this << ( shift % WordBits ) ) << ( shift - ( shift % WordBits ) );
    }
  else
    {
      unsigned int* value = _valueBuffer;

      for ( i = 0; i < _wordCount; i++ )
        *( value++ ) = 0;
    }

  return *this;
}


//
// The same as operator<< but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator<<=( unsigned int shift )
{

  unsigned int i;

  if ( shift < _size )
    {
      if ( shift < WordBits )
        {
          unsigned int* value = _valueBuffer + _wordCount - 1;
          int invShift = WordBits - shift;
          unsigned int mask = ( 1 << shift ) - 1;
          unsigned int cin = 0;
          unsigned int old;

          for ( i = 0; i < _wordCount; i++ )
            {
              old = *value;
              *value = ( *value << shift ) | cin;
              value--;
              cin = ( old >> invShift ) & mask;
            }

          truncateTop();
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int* value = _valueBuffer;
          unsigned int offset = shift / WordBits;

          for ( i = offset; i < _wordCount; i++ )
            {
              *value = *( value + offset );
              value++;
            }

          for ( i = 0; i < offset; i++ )
            *( value++ ) = 0;

          truncateTop();
        }
      else if ( shift != 0 )
        *this = ( *this << ( shift % WordBits ) ) << ( shift - ( shift % WordBits ) );
    }
  else
    {
      unsigned int* value = _valueBuffer;

      for ( i = 0; i < _wordCount; i++ )
        *( value++ ) = 0;
    }
      
  return *this;
}


//
// Non-member function for right shifting an RNumber using an RNumber.
//
inline const RNumber rnumber::rightShift( const RNumber& n, const RNumber& shift )
{
  const unsigned int nwc = n._wordCount;
  const unsigned int* value = n._valueBuffer;
  unsigned int* resValue0 = getTempBuffer( nwc );
  unsigned int* resValue = resValue0;

  unsigned int i;

  if (shift < n._size) {
    if (shift < WordBits) {
      unsigned int intShift = shift.uint32();
      int invShift = WordBits - intShift;
      unsigned int mask = ( 1 << intShift ) - 1;
      unsigned int cin = 0;

      for (i = 0; i < nwc; i++) {
        *(resValue++) = (*value >> intShift) | cin;
        cin = (*(value++) & mask) << invShift;
      }
    }
    else if ((shift % WordBits) == 0) {
      unsigned int offset = shift.uint32() / WordBits;

      for ( i = 0; i < offset; i++ ) {
        *( resValue++ ) = 0;
      }

      for ( i = offset; i < nwc; i++ ) {
        *( resValue++ ) = *( value++ );
      }
    } else if (shift == 0) {
      for ( i = 0; i < nwc; i++ ) {
        *( resValue++ ) = *( value++ );
      }
    } else {
      return ( n >> ( shift % WordBits ) ) >> ( shift - ( shift % WordBits ) );
    }
  } else {
    for ( i = 0; i < nwc; i++ ) {
      *( resValue++ ) = 0;
    }
  }

  return RNumber( resValue0, nwc, n._size );
}


//
// Non-member function for right shifting an RNumber using an unsigned.
//
inline const RNumber rnumber::rightShift( const RNumber& n, unsigned int shift )
{

  const unsigned int nwc = n._wordCount;

  const unsigned int* value = n._valueBuffer;
  unsigned int* resValue0 = getTempBuffer( nwc );
  unsigned int* resValue = resValue0;

  unsigned int i;

  if ( shift < n._size )
    {
      if ( shift < WordBits )
        {
          int invShift = WordBits - shift;
          unsigned int mask = ( 1 << shift ) - 1;
          unsigned int cin = 0;

          for ( i = 0; i < nwc; i++ )
            {
              *( resValue++ ) = ( *value >> shift ) | cin;
              cin = ( *( value++ ) & mask ) << invShift;
            }
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int offset = shift / WordBits;

          for ( i = 0; i < offset; i++ )
            *( resValue++ ) = 0;

          for ( i = offset; i < nwc; i++ )
            *( resValue++ ) = *( value++ );
        }
      else if ( shift == 0 )
        {
          for ( i = 0; i < nwc; i++ )
            *( resValue++ ) = *( value++ );
        }
      else
        return ( n >> ( shift % WordBits ) ) >> ( shift - ( shift % WordBits ) );
    }
  else
    {
      for ( i = 0; i < nwc; i++ )
        *( resValue++ ) = 0;
    }

  return RNumber( resValue0, nwc, n._size );
}


//
// Non-member function for right shifting an RNumber using an RNumber.
//
inline const RNumber rnumber::rightShift( unsigned int n, const RNumber& shift )
{

  unsigned int* resValue0 = getTempBuffer( 1 );

  if ( shift == 0 )
    *resValue0 = n;
  else if ( shift < WordBits )
    *resValue0 = n >> shift.uint32();
  else
    *resValue0 = 0;

  return RNumber( resValue0, 1, WordBits );
}


//
// Non-member function for right shifting an RNumber with an RNumber.
//
const RNumber rnumber::operator>>( const RNumber& n1, const RNumber& n2 )
{

  return rightShift( n1, n2 );
}


//
// Non-member function for right shifting an RNumber with an unsigned.
//
const RNumber rnumber::operator>>( const RNumber& n1, unsigned int n2 )
{

  return rightShift( n1, n2 );
}


//
// Non-member function for right shifting an unsigned with an RNumber.
//
const RNumber rnumber::operator>>( unsigned int n1, const RNumber& n2 )
{

  return rightShift( n1, n2 );
}


//
// The same as operator>> but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator>>=( const RNumber& shift ) 
{

  unsigned int* value = _valueBuffer;
  unsigned int i;

  if ( shift < _size )
    {
      if ( shift < WordBits )
        {
          unsigned int intShift = shift.uint32();
          int invShift = WordBits - intShift;
          unsigned int mask = ( 1 << intShift ) - 1;
          unsigned int cin = 0;
          unsigned int old;

          for ( i = 0; i < _wordCount; i++ )
            {
              old = *value;
              *value = ( *value >> intShift ) | cin;
              value++;
              cin = ( old & mask ) << invShift;
            }
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int offset = shift.uint32() / WordBits;

          value = _valueBuffer + _wordCount - 1;

          for ( i = _wordCount - 1; i >= offset; i-- )
            {
              *value = *( value - offset );
              value--;
            }

          for ( i = 0; i < offset; i++ )
            *( value-- ) = 0;
        }
      else if ( shift != 0 )
        *this = ( *this >> ( shift % WordBits ) ) >> ( shift - ( shift % WordBits ) );
    }
  else
    {
      for ( i = 0; i < _wordCount; i++ )
        *( value++ ) = 0; 
    }
      
  return *this;
}


//
// The same as operator>> but the assignment allows us to optimize the code to
// not create temporary objects.
//
RNumber& RNumber::operator>>=( unsigned int shift ) 
{

  unsigned int* value = _valueBuffer;
  unsigned int i;

  if ( shift < _size )
    {
      if ( shift < WordBits )
        {
          int invShift = WordBits - shift;
          unsigned int mask = ( 1 << shift ) - 1;
          unsigned int cin = 0;
          unsigned int old;

          for ( i = 0; i < _wordCount; i++ )
            {
              old = *value;
              *value = ( *value >> shift ) | cin;
              value++;
              cin = ( old & mask ) << invShift;
            }
        }
      else if ( ( shift % WordBits ) == 0 )
        {
          unsigned int offset = shift / WordBits;

          value = _valueBuffer + _wordCount - 1;

          for ( i = _wordCount - 1; i >= offset; i-- )
            {
              *value = *( value - offset );
              value--;
            }

          for ( i = 0; i < offset; i++ )
            *( value-- ) = 0;
        }
      else if ( shift != 0 )
        *this = ( *this >> ( shift % WordBits ) ) >> ( shift - ( shift % WordBits ) );
    }
  else
    {
      for ( i = 0; i < _wordCount; i++ )
        *( value++ ) = 0; 
    }
      
  return *this;
}

//
// Return a -1, 0 or 1 for less than, equal to, or greater than, respectively.
//
int RNumber::compare( const RNumber& number ) const
{

  if ( *this < number )
    return -1;
  else if ( *this == number )
    return 0;
  else
    return 1;
}


//
// Bitwise invert.
//
RNumber& RNumber::invert()
{

  for ( unsigned int i = 0; i < _wordCount; i++ )
    _valueBuffer[i] = ~_valueBuffer[i];

  truncateTop();

  return *this;
}


//
// 2's complement.
//
RNumber& RNumber::negate()
{

  invert();
  operator+=( 1 );

  return *this;
}


//
// Set all bits to one.
//
RNumber& RNumber::setAll()
{

  for ( unsigned int i = 0; i < _wordCount; i++ )
    _valueBuffer[i] = 0xffffffff;

  truncateTop();

  return *this;
}


//
// Set all bits to zero.
//
RNumber& RNumber::clearAll()
{

  for ( unsigned int i = 0; i < _wordCount; ++i )
    _valueBuffer[i] = 0;

  return *this;
}


//
// Extend the sign based on the specified bit.
//
RNumber& RNumber::signExtend( unsigned int bit )
{

  if ( bit )
    {
      int sign = getBit( bit );
      int size = _size - bit;
      int n    = _wordCount - ( size / WordBits );

      if ( size % WordBits )
        {
          unsigned int mask = ( 1 << ( size % WordBits ) ) - 1;

          _valueBuffer[n - 1] = ( sign ) ? ( _valueBuffer[n - 1] | ~mask ) :
            ( _valueBuffer[n - 1] & mask );
          n--;
        }

      unsigned int v = ( sign ? 0xffffffff : 0x0 );

      for ( int i = 0; i < n; i++ )
        _valueBuffer[i] = v;

      truncateTop();
    }

  return *this;
}


//
// Truncate down to the specified bit size.
//
RNumber& RNumber::truncate( unsigned int size )
{

  if ( _size <= WordBits )
    return truncateInt( size );
  else
    return truncateExtended( size );
}

// Returns true if zero (all bits clear).     
bool RNumber::iszero() const {
  unsigned z = _valueBuffer[0];       
  for (unsigned i = 1; i != _wordCount; ++i) {         
    z |= _valueBuffer[i];
  }       
  return !z;
}

//
// Get the specified bit. Bit 0 is the most significant bit.
//
unsigned int RNumber::getBit( unsigned int pos ) const
{

  pos = _size - pos - 1;

  int word = _wordCount - ( pos / WordBits ) - 1;
  int shift = pos % WordBits;
  const unsigned int* value = _valueBuffer;

  return ( ( word >= 0 ) ? ( value[word] >> shift ) & 0x1 : 0 );
}


//
// Get the specified bit. Bit 0 is the least significant bit.
//
unsigned int RNumber::getBitLSB( unsigned int pos ) const
{

  int word = _wordCount - ( pos / WordBits ) - 1;
  int shift = pos % WordBits;
  const unsigned int* value = _valueBuffer;

  return ( ( word >= 0 ) ? ( value[word] >> shift ) & 0x1 : 0 );
}


//
// Set the specified bit. Bit 0 is the most significant bit.
//
void RNumber::setBit( unsigned int pos, unsigned int val )
{

  pos = _size - pos - 1;

  int word = _wordCount - ( pos / WordBits ) - 1;
  int shift = pos % WordBits;
  unsigned int mask = 1 << shift;
  unsigned int* value = _valueBuffer;

  if ( word >= 0 )
    value[word] = ( value[word] & ~mask ) | ( ( val & 0x1 ) << shift );
}


//
// Set the specified bit. Bit 0 is the least significant bit.
//
void RNumber::setBitLSB( unsigned int pos, unsigned int val )
{
  int word = _wordCount - ( pos / WordBits ) - 1;
  int shift = pos % WordBits;
  unsigned int mask = 1 << shift;
  unsigned int* value = _valueBuffer;

  if ( word >= 0 )
    value[word] = ( value[word] & ~mask ) | ( ( val & 0x1 ) << shift );
}


//
// Return the contents of the RNumber in a string.
//
string RNumber::str(int format) const
{
# ifdef STD_CPP
  ostringstream ss;
  printToOS(ss,format);
  return ss.str();
# else
  strstream ss;
  string str;
  printToOS(ss,format);
  ss >> str;
  return str;
#endif
}

unsigned char * RNumber::bigEndianArrayOfBytes(unsigned char * buffer) const {
   if (buffer == 0) {
      buffer = new unsigned char [_size >> 3] + 1;
   }
   int buffer_cursor = 0;
   // _valueBuffer[_wordCount - 1] is least significant word
   for (unsigned x = 0; x < _wordCount; ++x) {
      buffer[buffer_cursor++] = _valueBuffer[x] >> 24 & 0xff;
      buffer[buffer_cursor++] = _valueBuffer[x] >> 16 & 0xff;
      buffer[buffer_cursor++] = _valueBuffer[x] >> 8 & 0xff;
      buffer[buffer_cursor++] = _valueBuffer[x] & 0xff;
   }
   return buffer;
}

//
// Return a field of bits from 'start' to 'end', stored in an unsigned int.
// Bit 0 is the most significant bit. There are 3 cases to consider:
//   1) start and end positions are the same value.
//   2) start and end positions are within a physical word boundary.
//   3) the most expensive - shift the whole number and mask.
//
unsigned int RNumber::getUIntField( unsigned int start, unsigned int end ) const
{

  assert( start < _size && end < _size );

  if ( start == end )
    {
      // The start and end are the same so our job is simple; return the bit.
      return getBit( start );
    }
  else
    {
      unsigned int length = end - start + 1;
      assert( length <= 32 );

      unsigned int mask = ( length < 32 ) ? ( 1 << length ) - 1 : -1;

      start = _size - start - 1;
      end = _size - end - 1;

      if ( start / WordBits == end / WordBits )
        {
          // The start and end values do not cross over word boundaries, with
          // respect to the total size. Shift over and mask the proper field.
          unsigned int word = _wordCount - ( start / WordBits ) - 1;
          unsigned int shift = end % WordBits;

          return ( _valueBuffer[word] >> shift ) & mask;
        }
      else
        return ( ( *this >> end ).uint32() & mask );
    }
}


//
// Return a field of bits from 'start' to 'end', stored in an RNumber.
// Bit 0 is the most significant bit.
//
RNumber RNumber::getField( unsigned int start, unsigned int end ) const
{

  unsigned int length = end - start + 1;

  if ( length <= WordBits )
    return RNumber( getUIntField ( start, end ), _size );
  else
    {
      unsigned int shift = _size - end - 1;
      RNumber mask = ( RNumber ( 1, _size ) << length ) - 1;

      return ( *this >> shift ) & mask;
    }
}


//
// Set the field of bits in positions 'start' to 'end' using the contents of number.
// Bit 0 is the most significant bit.
//
void RNumber::setField( unsigned int start, unsigned int end, const RNumber& number )
{

  unsigned int length = end - start + 1;
  unsigned int shift = _size - end - 1;

  RNumber mask = ( ( RNumber ( 1, _size ) << length ) - 1 ) << shift;
  RNumber newValue = ( RNumber ( number, _size ) << shift ) & mask;
  *this = ( *this & ~mask ) | newValue;
}


//
// Set the default bit-size that is given to number values when the
// constructor does not include an explicit size value.
//
void RNumber::setDefaultSize( unsigned int size )
{

  _defaultSize = size;
}

//
// Stream out the contents of the RNumber using the specified format options.
//
ostream& rnumber::operator<<( ostream& os, const RNumber& number )
{
  number.printWithStreamRadix(os,0);
  return os;
}

//
// Print out the contents of the RNumber to the specified output stream.
//
ostream & RNumber::printToOS( ostream& os ) const
{
  printWithStreamRadix(os,rprefix);
  return os;
}


//
// Print with a specific radix.
//
ostream& RNumber::printToOS( ostream& os, int format ) const
{
  if (format & rhex) {
    printHex( os, format );
  } else if (format & rdec) {
    printDec (os, format );
  } else if (format & rbin) {
    printBin (os, format);
  } else {
    printWithStreamRadix(os, format);
  }
  return os;
}

// Prints the number to a given stream using the radix specified by the stream.
// A prefix for the base is printed if the prefix flag is true.
inline void RNumber::printWithStreamRadix(ostream &os,int format) const
{
  unsigned int fmt = os.flags() & ios::basefield;
  
  if (os.flags() & ios_base::showbase) {
    format |= rprefix;
  }
  
  // We cheat here- we use octal to designate binary so that we don't
  // have to mess with xalloc.
  switch (fmt) {
  case ios::oct:
    printBin( os,format );
    break;
  case ios::hex:
    printHex( os,format );
    break;
  default:
    printDec( os, format );
    break;
  }
}

//
// Stream out a binary representation of the contents of RNumber.
//
void RNumber::printBin( ostream& os,int format ) const
{

  unsigned int width = os.width();

  int diff = width - _size;

  if (format & rprefix)
    os << "0b";

  // Pad with zeros. If diff is negative, we fall through.
  for ( int i = 0; i < diff; ++i )
    os << '0';

  for ( unsigned int i = 0; i < _size; ++i )
    os << getBit( i );
}


//
// Stream out a decimal representation of the contents of RNumber.
//
void RNumber::printDec( ostream& os,int format ) const
{

  // Set decimal format and save old flags.
  ios::fmtflags old_options = os.flags( os.flags() | ios::dec );

  unsigned int len = ( _size + 1 ) / 2;
  char* str = new char [len + 1];
  memset( str, ' ', len );
  *( str + len ) = '\0';

  char* p = str + len - 1;

  RNumber tmp( *this );

  if ( tmp == 0 )
    *p = '0';
  else
    {
      RNumber div( 0, _size );

      while ( tmp != 0 )
        {
          div = tmp / 10;
          *p-- = '0' + ( tmp - div * 10 ).uint32();
          tmp = div;
        }

      p++;
    }

  os << p;

  delete [] str;

  os.flags( old_options );
}


//
// Stream out a hexadecimal representation of the contents of RNumber.
//
void RNumber::printHex( ostream& os,int format ) const
{

  // Set hex format and save old flags.
  ios::fmtflags old_options = os.flags( ( os.flags() & ~ios::basefield ) |
                                        ios::hex );

  unsigned int width = os.width();

  const unsigned int* value = _valueBuffer;

  // Print a prefix if requested.
  if (format & rprefix) {
    os << "0x";
  }

  // Turn off prefix printing for the interior words.
  os << noshowbase;

  // write leading word, with any necessary padding.
  if ( width > WordBits / 4 || ( width == 0 && _wordCount > 1 )) {
    unsigned int n = ( ( _size % WordBits ) + 3 ) / 4;
    char oldFill = os.fill( '0' );

    if ( n == 0 )
      n = 8;
      
    os << setw( n ) << value[0];
    os.fill( oldFill );
  } else {
    os << value[0];
  }

  // Continue with any other words.
  char oldFill = os.fill( '0' );
  for ( unsigned int i = 1; i < _wordCount; i++ ) {
    os << setw( WordBits / 4 );
    os << value[i];
  }

  os.fill( oldFill );
  os.flags( old_options );
}

//
// Read in a hexadecimal value into the RNumber.
//
template <class Getter>
char readHex( RNumber& number,Getter getter )
{
  char c;

  while ( 1 ){
    c = getter();
    if ( isdigit( c ) ){
      number <<= 4;
      number |= ( c - '0' );
    }
    else if ( ( c = toupper( c ) ) >= 'A' && c <= 'F' ) {
      number <<= 4;
      number |= ( ( c - 'A' ) + 0xa );
    }
    else if ( c == '_' ) {
      // skip
    } else {
      getter.putback(c);
      return c;
    }
  }
}

//
// Read in a binary value into the RNumber.
//
template <class Getter>
char readBin( RNumber& number, Getter getter )
{
  char c;

  while ( 1 ) {
    c = getter();

    if ( c == '0' )
      number <<= 1;
    else if ( c == '1' ) {
      number <<= 1;
      number |= 1;
    }
    else if ( c == '_' ) {
      // skip
    } else {
      getter.putback(c);
      return c;
    }
  }
}

//
// Read in a decimal value into the RNumber.
//
template <class Getter>
char readDec( RNumber& number, Getter getter )
{
  char c;

  while ( 1 ) {
    c = getter();
    
    if ( isdigit( c ) ) {
      number *= 10;
      number += ( c - '0' );
    }
    else if ( c == '_' ) {
      // skip
    } else {
      getter.putback(c);
      return c;
    }
  }
}

//
// Templatized reading function.  This is used by both stream and string
// input systems.  The Getter template argument is a class which should
// define the following methods:
//
// char operator():     Return a new character on each call.  Return
//                      a non-numeric character (typically 0) to signify
//                      end of input.  This should be a "get" operation,
//                      in that it shouldn't eat leading whitespace.
//
// char eatwhite():     This should absorb whitespace and return the first
//                      non-whitespace character.  This is equivalent to
//                      a stream ">>" operation.
// 
// void putback(char):  Put back last char read.  It's always called with 
//                      the last character read, so a string implementation 
//                      can ignore the parameter.
//


// General input support for hexadecimal, binary and decimal (the default)
// numbers.  Only decimal numbers may include a unary plus or minus.
// We absorb characters until we see a bad one (non-numeric and not '_'), then
// we quit.
//
template<class Getter>
void readNumber( RNumber& number, Getter getter )
{
  bool negate  = false;
  bool decimal = true;

  // Zero out the entire number.
  number.clearAll();

  // Absorb any prior white-space and get the first char.
  char c = getter.eatwhite();
 
  if ( c == '-' ) {
    // A unary minus; thus, we have a decimal, negated number.
    negate = true;
  }
  else if ( c == '+' ) {
    // A unary plus; thus, we have a decimal number.
  }
  else if ( c == '0' ) {
    // Octal numbers are *not* supported; thus, the next char is needed to
    // determine the base of the numeric.
    c = tolower( getter() );

    if ( c == 'x' ) {
      // Hex mode.
      decimal = false;
      readHex(number,getter);
    }
    else if ( c == 'b' ) {
      // Binary mode.
      decimal = false;
      readBin(number,getter);
    }
    else {
      // Not a recognized prefix, so put the character back.
      getter.putback( c );
      getter.putback( '0' );
    }
  }
  else {
    // Not an indicator character, so put it back.
    getter.putback( c );
  }

  // If all else fails, we assume decimal notation.
  if ( decimal ) {
    readDec(number,getter);
    // If the decimal number was prepended with a unary minus, negate it.
    if ( negate ) {
      number.negate();
    }
  }
}

// Input support w/radix specified by caller.  No prefix is allowed.
template<class Getter>
void readNumber(RNumber &number,Getter getter,int radix)
{
  if        (radix & RNumber::rdec) {
    readDec( number,getter );
  } else if (radix & RNumber::rhex) {
    readHex( number,getter );
  } else if (radix & RNumber::rbin) {
    readBin( number,getter );
  } else {
    readDec( number,getter );
  }
}

// Getter class for stream reading.
class StreamGet {
public:
  StreamGet(istream &is) : _is(is) {};
  char operator()() { return _is.get(); };
  char eatwhite() { char c; _is >> c; return c; };
  void putback(char c) { _is.putback(c); };
private:
  istream &_is;
};

// Stream reading.
istream& rnumber::operator>>( istream& is, RNumber& number )
{
  StreamGet getter(is);
  readNumber(number,getter);
  return is;
}

// Getter class for string reading.
class StringGet {
public:
  StringGet(const string &s) : _s(s), _i(_s.begin()) {};
  char operator()() { 
    return (_i == _s.end()) ? 0 : *(_i++);
  };
  char eatwhite() { 
    char c;
    while ( (c = operator()()) && isspace(c));
    return c;
  };
  void putback(char c) { --_i; };
private:
  const string &_s;
  string::const_iterator _i;
};

// String reading.
void readstr(RNumber &number,const string &s)
{
  StringGet getter(s);
  readNumber(number,getter);
}

// String reading w/explicit prefix.
void readstr(RNumber &number,const string &s,int format)
{
  StringGet getter(s);
  readNumber(number,getter,format);
}

//
// Read from a binary file. The format is: <length> <words>
//
void RNumber::read( istream& is )
{

  _size = readInt(is);

  if ( is.fail() )
    throw std::runtime_error ( "io_fail_error - reading" );

  _wordCount = ( _size + WordBits - 1 ) / WordBits;

  if ( _wordCount > WORD_THRESHOLD )
    _valueBuffer = _value.varValue = new unsigned int [_wordCount];
  else
    _valueBuffer = _value.fixedValue + WORD_THRESHOLD - _wordCount;

  unsigned int* value = _valueBuffer;

  for (unsigned i = 0; i != _wordCount; ++i) {
    value[i] = readInt(is);
    if ( is.fail() )
      throw runtime_error ( "io_fail_error - reading" );
  }

}


//
// Write to a binary file. The format is: <length> <words>
//
void RNumber::write( ostream& os ) const
{
  writeInt(os,_size);

  if ( os.fail() )
    throw runtime_error ( "io_fail_error - writing" );

  const unsigned *value = _valueBuffer;

  for (unsigned i = 0; i != _wordCount; ++i) {
    writeInt(os,value[i]);
    if ( os.fail() )
      throw runtime_error ( "io_fail_error - writing" );
  }

}

// Return number of underscore characters.     
inline int count_underscores(const string &s) {
  int count = 0;       
  for (string::const_iterator i = s.begin(); i != s.end(); ++i) {         
    if ( *i == '_' ) ++count;       
  }       
  return count; 
}

//
// Calculate the size of the string using the following steps. The first step
// that is correct wins.
//   1) If the number contains a sign (+ or -), it must be decimal.
//   2) A prefix of 0x or 0X indicates hexadecimal.
//   3) A prefix of 0b or 0B indicates binary.
//   4) A radix of 2, 10, or 16 will be used to indicate binary, decimal, or
//      hexadecimal respectively.
//   5) Otherwise, default to decimal and adjust the radix to 10.
//
// The passed in radix will be updated to the determined correct value.
// If the string is empty, the default RNumber size is used.
//
unsigned int RNumber::getSizeWithRadix (const string& str, Format radix) {

  unsigned int n = 0;
  unsigned int size;
  char c = str[n];

  // Skip leading whitespace.
  while ( c == ' ' || c == '\t' )
    c = str[++n];

  // if no explicit radix requested, try to determine the
  // radix by prefix hints.
  if (radix & rios) {
    if ( c == '+' || c == '-' )
      radix = rdec;
    else if ( c == '0' ) {
      c = str[++n];

      if ( tolower( c ) == 'x' ) {
        radix = rhex;
        n++;
      }
      else if ( tolower( c ) == 'b' ) {
        radix = rbin;
        n++;
      }
      else
        n--;
    }
  }

  // For a radix of rdec or rhex, the max number of bits per digit is a nibble;
  // if the radix is rbin, each digit represents a bit; otherwise, default to
  // nibbled digits and set the radix to rdec.
  if ( radix & rdec || radix & rhex )
    size = ( str.length() - n -count_underscores(str)) << 2;
  else if ( radix & rbin )
    size = str.length() - n - count_underscores(str);
  else {
    size = ( str.length() - n - count_underscores(str)) << 2;
    radix = rdec;
  }
  if (!size) {
    size = defaultSize();
  }

  return size;
}

