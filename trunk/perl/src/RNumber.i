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
**
** This is a swig interface file for the C wrapper for the C++ RNumber class.
** ===========================================================================
*/
%module RNumber
%{
 
  %}

extern int rnumber_predicate_init();

extern struct RNumber;
extern struct RNumber * rnumber_create();
extern struct RNumber * rnumber_create_from_unsigned( unsigned long number );
extern struct RNumber * rnumber_create_from_unsigned_variable_sizing( unsigned long number );
extern struct RNumber * rnumber_create_from_unsigned_of_size( unsigned long number, unsigned int size );
extern struct RNumber * rnumber_create_from_unsigned_of_size_variable_sizing( unsigned long number, unsigned int size );
extern struct RNumber * rnumber_create_from_string( char * number  );
extern struct RNumber * rnumber_create_from_string_variable_sizing( char * number );
extern struct RNumber * rnumber_create_from_string_of_size( char * number, unsigned int size );
extern struct RNumber * rnumber_create_from_string_of_size_variable_sizing(  char * number, unsigned int size );
extern struct RNumber * rnumber_create_from_string_of_radix( char * number, int radix );
extern struct RNumber * rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix );
extern struct RNumber * rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix);
extern struct RNumber * rnumber_create_from_string_of_size_of_radix_variable_sizing( char * number, unsigned int size,
										     int radix);
extern struct RNumber * rnumber_create_from_numVector( unsigned long* numVector, unsigned int wordCount, unsigned int size );
extern struct RNumber * rnumber_create_from_numVector_variable_sizing( unsigned long* numVector, unsigned int wordCount, 
								       unsigned int size );

extern struct RNumber * rnumber_create_from_rnumber( const struct RNumber * rnumber );
extern struct RNumber * rnumber_copy_to_size( const struct RNumber * number, unsigned int size);
extern struct RNumber * rnumber_copy_to_size_variable_sizing( const struct RNumber * number, unsigned int size);
extern void rnumber_destroy( struct RNumber * rnumber );

  // Assignment methods. operator=() assigns the value constrained by sizing;
  // assign() assigns the value with dynamic sizing; clone() assigns all
  // attributes; resize() truncates/expands the value and sets fixed sizing.
