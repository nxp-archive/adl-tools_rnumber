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
#include "bl-rnumber.h"
#include "C-RNumber.h"

#include "rnumber_proxy.h"

RNumber_proxy_t * bl_rnumber_create() 
{
  return proxy_from_rnumber(bl_rnumber_create());
}

RNumber_proxy_t * bl_rnumber_create_from_unsigned( unsigned int number )
{
  return proxy_from_rnumber(rnumber_create_from_unsigned(number));
}

RNumber_proxy_t * bl_rnumber_create_from_unsigned_variable_sizing( unsigned int number )
{
  return proxy_from_rnumber(rnumber_create_from_unsigned_variable_sizing(number));
}

RNumber_proxy_t * bl_rnumber_create_from_unsigned_of_size( unsigned int number, unsigned int size )
{
  return proxy_from_rnumber(rnumber_create_from_unsigned_of_size(number, size));
}

RNumber_proxy_t * bl_rnumber_create_from_unsigned_of_size_variable_sizing( unsigned int number, unsigned int size )
{
  return proxy_from_rnumber(rnumber_create_from_unsigned_of_size_variable_sizing(number, size));
}

RNumber_proxy_t * bl_rnumber_create_from_string(  char * number  )
{
  return proxy_from_rnumber(rnumber_create_from_string(number));
}

RNumber_proxy_t * bl_rnumber_create_from_string_variable_sizing( const char * number )
{
  return proxy_from_rnumber( rnumber_create_from_string_variable_sizing( number));
}

RNumber_proxy_t * bl_rnumber_create_from_string_of_size( char * number, unsigned int size )
{
  return proxy_from_rnumber(rnumber_create_from_string_of_size( number, size));
}

RNumber_proxy_t * bl_rnumber_create_from_string_of_size_variable_sizing( char * number, unsigned int size )
{
  return proxy_from_rnumber(rnumber_create_from_string_of_size_variable_sizing ( number, size));
}

RNumber_proxy_t * bl_rnumber_create_from_string_of_radix( char * number, int radix )
{
  return proxy_from_rnumber(new RNumber( string(number), get_radix(radix)));
}

RNumber_proxy_t * bl_rnumber_create_from_string_of_radix_variable_sizing( char * number, int radix )
{
  return proxy_from_rnumber(new RNumber( string(number), get_radix(radix), RNumber::dynamic));
}

RNumber_proxy_t * bl_rnumber_create_from_string_of_size_of_radix( char * number, unsigned int size, int radix)
{
  return proxy_from_rnumber(new RNumber( string(number), size, get_radix(radix)));
}

RNumber_proxy_t * bl_rnumber_create_from_string_of_size_of_radix_variable_sizing( char * number, unsigned int size, int radix) 
{
  return proxy_from_rnumber(new RNumber( string(number), size, get_radix(radix), RNumber::dynamic));
}

RNumber_proxy_t * bl_rnumber_create_from_numVector( unsigned int* numVector, unsigned int wordCount, unsigned int size )
{
  return proxy_from_rnumber(new RNumber( numVector, wordCount, size ));
}

RNumber_proxy_t * bl_rnumber_create_from_numVector_variable_sizing(unsigned int* numVector, unsigned int wordCount, unsigned int size )
{
  return proxy_from_rnumber(new RNumber( numVector, wordCount, size, RNumber::dynamic));
}

RNumber_proxy_t * bl_rnumber_create_from_rnumber( const RNumber * rnumber )
{
  return proxy_from_rnumber(new RNumber(*rnumber));
}

RNumber_proxy_t * bl_rnumber_copy_to_size( const RNumber * number, unsigned int size)
{
  return proxy_from_rnumber(new RNumber(*number, size));
}

RNumber_proxy_t * bl_rnumber_copy_to_size_variable_sizing( const RNumber * number, unsigned int size)
{
  return proxy_from_rnumber(new RNumber(*number, size, RNumber::dynamic));
}


// Unary arithmetic operators.
RNumber_proxy_t * bl_rnumber_unary_minus( RNumber * rnumber)
{
  return proxy_from_rnumber(new RNumber(-(*rnumber)));
}

RNumber_proxy_t * bl_rnumber_unary_tilde( RNumber * rnumber)
{
  return proxy_from_rnumber(new RNumber(~(*rnumber)));
}

