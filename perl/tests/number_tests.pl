#!/usr/local/bin/perl -w
##!/usr/bin/env perl -w

use lib '../src/';
use rnumber;

sub rnumber_cstr {
  return RNumber::rnumber_cstr($_[0]);
}

print "create from int\n";
{
  my $a =  RNumber::rnumber_create_from_unsigned(10);
  my $b =  RNumber::rnumber_create_from_unsigned(15);
  print "before\n";
  print "a ", $a, " b ", $b, "\n";
  print "after\n";
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), 
	 " rn=?", RNumber::rnumber_rn_equal_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn!=?", RNumber::rnumber_rn_notequal_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), 
	 " rn<?", RNumber::rnumber_rn_lessthan_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn<=?", RNumber::rnumber_rn_lessequal_rn($a,$b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn>?", RNumber::rnumber_rn_greaterthan_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn>=?", RNumber::rnumber_rn_greaterequal_rn( $a, $b), "\n");
}

print "create from string\n";
{
  my $a = RNumber::rnumber_create_from_string("10");
  my $b = RNumber::rnumber_create_from_string("15");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn=?", RNumber::rnumber_rn_equal_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn!=?", RNumber::rnumber_rn_notequal_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn<?", RNumber::rnumber_rn_lessthan_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn<=?", RNumber::rnumber_rn_lessequal_rn($a,$b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), 
	 " rn>?", RNumber::rnumber_rn_greaterthan_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), " rn>=?", 
	 RNumber::rnumber_rn_greaterequal_rn( $a, $b), "\n");
}

print "equal numbers\n";
{
  my $a = RNumber::rnumber_create_from_string("10");
  my $b = RNumber::rnumber_create_from_string("10");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), 
	 " rn=?",  RNumber::rnumber_rn_equal_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), 
	 " rn!=?", RNumber::rnumber_rn_notequal_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn<?",  RNumber::rnumber_rn_lessthan_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn<=?", RNumber::rnumber_rn_lessequal_rn($a,$b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b),
	 " rn>?",  RNumber::rnumber_rn_greaterthan_rn($a, $b), "\n");
  print("a=0x",RNumber::rnumber_cstr($a), " b=0x",RNumber::rnumber_cstr($b), 
	 " rn>=?", RNumber::rnumber_rn_greaterequal_rn( $a, $b), "\n");
}

{
  my $a = RNumber::rnumber_create_from_string("10");
  my $b = RNumber::rnumber_create_from_string("0xff");
  my $c = RNumber::rnumber_create_from_string("0xff");
  print "a ", $a, "\n";
  print "a ", RNumber::rnumber_cstr($a), "\n";
  print "b ", RNumber::rnumber_cstr($b), "\n";
  print "c ", RNumber::rnumber_cstr($c), "\n";
  print "a = b ", RNumber::rnumber_rn_equal_rn($a, $b), "\n";
  print "b = c ", RNumber::rnumber_rn_equal_rn($b, $c), "\n";
  print "a = 10 ", RNumber::rnumber_rn_equal_ui($a, 10), "\n";
  print "10 = a ", RNumber::rnumber_ui_equal_rn(10, $a), "\n";
  # rnumber-parse-string is currently only supported with bigloo binding.
  #print "parse from string qtv -> " rnumber-parse-string "qtv"))
  #(print "parse from string \"10\" -> " (rnumber-parse-string "10"))
  print ("5 - 3 -> ",
	 RNumber::rnumber_cstr(RNumber::rnumber_rn_minus_rn(RNumber::rnumber_create_from_unsigned(5),
								  RNumber::rnumber_create_from_string("3"))),
	 "\n");
}
