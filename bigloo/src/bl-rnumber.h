/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** This file wraps the C-RNumber.h functions which return allocated
** memory so that bigloo can garbage collect them.
** The new functions are prepended with bl_
**
**
** All RNumber * references have been changed to RNumber_proxy_t references
** and the guts are extracted for callin C-RNumber functions.
** ===========================================================================
*/
#ifndef bl_RNumber_h
#define bl_RNumber_h "$Id$"

#ifdef __cplusplus
class RNumber;
extern "C" {
#else
  struct RNumber; 
#endif

#include "rnumber/rnumber_proxy.h"
#define WORD_THRESHOLD 2

RNumber_proxy_t bl_rnumber_create(); 
RNumber_proxy_t bl_rnumber_create_from_unsigned( unsigned int number );
RNumber_proxy_t bl_rnumber_create_from_unsigned_variable_sizing( unsigned int number );
RNumber_proxy_t bl_rnumber_create_from_unsigned_of_size( unsigned int number, unsigned int size );
RNumber_proxy_t bl_rnumber_create_from_unsigned_of_size_variable_sizing( unsigned int number, unsigned int size );
RNumber_proxy_t bl_rnumber_create_from_string( char * number  );
RNumber_proxy_t bl_rnumber_create_from_string_variable_sizing( char * number );
RNumber_proxy_t bl_rnumber_create_from_string_of_size( char * number, unsigned int size );
RNumber_proxy_t bl_rnumber_create_from_string_of_size_variable_sizing(  char * number, unsigned int size );
RNumber_proxy_t bl_rnumber_create_from_string_of_radix( char * number, int radix );
RNumber_proxy_t bl_rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix );
RNumber_proxy_t bl_rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix);
RNumber_proxy_t bl_rnumber_create_from_string_of_size_of_radix_variable_sizing( char * number, unsigned int size, int radix);
RNumber_proxy_t bl_rnumber_create_from_numVector( unsigned int* numVector, unsigned int wordCount, unsigned int size );
RNumber_proxy_t bl_rnumber_create_from_numVector_variable_sizing( unsigned int* numVector, unsigned int wordCount, unsigned int size );

RNumber_proxy_t bl_rnumber_create_from_rnumber( RNumber_proxy_t rnumber );
RNumber_proxy_t bl_rnumber_copy_to_size( RNumber_proxy_t number, unsigned int size);
RNumber_proxy_t bl_rnumber_copy_to_size_variable_sizing( RNumber_proxy_t number, unsigned int size);

  // Unary arithmetic operators.
RNumber_proxy_t bl_rnumber_unary_minus( RNumber_proxy_t rnumber);
RNumber_proxy_t bl_rnumber_unary_tilde( RNumber_proxy_t rnumber);

RNumber_proxy_t bl_rnumber_getfield( RNumber_proxy_t rnumber, unsigned int start, unsigned int end );

// Non-member functions that allow for mixed arithmetic expressions between
// RNumbers and unsigned integers.
RNumber_proxy_t bl_rnumber_rn_plus_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_plus_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_plus_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_add_ext_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_add_ext_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_add_ext_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_minus_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_minus_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_minus_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_multiply_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_multiply_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_multiply_ui( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_multiply_ext_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_multiply_ext_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_multiply_ext_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_divide_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_divide_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_divide_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_mod_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_mod_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_mod_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_bitand_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_bitand_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_bitand_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_bitor_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_bitor_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_bitor_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_bitxor_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_bitxor_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_bitxor_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_leftshift_rn( RNumber_proxy_t n, RNumber_proxy_t shift );
RNumber_proxy_t bl_rnumber_rn_leftshift_ui( RNumber_proxy_t n, unsigned int shift );
RNumber_proxy_t bl_rnumber_ui_leftshift_rn( unsigned int n, RNumber_proxy_t shift );
RNumber_proxy_t bl_rnumber_rn_leftshift_ext_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_leftshift_ext_ui( RNumber_proxy_t n1, unsigned int n2 );
RNumber_proxy_t bl_rnumber_ui_leftshift_ext_rn( unsigned int n1, RNumber_proxy_t n2 );
RNumber_proxy_t bl_rnumber_rn_rightshift_rn( RNumber_proxy_t n, RNumber_proxy_t shift );
RNumber_proxy_t bl_rnumber_rn_rightshift_ui( RNumber_proxy_t n, unsigned int shift );
RNumber_proxy_t bl_rnumber_ui_rightshift_rn( unsigned int n, RNumber_proxy_t shift );

  /* <here> */
void bl_rnumber_destroy( RNumber_proxy_t rnumber );
RNumber_proxy_t bl_rnumber_assign_from_uint ( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_assign_from_string ( RNumber_proxy_t rnumber, char * number_string );
RNumber_proxy_t bl_rnumber_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_copy( RNumber_proxy_t rnumber, RNumber_proxy_t number );
void      bl_rnumber_resize( RNumber_proxy_t rnumber, unsigned int size );
RNumber_proxy_t bl_rnumber_plus_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_plus_assign_from_unsigned ( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_minus_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_minus_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_multiply_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_multiply_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_divide_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_divide_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_mod_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_mod_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_bitand_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_bitand_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_bitor_assign( RNumber_proxy_t rnumber,  RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_bitor_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_bitxor_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number );
RNumber_proxy_t bl_rnumber_bitxor_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number );
RNumber_proxy_t bl_rnumber_leftshift_assign( RNumber_proxy_t rnumber, RNumber_proxy_t shift );
RNumber_proxy_t bl_rnumber_leftshift_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int shift );
RNumber_proxy_t bl_rnumber_rightshift_assign( RNumber_proxy_t rnumber,  RNumber_proxy_t shift );
RNumber_proxy_t bl_rnumber_rightshift_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int shift );
int bl_rnumber_not( RNumber_proxy_t rnumber);
int bl_rnumber_signed_lessthan( RNumber_proxy_t rnumber, RNumber_proxy_t number );
int bl_rnumber_signed_lessequal( RNumber_proxy_t rnumber, RNumber_proxy_t number );
int bl_rnumber_signed_greaterthan( RNumber_proxy_t rnumber, RNumber_proxy_t number );
int bl_rnumber_signed_greaterequal( RNumber_proxy_t rnumber, RNumber_proxy_t number );
int bl_rnumber_compare( RNumber_proxy_t rnumber, RNumber_proxy_t number );

  // Miscellaneous bit manipulation methods.
