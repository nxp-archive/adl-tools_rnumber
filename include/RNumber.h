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
#ifndef RNUMBER_H
#define RNUMBER_H "$Id$"

#include <algo.h>
#include <string>

#include "types.h"

const unsigned int WORD_THRESHOLD = 2;

class RNumber
{
public:
  enum Radix { rdec, rhex, rbin, rios };
  enum Sizing { fixed, dynamic };

  // Constructors and destructor. All numbers are fixed size by default.
  RNumber();
  RNumber( const RNumber& number );
  RNumber( unsigned int number, Sizing sizing = fixed );
  RNumber( unsigned int number, unsigned int size, Sizing sizing = fixed );
  RNumber( const string& number, Sizing sizing = fixed );
  RNumber( const string& number, unsigned int size, Sizing sizing = fixed );
  RNumber( const string& number, Radix radix, Sizing sizing = fixed );
  RNumber( const string& number, unsigned int size, Radix radix, Sizing sizing = fixed );
  RNumber( const RNumber& number, unsigned int size, Sizing sizing = fixed );
  RNumber( unsigned int radix, const string& str, int size = -1 );  // deprecated
  RNumber(const unsigned int* numVector, unsigned int wordCount, unsigned int size, Sizing sizing = fixed );
  ~RNumber();

  // Assignment methods. operator=() assigns the value constrained by sizing;
  // assign() assigns the value with dynamic sizing; clone() assigns all
  // attributes; resize() truncates/expands the value and sets fixed sizing.
  RNumber& operator=( unsigned int number );
  RNumber& operator=( const string& number );
  RNumber& operator=( const RNumber& number );
  RNumber& assign( const RNumber& number );
  RNumber& set( const RNumber& number ) { return copy( number ); }  // deprecated
  RNumber& copy( const RNumber& number );
  void resize( unsigned int size );

  // Unary arithmetic operators.
  const RNumber operator-() const;
  const RNumber operator~() const;

  // Arithmetic assignment operators; assignment size depends on sizing state.
  RNumber& operator+=( const RNumber& number );
  RNumber& operator+=( unsigned int number );
  RNumber& operator-=( const RNumber& number );
  RNumber& operator-=( unsigned int number );
  RNumber& operator*=( const RNumber& number );
  RNumber& operator*=( unsigned int number );
  RNumber& operator/=( const RNumber& number );
  RNumber& operator/=( unsigned int number );
  RNumber& operator%=( const RNumber& number );
  RNumber& operator%=( unsigned int number );
  RNumber& operator&=( const RNumber& number );
  RNumber& operator&=( unsigned int number );
  RNumber& operator|=( const RNumber& number );
  RNumber& operator|=( unsigned int number );
  RNumber& operator^=( const RNumber& number );
  RNumber& operator^=( unsigned int number );
  RNumber& operator<<=( const RNumber& shift );
  RNumber& operator<<=( unsigned int shift );
  RNumber& operator>>=( const RNumber& shift );
  RNumber& operator>>=( unsigned int shift );

  // Unary conditional expression operators.
  bool operator!() const;

  // Signed conditional expression operators.
  bool signedLT( const RNumber& number ) const;
  bool signedLE( const RNumber& number ) const;
  bool signedGT( const RNumber& number ) const;
  bool signedGE( const RNumber& number ) const;
  int compare( const RNumber& number ) const;

  // Miscellaneous bit manipulation methods.
  RNumber& invert();
  RNumber& negate();
  RNumber& setAll();
  RNumber& setToAllOnes() { return setAll (); }   // deprecated
  RNumber& clearAll();
  RNumber& signExtend( unsigned int bit );
  // RNumber& signExtendLSB( unsigned int bit );      // implement
  RNumber& truncate( unsigned int size );

  // Bit value accessors and manipulators.
  unsigned int getBit( unsigned int pos ) const;
  unsigned int getBitLSB( unsigned int pos ) const;
  void setBit( unsigned int pos, unsigned int value );
  void setBitLSB( unsigned int pos, unsigned int value );
  void assignBit( unsigned int pos, unsigned int value )
  { return setBit( pos, value ); } // deprecated
  void assignBitLSB( unsigned int pos, unsigned int value )
  { return setBitLSB( pos, value ); } // deprecated