extern struct RNumber * rnumber_assign_from_uint ( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_assign_from_string ( struct RNumber * rnumber, char * number_string );
extern struct RNumber * rnumber_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_copy( struct RNumber * rnumber, struct RNumber * number );
extern void      rnumber_resize( struct RNumber * rnumber, unsigned int size );

  // Unary arithmetic operators.
extern struct RNumber * rnumber_unary_minus( struct RNumber * rnumber);
extern struct RNumber * rnumber_unary_tilde( struct RNumber * rnumber);

  // Arithmetic assignment operators; assignment size depends on sizing state.
extern struct RNumber * rnumber_plus_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_plus_assign_from_unsigned ( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_minus_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_minus_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_multiply_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_multiply_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_divide_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_divide_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_mod_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_mod_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_bitand_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_bitand_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_bitor_assign( struct RNumber * rnumber,  struct RNumber * number );
extern struct RNumber * rnumber_bitor_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_bitxor_assign( struct RNumber * rnumber, struct RNumber * number );
extern struct RNumber * rnumber_bitxor_assign_from_unsigned( struct RNumber * rnumber, unsigned long number );
extern struct RNumber * rnumber_leftshift_assign( struct RNumber * rnumber, struct RNumber * shift );
extern struct RNumber * rnumber_leftshift_assign_from_unsigned( struct RNumber * rnumber, unsigned int shift );
extern struct RNumber * rnumber_rightshift_assign( struct RNumber * rnumber,  struct RNumber * shift );
extern struct RNumber * rnumber_rightshift_assign_from_unsigned( struct RNumber * rnumber, unsigned int shift );

  // Unary conditional expression operators.
extern int rnumber_not( struct RNumber * rnumber);

  // Signed conditional expression operators.
extern int rnumber_signed_lessthan( struct RNumber * rnumber, struct RNumber * number );
extern int rnumber_signed_lessequal( struct RNumber * rnumber, struct RNumber * number );
extern int rnumber_signed_greaterthan( struct RNumber * rnumber, struct RNumber * number );
extern int rnumber_signed_greaterequal( struct RNumber * rnumber, struct RNumber * number );
extern int  rnumber_compare( struct RNumber * rnumber, struct RNumber * number );

  // Miscellaneous bit manipulation methods.
extern struct RNumber * rnumber_invert( struct RNumber * rnumber);
extern struct RNumber * rnumber_negate( struct RNumber * rnumber);
extern struct RNumber * rnumber_set_all( struct RNumber * rnumber);
extern struct RNumber * rnumber_clear_all( struct RNumber * rnumber);
extern struct RNumber * rnumber_sign_extend( struct RNumber * rnumber, unsigned int bit );
extern struct RNumber * rnumber_truncate( struct RNumber * rnumber, unsigned int size );

  // Bit value accessors and manipulators.
extern unsigned int rnumber_getbit( struct RNumber * rnumber, unsigned int pos);
extern unsigned int rnumber_getbit_lsb( struct RNumber * rnumber, unsigned int pos );
extern void rnumber_setbit( struct RNumber * rnumber, unsigned int pos, unsigned int value );
extern void rnumber_setbit_lsb( struct RNumber * rnumber,unsigned int pos, unsigned int value );
extern void rnumber_assignbit( struct RNumber * rnumber, unsigned int pos, unsigned int value );
extern void rnumber_assignbit_lsb( struct RNumber * rnumber, unsigned int pos, unsigned int value );

  // Value accessors.
extern unsigned int rnumber_get_uint( struct RNumber * rnumber);
extern char * rnumber_cstr( const struct RNumber * rnumber);
extern char * rnumber_cstr_radix( const struct RNumber * rnumber, int radix,int bool_prefix);

  // Value field accessors and manipulators.
extern int rnumber_get_int_field( struct RNumber * rnumber, unsigned int start, unsigned int end );
extern unsigned int rnumber_get_uint_field( struct RNumber * rnumber,unsigned int start, unsigned int end );
extern struct RNumber * rnumber_getfield( struct RNumber * rnumber, unsigned int start, unsigned int end );
extern void rnumber_set_field( struct RNumber * rnumber, unsigned int start, unsigned int end, struct RNumber * num );

  // Attribute accessors and manipulators.
extern unsigned rnumber_size( const struct RNumber * rnumber);
extern unsigned rnumber_wordcount( const struct RNumber * rnumber);

extern const unsigned * rnumber_buffer( struct RNumber * rnumber);

extern unsigned int rnumber_get_default_size();
extern void rnumber_set_default_size( unsigned int size );

extern int rnumber_sizing( struct RNumber * rnumber);
extern int rnumber_dynamic();
extern int rnumber_fixed(); 
extern void rnumber_set_dynamic( struct RNumber * rnumber);
extern void rnumber_set_fixed( struct RNumber * rnumber);

  // Streaming I/O methods.
extern void rnumber_print_to_os( const struct RNumber * rnumber, void * os );
extern void rnumber_print_with_radix( const struct RNumber * rnumber, void * os, int radix, int bool_prefix );

//friend istream& operator>>( istream& is, RNumber& number );
//friend ostream& operator<<( ostream& os, const RNumber& number );
extern void rnumber_read_from_is( struct RNumber * rnumber, void * is );
extern void rnumber_write_to_os( struct RNumber * rnumber, void * os );

//   friend struct Hash {
//     size_t operator()( const RNumber& num ) const;
//   };

//   friend struct Equal {
//     size_t operator()( const RNumber& num1, const RNumber& num2 ) const;
//   };

// Non-member functions that allow for mixed arithmetic expressions between
// RNumbers and unsigned integers.
extern  struct RNumber * rnumber_rn_plus_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_plus_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_plus_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_add_ext_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_add_ext_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_add_ext_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_minus_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_minus_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_minus_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_multiply_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_multiply_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_multiply_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_multiply_ext_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_multiply_ext_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_multiply_ext_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_divide_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_divide_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_divide_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_mod_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_mod_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_mod_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_bitand_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_bitand_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_bitand_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_bitor_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_bitor_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_bitor_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_bitxor_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_bitxor_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_bitxor_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_leftshift_rn( const struct RNumber * n, const struct RNumber * shift );
extern  struct RNumber * rnumber_rn_leftshift_ui( const struct RNumber * n, unsigned int shift );
extern  struct RNumber * rnumber_ui_leftshift_rn( unsigned long n, const struct RNumber * shift );
extern  struct RNumber * rnumber_rn_leftshift_ext_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_leftshift_ext_ui( const struct RNumber * n1, unsigned long n2 );
extern  struct RNumber * rnumber_ui_leftshift_ext_rn( unsigned long n1, const struct RNumber * n2 );
extern  struct RNumber * rnumber_rn_rightshift_rn( const struct RNumber * n, const struct RNumber * shift );
extern  struct RNumber * rnumber_rn_rightshift_ui( const struct RNumber * n, unsigned int shift );
extern  struct RNumber * rnumber_ui_rightshift_rn( unsigned long n, const struct RNumber * shift );

// Non-member functions that allow for mixed conditional expressions between
// RNumbers and unsigned integers.
extern int rnumber_rn_notequal_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern int rnumber_rn_notequal_ui( const struct RNumber * n1, unsigned long n2 );
extern int rnumber_ui_notequal_rn( unsigned long n1, const struct RNumber * n2 );
extern int rnumber_rn_equal_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern int rnumber_rn_equal_ui( const struct RNumber * n1, unsigned long n2 );
extern int rnumber_ui_equal_rn( unsigned long n1, const struct RNumber * n2 );
extern int rnumber_rn_lessthan_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern int rnumber_rn_lessthan_ui( const struct RNumber * n1, unsigned long n2 );
extern int rnumber_ui_lessthan_rn( unsigned long n1, const struct RNumber * n2 );
extern int rnumber_rn_lessequal_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern int rnumber_rn_lessequal_ui( const struct RNumber * n1, unsigned long n2 );
extern int rnumber_ui_lessequal_rn( unsigned long n1, const struct RNumber * n2 );
extern int rnumber_rn_greaterthan_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern int rnumber_rn_greaterthan_ui( const struct RNumber * n1, unsigned long n2 );
extern int rnumber_ui_greaterthan_rn( unsigned long n1, const struct RNumber * n2 );
extern int rnumber_rn_greaterequal_rn( const struct RNumber * n1, const struct RNumber * n2 );
extern int rnumber_rn_greaterequal_ui( const struct RNumber * n1, unsigned long n2 );
extern int rnumber_ui_greaterequal_rn( unsigned long n1, const struct RNumber * n2 );

extern int rnumber_rhex();
extern int rnumber_rbin();
extern int rnumber_rdec();

// This class is never instantiated- it's purely static.  It contains
// multiple RandomObj generators which may be swapped in and out- the
// current generator is then used by the various get functions.

// By default, we set the seed based upon the time.
extern void random_create();
extern void random_set_gate_all ( int state_in );
extern void random_set_gate ( int state_in, int apply_to_all );

// Generated seed (time based).
extern unsigned random_init();
// Explicitly set seed.  If the value is 0, the time will be used.
extern unsigned random_init_from_seed( unsigned seed );

// Create a new generator and store its handle.
// This does not select the generator for use.
extern int random_add_new_gen();
extern int random_add_new_gen_with_seed(unsigned seed);
// Remove n generators from the end of the list.
extern void random_pop_gen(int x);
// Specify a new generator to use.
extern int  random_set_cur_gen(int x);
// Get the current generator handle.
extern int random_get_cur_gen();
// Return the number of generators that we currently have.
extern int random_get_num_gen();

// Get a value from the current generator.
extern struct RNumber * random_get_rnumber( int size );
extern unsigned  random_get_integer();
extern unsigned  random_get_integer_n( unsigned n );
extern double    random_get_double();

extern struct RNumber *  random_get_from_range_rnumber( struct RNumber * minimum, 
							struct RNumber * maximum );
extern unsigned   random_get_from_range_unsigned( unsigned minimum, unsigned maximum );

// Load/save the state of the random number generator.
extern void random_save (void * os);
extern void random_load (void * is);
// Get/set info about the random number generator.
extern void * random_get_state();
extern void random_set_state( void * state);
// Return the offset that the current generator is at.
extern unsigned random_get_count();

