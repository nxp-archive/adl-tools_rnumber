/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** This is a C wrapper for the C++ RNumber class.
** ===========================================================================
*/
#include "C-RNumber.h"
#include "RNumber.h"

RNumber * rnumber_create() 
{
  return new RNumber();
}

RNumber * rnumber_create_from_unsigned( unsigned int number )
{
  return new RNumber (number);
}

RNumber * rnumber_create_from_unsigned_variable_sizing( unsigned int number )
{
  return new RNumber(number, RNumber::dynamic);
}

RNumber * rnumber_create_from_unsigned_of_size( unsigned int number, unsigned int size )
{
  return new RNumber(number, size);
}

RNumber * rnumber_create_from_unsigned_of_size_variable_sizing( unsigned int number, unsigned int size )
{
  return new RNumber(number, size, RNumber::dynamic);
}

RNumber * rnumber_create_from_string(  char * number  )
{
  return new RNumber( string(number));
}

RNumber * rnumber_create_from_string_variable_sizing( const char * number )
{
  return new RNumber( string(number), RNumber::dynamic);
}

RNumber * rnumber_create_from_string_of_size( char * number, unsigned int size )
{
  return new RNumber( string(number), size);
}

RNumber * rnumber_create_from_string_of_size_variable_sizing( char * number, unsigned int size )
{
  return new RNumber ( string(number), size, RNumber::dynamic);
}

static RNumber::Radix get_radix(int radix) 
{
  switch (radix) 
    {
    case 10:
      return RNumber::rdec;
      break;
    case 16:
      return RNumber::rhex;
      break;
    case 2:
      return RNumber::rbin;
      break;
    case 0:
    default:
      return RNumber::rios;
      break;
    }
  return RNumber::rios;
}

RNumber * rnumber_create_from_string_of_radix( char * number, int radix )
{
  return new RNumber( string(number), get_radix(radix));
}

RNumber * rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix )
{
  return new RNumber( string(number), get_radix(radix), RNumber::dynamic);
}

RNumber * rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix)
{
  return new RNumber( string(number), size, get_radix(radix));
}

RNumber * rnumber_create_from_string_of_size_of_radix_variable_sizing( char * number, unsigned int size, int radix) 
{
  return new RNumber( string(number), size, get_radix(radix), RNumber::dynamic);
}

RNumber * rnumber_create_from_numVector( unsigned int* numVector, unsigned int wordCount, unsigned int size )
{
  return new RNumber( numVector, wordCount, size );
}

RNumber * rnumber_create_from_numVector_variable_sizing(unsigned int* numVector, unsigned int wordCount, unsigned int size )
{
  return new RNumber( numVector, wordCount, size, RNumber::dynamic);
}

RNumber * rnumber_create_from_rnumber( const RNumber * rnumber )
{
  return new RNumber(*rnumber);
}

RNumber * rnumber_copy_to_size( const RNumber * number, unsigned int size)
{
  return new RNumber(*number, size);
}

RNumber * rnumber_copy_to_size_variable_sizing( const RNumber * number, unsigned int size)
{
  return new RNumber(*number, size, RNumber::dynamic);
}

void rnumber_destroy( RNumber * rnumber )
{
  delete rnumber;
}

// Assignment methods. operator=() assigns the value constrained by sizing;
// assign() assigns the value with dynamic sizing; clone() assigns all
// attributes; resize() truncates/expands the value and sets fixed sizing.
RNumber * rnumber_assign_from_uint ( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber) = number);
}

RNumber * rnumber_assign_from_string ( RNumber * rnumber, char * number_string )
{
  return &( (*rnumber) = string(number_string));
}

RNumber * rnumber_assign( RNumber * rnumber, RNumber * number )
{
  return &( (*rnumber) = (*number));
}

RNumber * rnumber_copy( RNumber * rnumber, RNumber * number )
{
  return &(rnumber->copy(*number));
}

void rnumber_resize( RNumber * rnumber, unsigned int size )
{
  rnumber->resize(size);
}

  // Unary arithmetic operators.
RNumber * rnumber_unary_minus( RNumber * rnumber)
{
  return new RNumber(-(*rnumber));
}

RNumber * rnumber_unary_tilde( RNumber * rnumber)
{
  return new RNumber(~(*rnumber));
}

// Arithmetic assignment operators; assignment size depends on sizing state.
RNumber * rnumber_plus_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)+=(*number));
}

RNumber * rnumber_plus_assign_from_unsigned ( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)+=number);
}

RNumber * rnumber_minus_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)-=(*number));
}

RNumber * rnumber_minus_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)-=number);
}

RNumber * rnumber_multiply_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)*=(*number));
}

RNumber * rnumber_multiply_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)*=number);
}

RNumber * rnumber_divide_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)/=(*number));
}

