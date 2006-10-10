#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

package rnumber;
require RNumber;
require Exporter;

@ISA = qw(Exporter);

RNumber::rnumber_predicate_init();

@EXPORT = qw(stringp integerp rnumberp numericp rn_version rn_ctor rn_cstr rn_parse_string 
	     rn_int rn_eq rn_neq rn_lt rn_le rn_gt rn_ge rn_ls rn_rs rn_plus rn_minus 
	     rn_div rn_mult rn_bitor rn_bitand rn_mod rn_size);

sub rnumberp {
  my $a = shift @_;
  #print "<rnumberp>\n";
  unless (ref $a) {
    #print "</rnumberp ref $a failed>\n";
    return 0;
  };
  # for some reason, perl 5 and 5.[68] use a different string for the name of the structure.
  # if this can be calculated instead of hardcoded, the code below should change.
  if ($a->isa("_p_RNumber") || $a->isa("RNumber")) {
    #print "</rnumberp this is an RNumber>\n";
    return 1;
  }
  #print "</rnumberp this is not a _p_RNumber or RNumber>\n";
  return 0;
}

sub rn_version {
  print "rnumber_version is currently unimplemented\n";
}

sub rn_ctor {
  #print "rn_ctor\n";
  my $number = shift;
  my $size;
  if ($size = shift) {
    if ( rnumberp ($number)) {
      #print "create rnumber from rnumber $number\n";
      return RNumber::rnumber_create_from_rnumber($number);
    } elsif ( numericp ($number)) {
      #print "create rnumber from unsigned of  size $size and value $number\n";
      return RNumber::rnumber_create_from_unsigned_of_size($number,$size);
    } elsif ( stringp ($number)) {
      #print "create rnumber from string of size $size and value $number\n";
      return RNumber::rnumber_create_from_string_of_size($number,$size);
    }
  } else {
    if ( rnumberp ($number)) {
      #print "create rnumber from rnumber of default size and value $number\n";
      return RNumber::rnumber_create_from_rnumber($number);
    } elsif ( numericp ($number)) {
      #print "create rnumber from unsigned of default size and value $number\n";
      return RNumber::rnumber_create_from_unsigned($number);
    } elsif ( stringp ($number)) {
      #print "create rnumber from string of default size and value $number\n";
      return RNumber::rnumber_create_from_string($number);
    }
  }
  print("rnumber_ctor should be called with an integer, rnumber, or a string with an optional ",
	"2nd integer parameter for size.\n");
  return 0;
}

sub rn_cstr {
  my $number = shift @_;
  my $radix;
  if ( $radix = shift @_) {
    my $prefix;
    if ( @_ ) {
      $prefix = shift @_;
      return RNumber::rnumber_cstr_radix($number, $radix, $prefix);
    } else {
      return RNumber::rnumber_cstr_radix($number, $radix, 1);      
    }
  }
  return RNumber::rnumber_cstr_radix($number,16,0);
}

sub rn_parse_string {
  print "rnumber_parse_string is currently unimplemented\n";
}

sub rn_int {
  return rnumber_get_uint($_[0]);
}

sub rn_eq {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_equal_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_equal_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_equal_rn(@_);
  } else {
    return ($_[0] = $_[1]);
  }
}

sub rn_neq {
  return not rn_eq(@_);
}

sub rn_lt {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_lessthan_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_lessthan_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_lessthan_rn(@_);
  } else {
    return ($_[0] < $_[1]);
  }
}

sub rn_le {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_lessequal_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_lessequal_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_lessequal_rn(@_);
  } else {
    return ($_[0] <= $_[1]);
  }
}

sub rn_gt {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_greaterthan_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_greaterthan_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_greaterthan_rn(@_);
  } else {
    return ($_[0] > $_[1]);
  }
}

sub rn_ge {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_greaterequal_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_greaterequal_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_greaterequal_rn(@_);
  } else {
    return ($_[0] <= $_[1]);
  }
}

sub rn_ls {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_leftshift_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_leftshift_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_leftshift_rn($_[0], ($_[1] % 32));
  } else {
    return ($_[0] << $_[1]);
  }
}

sub rn_rs {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_rightshift_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_rightshift_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_rightshift_rn($_[0], ($_[1] % 32));
  } else {
    return ($_[0] >> $_[1]);
  }
}

sub rn_plus {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  #print "rn_1 $first_rn ui_1 $first_ui rn_2 $second_rn ui_2 $second_ui\n";
  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_plus_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_plus_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_plus_rn(@_);
  } else {
    print "Error: rn_plus should be called with an integer and an rnumber. Called with ('$_[0]', '$_[1]')\n";
    return 0;
  }
}

