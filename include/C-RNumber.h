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
#ifndef C-RNumber_h
#define C-RNumber_h "$Id$"

#include "types.h"

#ifdef _cplusplus
#extern "C" {
#endif
 
const unsigned int WORD_THRESHOLD = 2;
class RNumber;

RNumber * rnumber_create();
RNumber * rnumber_create_from_int( unsigned int number );
RNumber * rnumber_create_from_int_variable_sizing( unsigned int number );
RNumber * rnumber_create_of_size( unsigned int number, unsigned int size );
RNumber * rnumber_create_of_size_variable_sizing( unsigned int number, unsigned int size );
RNumber * rnumber_create_from_string( char * number  );
RNumber * rnumber_create_from_string_variable_sizing( char * number, Sizing sizing = fixed );
RNumber * rnumber_create_from_string_of_size( char * number, unsigned int size );
RNumber * rnumber_create_from_string_of_size_variable_sizing(  char * number, unsigned int size );
RNumber * rnumber_create_from_string_of_radix( char * number, int radix );
RNumber * rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix );
RNumber * rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix);
RNumber * rnumber_create_from_string_of_size_of_radix_variable_sizing( char * number, unsigned int size, int radix);
RNumber * rnumber_create_from_numVector( unsigned int* numVector, unsigned int wordCount, unsigned int size );
RNumber * rnumber_create_from_numVector_variable_size( unsigned int* numVector, unsigned int wordCount, unsigned int size );

RNumber * rnumber_copy( const RNumber * rnumber );
RNumber * rnumber_copy_to_size( const RNumber * number, unsigned int size);
RNumber * rnumber_copy_to_size_variable_size( const RNumber * number, unsigned int size);
void rnumber_destroy( RNumber * rnumber );

  // Assignment methods. operator=() assigns the value constrained by sizing;
  // assign() assigns the value with dynamic sizing; clone() assigns all
  // attributes; resize() truncates/expands the value and sets fixed sizing.
RNumber * rnumber_assign_from_int ( RNumber * rnumber, int number );
RNumber * rnumber_assign_from_string ( RNumber * rnumber, char * number_string );
RNumber * rnumber_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_copy( RNumber * rnumber, RNumber * number );
void      rnumber_resize( RNumber * rnumber, unsigned int size );

  // Unary arithmetic operators.
RNumber * rnumber_unary_minus( RNumber * rnumber);
RNumber * rnumber_unary_tilde( RNumber * rnumber);

  // Arithmetic assignment operators; assignment size depends on sizing state.
RNumber * rnumber_plus_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_plus_assign_from_int ( RNumber * rnumber, unsigned int number );
RNumber * rnumber_minus_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_minus_assign_from_int( RNumber * rnumber, unsigned int number );
RNumber * rnumber_mult_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_mult_assign_from_int( RNumber * rnumber, unsigned int number );
RNumber * rnumber_div_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_div_assign( RNumber * rnumber, unsigned int number );
RNumber * rnumber_mod_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_mod_assign_from_int( RNumber * rnumber, unsigned int number );
RNumber * rnumber_bitand_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_bitand_assign_from_int( RNumber * rnumber, unsigned int number );
RNumber * rnumber_bitor_assign( RNumber * rnumber,  RNumber * number );
RNumber * rnumber_bitor_assign_from_int( RNumber * rnumber, unsigned int number );
RNumber * rnumber_bitxor_assign( RNumber * rnumber, RNumber * number );
RNumber * rnumber_bitxor_assign_from_int( RNumber * rnumber, unsigned int number );
RNumber * rnumber_leftshift_assign( RNumber * rnumber, RNumber * shift );
RNumber * rnumber_leftshift_assign_from_int( RNumber * rnumber, unsigned int shift );
RNumber * rnumber_rightshift_assign( RNumber * rnumber,  RNumber * shift );
RNumber * rnumber_rightshift_assign_from_int( RNumber * rnumber, unsigned int shift );

  // Unary conditional expression operators.
bool rnumber_not();

  // Signed conditional expression operators.
bool rnumber_signed_lessthan( RNumber * rnumber, RNumber * number );
bool rnumber_signed_lessequal( RNumber * rnumber, RNumber * number );
bool rnumber_signed_greaterthan( RNumber * rnumber, RNumber * number );
bool rnumber_signed_greaterequal( RNumber * rnumber, RNumber * number );
int  rnumber_compare( RNumber * rnumber, RNumber * number );

  // Miscellaneous bit manipulation methods.
RNumber * rnumber_invert( RNumber * rnumber);
RNumber * rnumber_negate( RNumber * rnumber);
RNumber * rnumber_set_all( RNumber * rnumber);
RNumber * rnumber_clear_all( RNumber * rnumber);
RNumber * rnumber_sign_extend( RNumber * rnumber, unsigned int bit );
RNumber * rnumber_truncate( RNumber * rnumber, unsigned int size );

  // Bit value accessors and manipulators.
unsigned int rnumber_getbit( RNumber * rnumber, unsigned int pos);
unsigned int rnumber_getbit_lsb( RNumber * rnumber, unsigned int pos );
void rnumber_setbit( RNumber * rnumber, unsigned int pos, unsigned int value );
void rnumber_setbit_lsb( RNumber * rnumberunsigned int pos, unsigned int value );
void rnumber_assignbit( RNumber * rnumber, unsigned int pos, unsigned int value );
void rnumber_assignbit_lsb( unsigned int pos, unsigned int value );

  // Value accessors.
unsigned int rnumber_get_uint( RNumber * rnumber);
char * rnumber_cstr( RNumber * rnumber) const;
char * rnumber_cstr_radix( RNumber * rnumber, int radix,int bool_prefix) const;

  // Value field accessors and manipulators.
int rnumber_get_int_field( RNumber * rnumber, unsigned int start, unsigned int end );
unsigned int rnumber_get_uint_field( RNumber * rnumber,unsigned int start, unsigned int end );
RNumber * rnumber_getfield( RNumber * rnumber, unsigned int start, unsigned int end );
void rnumber_set_field( RNumber * rnumber, unsigned int start, unsigned int end, RNumber * num );

  // Attribute accessors and manipulators.
unsigned rnumber_size( RNumber * rnumber);
unsigned rnumber_wordcount( RNumber * rnumber);

unsigned * rnumber_buffer( RNumber * rnumber) const;

unsigned int rnumber_get_default_size();
void rnumber_set_default_size( unsigned int size );

int rnumber_sizing( RNumber * rnumber);
void rnumber_set_dynamic( RNumber * rnumber);
void rnumber_set_fixed( RNumber * rnumber);

  // Streaming I/O methods.
void rnumber_print_to_os( RNumber * rnumber, void * os );
void rnumber_print_with_radix( Rnumber, * rnumber, void * os, int radix, bool prefix=false ) const;

//friend istream& operator>>( istream& is, RNumber& number );
//friend ostream& operator<<( ostream& os, const RNumber& number );
void rnumber_read_from_is( RNumber * rnumber, void * is );
void rnumber_write_to_os( RNumber * rnumber, void * os );

//   friend struct Hash {
//     size_t operator()( const RNumber& num ) const;
//   };

//   friend struct Equal {
//     size_t operator()( const RNumber& num1, const RNumber& num2 ) const;
//   };

#ifdef _cplusplus
}
#endif

#endif