RNumber * rnumber_divide_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)/=number);
}

RNumber * rnumber_mod_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)%=(*number));
}

RNumber * rnumber_mod_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)%=number);
}

RNumber * rnumber_bitand_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)&=(*number));
}

RNumber * rnumber_bitand_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)&=number);
}

RNumber * rnumber_bitor_assign( RNumber * rnumber,  RNumber * number )
{
  return &((*rnumber)|=(*number));
}

RNumber * rnumber_bitor_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)|=number);
}

RNumber * rnumber_bitxor_assign( RNumber * rnumber, RNumber * number )
{
  return &((*rnumber)^=(*number));
}

RNumber * rnumber_bitxor_assign_from_unsigned( RNumber * rnumber, unsigned int number )
{
  return &((*rnumber)^=number);
}

RNumber * rnumber_leftshift_assign( RNumber * rnumber, RNumber * shift )
{
  return &((*rnumber)<<=(*shift));
}

RNumber * rnumber_leftshift_assign_from_unsigned( RNumber * rnumber, unsigned int shift )
{
  return &((*rnumber)<<=shift);
}

RNumber * rnumber_rightshift_assign( RNumber * rnumber,  RNumber * shift )
{
  return &((*rnumber)>>=(*shift));
}

RNumber * rnumber_rightshift_assign_from_unsigned( RNumber * rnumber, unsigned int shift )
{
  return &((*rnumber)>>=shift);
}

// Unary conditional expression operators.
int rnumber_not( RNumber * rnumber)
{
  return !(*rnumber);
}

  // Signed conditional expression operators.
int rnumber_signed_lessthan( RNumber * rnumber, RNumber * number )
{
  return rnumber->signedLT(*number);
}

int rnumber_signed_lessequal( RNumber * rnumber, RNumber * number )
{
  return rnumber->signedLE(*number);
}

int rnumber_signed_greaterthan( RNumber * rnumber, RNumber * number )
{
  return rnumber->signedGT(*number);
}

int rnumber_signed_greaterequal( RNumber * rnumber, RNumber * number )
{
  return rnumber->signedGE(*number);
}

int  rnumber_compare( RNumber * rnumber, RNumber * number )
{
  return rnumber->compare(*number);
}

  // Miscellaneous bit manipulation methods.
RNumber * rnumber_invert( RNumber * rnumber)
{
  return &rnumber->invert();
}

RNumber * rnumber_negate( RNumber * rnumber)
{
  return &rnumber->negate();
}

RNumber * rnumber_set_all( RNumber * rnumber)
{
  return &rnumber->setAll();
}

RNumber * rnumber_clear_all( RNumber * rnumber)
{
  return &rnumber->clearAll();
}

RNumber * rnumber_sign_extend( RNumber * rnumber, unsigned int bit )
{
  return &rnumber->signExtend(bit);
}

RNumber * rnumber_truncate( RNumber * rnumber, unsigned int size )
{
  return &rnumber->truncate(size);
}

  // Bit value accessors and manipulators.
unsigned int rnumber_getbit( RNumber * rnumber, unsigned int pos)
{
  return rnumber->getBit(pos);
}

unsigned int rnumber_getbit_lsb( RNumber * rnumber, unsigned int pos )
{
  return rnumber->getBitLSB(pos);
}

void rnumber_setbit( RNumber * rnumber, unsigned int pos, unsigned int value )
{
  return rnumber->setBit(pos,value);
}

void rnumber_setbit_lsb( RNumber * rnumber, unsigned int pos, unsigned int value )
{
  return rnumber->setBitLSB(pos, value);
}

void rnumber_assignbit( RNumber * rnumber, unsigned int pos, unsigned int value )
{
  return rnumber->assignBit(pos, value);
}

void rnumber_assignbit_lsb( RNumber * rnumber, unsigned int pos, unsigned int value )
{
  return rnumber->assignBitLSB(pos, value);
}

  // Value accessors.
unsigned int rnumber_get_uint( RNumber * rnumber)
{
  return rnumber->getUInt();
}

char * rnumber_cstr( const RNumber * rnumber) 
{
  string str = rnumber->str();
  char * return_value = reinterpret_cast<char*>(malloc( str.size() + 1));
  strcpy(return_value, str.c_str());
  return return_value;
}

char * rnumber_cstr_radix( const RNumber * rnumber, int radix, int bool_prefix)
{
  string str = rnumber->strradix(get_radix(radix), bool_prefix);
  char * return_value = reinterpret_cast<char *>(malloc( str.size() + 1));
  strcpy(return_value, str.c_str());
  return return_value;
}

  // Value field accessors and manipulators.
int rnumber_get_int_field( RNumber * rnumber, unsigned int start, unsigned int end )
{
  return rnumber->getIntField(start, end);
}