sub rn_minus {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);
  

#  print  "first_rn  '$first_rn' first_ui  '$first_ui' second_rn '$second_rn' second_ui '$second_ui'\n";
#  print "\@_ @_\n";

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_minus_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_minus_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_minus_rn(@_);
  } else {
    return ($_[0] - $_[1]);
  }
}

sub rn_div {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_divide_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_divide_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_divide_rn(@_);
  } else {
    return ($_[0] / $_[1]);
  }
}

sub rn_mult {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_multiply_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_multiply_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_multiply_rn(@_);
  } else {
    return ($_[0] * $_[1]);
  }
}

sub rn_bitor {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_bitor_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_bitor_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_bitor_rn(@_);
  } else {
    return ($_[0] | $_[1]);
  }
}

sub rn_bitand {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_bitand_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_bitand_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_bitand_rn(@_);
  } else {
    return ($_[0] & $_[1]);
  }
}

sub rn_mod {
  my $first_rn = rnumberp($_[0]);
  my $first_ui = numericp($_[0]);
  my $second_rn = rnumberp($_[1]);
  my $second_ui = numericp($_[1]);

  if ($first_rn && $second_rn) {
    return RNumber::rnumber_rn_mod_rn(@_);
  } elsif ($first_rn && $second_ui) {
    return RNumber::rnumber_rn_mod_ui(@_);
  } elsif ($first_ui && $second_rn) {
    return RNumber::rnumber_ui_mod_rn(@_);
  } else {
    return ($_[0] % $_[1]);
  }
}

sub rn_size {
  return RNumber::rnumber_size($_[0]);
}

package _p_RNumber;

sub DESTROY {
  my ($rnumber) = @_;
  #print( "(destroy ". $rnumber .")");
  RNumber::rnumber_destroy($rnumber);
}

use overload 
    '+' => \&overload_add,
    '-' => \&overload_minus,
    '%' => \&overload_mod,
    '*' => \&overload_mult,
    '/' => \&overload_div,
    '&' => \&overload_bitand,
    '|' => \&overload_bitor,
    '==' => \&overload_equal,
    '!=' => \&overload_not_equal,
    '<'  => \&overload_lessthan,
    '<=' => \&overload_lessequal,
    '>'  => \&overload_greaterthan,
    '>=' => \&overload_greaterequal,
    '<<' => \&overload_leftshift,
    '>>' => \&overload_rightshift,
    '""' => \&overload_to_string;

sub overload_add {
  #print "overload_add\n";
  my ($x, $y, $swapped) = @_;
  if ( $swapped ) {
    rnumber::rn_plus($y, $x);
  } else {
    rnumber::rn_plus($x, $y);
  }
}

sub overload_minus {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_minus($y, $x);
  } else {
    rnumber::rn_minus($x, $y);
  }
}

sub overload_mod {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_mod($y, $x);
  } else {
    rnumber::rn_mod($x, $y);
  }
}

sub overload_mult {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_mult($y, $x);
  } else {
    rnumber::rn_mult($x, $y);
  }
}

sub overload_div {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_div($y, $x);
  } else {
    rnumber::rn_div($x, $y);
  }
}

sub overload_bitand {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_bitand($y, $x);
  } else {
    rnumber::rn_bitand($x, $y);
  }
}

sub overload_bitor {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_bitor($y, $x);
  } else {
    rnumber::rn_bitor($x, $y);
  }
}

sub overload_equal {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_eq($y, $x);
  } else {
    rnumber::rn_eq($x, $y);
  }
}

sub overload_not_equal {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_neq($y, $x);
  } else {
    rnumber::rn_neq($x, $y);
  }
}

sub overload_lessthan {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_lt($y, $x);
  } else {
    rnumber::rn_lt($x, $y);
  }
}

sub overload_lessequal {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_le($y, $x);
  } else {
    rnumber::rn_le($x, $y);
  }
}

sub overload_greaterthan {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_gt($y, $x);
  } else {
    rnumber::rn_gt($x, $y);
  }
}

sub overload_greaterequal {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_ge($y, $x);
  } else {
    rnumber::rn_ge($x, $y);
  }
}

sub overload_leftshift {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_ls($y, $x);
  } else {
    rnumber::rn_ls($x, $y);
  }
}

sub overload_rightshift {
  my ($x, $y, $swapped) = @_;
  if ($swapped) {
    rnumber::rn_rs($y, $x);
  } else {
    rnumber::rn_rs($x, $y);
  }
}

sub overload_to_string {
  #print "overload to string\n";
  my ($x, $y, $swapped) = @_;
  rnumber::rn_cstr($x);
}

1;

