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
#ifndef C_RNumber_h
#define C_RNumber_h "$Id$"

#ifdef __cplusplus
class RNumber;
extern "C" {
#else
  struct RNumber;
#endif
 
#define WORD_THRESHOLD 2

struct RNumber * rnumber_create();
struct RNumber * rnumber_create_from_unsigned( unsigned int number );
struct RNumber * rnumber_create_from_unsigned_variable_sizing( unsigned int number );
struct RNumber * rnumber_create_from_unsigned_of_size( unsigned int number, unsigned int size );
struct RNumber * rnumber_create_from_unsigned_of_size_variable_sizing( unsigned int number, unsigned int size );
struct RNumber * rnumber_create_from_string( char * number  );
struct RNumber * rnumber_create_from_string_variable_sizing( char * number );
struct RNumber * rnumber_create_from_string_of_size( char * number, unsigned int size );
struct RNumber * rnumber_create_from_string_of_size_variable_sizing(  char * number, unsigned int size );
struct RNumber * rnumber_create_from_string_of_radix( char * number, int radix );
struct RNumber * rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix );
struct RNumber * rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix);
struct RNumber * rnumber_create_from_string_of_size_of_radix_variable_sizing( char * number, unsigned int size, int radix);
struct RNumber * rnumber_create_from_numVector( unsigned int* numVector, unsigned int wordCount, unsigned int size );
struct RNumber * rnumber_create_from_numVector_variable_sizing( unsigned int* numVector, unsigned int wordCount, unsigned int size );

struct RNumber * rnumber_create_from_rnumber( const struct RNumber * rnumber );
struct RNumber * rnumber_copy_to_size( const struct RNumber * number, unsigned int size);
struct RNumber * rnumber_copy_to_size_variable_sizing( const struct RNumber * number, unsigned int size);
void rnumber_destroy( struct RNumber * rnumber );

  // Assignment methods. operator=() assigns the value constrained by sizing;
  // assign() assigns the value with dynamic sizing; clone() assigns all
  // attributes; resize() truncates/expands the value and sets fixed sizing.
