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
** ===========================================================================
*/
#include "bl-rnumber.h"
#include "C-RNumber.h"

#include "rnumber/rnumber_proxy.h"

RNumber_proxy_t bl_rnumber_create() {
  return proxy_from_rnumber(rnumber_create());
}

RNumber_proxy_t bl_rnumber_create_from_unsigned( unsigned int number ){
  return proxy_from_rnumber(rnumber_create_from_unsigned(number));
}

RNumber_proxy_t bl_rnumber_create_from_unsigned_variable_sizing( unsigned int number ){
  return proxy_from_rnumber(rnumber_create_from_unsigned_variable_sizing(number));
}

RNumber_proxy_t bl_rnumber_create_from_unsigned_of_size( unsigned int number, unsigned int size ){
  return proxy_from_rnumber(rnumber_create_from_unsigned_of_size(number, size));
}

RNumber_proxy_t bl_rnumber_create_from_unsigned_of_size_variable_sizing( unsigned int number, unsigned int size ){
  return proxy_from_rnumber(rnumber_create_from_unsigned_of_size_variable_sizing(number, size));
}

RNumber_proxy_t bl_rnumber_create_from_string(  char * number  ){
  return proxy_from_rnumber(rnumber_create_from_string(number));
}

RNumber_proxy_t bl_rnumber_create_from_string_variable_sizing( char * number ){
  return proxy_from_rnumber( rnumber_create_from_string_variable_sizing( number));
}

RNumber_proxy_t bl_rnumber_create_from_string_of_size( char * number, unsigned int size ){
  return proxy_from_rnumber(rnumber_create_from_string_of_size( number, size));
}

RNumber_proxy_t bl_rnumber_create_from_string_of_size_variable_sizing( char * number, unsigned int size ){
  return proxy_from_rnumber(rnumber_create_from_string_of_size_variable_sizing ( number, size));
}

RNumber_proxy_t bl_rnumber_create_from_string_of_radix( char * number, int radix ){
  return proxy_from_rnumber(rnumber_create_from_string_of_radix(number, radix));
}

RNumber_proxy_t bl_rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix ){
  return proxy_from_rnumber(rnumber_create_from_string_of_radix_variable_sizing
                            ( number, radix));
}

RNumber_proxy_t bl_rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix){
  return proxy_from_rnumber(rnumber_create_from_string_of_size_of_radix
                            ( number, size, radix));
}

RNumber_proxy_t bl_rnumber_create_from_string_of_size_of_radix_variable_sizing
( char * number, unsigned int size, int radix) {
  return proxy_from_rnumber(rnumber_create_from_string_of_size_of_radix_variable_sizing
                            ( number, size, radix));
}

RNumber_proxy_t bl_rnumber_create_from_numVector
( unsigned int* numVector, unsigned int wordCount, unsigned int size ){
  return proxy_from_rnumber(rnumber_create_from_numVector( numVector, wordCount, size ));
}

RNumber_proxy_t bl_rnumber_create_from_numVector_variable_sizing
(unsigned int* numVector, unsigned int wordCount, unsigned int size ){
  return proxy_from_rnumber(rnumber_create_from_numVector_variable_sizing
                            ( numVector, wordCount, size));
}