  // Value accessors.
  unsigned int intValue() const  { return getUInt(); }  // deprecated
  unsigned int getInt() const    { return getUInt(); }  // deprecated
  unsigned int getUInt() const;
  string str() const;
  string strradix(Radix=RNumber::rdec,bool prefix=false) const;

  // Value field accessors and manipulators.
  unsigned int getIntField( unsigned int start, unsigned int end ) const { return getUIntField( start, end ); }  // deprecated
  unsigned int getUIntField( unsigned int start, unsigned int end ) const;
  // unsigned int getUIntFieldLSB( unsigned int start, unsigned int end ) const;  // implement
  RNumber getField( unsigned int start, unsigned int end ) const;
  // RNumber getFieldLSB( unsigned int start, unsigned int end ) const;      // implement
  void setField( unsigned int start, unsigned int end, const RNumber& num );
  // void setFieldLSB( unsigned int start, unsigned int end, const RNumber& num ); // implement

  // Attribute accessors and manipulators.
  unsigned size() const;
  unsigned wordcount() const;

  const unsigned *buffer() const;

  static unsigned int defaultSize()  { return _defaultSize; }       // deprecated
  static unsigned int getDefaultSize();
  static void setDefaultSize( unsigned int size );

  Sizing sizing() const;
  void setDynamic();
  void setFixed();

  // Streaming I/O methods.
  void printToOS( ostream& os ) const;
  ostream& printWithRadix( ostream& os, Radix = rios, bool prefix=false ) const;
  friend istream& operator>>( istream& is, RNumber& number );
  friend ostream& operator<<( ostream& os, const RNumber& number );
  void read( istream& is );
  void write( ostream& os ) const;

  friend struct Hash {
    size_t operator()( const RNumber& num ) const;
  };

  friend struct Equal {
    size_t operator()( const RNumber& num1, const RNumber& num2 ) const;
  };
    
private:
  static unsigned int _defaultSize;

  unsigned int _size;
  unsigned int _wordCount;
  unsigned int* _valueBuffer;
  Sizing _sizing;

  union
  {
    unsigned int* varValue;
    unsigned int fixedValue[WORD_THRESHOLD];
  } _value;

  void initNumber( unsigned int size, Sizing sizing );
  void cloneNumber( const RNumber& number );
  void assignAndTruncateNumber( const RNumber& number );
  void assignNumber( const RNumber& number );
  unsigned int code() const;

  RNumber& truncateTop();
  RNumber& truncateInt( unsigned int size );
  RNumber& truncateExtended( unsigned int size );

  unsigned int getSizeWithRadix( const string& number, Radix& radix );
  void printWithStreamRadix(ostream &os,bool prefix) const;
  void printDec( ostream& os ) const;
  void printBin( ostream& os,bool prefix) const;
  void printHex( ostream& os,bool prefix ) const;