struct RNumber * rnumber_assign_from_uint ( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_assign_from_string ( struct RNumber * rnumber, char * number_string );
struct RNumber * rnumber_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_copy( struct RNumber * rnumber, struct RNumber * number );
void      rnumber_resize( struct RNumber * rnumber, unsigned int size );

  // Unary arithmetic operators.
struct RNumber * rnumber_unary_minus( struct RNumber * rnumber);
struct RNumber * rnumber_unary_tilde( struct RNumber * rnumber);

  // Arithmetic assignment operators; assignment size depends on sizing state.
struct RNumber * rnumber_plus_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_plus_assign_from_unsigned ( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_minus_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_minus_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_multiply_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_multiply_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_divide_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_divide_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_mod_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_mod_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_bitand_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_bitand_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_bitor_assign( struct RNumber * rnumber,  struct RNumber * number );
struct RNumber * rnumber_bitor_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_bitxor_assign( struct RNumber * rnumber, struct RNumber * number );
struct RNumber * rnumber_bitxor_assign_from_unsigned( struct RNumber * rnumber, unsigned int number );
struct RNumber * rnumber_leftshift_assign( struct RNumber * rnumber, struct RNumber * shift );
struct RNumber * rnumber_leftshift_assign_from_unsigned( struct RNumber * rnumber, unsigned int shift );
struct RNumber * rnumber_rightshift_assign( struct RNumber * rnumber,  struct RNumber * shift );
struct RNumber * rnumber_rightshift_assign_from_unsigned( struct RNumber * rnumber, unsigned int shift );

  // Unary conditional expression operators.
int rnumber_not( struct RNumber * rnumber);

  // Signed conditional expression operators.
int rnumber_signed_lessthan( struct RNumber * rnumber, struct RNumber * number );
int rnumber_signed_lessequal( struct RNumber * rnumber, struct RNumber * number );
int rnumber_signed_greaterthan( struct RNumber * rnumber, struct RNumber * number );
int rnumber_signed_greaterequal( struct RNumber * rnumber, struct RNumber * number );
int  rnumber_compare( struct RNumber * rnumber, struct RNumber * number );

  // Miscellaneous bit manipulation methods.
struct RNumber * rnumber_invert( struct RNumber * rnumber);
struct RNumber * rnumber_negate( struct RNumber * rnumber);
struct RNumber * rnumber_set_all( struct RNumber * rnumber);
struct RNumber * rnumber_clear_all( struct RNumber * rnumber);
struct RNumber * rnumber_sign_extend( struct RNumber * rnumber, unsigned int bit );
struct RNumber * rnumber_truncate( struct RNumber * rnumber, unsigned int size );

  // Bit value accessors and manipulators.
unsigned int rnumber_getbit( struct RNumber * rnumber, unsigned int pos);
unsigned int rnumber_getbit_lsb( struct RNumber * rnumber, unsigned int pos );
void rnumber_setbit( struct RNumber * rnumber, unsigned int pos, unsigned int value );
void rnumber_setbit_lsb( struct RNumber * rnumber,unsigned int pos, unsigned int value );
void rnumber_assignbit( struct RNumber * rnumber, unsigned int pos, unsigned int value );
void rnumber_assignbit_lsb( struct RNumber * rnumber, unsigned int pos, unsigned int value );

  // Value accessors.
unsigned int rnumber_get_uint( struct RNumber * rnumber);
char * rnumber_cstr( const struct RNumber * rnumber);
char * rnumber_cstr_radix( const struct RNumber * rnumber, int radix,int bool_prefix);

  // Value field accessors and manipulators.
int rnumber_get_int_field( struct RNumber * rnumber, unsigned int start, unsigned int end );
unsigned int rnumber_get_uint_field( struct RNumber * rnumber,unsigned int start, unsigned int end );
struct RNumber * rnumber_getfield( struct RNumber * rnumber, unsigned int start, unsigned int end );
void rnumber_set_field( struct RNumber * rnumber, unsigned int start, unsigned int end, struct RNumber * num );

  // Attribute accessors and manipulators.
unsigned rnumber_size( const struct RNumber * rnumber);
unsigned rnumber_wordcount( const struct RNumber * rnumber);

const unsigned * rnumber_buffer( struct RNumber * rnumber);

unsigned int rnumber_get_default_size();
void rnumber_set_default_size( unsigned int size );

int rnumber_sizing( struct RNumber * rnumber);
int rnumber_dynamic();
int rnumber_fixed(); 
void rnumber_set_dynamic( struct RNumber * rnumber);
void rnumber_set_fixed( struct RNumber * rnumber);

  // Streaming I/O methods.
void rnumber_print_to_os( const struct RNumber * rnumber, void * os );
void rnumber_print_with_radix( const struct RNumber * rnumber, void * os, int radix, int bool_prefix );

//friend istream& operator>>( istream& is, RNumber& number );
//friend ostream& operator<<( ostream& os, const RNumber& number );
void rnumber_read_from_is( struct RNumber * rnumber, void * is );
void rnumber_write_to_os( struct RNumber * rnumber, void * os );

//   friend struct Hash {
//     size_t operator()( const RNumber& num ) const;
//   };

//   friend struct Equal {
//     size_t operator()( const RNumber& num1, const RNumber& num2 ) const;
//   };

// Non-member functions that allow for mixed arithmetic expressions between
// RNumbers and unsigned integers.
 struct RNumber * rnumber_rn_plus_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_plus_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_plus_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_add_ext_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_add_ext_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_add_ext_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_minus_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_minus_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_minus_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_multiply_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_multiply_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_multiply_ui( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_multiply_ext_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_multiply_ext_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_multiply_ext_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_divide_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_divide_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_divide_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_mod_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_mod_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_mod_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_bitand_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_bitand_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_bitand_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_bitor_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_bitor_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_bitor_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_bitxor_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_bitxor_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_bitxor_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_leftshift_rn( const struct RNumber * n, const struct RNumber * shift );
 struct RNumber * rnumber_rn_leftshift_ui( const struct RNumber * n, unsigned int shift );
 struct RNumber * rnumber_ui_leftshift_rn( unsigned int n, const struct RNumber * shift );
 struct RNumber * rnumber_rn_leftshift_ext_rn( const struct RNumber * n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_leftshift_ext_ui( const struct RNumber * n1, unsigned int n2 );
 struct RNumber * rnumber_ui_leftshift_ext_rn( unsigned int n1, const struct RNumber * n2 );
 struct RNumber * rnumber_rn_rightshift_rn( const struct RNumber * n, const struct RNumber * shift );
 struct RNumber * rnumber_rn_rightshift_ui( const struct RNumber * n, unsigned int shift );
 struct RNumber * rnumber_ui_rightshift_rn( unsigned int n, const struct RNumber * shift );

// Non-member functions that allow for mixed conditional expressions between
// RNumbers and unsigned integers.
int rnumber_rn_notequal_rn( const struct RNumber * n1, const struct RNumber * n2 );
int rnumber_rn_notequal_ui( const struct RNumber * n1, unsigned int n2 );
int rnumber_ui_notequal_rn( unsigned int n1, const struct RNumber * n2 );
int rnumber_rn_equal_rn( const struct RNumber * n1, const struct RNumber * n2 );
int rnumber_rn_equal_ui( const struct RNumber * n1, unsigned int n2 );
int rnumber_ui_equal_rn( unsigned int n1, const struct RNumber * n2 );
int rnumber_rn_lessthan_rn( const struct RNumber * n1, const struct RNumber * n2 );
int rnumber_rn_lessthan_ui( const struct RNumber * n1, unsigned int n2 );
int rnumber_ui_lessthan_rn( unsigned int n1, const struct RNumber * n2 );
int rnumber_rn_lessequal_rn( const struct RNumber * n1, const struct RNumber * n2 );
int rnumber_rn_lessequal_ui( const struct RNumber * n1, unsigned int n2 );
int rnumber_ui_lessequal_rn( unsigned int n1, const struct RNumber * n2 );
int rnumber_rn_greaterthan_rn( const struct RNumber * n1, const struct RNumber * n2 );
int rnumber_rn_greaterthan_ui( const struct RNumber * n1, unsigned int n2 );
int rnumber_ui_greaterthan_rn( unsigned int n1, const struct RNumber * n2 );
int rnumber_rn_greaterequal_rn( const struct RNumber * n1, const struct RNumber * n2 );
int rnumber_rn_greaterequal_ui( const struct RNumber * n1, unsigned int n2 );
int rnumber_ui_greaterequal_rn( unsigned int n1, const struct RNumber * n2 );

int rnumber_rhex();
int rnumber_rbin();
int rnumber_rdec();

#ifdef __cplusplus
}
#endif

#undef WORD_THRESHOLD

#endif