RNumber_proxy_t bl_rnumber_create_from_rnumber( RNumber_proxy_t rnumber ){
  return proxy_from_rnumber(rnumber_create_from_rnumber(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_copy_to_size( RNumber_proxy_t number, unsigned int size){
  return proxy_from_rnumber(rnumber_copy_to_size(RNUM_FROM_PROXY(number), size));
}

RNumber_proxy_t bl_rnumber_copy_to_size_variable_sizing( RNumber_proxy_t number, unsigned int size){
  return proxy_from_rnumber(rnumber_copy_to_size_variable_sizing(RNUM_FROM_PROXY(number), size));
}

// Unary arithmetic operators.
RNumber_proxy_t bl_rnumber_unary_minus( RNumber_proxy_t rnumber){
  return proxy_from_rnumber(rnumber_unary_minus(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_unary_tilde( RNumber_proxy_t rnumber){
  return proxy_from_rnumber(rnumber_unary_tilde(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_getfield( RNumber_proxy_t rnumber, unsigned int start, unsigned int end ){
  return proxy_from_rnumber(rnumber_getfield(RNUM_FROM_PROXY(rnumber),start, end));
}

// Non-member functions that allow for mixed arithmetic expressions between
// RNumber_proxy_ts and unsigned integers.
RNumber_proxy_t bl_rnumber_rn_plus_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_plus_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}

RNumber_proxy_t bl_rnumber_rn_plus_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_plus_ui(RNUM_FROM_PROXY(n1), n2));
}
RNumber_proxy_t bl_rnumber_ui_plus_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_plus_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_add_ext_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_add_ext_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_add_ext_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return proxy_from_rnumber(rnumber_rn_add_ext_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_add_ext_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_add_ext_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_minus_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_minus_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_minus_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_minus_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_minus_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return proxy_from_rnumber(rnumber_ui_minus_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_multiply_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return proxy_from_rnumber(rnumber_rn_multiply_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_multiply_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return proxy_from_rnumber(rnumber_rn_multiply_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_multiply_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return proxy_from_rnumber(rnumber_ui_multiply_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_multiply_ext_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_multiply_ext_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_multiply_ext_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_multiply_ext_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_multiply_ext_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_multiply_ext_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_divide_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_divide_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_divide_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return proxy_from_rnumber(rnumber_rn_divide_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_divide_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return proxy_from_rnumber(rnumber_ui_divide_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_mod_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_mod_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_mod_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_mod_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_mod_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_mod_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_bitand_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_bitand_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_bitand_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_bitand_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_bitand_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_bitand_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_bitor_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_bitor_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_bitor_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_bitor_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_bitor_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_bitor_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_bitxor_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_bitxor_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_bitxor_ui( RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_bitxor_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_bitxor_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_bitxor_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_leftshift_rn( RNumber_proxy_t n, RNumber_proxy_t shift ){
  return proxy_from_rnumber(rnumber_rn_leftshift_rn(RNUM_FROM_PROXY(n),RNUM_FROM_PROXY(shift)));
}
RNumber_proxy_t bl_rnumber_rn_leftshift_ui( RNumber_proxy_t n, unsigned int shift ){
  return proxy_from_rnumber(rnumber_rn_leftshift_ui(RNUM_FROM_PROXY(n),shift));
}
RNumber_proxy_t bl_rnumber_ui_leftshift_rn( unsigned int n, RNumber_proxy_t shift ){
  return proxy_from_rnumber(rnumber_ui_leftshift_rn(n,RNUM_FROM_PROXY(shift)));
}
RNumber_proxy_t bl_rnumber_rn_leftshift_ext_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_rn_leftshift_ext_rn(RNUM_FROM_PROXY(n1),RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_leftshift_ext_ui(  RNumber_proxy_t n1, unsigned int n2 ){
  return proxy_from_rnumber(rnumber_rn_leftshift_ext_ui(RNUM_FROM_PROXY(n1),n2));
}
RNumber_proxy_t bl_rnumber_ui_leftshift_ext_rn( unsigned int n1, RNumber_proxy_t n2 ){
  return proxy_from_rnumber(rnumber_ui_leftshift_ext_rn(n1,RNUM_FROM_PROXY(n2)));
}
RNumber_proxy_t bl_rnumber_rn_rightshift_rn( RNumber_proxy_t n, RNumber_proxy_t shift ){
  return proxy_from_rnumber(rnumber_rn_rightshift_rn(RNUM_FROM_PROXY(n),RNUM_FROM_PROXY(shift)));
}
RNumber_proxy_t bl_rnumber_rn_rightshift_ui( RNumber_proxy_t n, unsigned int shift ){
  return proxy_from_rnumber(rnumber_rn_rightshift_ui(RNUM_FROM_PROXY(n),shift));
}
RNumber_proxy_t bl_rnumber_ui_rightshift_rn( unsigned int n, RNumber_proxy_t shift ){
  return proxy_from_rnumber(rnumber_ui_rightshift_rn(n,RNUM_FROM_PROXY(shift)));
}

/* <here> */
void bl_rnumber_destroy( RNumber_proxy_t rnumber ) {
  return rnumber_destroy(RNUM_FROM_PROXY(rnumber) );
}

RNumber_proxy_t bl_rnumber_assign_from_uint ( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_assign_from_uint (RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_assign_from_string ( RNumber_proxy_t rnumber, char * number_string ) {
  return proxy_from_rnumber(rnumber_assign_from_string (RNUM_FROM_PROXY(rnumber),  number_string ));
}

RNumber_proxy_t bl_rnumber_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_copy( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_copy(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

void      bl_rnumber_resize( RNumber_proxy_t rnumber, unsigned int size ) {
  return rnumber_resize(RNUM_FROM_PROXY(rnumber),  size );
}

RNumber_proxy_t bl_rnumber_plus_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_plus_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_plus_assign_from_unsigned ( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_plus_assign_from_unsigned (RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_minus_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_minus_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_minus_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_minus_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_multiply_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_multiply_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_multiply_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_multiply_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_divide_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_divide_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_divide_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_divide_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_mod_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_mod_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_mod_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_mod_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_bitand_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_bitand_assign(RNUM_FROM_PROXY(rnumber), RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_bitand_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_bitand_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_bitor_assign( RNumber_proxy_t rnumber,  RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_bitor_assign(RNUM_FROM_PROXY(rnumber),   RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_bitor_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_bitor_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_bitxor_assign( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return proxy_from_rnumber(rnumber_bitxor_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) ));
}

RNumber_proxy_t bl_rnumber_bitxor_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int number ) {
  return proxy_from_rnumber(rnumber_bitxor_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  number ));
}

RNumber_proxy_t bl_rnumber_leftshift_assign( RNumber_proxy_t rnumber, RNumber_proxy_t shift ) {
  return proxy_from_rnumber(rnumber_leftshift_assign(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(shift) ));
}

RNumber_proxy_t bl_rnumber_leftshift_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int shift ) {
  return proxy_from_rnumber(rnumber_leftshift_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  shift ));
}

RNumber_proxy_t bl_rnumber_rightshift_assign( RNumber_proxy_t rnumber,  RNumber_proxy_t shift ) {
  return proxy_from_rnumber(rnumber_rightshift_assign(RNUM_FROM_PROXY(rnumber), RNUM_FROM_PROXY(shift)));
}

RNumber_proxy_t bl_rnumber_rightshift_assign_from_unsigned( RNumber_proxy_t rnumber, unsigned int shift ) {
  return proxy_from_rnumber(rnumber_rightshift_assign_from_unsigned(RNUM_FROM_PROXY(rnumber),  shift ));
}

int bl_rnumber_not( RNumber_proxy_t rnumber) {
  return rnumber_not(RNUM_FROM_PROXY(rnumber));
}

int bl_rnumber_signed_lessthan( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return rnumber_signed_lessthan(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) );
}

int bl_rnumber_signed_lessequal( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return rnumber_signed_lessequal(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) );
}

int bl_rnumber_signed_greaterthan( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return rnumber_signed_greaterthan(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) );
}

int bl_rnumber_signed_greaterequal( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return rnumber_signed_greaterequal(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) );
}

int bl_rnumber_compare( RNumber_proxy_t rnumber, RNumber_proxy_t number ) {
  return rnumber_compare(RNUM_FROM_PROXY(rnumber),  RNUM_FROM_PROXY(number) );
}

RNumber_proxy_t bl_rnumber_invert( RNumber_proxy_t rnumber) {
  return proxy_from_rnumber(rnumber_invert(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_negate( RNumber_proxy_t rnumber) {
  return proxy_from_rnumber(rnumber_negate(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_set_all( RNumber_proxy_t rnumber) {
  return proxy_from_rnumber(rnumber_set_all(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_clear_all( RNumber_proxy_t rnumber) {
  return proxy_from_rnumber(rnumber_clear_all(RNUM_FROM_PROXY(rnumber)));
}

RNumber_proxy_t bl_rnumber_sign_extend( RNumber_proxy_t rnumber, unsigned int bit ) {
  return proxy_from_rnumber(rnumber_sign_extend(RNUM_FROM_PROXY(rnumber),  bit ));
}

RNumber_proxy_t bl_rnumber_truncate( RNumber_proxy_t rnumber, unsigned int size ) {
  return proxy_from_rnumber(rnumber_truncate(RNUM_FROM_PROXY(rnumber),  size ));
}

unsigned int bl_rnumber_getbit( RNumber_proxy_t rnumber, unsigned int pos) {
  return rnumber_getbit(RNUM_FROM_PROXY(rnumber),  pos);
}

unsigned int bl_rnumber_getbit_lsb( RNumber_proxy_t rnumber, unsigned int pos ) {
  return rnumber_getbit_lsb(RNUM_FROM_PROXY(rnumber),  pos );
}

void bl_rnumber_setbit( RNumber_proxy_t rnumber, unsigned int pos, unsigned int value ) {
  return rnumber_setbit(RNUM_FROM_PROXY(rnumber),  pos,  value );
}

void bl_rnumber_setbit_lsb( RNumber_proxy_t rnumber,unsigned int pos, unsigned int value ) {
  return rnumber_setbit_lsb(RNUM_FROM_PROXY(rnumber), pos,  value );
}

void bl_rnumber_assignbit( RNumber_proxy_t rnumber, unsigned int pos, unsigned int value ) {
  return rnumber_assignbit(RNUM_FROM_PROXY(rnumber),  pos,  value );
}

void bl_rnumber_assignbit_lsb( RNumber_proxy_t rnumber, unsigned int pos, unsigned int value ) {
  return rnumber_assignbit_lsb(RNUM_FROM_PROXY(rnumber),  pos,  value );
}

unsigned int bl_rnumber_get_uint( RNumber_proxy_t rnumber) {
  return rnumber_get_uint(RNUM_FROM_PROXY(rnumber));
}

char * bl_rnumber_cstr( RNumber_proxy_t rnumber) {
  return rnumber_cstr(RNUM_FROM_PROXY(rnumber));
}

char * bl_rnumber_cstr_radix( RNumber_proxy_t rnumber, int radix,int bool_prefix) {
  return rnumber_cstr_radix(RNUM_FROM_PROXY(rnumber),  radix, bool_prefix);
}

int bl_rnumber_get_int_field( RNumber_proxy_t rnumber, unsigned int start, unsigned int end ) {
  return rnumber_get_int_field(RNUM_FROM_PROXY(rnumber),  start,  end );
}

unsigned int bl_rnumber_get_uint_field( RNumber_proxy_t rnumber,unsigned int start, unsigned int end ) {
  return rnumber_get_uint_field(RNUM_FROM_PROXY(rnumber), start,  end );
}

void bl_rnumber_set_field( RNumber_proxy_t rnumber, unsigned int start, unsigned int end, RNumber_proxy_t num ) {
  return rnumber_set_field(RNUM_FROM_PROXY(rnumber),  start,  end, RNUM_FROM_PROXY(num));
}

unsigned bl_rnumber_size( RNumber_proxy_t rnumber) {
  return rnumber_size(RNUM_FROM_PROXY(rnumber));
}

unsigned bl_rnumber_wordcount( RNumber_proxy_t rnumber) {
  return rnumber_wordcount(RNUM_FROM_PROXY(rnumber));
}


const unsigned * bl_rnumber_buffer( RNumber_proxy_t rnumber) {
  return rnumber_buffer(RNUM_FROM_PROXY(rnumber));
}

unsigned int bl_rnumber_get_default_size() {
  return rnumber_get_default_size();
}

int bl_rnumber_sizing( RNumber_proxy_t rnumber) {
  return rnumber_sizing(RNUM_FROM_PROXY(rnumber));
}

int bl_rnumber_dynamic() {
  return rnumber_dynamic();
}

int bl_rnumber_fixed() {
  return rnumber_fixed();
}
void bl_rnumber_set_dynamic( RNumber_proxy_t rnumber) {
  return rnumber_set_dynamic(RNUM_FROM_PROXY(rnumber));
}

void bl_rnumber_set_fixed( RNumber_proxy_t rnumber) {
  return rnumber_set_fixed(RNUM_FROM_PROXY(rnumber));
}

// Streaming I/O methods.
void bl_rnumber_print_to_os( RNumber_proxy_t rnumber, void * os ) {
  return rnumber_print_to_os(RNUM_FROM_PROXY(rnumber),  os );
}

void bl_rnumber_print_with_radix( RNumber_proxy_t rnumber, void * os, int radix, int bool_prefix ) {
  return rnumber_print_with_radix(RNUM_FROM_PROXY(rnumber), os,  radix,  bool_prefix );
}


//friend istream& operator>>( istream& is, RNumber& number );
//friend ostream& operator<<( ostream& os, const RNumber& number );
void bl_rnumber_read_from_is( RNumber_proxy_t rnumber, void * is ) {
  return rnumber_read_from_is(RNUM_FROM_PROXY(rnumber),  is );
}

void bl_rnumber_write_to_os( RNumber_proxy_t rnumber, void * os ) {
  return rnumber_write_to_os(RNUM_FROM_PROXY(rnumber),  os );
}

int bl_rnumber_rn_notequal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return rnumber_rn_notequal_rn(RNUM_FROM_PROXY(n1),  RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_notequal_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return rnumber_rn_notequal_ui(RNUM_FROM_PROXY(n1),  n2 );
}

int bl_rnumber_ui_notequal_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return rnumber_ui_notequal_rn(n1, RNUM_FROM_PROXY(n2));
}

int bl_rnumber_rn_equal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return rnumber_rn_equal_rn(RNUM_FROM_PROXY(n1), RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_equal_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return rnumber_rn_equal_ui(RNUM_FROM_PROXY(n1),  n2 );
}

int bl_rnumber_ui_equal_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return rnumber_ui_equal_rn(n1,  RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_lessthan_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return rnumber_rn_lessthan_rn(RNUM_FROM_PROXY(n1),  RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_lessthan_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return rnumber_rn_lessthan_ui(RNUM_FROM_PROXY(n1),  n2 );
}

int bl_rnumber_ui_lessthan_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return rnumber_ui_lessthan_rn(n1,  RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_lessequal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return rnumber_rn_lessequal_rn(RNUM_FROM_PROXY(n1), RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_lessequal_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return rnumber_rn_lessequal_ui(RNUM_FROM_PROXY(n1), n2 );
}

int bl_rnumber_ui_lessequal_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return rnumber_ui_lessequal_rn(n1, RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_greaterthan_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return rnumber_rn_greaterthan_rn(RNUM_FROM_PROXY(n1),  RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_greaterthan_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return rnumber_rn_greaterthan_ui(RNUM_FROM_PROXY(n1),  n2 );
}

int bl_rnumber_ui_greaterthan_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return rnumber_ui_greaterthan_rn(n1,  RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_greaterequal_rn( RNumber_proxy_t n1, RNumber_proxy_t n2 ) {
  return rnumber_rn_greaterequal_rn(RNUM_FROM_PROXY(n1), RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rn_greaterequal_ui( RNumber_proxy_t n1, unsigned int n2 ) {
  return rnumber_rn_greaterequal_ui(RNUM_FROM_PROXY(n1), n2 );
}

int bl_rnumber_ui_greaterequal_rn( unsigned int n1, RNumber_proxy_t n2 ) {
  return rnumber_ui_greaterequal_rn(n1, RNUM_FROM_PROXY(n2) );
}

int bl_rnumber_rhex() {
  return rnumber_rhex();
}

int bl_rnumber_rbin() {
  return rnumber_rbin();
}

int bl_rnumber_rdec() {
  return rnumber_rdec();
}