unsigned int rnumber_get_uint_field( RNumber * rnumber,unsigned int start, unsigned int end )
{
  return rnumber->getUIntField(start, end);
}

RNumber * rnumber_getfield( RNumber * rnumber, unsigned int start, unsigned int end )
{
  return new RNumber(rnumber->getField(start, end));
}

void rnumber_set_field( RNumber * rnumber, unsigned int start, unsigned int end, RNumber * num )
{
  return rnumber->setField(start, end, (*num));
}

  // Attribute accessors and manipulators.
unsigned rnumber_size( const struct RNumber * rnumber)
{
  return rnumber->size();
}

unsigned rnumber_wordcount( const RNumber * rnumber)
{
  return rnumber->wordcount();
}

const unsigned * rnumber_buffer( RNumber * rnumber) 
{
  return rnumber->buffer();
}

unsigned int rnumber_get_default_size()
{
  return RNumber::getDefaultSize();
}

void rnumber_set_default_size( unsigned int size )
{
  return RNumber::setDefaultSize(size);
}

int rnumber_sizing( RNumber * rnumber)
{
  return rnumber->sizing();
}

int rnumber_dynamic()
{
  return RNumber::dynamic;
}

int rnumber_fixed()
{
  return RNumber::fixed;
}

void rnumber_set_dynamic( RNumber * rnumber)
{
  rnumber->setDynamic();
}

void rnumber_set_fixed( RNumber * rnumber)
{
  rnumber->setFixed();
}

  // Streaming I/O methods.
void rnumber_print_to_os( const RNumber * rnumber, void * os )
{
  ostream * oos = reinterpret_cast<ostream *>(os);
  rnumber->printToOS(*oos);
}

void rnumber_print_with_radix( const RNumber * rnumber, void * os, int radix, int bool_prefix ) 
{
  ostream * oos = reinterpret_cast<ostream *>(os);
  rnumber->printWithRadix(*oos, get_radix(radix), bool_prefix);
}

//friend istream& operator>>( istream& is, RNumber& number );
//friend ostream& operator<<( ostream& os, const RNumber& number );
void rnumber_read_from_is( RNumber * rnumber, void * is )
{
  istream * iis = reinterpret_cast<istream *>(is);
  (*iis) >> (*rnumber);
}

void rnumber_write_to_os( RNumber * rnumber, void * os )
{
  ostream * oos = reinterpret_cast<ostream *>(os);
  (*oos) << (*rnumber);
}