  friend  const RNumber add( const RNumber& n1, const RNumber& n2, bool extend );
  friend  const RNumber add( const RNumber& n1, unsigned int n2, bool extend );
  friend  const RNumber subtract( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber subtract( const RNumber& n1, unsigned int n2 );
  friend  const RNumber subtract( unsigned int n1, const RNumber& n2 );
  friend  const RNumber multiply( const RNumber& n1, const RNumber& n2, bool extend );
  friend  const RNumber multiply( const RNumber& n1, unsigned int n2, bool extend );
  friend  const RNumber divide( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber divide( const RNumber& n1, unsigned int n2 );
  friend  const RNumber divide( unsigned int n1, const RNumber& n2 );
  friend  const RNumber mod( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber mod( const RNumber& n1, unsigned int n2 );
  friend  const RNumber mod( unsigned int n1, const RNumber& n2 );
  friend  const RNumber bitWiseAnd( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber bitWiseAnd( const RNumber& n1, unsigned int n2 );
  friend  const RNumber bitWiseOr( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber bitWiseOr( const RNumber& n1, unsigned int n2 );
  friend  const RNumber bitWiseXor( const RNumber& n1, const RNumber& n2 );
  friend  const RNumber bitWiseXor( const RNumber& n1, unsigned int n2 );
  friend const  RNumber leftShift( const RNumber& num, const RNumber& shift, bool extend );
  friend const  RNumber leftShift( const RNumber& num, unsigned int shift, bool extend );
  friend const  RNumber leftShift( unsigned int num, const RNumber& shift, bool extend );
  friend  const RNumber rightShift( const RNumber& num, const RNumber& shift );
  friend  const RNumber rightShift( const RNumber& num, unsigned int shift );
  friend  const RNumber rightShift( unsigned int num, const RNumber& shift );

  friend  bool notEqual( const RNumber& n1, const RNumber& n2 );
  friend  bool notEqual( const RNumber& n1, unsigned int n2 );
  friend  bool equal( const RNumber& n1, const RNumber& n2 );
  friend  bool equal( const RNumber& n1, unsigned int n2 );
  friend  bool lessThan( const RNumber& n1, const RNumber& n2, bool orEqual );
  friend  bool lessThan( const RNumber& n1, unsigned int n2, bool orEqual );
  friend  bool lessThan( unsigned int n1, const RNumber& n2, bool orEqual );
  friend  bool greaterThan( const RNumber& n1, const RNumber& n2, bool orEqual );
  friend  bool greaterThan( const RNumber& n1, unsigned int n2, bool orEqual );
  friend  bool greaterThan( unsigned int n1, const RNumber& n2, bool orEqual );
};

// Non-member functions that allow for mixed arithmetic expressions between
// RNumbers and unsigned integers.
const RNumber operator+( const RNumber& n1, const RNumber& n2 );
const RNumber operator+( const RNumber& n1, unsigned int n2 );
const RNumber operator+( unsigned int n1, const RNumber& n2 );
const RNumber addExt( const RNumber& n1, const RNumber& n2 );
const RNumber addExt( const RNumber& n1, unsigned int n2 );
const RNumber addExt( unsigned int n1, const RNumber& n2 );
const RNumber operator-( const RNumber& n1, const RNumber& n2 );
const RNumber operator-( const RNumber& n1, unsigned int n2 );
const RNumber operator-( unsigned int n1, const RNumber& n2 );
const RNumber operator*( const RNumber& n1, const RNumber& n2 );
const RNumber operator*( const RNumber& n1, unsigned int n2 );
const RNumber operator*( unsigned int n1, const RNumber& n2 );
const RNumber multiplyExt( const RNumber& n1, const RNumber& n2 );
const RNumber multiplyExt( const RNumber& n1, unsigned int n2 );
const RNumber multiplyExt( unsigned int n1, const RNumber& n2 );
const RNumber operator/( const RNumber& n1, const RNumber& n2 );
const RNumber operator/( const RNumber& n1, unsigned int n2 );
const RNumber operator/( unsigned int n1, const RNumber& n2 );
const RNumber operator%( const RNumber& n1, const RNumber& n2 );
const RNumber operator%( const RNumber& n1, unsigned int n2 );
const RNumber operator%( unsigned int n1, const RNumber& n2 );
const RNumber operator&( const RNumber& n1, const RNumber& n2 );
const RNumber operator&( const RNumber& n1, unsigned int n2 );
const RNumber operator&( unsigned int n1, const RNumber& n2 );
const RNumber operator|( const RNumber& n1, const RNumber& n2 );
const RNumber operator|( const RNumber& n1, unsigned int n2 );
const RNumber operator|( unsigned int n1, const RNumber& n2 );
const RNumber operator^( const RNumber& n1, const RNumber& n2 );
const RNumber operator^( const RNumber& n1, unsigned int n2 );
const RNumber operator^( unsigned int n1, const RNumber& n2 );
const RNumber operator<<( const RNumber& n, const RNumber& shift );
const RNumber operator<<( const RNumber& n, unsigned int shift );
const RNumber operator<<( unsigned int n, const RNumber& shift );
const RNumber leftShiftExt( const RNumber& n1, const RNumber& n2 );
const RNumber leftShiftExt( const RNumber& n1, unsigned int n2 );
const RNumber leftShiftExt( unsigned int n1, const RNumber& n2 );
const RNumber operator>>( const RNumber& n, const RNumber& shift );
const RNumber operator>>( const RNumber& n, unsigned int shift );
const RNumber operator>>( unsigned int n, const RNumber& shift );

// Non-member functions that allow for mixed conditional expressions between
// RNumbers and unsigned integers.
bool operator!=( const RNumber& n1, const RNumber& n2 );
bool operator!=( const RNumber& n1, unsigned int n2 );
bool operator!=( unsigned int n1, const RNumber& n2 );
bool operator==( const RNumber& n1, const RNumber& n2 );
bool operator==( const RNumber& n1, unsigned int n2 );
bool operator==( unsigned int n1, const RNumber& n2 );
bool operator<( const RNumber& n1, const RNumber& n2 );
bool operator<( const RNumber& n1, unsigned int n2 );
bool operator<( unsigned int n1, const RNumber& n2 );
bool operator<=( const RNumber& n1, const RNumber& n2 );
bool operator<=( const RNumber& n1, unsigned int n2 );
bool operator<=( unsigned int n1, const RNumber& n2 );
bool operator>( const RNumber& n1, const RNumber& n2 );
bool operator>( const RNumber& n1, unsigned int n2 );
bool operator>( unsigned int n1, const RNumber& n2 );
bool operator>=( const RNumber& n1, const RNumber& n2 );
bool operator>=( const RNumber& n1, unsigned int n2 );
bool operator>=( unsigned int n1, const RNumber& n2 );

// ---------------------------------------------------------------------------

//
// Create a new RNumber of default size with a value of zero.
//
inline RNumber::RNumber()
{
  initNumber( _defaultSize, dynamic );
}


//
// Create a new RNumber which is a clone of the specified number.
//
inline RNumber::RNumber( const RNumber& number )
{
  cloneNumber( number );
}


//
// Create a new RNumber with the specified value.
//
inline RNumber::RNumber( unsigned int number, Sizing sizing )
{
  initNumber( _defaultSize, sizing );
  _valueBuffer[_wordCount - 1] = number;
}

//
// Cleanup the memory allocation if necessary.
//
inline RNumber::~RNumber()
{
  if ( _wordCount > WORD_THRESHOLD )
    delete [] _value.varValue;
}

//
// A core method which determines whether the specified size will fit in our
// internal fixed size member or that a larger sized memory allocation is
// necessary. Either way, the space is initialized to 0.
//
inline void RNumber::initNumber( unsigned int size, Sizing sizing )
{
  // Update the RNumber internal members.
  _size = size;
  _wordCount = ( _size + WORD_BITS - 1 ) / WORD_BITS;
  _sizing = sizing;

  if ( _wordCount <= WORD_THRESHOLD )
    {
      _valueBuffer = _value.fixedValue + WORD_THRESHOLD - _wordCount;

      // This loop will be unrolled by the compiler and thus quite fast.
      for ( unsigned int i = 0; i < WORD_THRESHOLD; i++ )
	_value.fixedValue[i] = 0;
    }
  else
    {
      _valueBuffer = _value.varValue = new unsigned int[_wordCount];

      // This loop will be tight but we do not incur the memset() function
      // call penalty.
      for ( unsigned int i = 0; i < _wordCount; i++ )
	_valueBuffer[i] = 0;
    }
}


//
// Allocate a new number and copy everything from the specified RNumber.
//
inline void RNumber::cloneNumber( const RNumber& number )
{
  // Update the RNumber internal members.
  _size = number._size;
  _wordCount = number._wordCount;
  _sizing = number._sizing;

  if ( _wordCount <= WORD_THRESHOLD )
    {
      _valueBuffer = _value.fixedValue + WORD_THRESHOLD - _wordCount;

      // This loop will be unrolled by the compiler and thus quite fast.
      for ( unsigned int i = 0; i < WORD_THRESHOLD; i++ )
	_value.fixedValue[i] = number._value.fixedValue[i];
    }
  else
    {
      unsigned int* nvb = number._valueBuffer;
      _valueBuffer = _value.varValue = new unsigned int[_wordCount];

      // This loop will be tight but we do not incur the memcpy() function
      // call penalty.
      for ( unsigned int i = 0; i < _wordCount; i++ )
	_valueBuffer[i] = nvb[i];
    }
}

//
// Return true if all bits are zero.
//
inline bool RNumber::operator!() const
{
  for ( unsigned int i = 0; i < _wordCount; i++ )
    if ( _valueBuffer[i] != 0 )
      return false;

  return true;
}


//
// Non-member function for boolean inequality of two RNumbers.
//
inline bool notEqual( const RNumber& n1, const RNumber& n2 )
{
  return !( n1 == n2 );
}


//
// Non-member function for boolean inequality of an RNumber and an unsigned.
//
inline bool notEqual( const RNumber& n1, unsigned int n2 )
{
  for ( unsigned int i = 0; i < n1._wordCount - 1; i++ )
    if ( n1._valueBuffer[i] != 0 )
      return true;

  return ( n1._valueBuffer[n1._wordCount - 1] != n2 );
}


//
// Non-member function for boolean inequality of two RNumbers.
//
inline bool operator!=( const RNumber& n1, const RNumber& n2 )
{
  return notEqual( n1, n2 );
}


//
// Non-member function for boolean inequality of an RNumber and an unsigned.
//
inline bool operator!=( const RNumber& n1, unsigned int n2 )
{
  return notEqual( n1, n2 );
}


//
// Non-member function for boolean inequality of an unsigned and an RNumber.
//
inline bool operator!=( unsigned int n1, const RNumber& n2 )
{
  return notEqual( n2, n1 );
}


//
// Non-member function for boolean equality of two RNumbers.
//
inline bool equal( const RNumber& n1, const RNumber& n2 )
{
  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  unsigned int minwc = min( n1wc, n2wc );

  const unsigned int* value = n1._valueBuffer;
  const unsigned int* numValue = n2._valueBuffer;

  int j = n1wc - 1;
  int k = n2wc - 1;
  unsigned int i;

  for ( i = 0; i < minwc; i++, j--, k-- )
    {
      if ( value[j] != numValue[k] )
	return false;
    }

  const unsigned int* p;

  if ( minwc < n1wc )
    {
      p = value;
      minwc = n1wc - minwc;
    }
  else if ( minwc < n2wc )
    {
      p = numValue;
      minwc = n2wc - minwc;
    }
  else
    return true;
      
  for ( i = 0; i < minwc; i++ )
    {
      if ( p[i] != 0 )
	return false;
    }

  return true;
}


//
// Non-member function for boolean equality of an RNumber and an unsigned.
//
inline bool equal( const RNumber& n1, unsigned int n2 )
{
  for ( unsigned int i = 0; i < n1._wordCount - 1; i++ )
    if ( n1._valueBuffer[i] != 0 )
      return false;

  return ( n1._valueBuffer[n1._wordCount - 1] == n2 );
}


//
// Non-member function for boolean equality of two RNumbers.
//
inline bool operator==( const RNumber& n1, const RNumber& n2 )
{
  return equal( n1, n2 );
}


//
// Non-member function for boolean equality of an RNumber and an unsigned.
//
inline bool operator==( const RNumber& n1, unsigned int n2 )
{
  return equal( n1, n2 );
}


//
// Non-member function for boolean equality of an unsigned and an RNumber.
//
inline bool operator==( unsigned int n1, const RNumber& n2 )
{
  return equal( n2, n1 );
}


//
// Non-member function for boolean less than of two RNumbers.
//
inline bool lessThan( const RNumber& n1, const RNumber& n2, bool orEqual )
{
  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );

  const unsigned int* value = n1._valueBuffer;
  const unsigned int* numValue = n2._valueBuffer;

  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;

  if ( n1wc > n2wc )
    {
      for ( i = 0; i < n1wc - n2wc; i++ )
	if ( value[i] != 0 )
	  return false;

      j = i;
    }
  else if ( n1wc < n2wc )
    {
      for ( i = 0; i < n2wc - n1wc; i++ )
	if ( numValue[i] != 0 )
	  return true;

      k = i;
    }

  for ( i = 0; i < minwc; i++, j++, k++ )
    {
      if ( value[j] < numValue[k] )
	return true;
      else if ( value[j] > numValue[k] )
	return false;
    }

  return orEqual;
}


//
// Non-member function for boolean less than of an RNumber and an unsigned.
//
inline bool lessThan( const RNumber& n1, unsigned int n2, bool orEqual )
{
  const unsigned int n1wc = n1._wordCount;
  const unsigned int* value = n1._valueBuffer;
  unsigned int i = 0;

  if ( n1wc > 1 )
    {
      for ( i = 0; i < n1wc - 1; i++ )
	if ( value[i] != 0 )
	  return false;
    }

  if ( value[i] < n2 )
    return true;
  else if ( value[i] > n2 )
    return false;

  return orEqual;
}


//
// Non-member function for boolean less than of an unsigned and an RNumber.
//
inline bool lessThan( unsigned int n1, const RNumber& n2, bool orEqual )
{
  const unsigned int n2wc = n2._wordCount;
  const unsigned int* numValue = n2._valueBuffer;
  unsigned int i = 0;

  if ( n2wc > 1 )
    {
      for ( i = 0; i < n2wc - 1; i++ )
	if ( numValue[i] != 0 )
	  return true;
    }

  if ( n1 < numValue[i] )
    return true;
  else if ( n1 > numValue[i] )
    return false;

  return orEqual;
}


//
// Non-member function for boolean less than of two RNumbers.
//
inline bool operator<( const RNumber& n1, const RNumber& n2 )
{
  return lessThan( n1, n2, false );
}


//
// Non-member function for boolean less than of an RNumber and an unsigned.
//
inline bool operator<( const RNumber& n1, unsigned int n2 )
{
  return lessThan( n1, n2, false );
}


//
// Non-member function for boolean less than of an unsigned and an RNumber.
//
inline bool operator<( unsigned int n1, const RNumber& n2 )
{
  return lessThan( n1, n2, false );
}


//
// Non-member function for boolean less than or equal of two RNumbers.
//
inline bool operator<=( const RNumber& n1, const RNumber& n2 )
{
  return lessThan( n1, n2, true );
}


//
// Non-member function for boolean less than or equal of an RNumber and an unsigned.
//
inline bool operator<=( const RNumber& n1, unsigned int n2 )
{
  return lessThan( n1, n2, true );
}


//
// Non-member function for boolean less than or equal of an unsigned and an RNumber.
//
inline bool operator<=( unsigned int n1, const RNumber& n2 )
{
  return lessThan( n1, n2, true );
}


//
// Non-member function for boolean greater than of two RNumbers.
//
inline bool greaterThan( const RNumber& n1, const RNumber& n2, bool orEqual )
{
  const unsigned int n1wc = n1._wordCount;
  const unsigned int n2wc = n2._wordCount;
  const unsigned int minwc = min( n1wc, n2wc );

  const unsigned int* value = n1._valueBuffer;
  const unsigned int* numValue = n2._valueBuffer;

  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;

  if ( n1wc > n2wc )
    {
      for ( i = 0; i < n1wc - n2wc; i++ )
	if ( value[i] != 0 )
	  return true;

      j = i;
    }
  else if ( n1wc < n2wc )
    {
      for ( i = 0; i < n2wc - n1wc; i++ )
	if ( numValue[i] != 0 )
	  return false;

      k = i;
    }

  for ( i = 0; i < minwc; i++, j++, k++ )
    {
      if ( value[j] < numValue[k] )
	return false;
      else if ( value[j] > numValue[k] )
	return true;
    }

  return orEqual;
}


//
// Non-member function for boolean greater than of an RNumber and an unsigned.
//
inline bool greaterThan( const RNumber& n1, unsigned int n2, bool orEqual )
{
  const unsigned int n1wc = n1._wordCount;
  const unsigned int* value = n1._valueBuffer;
  unsigned int i = 0;

  if ( n1wc > 1 )
    {
      for ( i = 0; i < n1wc - 1; i++ )
	if ( value[i] != 0 )
	  return true;
    }

  if ( value[i] < n2 )
    return false;
  else if ( value[i] > n2 )
    return true;

  return orEqual;
}


//
// Non-member function for boolean greater than of an unsigned and an RNumber.
//
inline bool greaterThan( unsigned int n1, const RNumber& n2, bool orEqual )
{
  const unsigned int n2wc = n2._wordCount;
  const unsigned int* numValue = n2._valueBuffer;
  unsigned int i = 0;

  if ( n2wc > 1 )
    {
      for ( i = 0; i < n2wc - 1; i++ )
	if ( numValue[i] != 0 )
	  return false;
    }

  if ( n1 < numValue[i] )
    return false;
  else if ( n1 > numValue[i] )
    return true;

  return orEqual;
}


//
// Non-member function for boolean greater than of two RNumbers.
//
inline bool operator>( const RNumber& n1, const RNumber& n2 )
{
  return greaterThan( n1, n2, false );
}


//
// Non-member function for boolean greater than of an RNumber and an unsigned.
//
inline bool operator>( const RNumber& n1, unsigned int n2 )
{
  return greaterThan( n1, n2, false );
}


//
// Non-member function for boolean greater than of an unsigned and an RNumber.
//
inline bool operator>( unsigned int n1, const RNumber& n2 )
{
  return greaterThan( n1, n2, false );
}


//
// Non-member function for boolean greater than or equal of two RNumbers.
//
inline bool operator>=( const RNumber& n1, const RNumber& n2 )
{
  return greaterThan( n1, n2, true );
}


//
// Non-member function for boolean greater than or equal of an RNumber and an unsigned.
//
inline bool operator>=( const RNumber& n1, unsigned int n2 )
{
  return greaterThan( n1, n2, true );
}


//
// Non-member function for boolean greater than or equal of an unsigned and an RNumber.
//
inline bool operator>=( unsigned int n1, const RNumber& n2 )
{
  return greaterThan( n1, n2, true );
}


//
// A signed version of boolean less than.
//
inline bool RNumber::signedLT( const RNumber& number ) const
{
  unsigned int sign1 = 0;
  unsigned int sign2 = 0;

  if ( _size == number._size )
    {
      sign1 = getBit( 0 );
      sign2 = number.getBit( 0 );
    }
  else if ( _size < number._size )
    sign2 = number.getBit( 0 );
  else
    sign1 = getBit(0);

  if ( sign1 == 1 && sign2 == 0 )
    return true;
  else if ( sign1 == 0 && sign2 == 1 )
    return false;
  else
    return ( *this < number );
}


//
// A signed version of boolean less than or equal.
//
inline bool RNumber::signedLE( const RNumber& number ) const
{
  return ( signedLT( number ) || *this == number );
}


//
// A signed version of boolean greater than.
//
inline bool RNumber::signedGT( const RNumber& number ) const
{
  unsigned int sign1 = 0;
  unsigned int sign2 = 0;

  if ( _size == number._size )
    {
      sign1 = getBit( 0 );
      sign2 = number.getBit( 0 );
    }
  else if ( _size < number._size )
    sign2 = number.getBit( 0 );
  else
    sign1 = getBit( 0 );

  if ( sign1 == 1 && sign2 == 0 )
    return false;
  else if ( sign1 == 0 && sign2 == 1 )
    return true;
  else
    return ( *this > number );
}


//
// A signed version of boolean greater than or equal.
//
inline bool RNumber::signedGE( const RNumber& number ) const
{
  return ( signedGT( number ) || *this == number );
}

//
// Generate and return a checksum code.
//
inline unsigned int RNumber::code() const
{
  unsigned int code = 0;
  for ( unsigned int i = 0; i < _wordCount; i++ )
    code ^= _valueBuffer[i];
  return code;
}


//
// Return the numeric data in an unsigned integer. Loss of data will occur if
// the size of the number is greater than the size of an unsigned int.
//
inline unsigned int RNumber::getUInt() const
{
  return _valueBuffer[_wordCount - 1];
}

//
// Return the bit-size that the number value is occupying.
//
inline unsigned RNumber::size() const
{
  return _size;
}

// 
// Return size in words.
//
inline unsigned RNumber::wordcount() const
{
  return _wordCount;
}

//
// Access the word-buffer used to store the integer.
//
inline const unsigned *RNumber::buffer() const
{
  return _valueBuffer;
}

//
// Return the current sizing state -- either fixed or dynamic.
//
inline RNumber::Sizing RNumber::sizing() const
{
  return _sizing;
}

//
// Set the sizing state to dynamic.
//
inline void RNumber::setDynamic()
{
  _sizing = dynamic;
}


//
// Set the sizing state to fixed.
//
inline void RNumber::setFixed()
{
  _sizing = fixed;
}

inline size_t RNumber::Hash::operator()( const RNumber& num ) const 
{ 
  return num.code(); 
}

inline size_t RNumber::Equal::operator()( const RNumber& num1, const RNumber& num2 ) const 
{ 
  return (num1 == num2); 
}

#endif