RNumber_proxy_t bl_rnumber_invert( RNumber_proxy_t rnumber);
RNumber_proxy_t bl_rnumber_negate( RNumber_proxy_t rnumber);
RNumber_proxy_t bl_rnumber_set_all( RNumber_proxy_t rnumber);
RNumber_proxy_t bl_rnumber_clear_all( RNumber_proxy_t rnumber);
void bl_rnumber_sign_extend( RNumber_proxy_t rnumber, unsigned int bit );
RNumber_proxy_t bl_rnumber_truncate( RNumber_proxy_t rnumber, unsigned int size );
unsigned int bl_rnumber_getbit( RNumber_proxy_t rnumber, unsigned int pos);
unsigned int bl_rnumber_getbit_lsb( RNumber_proxy_t rnumber, unsigned int pos );
void bl_rnumber_setbit( RNumber_proxy_t rnumber, unsigned int pos, unsigned int value );
void bl_rnumber_setbit_lsb( RNumber_proxy_t rnumber,unsigned int pos, unsigned int value );
void bl_rnumber_assignbit( RNumber_proxy_t rnumber, unsigned int pos, unsigned int value );
void bl_rnumber_assignbit_lsb( RNumber_proxy_t rnumber, unsigned int pos, unsigned int value );

  // Value accessors.
unsigned int bl_rnumber_get_uint( RNumber_proxy_t rnumber);
char * bl_rnumber_cstr( RNumber_proxy_t rnumber);
char * bl_rnumber_cstr_radix( RNumber_proxy_t rnumber, int radix,int bool_prefix);

  // Value field accessors and manipulators.
int bl_rnumber_get_int_field( RNumber_proxy_t rnumber, unsigned int start, unsigned int end );
unsigned int bl_rnumber_get_uint_field( RNumber_proxy_t rnumber,unsigned int start, unsigned int end );
void bl_rnumber_set_field( RNumber_proxy_t rnumber, unsigned int start, unsigned int end, RNumber_proxy_t num );
unsigned bl_rnumber_size( RNumber_proxy_t rnumber);
unsigned bl_rnumber_wordcount( RNumber_proxy_t rnumber);

const unsigned * bl_rnumber_buffer( RNumber_proxy_t rnumber);

unsigned int bl_rnumber_get_default_size();
void bl_rnumber_set_default_size( unsigned int size );

int bl_rnumber_sizing( RNumber_proxy_t rnumber);
int bl_rnumber_dynamic();
int bl_rnumber_fixed(); 
void bl_rnumber_set_dynamic( RNumber_proxy_t rnumber);
void bl_rnumber_set_fixed( RNumber_proxy_t rnumber);

  // Streaming I/O methods.
void bl_rnumber_print_to_os( RNumber_proxy_t rnumber, void * os );
void bl_rnumber_print_with_radix( RNumber_proxy_t rnumber, void * os, int radix, int bool_prefix );

//friend istream& operator>>( istream& is, RNumber& number );
//friend ostream& operator<<( ostream& os, const RNumber& number );
void bl_rnumber_read_from_is( RNumber_proxy_t rnumber, void * is );
void bl_rnumber_write_to_os( RNumber_proxy_t rnumber, void * os );
int bl_rnumber_rn_notequal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_notequal_ui( RNumber_proxy_t n1, unsigned int n2 );
int bl_rnumber_ui_notequal_rn( unsigned int n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_equal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_equal_ui( RNumber_proxy_t n1, unsigned int n2 );
int bl_rnumber_ui_equal_rn( unsigned int n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_lessthan_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_lessthan_ui( RNumber_proxy_t n1, unsigned int n2 );
int bl_rnumber_ui_lessthan_rn( unsigned int n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_lessequal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_lessequal_ui( RNumber_proxy_t n1, unsigned int n2 );
int bl_rnumber_ui_lessequal_rn( unsigned int n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_greaterthan_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_greaterthan_ui( RNumber_proxy_t n1, unsigned int n2 );
int bl_rnumber_ui_greaterthan_rn( unsigned int n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_greaterequal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 );
int bl_rnumber_rn_greaterequal_ui( RNumber_proxy_t n1, unsigned int n2 );
int bl_rnumber_ui_greaterequal_rn( unsigned int n1, RNumber_proxy_t n2 );

int bl_rnumber_rhex();
int bl_rnumber_rbin();
int bl_rnumber_rdec();

#ifdef __cplusplus
}
#endif

#endif