RNumber_proxy_t * bl_rnumber_getfield( RNumber * rnumber, unsigned int start, unsigned int end )
{
  return proxy_from_rnumber(new RNumber(rnumber->getField(start, end)));
}

// Non-member functions that allow for mixed arithmetic expressions between
// RNumber_proxy_ts and unsigned integers.
struct RNumber * bl_rnumber_rn_plus_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(*n1 + *n2));
}
struct RNumber_proxy_t * bl_rnumber_rn_plus_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber(*n1 + n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_plus_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(n1 + *n2));
}
struct RNumber_proxy_t * bl_rnumber_rn_add_ext_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(addExt(*n1,*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_add_ext_ui( const struct RNumber * n1, unsigned int n2 ) {
  return proxy_from_rnumber(new RNumber(addExt(*n1,n2)));
}
struct RNumber_proxy_t * bl_rnumber_ui_add_ext_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(addExt(n1,*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_minus_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber((*n1)-(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_minus_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber(*n1-n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_minus_rn( unsigned int n1, const struct RNumber * n2 ) {
  return proxy_from_rnumber(new RNumber(n1-(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_multiply_rn( const struct RNumber * n1, const struct RNumber * n2 ) {
  return proxy_from_rnumber(new RNumber((*n1)*(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_multiply_ui( const struct RNumber * n1, unsigned int n2 ) {
  return proxy_from_rnumber(new RNumber((*n1)*n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_multiply_ui( unsigned int n1, const struct RNumber * n2 ) {
  return proxy_from_rnumber(new RNumber(n1*(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_multiply_ext_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(multiplyExt(*n1,*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_multiply_ext_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber(multiplyExt(*n1,n2)));
}
struct RNumber_proxy_t * bl_rnumber_ui_multiply_ext_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(multiplyExt(n1,*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_divide_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber((*n1)/(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_divide_ui( const struct RNumber * n1, unsigned int n2 ) {
  return proxy_from_rnumber(new RNumber((*n1)/n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_divide_rn( unsigned int n1, const struct RNumber * n2 ) {
  return proxy_from_rnumber(new RNumber(n1/(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_mod_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber((*n1)%(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_mod_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber((*n1)%n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_mod_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(n1%(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_bitand_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber((*n1)&(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_bitand_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber((*n1)&n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_bitand_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(n1&(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_bitor_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber((*n1)|(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_bitor_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber((*n1)|n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_bitor_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(n1|(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_bitxor_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber((*n1)^(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_bitxor_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber((*n1)^n2));
}
struct RNumber_proxy_t * bl_rnumber_ui_bitxor_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(n1^(*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_leftshift_rn( const struct RNumber * n, const struct RNumber * shift ){
  return proxy_from_rnumber(new RNumber((*n)<<(*shift)));
}
struct RNumber_proxy_t * bl_rnumber_rn_leftshift_ui( const struct RNumber * n, unsigned int shift ){
  return proxy_from_rnumber(new RNumber((*n)<<shift));
}
struct RNumber_proxy_t * bl_rnumber_ui_leftshift_rn( unsigned int n, const struct RNumber * shift ){
  return proxy_from_rnumber(new RNumber(n<<(*shift)));
}
struct RNumber_proxy_t * bl_rnumber_rn_leftshift_ext_rn( const struct RNumber * n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(leftShiftExt(*n1,*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_leftshift_ext_ui( const struct RNumber * n1, unsigned int n2 ){
  return proxy_from_rnumber(new RNumber(leftShiftExt(*n1,n2)));
}
struct RNumber_proxy_t * bl_rnumber_ui_leftshift_ext_rn( unsigned int n1, const struct RNumber * n2 ){
  return proxy_from_rnumber(new RNumber(leftShiftExt(n1,*n2)));
}
struct RNumber_proxy_t * bl_rnumber_rn_rightshift_rn( const struct RNumber * n, const struct RNumber * shift ){
  return proxy_from_rnumber(new RNumber((*n)>>(*shift)));
}
struct RNumber_proxy_t * bl_rnumber_rn_rightshift_ui( const struct RNumber * n, unsigned int shift ){
  return proxy_from_rnumber(new RNumber((*n)>>shift));
}
struct RNumber_proxy_t * bl_rnumber_ui_rightshift_rn( unsigned int n, const struct RNumber * shift ){
  return proxy_from_rnumber(new RNumber(n>>(*shift)));
}

