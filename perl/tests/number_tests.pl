#!/usr/bin/env perl -w

use lib '../src/';
use pl_rnumber;

sub rnumber_cstr {
  return pl_rnumber::rnumber_cstr($_[0]);
}

# sub do-test {
#   my $a = shift;
#   my $b = shift;
#   print "a ", a, " b ", b;
#   print "a=0x", rnumber_cstr(a), " b=0x", rnumber_cstr(b), " rn=?", rn=? (a b);
#   print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn!=?" (rn!=? a b))
#    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn<?"  (rn<? a b))
#    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn<=?" (rn<=? a b))
#    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn>?"  (rn>? a b))
#    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn>=?" (rn>=? a b)))
#   }

print "create from int\n";
{
  my $a =  pl_rnumber::rnumber_create_from_unsigned(10);
  my $b =  pl_rnumber::rnumber_create_from_unsigned(15);
  print "a ", $a, " b ", $b, "\n";
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), 
	 " rn=?", pl_rnumber::rnumber_rn_equal_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn!=?", pl_rnumber::rnumber_rn_notequal_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), 
	 " rn<?", pl_rnumber::rnumber_rn_lessthan_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn<=?", pl_rnumber::rnumber_rn_lessequal_rn($a,$b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn>?", pl_rnumber::rnumber_rn_greaterthan_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn>=?", pl_rnumber::rnumber_rn_greaterequal_rn( $a, $b), "\n");
}

print "create from string\n";
{
  my $a = pl_rnumber::rnumber_create_from_string("10");
  my $b = pl_rnumber::rnumber_create_from_string("15");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn=?", pl_rnumber::rnumber_rn_equal_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn!=?", pl_rnumber::rnumber_rn_notequal_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn<?", pl_rnumber::rnumber_rn_lessthan_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn<=?", pl_rnumber::rnumber_rn_lessequal_rn($a,$b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), 
	 " rn>?", pl_rnumber::rnumber_rn_greaterthan_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), " rn>=?", 
	 pl_rnumber::rnumber_rn_greaterequal_rn( $a, $b), "\n");
}

print "equal numbers\n";
{
  my $a = pl_rnumber::rnumber_create_from_string("10");
  my $b = pl_rnumber::rnumber_create_from_string("10");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), 
	 " rn=?",  pl_rnumber::rnumber_rn_equal_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), 
	 " rn!=?", pl_rnumber::rnumber_rn_notequal_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn<?",  pl_rnumber::rnumber_rn_lessthan_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn<=?", pl_rnumber::rnumber_rn_lessequal_rn($a,$b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b),
	 " rn>?",  pl_rnumber::rnumber_rn_greaterthan_rn($a, $b), "\n");
  print("a=0x",pl_rnumber::rnumber_cstr($a), " b=0x",pl_rnumber::rnumber_cstr($b), 
	 " rn>=?", pl_rnumber::rnumber_rn_greaterequal_rn( $a, $b), "\n");
}

{
  my $a = pl_rnumber::rnumber_create_from_string("10");
  my $b = pl_rnumber::rnumber_create_from_string("0xff");
  my $c = pl_rnumber::rnumber_create_from_string("0xff");
  print "a ", $a, "\n";
  print "a ", pl_rnumber::rnumber_cstr($a), "\n";
  print "b ", pl_rnumber::rnumber_cstr($b), "\n";
  print "c ", pl_rnumber::rnumber_cstr($c), "\n";
  print "a = b ", pl_rnumber::rnumber_rn_equal_rn($a, $b), "\n";
  print "b = c ", pl_rnumber::rnumber_rn_equal_rn($b, $c), "\n";
  print "a = 10 ", pl_rnumber::rnumber_rn_equal_ui($a, 10), "\n";
  print "10 = a ", pl_rnumber::rnumber_ui_equal_rn(10, $a), "\n";
  # rnumber-parse-string is currently only supported with bigloo binding.
  #print "parse from string qtv -> " rnumber-parse-string "qtv"))
  #(print "parse from string \"10\" -> " (rnumber-parse-string "10"))
  print ("5 - 3 -> ",
	 pl_rnumber::rnumber_cstr(pl_rnumber::rnumber_rn_minus_rn(pl_rnumber::rnumber_create_from_unsigned(5),
								  pl_rnumber::rnumber_create_from_string("3"))),
	 "\n");
}


