  RNumber * rnumber_assign_from_uint ( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_assign_from_string ( RNumber * rnumber, char * number_string )
  RNumber * rnumber_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_copy( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_plus_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_plus_assign_from_unsigned ( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_minus_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_minus_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_multiply_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_multiply_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_divide_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_divide_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_mod_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_mod_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_bitand_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_bitand_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_bitor_assign( RNumber * rnumber,  RNumber * number )
  RNumber * rnumber_bitor_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_bitxor_assign( RNumber * rnumber, RNumber * number )
  RNumber * rnumber_bitxor_assign_from_unsigned( RNumber * rnumber, unsigned int number )
  RNumber * rnumber_leftshift_assign( RNumber * rnumber, RNumber * shift )
  RNumber * rnumber_leftshift_assign_from_unsigned( RNumber * rnumber, unsigned int shift )
  RNumber * rnumber_rightshift_assign( RNumber * rnumber,  RNumber * shift )
  RNumber * rnumber_rightshift_assign_from_unsigned( RNumber * rnumber, unsigned int shift )
  RNumber * rnumber_invert( RNumber * rnumber)
  RNumber * rnumber_negate( RNumber * rnumber)
  RNumber * rnumber_set_all( RNumber * rnumber)
  RNumber * rnumber_clear_all( RNumber * rnumber)
  RNumber * rnumber_sign_extend( RNumber * rnumber, unsigned int bit )
  RNumber * rnumber_truncate( RNumber * rnumber, unsigned int size )]