// Non-member functions that allow for mixed arithmetic expressions between
// RNumbers and unsigned integers.
struct RNumber * rnumber_rn_plus_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber(*n1 + *n2);
}
 struct RNumber * rnumber_rn_plus_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber(*n1 + n2);
}
 struct RNumber * rnumber_ui_plus_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(n1 + *n2);
}
 struct RNumber * rnumber_rn_add_ext_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber(addExt(*n1,*n1));
}
 struct RNumber * rnumber_rn_add_ext_ui( const struct RNumber * n1, unsigned int n2 ) {
  return new RNumber(addExt(*n1,n2));
}
 struct RNumber * rnumber_ui_add_ext_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(addExt(n1,*n2));
}
 struct RNumber * rnumber_rn_minus_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber((*n1)-(*n2));
}
 struct RNumber * rnumber_rn_minus_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber(*n1-n2);
}
 struct RNumber * rnumber_ui_minus_rn( unsigned int n1, const struct RNumber * n2 ) {
  return new RNumber(n1-(*n2));
}
 struct RNumber * rnumber_rn_multiply_rn( const struct RNumber * n1, const struct RNumber * n2 ) {
  return new RNumber((*n1)*(*n2));
}
 struct RNumber * rnumber_rn_multiply_ui( const struct RNumber * n1, unsigned int n2 ) {
  return new RNumber((*n1)*n2);
}
 struct RNumber * rnumber_ui_multiply_ui( unsigned int n1, const struct RNumber * n2 ) {
  return new RNumber(n1*(*n2));
}
 struct RNumber * rnumber_rn_multiply_ext_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber(multiplyExt(*n1,*n2));
}
 struct RNumber * rnumber_rn_multiply_ext_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber(multiplyExt(*n1,n2));
}
 struct RNumber * rnumber_ui_multiply_ext_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(multiplyExt(n1,*n2));
}
 struct RNumber * rnumber_rn_divide_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber((*n1)/(*n2));
}
 struct RNumber * rnumber_rn_divide_ui( const struct RNumber * n1, unsigned int n2 ) {
  return new RNumber((*n1)/n2);
}
 struct RNumber * rnumber_ui_divide_rn( unsigned int n1, const struct RNumber * n2 ) {
  return new RNumber(n1/(*n2));
}
 struct RNumber * rnumber_rn_mod_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber((*n1)%(*n2));
}
 struct RNumber * rnumber_rn_mod_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber((*n1)%n2);
}
 struct RNumber * rnumber_ui_mod_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(n1%(*n2));
}
 struct RNumber * rnumber_rn_bitand_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber((*n1)&(*n2));
}
 struct RNumber * rnumber_rn_bitand_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber((*n1)&n2);
}
 struct RNumber * rnumber_ui_bitand_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(n1&(*n2));
}
 struct RNumber * rnumber_rn_bitor_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber((*n1)|(*n2));
}
 struct RNumber * rnumber_rn_bitor_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber((*n1)|n2);
}
 struct RNumber * rnumber_ui_bitor_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(n1|(*n2));
}
 struct RNumber * rnumber_rn_bitxor_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber((*n1)^(*n2));
}
 struct RNumber * rnumber_rn_bitxor_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber((*n1)^n2);
}
 struct RNumber * rnumber_ui_bitxor_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(n1^(*n2));
}
 struct RNumber * rnumber_rn_leftshift_rn( const struct RNumber * n, const struct RNumber * shift ){
  return new RNumber((*n)<<(*shift));
}
 struct RNumber * rnumber_rn_leftshift_ui( const struct RNumber * n, unsigned int shift ){
  return new RNumber((*n)<<shift);
}
 struct RNumber * rnumber_ui_leftshift_rn( unsigned int n, const struct RNumber * shift ){
  return new RNumber(n<<(*shift));
}
 struct RNumber * rnumber_rn_leftshift_ext_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return new RNumber(leftShiftExt(*n1,*n2));
}
 struct RNumber * rnumber_rn_leftshift_ext_ui( const struct RNumber * n1, unsigned int n2 ){
  return new RNumber(leftShiftExt(*n1,n2));
}
 struct RNumber * rnumber_ui_leftshift_ext_rn( unsigned int n1, const struct RNumber * n2 ){
  return new RNumber(leftShiftExt(n1,*n2));
}
 struct RNumber * rnumber_rn_rightshift_rn( const struct RNumber * n, const struct RNumber * shift ){
  return new RNumber((*n)>>(*shift));
}
 struct RNumber * rnumber_rn_rightshift_ui( const struct RNumber * n, unsigned int shift ){
  return new RNumber((*n)>>shift);
}
 struct RNumber * rnumber_ui_rightshift_rn( unsigned int n, const struct RNumber * shift ){
  return new RNumber(n>>(*shift));
}

// Non-member functions that allow for mixed conditional expressions between
// RNumbers and unsigned integers.
int rnumber_rn_notequal_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return (*n1)!=(*n2);
}
int rnumber_rn_notequal_ui( const struct RNumber * n1, unsigned int n2 ) {
  return (*n1)!=n2;
}
int rnumber_ui_notequal_rn( unsigned int n1, const struct RNumber * n2 ){
  return n1!=(*n2);
}
int rnumber_rn_equal_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return (*n1)==(*n2);
}
int rnumber_rn_equal_ui( const struct RNumber * n1, unsigned int n2 ){
  return (*n1)==n2;
}
int rnumber_ui_equal_rn( unsigned int n1, const struct RNumber * n2 ){
  return n1==(*n2);
}
int rnumber_rn_lessthan_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return (*n1)<(*n2);
}
int rnumber_rn_lessthan_ui( const struct RNumber * n1, unsigned int n2 ){
  return (*n1)<n2;
}
int rnumber_ui_lessthan_rn( unsigned int n1, const struct RNumber * n2 ){
  return n1<(*n2);
}
int rnumber_rn_lessequal_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return (*n1)<=(*n2);
}
int rnumber_rn_lessequal_ui( const struct RNumber * n1, unsigned int n2 ){
  return (*n1)<=n2;
}
int rnumber_ui_lessequal_rn( unsigned int n1, const struct RNumber * n2 ){
  return n1<=(*n2);
}
int rnumber_rn_greaterthan_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return (*n1)>(*n2);
}
int rnumber_rn_greaterthan_ui( const struct RNumber * n1, unsigned int n2 ){
  return (*n1)>n2;
}
int rnumber_ui_greaterthan_rn( unsigned int n1, const struct RNumber * n2 ){
  return n1>(*n2);
}
int rnumber_rn_greaterequal_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return (*n1)>=(*n2);
}
int rnumber_rn_greaterequal_ui( const struct RNumber * n1, unsigned int n2 ){
  return (*n1)>=n2;
}
int rnumber_ui_greaterequal_rn( unsigned int n1, const struct RNumber * n2 ){
  return n1>=(*n2);
}

int rnumber_rhex() { return RNumber::rhex;}
int rnumber_rbin() { return RNumber::rbin;}
int rnumber_rdec() { return RNumber::rdec;}
