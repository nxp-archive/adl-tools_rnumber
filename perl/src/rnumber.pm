
package rnumber;
require pl_rnumber;
require Exporter;
@ISA = qw(Exporter);

pl_rnumber::rnumber_predicate_init();

@EXPORT = qw(stringp integerp rnumberp numericp rn_version rn_ctor rn_cstr rn_parse_string 
	     rn_int rn_eq rn_neq rn_lt rn_le rn_gt rn_ge rn_ls rn_rs rn_plus rn_minus 
	     rn_div rn_mult rn_bitor rn_bitand rn_mod rn_size);

sub rnumberp
{
  my $a = shift @_;
  unless (ref $a) {
    return 0;
  };
  return $a->isa("struct RNumberPtr");
}

sub rn_version
{
  print "rnumber_version is currently unimplemented\n";
}

sub rn_ctor 
{
  my $number = shift;
  my $size;
  if ($size = shift) {
    if ( rnumberp ($number)) {
      return pl_rnumber::rnumber_create_from_rnumber($number);
    } elsif ( numericp ($number)) {
      return pl_rnumber::rnumber_create_from_unsigned_of_size($number,$size);
    } elsif ( stringp ($number)) {
      return pl_rnumber::rnumber_create_from_string_of_size($number,$size);
    }
  } else {
    if ( rnumberp ($number)) {
      return pl_rnumber::rnumber_create_from_rnumber($number);
    } elsif ( numericp ($number)) {
      return pl_rnumber::rnumber_create_from_unsigned($number);
    } elsif ( stringp ($number)) {
      return pl_rnumber::rnumber_create_from_string($number);
    }
  }
  print("rnumber_ctor should be called with an integer, rnumber, or a string with an optional ",
	"2nd integer parameter for size.\n");
  return 0;
}

sub rn_cstr
{
  my $number = shift @_;
  my $radix;
  if ( $radix = shift @_) {
    my $prefix;
    if ( @_ ) {
      $prefix = shift @_;
      return pl_rnumber::rnumber_cstr_radix($number, $radix, $prefix);
    } else {
      return pl_rnumber::rnumber_cstr_radix($number, $radix, 1);      
    }
  }
  return pl_rnumber::rnumber_cstr($number);
}

sub rn_parse_string 
{
  print "rnumber_parse_string is currently unimplemented\n";
}

sub rn_int
{
  return rnumber_get_uint($_[0]);
}

sub rn_eq
{
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_equal_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_equal_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_equal_rn(@_);
  } else {
    return ($a = $b);
  }
}

sub rn_neq {
  return not rnumber_equal(@_);
}

sub rn_lt {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_lessthan_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_lessthan_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_lessthan_rn(@_);
  } else {
    return ($a < $b);
  }
}

sub rn_le {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_lessequal_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_lessequal_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_lessequal_rn(@_);
  } else {
    return ($a <= $b);
  }
}

sub rn_gt {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_greaterthan_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_greaterthan_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_greaterthan_rn(@_);
  } else {
    return ($a > $b);
  }
}

sub rn_ge {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_greaterequal_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_greaterequal_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_greaterequal_rn(@_);
  } else {
    return ($a <= $b);
  }
}

sub rn_ls {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_leftshift_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_leftshift_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_leftshift_rn(@_);
  } else {
    return ($a << $b);
  }
}

sub rn_rs {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_rightshift_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_rightshift_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_rightshift_rn(@_);
  } else {
    return ($a >> $b);
  }
}

sub rn_plus {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  #print  "first_rn  $first_rn first_ui  $first_ui second_rn $second_rn second_ui $second_ui\n";
  #print "\@_ @_\n";

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_plus_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_plus_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_plus_rn(@_);
  } else {
    return ($a + $b);
  }
}

sub rn_minus {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_minus_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_minus_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_minus_rn(@_);
  } else {
    return ($a - $b);
  }
}

sub rn_div {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_divide_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_divide_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_divide_rn(@_);
  } else {
    return ($a / $b);
  }
}

sub rn_mult {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_multiply_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_multiply_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_multiply_rn(@_);
  } else {
    return ($a * $b);
  }
}

sub rn_bitor {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_bitor_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_bitor_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_bitor_rn(@_);
  } else {
    return ($a | $b);
  }
}

sub rn_bitand {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_bitand_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_bitand_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_bitand_rn(@_);
  } else {
    return ($a & $b);
  }
}

sub rn_mod {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return pl_rnumber::rnumber_rn_mod_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return pl_rnumber::rnumber_rn_mod_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return pl_rnumber::rnumber_ui_mod_rn(@_);
  } else {
    return ($a % $b);
  }
}

sub rn_size {
  return pl_rnumber::rnumber_size($_[0]);
}

1;
