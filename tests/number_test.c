#include <stdio.h>
#include <unistd.h>

#include "C-RNumber.h"
#include "C-Random.h"
#include "c-io.h"

unsigned maxIter = 100;

const int Verbose = 0;

struct Calculator 
{
  const char *_pgm;
  int _fd1[2];
  int _fd2[2];
};

struct Calculator * make_calculator (const char *pgm);
void destroy_calculator ( struct Calculator * calculator);

unsigned calculator_check_arith ( struct Calculator * calculator, const struct RNumber * a, 
				  const struct RNumber * b, const struct RNumber * c, char *op, int bool_ext);
unsigned calculator_check_arith_unsigned (struct Calculator * calculator, const struct RNumber * a, 
					  unsigned b, const struct RNumber * c, char *op, int bool_ext);
unsigned calculator_check_comparator ( struct Calculator * calculator, const struct RNumber * a, 
				       const struct RNumber * b, int res, char *op);
unsigned calculator_check_comparator_unsigned ( struct Calculator * calculator, const struct RNumber * a, 
						unsigned b, int res, char *op);

void calculator_private_init ( struct Calculator * calculator);
void calculator_private_terminate ( struct Calculator * calculator);
unsigned calculator_private_arith_calc (const char *astr,unsigned asize, const char *bstr,unsigned bsize,
					const struct RNumber * c,const char *op, int bool_ext);

static void usage (char *pgm)
{
  printf ("Usage:  %s [-seed n] [-n] [-dcpath <path to dc] [-dc <dc program>]\n", pgm);
  exit (1);
}

static unsigned checkOperator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    unsigned size2 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size(0, size2);
    struct RNumber * c = rnumber_create_from_unsigned_of_size_variable_sizing(0, 1);
    int ext = 0;    

    a = random_get_rnumber(size1);
    if (op[0] == '/' || op[0] == '%') {
      do {
        b = random_get_rnumber (size2);
      } while (rnumber_rn_equal_ui(b,0));
    } else {
      b = random_get_rnumber (size2);
    }

    if (!strcmp(op,"+")) {
      c = rnumber_rn_plus_rn(a,b);
    } else if (!strcmp(op,"-")) {
      c = rnumber_rn_minus_rn(a, b);
    } else if (!strcmp(op,"*")) {
      c = rnumber_rn_multiply_rn(a, b);
    } else if (!strcmp(op,"/")) {
      c = rnumber_rn_divide_rn(a, b);
    } else if (!strcmp(op,"%")) {
      c = rnumber_rn_mod_rn(a, b);
    } else if (!strcmp(op,"+.")) {
      c = rnumber_rn_add_ext_rn(a,b);
      ext = 1;
    } else if (!strcmp(op,"*.")) {
      c = rnumber_rn_multiply_ext_rn(a,b);
      ext = 1;
    } else {
      assert(0);
    }

    /*    rc |= calc -> checkArith (a, b, c, op, ext);*/
    rc |= calculator_check_arith(calc, a, b, c, op, ext);

  }
  return rc;
}

static unsigned checkIntOperator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    unsigned b = 0;
    struct RNumber * c = rnumber_create_from_unsigned_of_size_variable_sizing(0, 1);
    int ext = 0;    

    a = random_get_rnumber (size1);
    if (op[0] == '/' || op[0] == '%') {
      do {
        b = random_get_integer ();
      } while ( b == 0);
    } else {
      b = random_get_interger ();
    }

    if (!strcmp(op,"+")) {
      c = rnumber_rn_plus_ui(a, b);
    } else if (!strcmp(op,"-")) {
      c = rnumber_rn_minus_ui(a, b);
    } else if (!strcmp(op,"*")) {
      c = rnumber_rn_multiply_ui(a, b);
    } else if (!strcmp(op,"/")) {
      c = rnumber_rn_divide_ui(a, b);
    } else if (!strcmp(op,"%")) {
      c = rnumber_rn_mod_ui(a, b);
    } else if (!strcmp(op,"+.")) {
      c = rnumber_rn_add_ext_ui(a,b);
      ext = 1;
    } else if (!strcmp(op,"*.")) {
      c = rnumber_rn_multiply_ext_ui(a,b);
      ext = 1;
    } else {
      assert(0);
    }

    /*    rc |= calc -> checkArith (a, b, c, op, ext);*/
    rc |= calculator_check_arith_unsigned( calc, a, b, c, op, ext);

  }
  return rc;
}

static unsigned checkMutator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned (1, 100) : size;
    unsigned size2 = (size == 0) ? random_get_from_range_unsigned (1, 100) : size;
    struct RNumber * a = rnumber_create_from_unsigned_of_size_variable_sizing(0, size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size(0, size2);
    struct RNumber * tmp = rnumber_create_from_unsigned_of_size(0, size1);

    a = random_get_rnumber(size1);
    rnumber_assign(tmp, a);
    if (op[0] == '/' || op[0] == '%') {
      do {
        b = random_get_rnumber (size2);
      } while (rnumber_rn_equal_ui(b, 0));
    } else {
      b = random_get_rnumber(size2);
    }
    switch (op[0]) {
      case '+': rnumber_plus_assign(a, b); break;
      case '-': rnumber_minus_assign(a, b); break;
      case '*': rnumber_multiply_assign(a, b); break;
      case '/': rnumber_divide_assign(a, b); break;
      case '%': rnumber_mod_assign(a, b); break;
      default:  assert (0);
    }
    /*    rc |= calc -> checkArith (tmp, b, a, op); */
    rc |= calculator_check_arith (calc,tmp, b, a, op,0); 
     
  }
  return rc;
}

static unsigned checkIntMutator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    struct RNumber * a = rnumber_create_from_unsigned_of_size_variable_sizing(0, size1);
    unsigned b;
    struct RNumber *tmp = rnumber_create_from_unsigned_of_size(0, size1);

    a = random_get_rnumber (size1);
    tmp = a;
    if (op[0] == '/' || op[0] == '%') {
      do {
        b = random_get_integer ();
      } while (b == 0);
    } else {
      b = random_get_integer ();
    }
    switch (op[0]) {
    case '+': rnumber_plus_assign_unsigned(a, b); break;
    case '-': rnumber_minus_assign_unsigned(a, b); break;
    case '*': rnumber_multiply_assign_unsigned(a, b); break;
    case '/': rnumber_divide_assign_unsigned(a, b); break;
    case '%': rnumber_mod_assign_unsigned(a, b); break;
    default:  assert (0);
    }
    rc |= calculator_check_arith_unsigned(calc,tmp, b, a, op,0);
  }
  return rc;
}

// special cases for multiply
static unsigned checkMultSpecialCases (struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  // first op is 0:
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = rnumber_create_from_unsigned_of_size(0, random_get_from_range_unsigned (33, 100));
    struct RNumber * y = random_get_rnumber (random_get_from_range_unsigned (1, 100));
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    rc |= calculator_check_arith( calc,x, y, rnumber_rn_multiply_rn(x, y), "*", 0);
    rnumber_rn_multiply_assign(tmp, y);
    rc |= calculator_check_arith( calc,x, y, tmp, "*=", 0);
  }

  // second op is 0
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber ( random_get_from_range_unsigned (1, 100));
    struct RNumber * y = rnumber_create_from_unsigned_of_size(0, random_get_from_range_unsigned (33, 100));
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_multiply_rn(x, y), "*", 0);
    rnumber_multiply_assign(tmp, y);
    rc |= calculator_check_arith(calc,x, y, tmp, "*=",0);
  }

  // first op is 1:
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = rnumber_create_from_unsigned_of_size (1, random_get_from_range_unsigned (33, 100));
    struct RNumber * y = random_get_rnumber(random_get_from_range (1, 100));
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_multiply_rn(x, y), "*", 0);
    rnumber_multiply_assign(tmp, y);
    rc |= calculate_check_arith(calc, x, y, tmp, "*=",0);
  }

  // second op is 1
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber(random_get_from_range (1, 100));
    struct RNumber * y = rnumber_create_from_unsigned_of_size(1, random_get_from_unsigned (33, 100));
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_multiply_rn(x, y), "*",0);
    rnumber_multiply_assign(tmp, y);
    rc |= calculator_check_arith(calc, x, y, tmp, "*=",0);
  }

  return rc;
}

// special cases for divide
static unsigned checkDivideSpecialCases (struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  // first op is 0:
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = rnumber_create_from_unsigned_of_size (0, random_get_from_range_unsigned(33, 100));
    unsigned size2 = random_get_from_range (1, 100);
    struct RNumber * y = rnumber_create_from_unsigned_of_size (0, size2);
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    do {
      y = random_get_rnumber (size2);
    } while (rnumber_rn_equal_ui(y, 0));
    rc |= calculator_check_arith(calc,x, y, rnumber_rn_divide_rn(x, y), "/",0);
    rnumber_divide_equal(tmp, y);
    rc |= calculator_check_arith(calc, x, y, tmp, "/=",0);
  }

  // second op is 1
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber(random_get_from_range (1, 100));
    struct RNumber * y = rnumber_create_from_unsigned_of_size(1, random_get_from_range_unsigned(33, 100));
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_divide_rn(x, y), "/",0);
    rnumber_divide_assign(tmp, y);
    rc |= calculator_check_arith(calc, x, y, tmp, "/=",0);
  }

  // first op has size > 32 bits, but can be represented in 32 bits
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber (random_get_from_range_unsigned(33, 100));
    unsigned size2 = random_get_from_range_unsigned(33, 100);
    struct RNumber * y = rnumber_create_from_unsigned_of_size(0, size2);
    do {
      y = random_get_rnumber(size2);
    } while ( rnumber_rn_equal_ui(y, 0));
    {
      unsigned s = rnumber_size(x);
      unsigned n = random_get_from_range_unsigned (s - 32, s - 1);
      rnumber_rightshift_assign_from_unsigned(x, n);
    }
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_divide_rn(x, y), "/",0);
    {
      struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
      rnumber_divide_assign(tmp, y);
      rc |= calculator_check_arith(calc, x, y, tmp, "/=",0);
    }
  }

  // both ops have size > 32 bits, but can be represented in 32 bits
  // first op has size > 32 bits, but can be represented in 32 bits
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber (random_get_from_range_unsigned(33, 100));
    unsigned size2 = random_get_from_range (33, 100);
    unsigned s, n;
    struct RNumber * y = rnumber_create_from_unsigned_of_size(0, size2);
    do {
      y = random_get_rnumber (size2);
      s = rnumber_size(y);
      n = random_get_from_range (s - 32, s - 1);
      rnumber_rn_rightshift_assign_ui(y, n);
    } while ( rnumber_rn_equal_ui(y, 0));
    s = rnumber_size(x);
    n = random_get_from_range_unsigned (s - 32, s - 1);
    rnumber_rn_rightshift_ui(x, n);
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_divide_rn(x, y), "/",0);
    {
      struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
      rnumber_rn_divide_assign_rn(tmp, y);
      rc |= calculator_check_arith(calc, x, y, tmp, "/=",0);
    }
  }

  // ops have leading bytes that are 0
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber(random_get_from_range_unsigned(40, 100));
    unsigned size2 = random_get_from_range_unsigned(40, 100);
    unsigned s, n;
    struct RNumber * y = rnumber_create_from_unsigned_of_size(0, size2);
    do {
      y = random_get_rnumber (size2);
      s = rnumber_size(y);
      n = random_get_from_range_unsigned(8, s - 32);
      rnumber_rn_rightshift_assign_ui(y, n);
    } while(rnumber_rn_equal_ui(y, 0));
    s = rnumber_size(x);
    n = random_get_from_range_unsigned (8, s - 32);
    rnumber_rn_rightshift_ui(x, n);
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_divide_rn(x, y), "/",0);
    {
      struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
      rnumber_divide_assign(tmp, y);
      rc |= calculator_check_arith(calc, x, y, tmp, "/=",0);
    }
  }
  return rc;
}

static unsigned checkComparator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    unsigned size2 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    struct RNumber * a = random_get_rnumber(size1);
    struct RNumber * b = random_get_rnumber(size2);
    struct RNumber * c = random_get_rnumber(size2);
    int res1, res2;
    if (size1 < size2) {
      rnumber_assign(c, a);
    } else {
      rnumber_assign(a, c);
    }
    if (strcmp (op, ">") == 0) {
      res1 = rnumber_rn_greaterthan_rn(a, b);
      res2 = rnumber_rn_greaterthan_rn(a, c);
    }
    else if (strcmp (op, ">=") == 0) {
      res1 = rnumber_rn_greaterequal_rn(a, b);
      res2 = rnumber_rn_greaterequal_rn(a, c);
    }
    else if (strcmp (op, "<") == 0) {
      res1 = rnumber_rn_lessthan_rn(a, b);
      res2 = rnumber_rn_lessthan_rn(a, c);
    }
    else if (strcmp (op, "<=") == 0) {
      res1 = rnumber_rn_lessequal_rn(a, b);
      res2 = rnumber_rn_lessequal_rn(a, c);
    }
    else if (strcmp (op, "==") == 0) {
      res1 = rnumber_rn_equal_rn(a, b);
      res2 = rnumber_rn_equal_rn(a, c);
    }
    else if (strcmp (op, "!=") == 0) {
      res1 = rnumber_rn_notequal_rn(a, b);
      res2 = rnumber_rn_notequal_rn(a, c);
    }
    else if (strcmp (op, "compare") == 0) {
      res1 = rnumber_compare(a, b);
      res2 = rnumber_compare(a, c);
    }
    else
      assert (0);
    rc |= calculator_check_comparator(calc, a, b, res1, op);
    rc |= calculator_check_comparator(calc, a, c, res2, op);
  }

  return rc;
}

static unsigned checkIntComparator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned (1, 100) : size;
    struct RNumber * a = random_get_rnumber (size1);
    unsigned b = random_get_integer();
    unsigned c = random_get_integer();
    int res1, res2;
    if (size1 < 32) {
      c = rnumber_get_uint(a);
    } else {
      rnumber_assign_uint(a, c);
    }

    if (strcmp (op, ">") == 0) {
      res1 = rnumber_rn_greater_ui(a, b);
      res2 = rnumber_rn_greater_ui(a, c);
    }
    else if (strcmp (op, ">=") == 0) {
      res1 = rnumber_rn_lessequal_ui(a, b);
      res2 = rnumber_rn_lessequal_ui(a, c);
    }
    else if (strcmp (op, "<") == 0) {
      res1 = rnumber_rn_lessthan_ui(a, b);
      res2 = rnumber_rn_lessthan_ui(a, c);
    }
    else if (strcmp (op, "<=") == 0) {
      res1 = rnumber_rn_lessequal_ui(a, b);
      res2 = rnumber_rn_lessequal_ui(a, c);
    }
    else if (strcmp (op, "==") == 0) {
      res1 = rnumber_rn_equal_ui(a, b);
      res2 = rnumber_rn_equal_ui(a, c);
    }
    else if (strcmp (op, "!=") == 0) {
      res1 = rnumber_rn_notequal_ui(a, b);
      res2 = rnumber_rn_notequal_ui(a, c);
    }
    else {
      assert (0);
    }
    rc |= calculator_check_comparator_unsigned(calc, a, b, res1, op);
    rc |= calculator_check_comparator_unsigned(calc, a, c, res2, op);
  }

  // special cases:  a == b
  for (i = 0; i < 5; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned (1, 100) : size;
    struct RNumber * a = random_get_rnumber(size1);
    unsigned b = random_get_uint ();
    int res;
    if (size1 < 32) {
      rnumber_assign_from_int(a, b);
    } else {
      b = rnumber_get_uint(a);
    }
    if (strcmp (op, ">") == 0)
      res = rnumber_rn_greaterthan_ui(a, b);
    else if (strcmp (op, ">=") == 0)
      res = rnumber_rn_greaterequal_ui(a, b);
    else if (strcmp (op, "<") == 0)
      res = rnumber_rn_lessthan_ui(a, b);
    else if (strcmp (op, "<=") == 0)
      res = rnumber_rn_lessequal_ui(a, b);
    else if (strcmp (op, "==") == 0)
      res = rnumber_rn_equal_ui(a, b);
    else if (strcmp (op, "!=") == 0)
      res = rnumber_rn_notequal_ui(a, b);
    rc |= calculator_check_comparator_unsigned(calc, a, b, res, op);
  }
  return rc;
}

static unsigned checkSignedComparator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned (1, 100) : size;
    unsigned size2 = (size == 0) ? random_get_from_range_unsinged (1, 100) : size;
    struct RNumber * a = random_get_rnumber (size1);
    struct RNumber * b = random_get_rnumber (size2);
    struct RNumber * c = random_get_rnumber (size2);
    int cmp, failed;

    // test b negative, a positive
    if (size1 <= size2) {
      rnumber_setbit(a, 0, 0);
      rnumber_setbit(b, 0, 1);
      failed = 0;
      if (strcmp (op, "GT") == 0) {
        cmp = rnumber_signed_greaterthan(a,b);
        failed = (! cmp);
      }
      else if (strcmp (op, "GE") == 0) {
        cmp = rnumber_signed_greaterequal(a, b);
        failed = (! cmp);
      }
      else if (strcmp (op, "LT") == 0) {
        cmp = rnumber_signed_lessthan(a, b);
        failed = cmp;
      }
      else if (strcmp (op, "LE") == 0) {
        cmp = rnumber_signed_lessequal(a,b);
        failed = cmp;
      }
      if (failed) {
        printf ("Error occurred in comparison signed%s on values %s(%d) and %s(%d)\n", op,
		rnumber_cstr(a), rnumber_size(a), rnumber_cstr(b), rnumber_size(b));
        rc = 1;
      }
    }

    // test a negative, b positive
    if (size1 >= size2) {
      rnumber_setbit(a, 0, 1);
      rnumber_setbit(b, 0, 0);
      failed = 0;
      if (strcmp (op, "GT") == 0) {
        cmp = rnumber_signed_greaterthan(a,b);
        failed = cmp;
      }
      else if (strcmp (op, "GE") == 0) {
        cmp = rnumber_signed_greaterequal(a,b);
        failed = cmp;
      }
      else if (strcmp (op, "LT") == 0) {
        cmp = rnumber_signed_lessthan(a,b);
        failed = (! cmp);
      }
      else if (strcmp (op, "LE") == 0) {
        cmp = rnumber_signed_lessequal(a,b);
        failed = (! cmp);
      }
      else
        assert (0);
      if (failed) {
        printf ("Error occurred in comparison signed%s on values %s(%d) and %s(%d)\n", op,
		rnumber_cstr(a), rnumber_size(a), rnumber_cstr(b), rnumber_size(b));
        rc = 1;
      }
    }

    {
      // test same sign
      unsigned s = random_get_integer_n(2);
      rnumber_setbit(a, 0, s);
      rnumber_setbit(b, 0, s);
      rnumber_setbit(c, 0, s);
    }
    if (size1 < size2) {
      rnumber_assign(c, a);
      rnumber_setbit(b, 0, 0);
    }
    else {
      rnumber_assign(a, c);
    }
    
    {
      int res1, res2;
      char *newop;
      if (strcmp (op, "GT") == 0) {
	res1 = rnumber_signed_greaterthan(a, b);
	res2 = rnumber_signed_greaterthan(a, c);
	newop = ">";
      }
      else if (strcmp (op, "GE") == 0) {
	res1 = rnumber_signed_greaterequal(a, b);
	res2 = rnumber_signed_greaterequal(a, c);
	newop = ">=";
      }
      else if (strcmp (op, "LT") == 0) {
	res1 = rnumber_signed_lessthan(a, b);
	res2 = rnumber_signed_lessthan(a, c);
	newop = "<";
      }
      else if (strcmp (op, "LE") == 0) {
	res1 = rnumber_signed_lessequal(a, b);
	res2 = rnumber_signed_lessequal(a, c);
	newop = "<=";
      }
      else
	assert (0);
      rc |= calculator_check_comparator(calc, a, b, res1, newop);
      rc |= calculator_check_comparator(calc, a, c, res2, newop);
    }
  }
  return rc;
}

  static unsigned checkBitAccessors (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < 50; i++) {
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    unsigned n = random_get_integer(size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size(1, size1);
    struct RNumber * c = rnumber_create_from_unsigned_of_size(1, size1);
    unsigned shift = size1 - n - 1;
    rnumber_rn_leftshift_assign_ui(b, shift);
    rnumber_rn_leftshift_assign_ui(c, n);

    rnumber_setbit(a, n, 1);
    if (rnumber_rn_notequal_rn(a, b)) {
      printf ("Error occurred in setting bit %d of 0 to produce %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (rnumber_getbit(a, n) != 1) {
      printf ("Error occurred in getting bit %d of %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }

    rnumber_assign_from_uint(a, 0);
    rnumber_setbit_lsb(a, n, 1);
    if (rnumber_rn_notequal_rn(a, c)) {
      printf ("Error occurred in setting bit %d of 0 to produce %s(%d)\n", n, rnumber_str(a), size1);
      rc = 1;
    }
    if (rnumber_getbit_lsb(a, n) != 1) {
      printf ("Error occurred in getting bit %d of %s(%d)\n", n, rnumber_str(a), size1);
      rc = 1;
    }

    rnumber_set_all(a);
    rnumber_invert(b);
    rnumber_invert(c);

    rnumber_setbit(a, n, 0);
    if (rnumber_rn_notequal_rn(a, b)) {
      printf ("Error occurred in clearing bit %d of ones to produce %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (rnumber_getbit(a,n) != 0) {
      printf ("Error occurred in getting bit %d of %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
    rnumber_set_all(a);
    rnumber_setbit_lsb(a, n, 0);
    if (rnumber_rn_notequal_rn(a, c)) {
      printf ("Error occurred in setting bit %d of ones to produce %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (rnumber_getbit_lsb(a,n) != 0) {
      printf ("Error occurred in getting bit %d of %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
  }

  return rc;
}

static unsigned checkFieldAccessors (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < 50; i++) {
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    unsigned n1 = random_get_integer (size1);
    unsigned n2 = random_get_from_range_unsigned(n1, size1 - 1);
    unsigned len = n2 - n1 + 1;
    struct RNumber *  field = rnumber_create_from_unsigned_of_size(0, len);
    struct RNumber * b = rnumber_copy_to_size(field, size1);
    unsigned shift = size1 - n2 - 1;

    rnumber_set_all(field);
    rnumber_rn_leftshift_assign_ui(b, shift);

    rnumber_set_field(a, n1, n2, field);
    if (rnumber_rn_notequal_rn(a, b)) {
      printf ("Error occurred in setting field %d:%d of 0 to produce %s(%d)\n", n1, n2, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (rnumber_getfield(a, n1, n2) != field) {
      printf ("Error occurred in getting field %d:%d of %s(%d)\n", n1, n2, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (n2 - n1 < 32) {
      if (rnumber_rn_notequal_ui(field, rnumber_get_int_field(a, n1, n2))) {
        printf ("Error occurred in getting int field %d:%d of %s(%d)\n", n1, n2, rnumber_cstr(a), size1);
        rc = 1;
      }
    }

    rnumber_set_all(a);
    rnumber_invert(b);

    rnumber_set_field(a,n1, n2, 0);
    if (rnumber_rn_notequal_rn(a, b)) {
      printf ("Error occurred in clearing field %d:%d of ones to produce %s(%d)\n", n1, n2, 
	      rnumber_cstr(a), size1);
      rc = 1;
    }
    if (rnumber_get_field(a, n1, n2) != 0) {
      printf ("Error occurred in getting field %d:%d of %s(%d)\n", n1, n2, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (n2 - n1 < 32) {
      if (rnumber_get_int_field(a, n1, n2) != 0) {
        printf ("Error occurred in getting int field %d:%d of %s(%d)\n", n1, n2, rnumber_cstr(a), size1);
        rc = 1;
      }
    }
  }
  return rc;
}

static unsigned checkSignExtends (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < 50; i++) {
    unsigned size1 = (size > 0) ? size : random_get_from_range (1, 100);
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    unsigned n = random_get_integer(size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size (0, size1);
    unsigned shift = size1 - n - 1;
    rnumber_set_all(b);
    rnumber_rn_leftshift_assign_ui(b, shift);

    rnumber_set_bit(a,n, 1);
    rnumber_sign_extend(a,n);
    if (rnumber_rn_notequal_rn(a, b)) {
      printf ("Error occurred in extending bit %d; produced %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }

    rnumber_set_all(a);
    rnumber_set_bit(a,n, 0);
    rnumber_invert(b);

    rnumber_sign_extend(a,n);
    if (a != b) {
      printf ("Error occurred in extending bit %d; produced %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
  }

  return rc;
}

static unsigned checkReadWrite (const struct RNumber * numa, int radix)
{
  unsigned rc = 0;
  unsigned size1 = rnumber_size(numa);

  void * ss1 = ss_create();
  rnumber_print_with_radix( numa, ss1, radix, 1);
  ss_ends(ss1);

  {
    char *str1;
    str1 = ss_str(ss1);
    {
      struct RNumber * num1 = rnumber_create_from_string(str1);
      
      if (numa != num1) {
	printf ("Error in reading/writing of %s(%d) with implied radix %d\n", 
		rnumber_str(numa), size1, radix);
	rc = 1;
      }
  if (size1 > 1) {
    // construct a smaller number with the string
    unsigned size2 = random_get_from_range_unsigned(1, size1 - 1);
    struct RNumber * numb = rnumber_create_from_rnumber(numa);
    rnumber_assign (numb, rnumber_rn_rightshift_ui( rnumber_rn_leftshift_ui(numb, (size1 - size2)), (size1 - size2)));
 
    {
      struct RNumber * nums1 = rnumber_create_from_string_of_size(str1, size2);
      if ( rnumber_rn_notequal(nums1, numb) || rnumber_size(nums1) != size2) {
	printf ("Error in reading/writing of %s(%d) to %d with implied radix %d\n", 
		rnumber_str(numa), size1, size2, radix);
	rc = 1;
      }

      {
	// construct a larger number with the string
	unsigned size3 = random_get_from_range_unsigned(size1 + 1, 100);
	struct RNumber * nums2 = rnumber_create_from_string_of_size(str1, size3);
	if ( rnumber_rn_notequal_rn(nums2, numa) || rnumber_size(nums2) != size3) {
	  printf ("Error in reading/writing of %s(%d) to %d with implied radix %d\n", 
		  rnumber_str(numa), size1, size3, radix);
	  rc = 1;
	}
      }
    }
  }
  {
    void * ss3 = ss_create();
    rnumber_print_with_radix(numa, ss3, radix,1);
    ss_ends(ss3);
    {
      char * str3 = ss_str(ss3);
      struct RNumber * num3 = rnumber_create_from_string_of_radix (str3, radix);
      if (rnumber_rn_notequal_rn(numa, num3)) {
	printf ("Error in hex reading/writing of %s(%d) with explicit radix %d\n", 
		rnumber_str(numa), rnumber_size(numa), radix);
	rc = 1;
      }
    }
  }
  if (size1 > 1) {
    // construct a smaller number with the string
    unsigned size2 = random_get_from_range_unsigned(1, size1 - 1);
    struct RNumber * numb = rnumber_create_from_rnumber(numa);
    rnumber_assign(numb, rnumber_rn_rightshift_ui(rnumber_rn_leftshift_ui(numb, (size1 - size2)), (size1 - size2)));
 
    RNumber nums1 (str3, size2, radix);
    if (nums1 != numb || nums1 . size () != size2) {
      printf ("Error in reading/writing of %s(%d) to %d with explicit radix %d\n", numa . str () . c_str (), size1, size2, radix);
      rc = 1;
    }

    // construct a larger number with the string
    unsigned size3 = Random::getFromRange (size1 + 1, 100);
    RNumber nums2 (str3, size3, radix);
    if (nums2 != numa || nums2 . size () != size3) {
      printf ("Error in reading/writing of %s(%d) to %d with explicit radix %d\n", numa . str () . c_str (), size1, size3, radix);
      rc = 1;
    }
  }
  return rc;
}

static unsigned checkConstructors ()
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = Random::getFromRange (1, 90);
    unsigned size2 = Random::getFromRange (91, 100);
    RNumber x0 = Random::getRNumber (size1);
    RNumber y0 = Random::getRNumber (size2);
    RNumber tmp (0, size2);

    // basic copy constructor
    RNumber z1 (x0);
    if (z1 != x0 || z1 . size () != size1) {
      printf ("Error occurred in basic copy constructor of %s(%d)\n", x0 . str () . c_str (), size1);
      rc = 1;
    }

    // construct larger number
    RNumber z2 (x0, size2);
    if (z2 != x0 || z2 . size () != size2) {
      printf ("Error occurred in sized copy constructor of %s(%d) to %d\n", x0 . str () . c_str (), size1, size2);
      rc = 1;
    }

    // construct smaller number
    RNumber z3 (y0, size1);
    tmp = y0;
    tmp <<= (size2 - size1);
    tmp >>= (size2 - size1);
    if (z3 != tmp || z3 . size () != size1) {
      printf ("Error occurred in sized copy constructor of %s(%d) to %d\n", y0 . str () . c_str (), size2, size1);
      rc = 1;
    }

    // construct from integer
    unsigned num = Random::getInteger ();
    RNumber z31 = num;
    if (z31 != num || z31 . size () != 32) {
      printf ("Error occurred in constructing from integer %x\n", num);
      rc = 1;
    }

    // construct to larger from integer
    RNumber z32 (num, size2);
    if (z32 != num || z32 . size () != size2) {
      printf ("Error occurred in constructing larger number (%d) from integer %x\n", size2, num);
      rc = 1;
    }

    // construct to smaller from integer
    unsigned size3 = Random::getFromRange (1, 31);
    RNumber z33 (num, size3);
    unsigned diff = 32 - size3;
    unsigned num2 = (num << diff) >> diff;
    if (z33 != num2 || z33 . size () != size3) {
      printf ("Error occurred in constructing smaller number (%d) from integer %x\n", size3, num);
      rc = 1;
    }

    // basic set
    RNumber z4 = Random::getRNumber (size1);
    z4 . set (x0);
    if (z4 != x0 || z4 . size () != x0 . size ()) {
      printf ("Error occurred in basic set of %s(%d)\n", x0 . str () . c_str (), size1);
      rc = 1;
    }

    // set from smaller
    RNumber z5 = Random::getRNumber (size2);
    z5 . set (x0);
    if (z5 != x0 || z5 . size () != x0 . size ()) {
      printf ("Error occurred in sized set of %s(%d) from %d\n", x0 . str () . c_str (), size1, size2);
      rc = 1;
    }

    // set from larger
    RNumber z6 = Random::getRNumber (size1);
    z6 . set (y0);
    if (z6 != y0 || z6 . size () != y0 . size ()) {
      printf ("Error occurred in sized set of %s(%d) from %d\n", y0 . str () . c_str (), size2, size1);
      rc = 1;
    }

    // basic operator=
    RNumber z7 = Random::getRNumber (size1);
    z7 = x0;
    if (z7 != x0 || z7 . size () != size1) {
      printf ("Error occurred in basic operator= of %s(%d)\n", x0 . str () . c_str (), size1);
      rc = 1;
    }

    // operator= from smaller
    RNumber z8 = Random::getRNumber (size2);
    z8 = x0;
    if (z8 != x0 || z8 . size () != size2) {
      printf ("Error occurred in sized operator= of %s(%d) to %d\n", x0 . str () . c_str (), size1, size2);
      rc = 1;
    }

    // operator= from larger
    RNumber z9 = Random::getRNumber (size1);
    z9 = y0;
    if ( (z9.sizing() == RNumber::dynamic && ( z9 != y0 || z9.size() != y0.size())) ||
         (z9.sizing() == RNumber::fixed && z9.size() != size1)) {
      printf ("Error occurred in sized operator= of %s(%d) to %d\n", y0 . str () . c_str (), size2, size1);
      rc = 1;
    }

    // operator= from integer
    RNumber z91 (0, 32);
    unsigned num91 = Random::getInteger ();
    z91 = num91;
    if (z91 != num91 || z91 . size () != 32) {
      printf ("Error occurred in operator= of %x\n", num91);
      rc = 1;
    }

    // operator= to larger from integer
    RNumber z92 = Random::getRNumber (size2);
    unsigned num92 = Random::getInteger ();
    z92 = num92;
    if (z92 != num92 || z92 . size () != size2) {
      printf ("Error occurred in operator= of %x to size %d\n", num92, size2);
      rc = 1;
    }

    // operator= to smaller from integer
    unsigned size93 = Random::getFromRange (1, 31);
    RNumber z93 = Random::getRNumber (size93);
    z93.setDynamic();
    unsigned num93 = Random::getInteger ();
    z93 = num93;
    unsigned mask = 0x1;
    unsigned count = 0;
    while (mask <= num93 && mask != 0) {
      mask <<= 1;
      count++;
    }
    if (z93 != num93 || z93 . size () < count) {
      printf ("Error occurred in operator= of %x to size %d\n", num93, size93);
      rc = 1;
    }

    // resize to larger
    RNumber z10 = Random::getRNumber (size1);
    RNumber largerValue( z10, size2 );

    z10 . resize (size2);

    if (z10 != largerValue || z10 . size () != size2) {
      printf ("Error occurred in resize from %d to %d\n", size1, size2);
      rc = 1;
    }

    // resize to smaller
    RNumber z11 = Random::getRNumber (size2);
    RNumber smallerValue( z11, size1 );

    z11 . resize (size1);

    if (z11 != smallerValue || z11 . size () != size1) {
      printf ("Error occurred in resize from %d to %d\n", size2, size1);
      rc = 1;
    }

    // test various string constructors
    RNumber num1a = Random::getRNumber (size1);
    rc |= checkReadWrite (num1a, RNumber::rhex);
    rc |= checkReadWrite (num1a, RNumber::rbin);
    rc |= checkReadWrite (num1a, RNumber::rdec);
  }

  return rc;
}

static unsigned checkInversions (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : Random::getFromRange (1, 100);
    RNumber a = Random::getRNumber (size1);
    RNumber tmp = a;
    RNumber ones (0, size1);
    ones . setAll ();

    a . negate ();
    if (a + tmp != 0) {
      printf ("Error occurred in negating %s; produced %s(%d)\n", tmp . str () . c_str (), a . str () . c_str (), size1);
      rc = 1;
    }

    a = -tmp;
    if (a + tmp != 0) {
      printf ("Error occurred in negating %s; produced %s(%d)\n", tmp . str () . c_str (), a . str () . c_str (), size1);
      rc = 1;
    }

    a = tmp;
    a . invert ();
    if ((a | tmp) != ones) {
      printf ("Error occurred in inverting %s; produced %s(%d)\n", tmp . str () . c_str (), a . str () . c_str (), size1);
      rc = 1;
    }

    a = ~tmp;
    if ((a | tmp) != ones) {
      printf ("Error occurred in inverting %s; produced %s(%d)\n", tmp . str () . c_str (), a . str () . c_str (), size1);
      rc = 1;
    }
  }

  return rc;
}

static unsigned checkShifts (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : Random::getFromRange (1, 100);
    unsigned n = Random::getInteger (size1);
    RNumber rn(n);
    RNumber a (0, size1);
    a . setAll ();
    RNumber b (0, size1 - n);
    b . setAll ();

    // This group of shifts should not be destructive, since we're allowing
    // the result to grow.
    RNumber tmpe = leftShiftExt(a,n) >> n;
    if (tmpe != a) {
      printf ("Error occurred in extendable shifting %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, n, tmpe . str () . c_str ());
      printf ("  Expected %s\n", a . str().c_str());
      rc = 1;
    }

    // This group of shifts should not be destructive, since we're allowing
    // the result to grow.
    tmpe = leftShiftExt(a,rn) >> rn;
    if (tmpe != a) {
      printf ("Error occurred in extendable shifting %s(%d) by %s; produced %s\n", a . str () . c_str (), size1, rn.str().c_str(), tmpe . str () . c_str ());
      printf ("  Expected %s\n", a . str().c_str());
      rc = 1;
    }

    // The rest of these shifts will be destructive, since the size of
    // the value may not grow.
    RNumber tmp = (a << n) >> n;
    if (tmp != b) {
      printf ("Error occurred in shifting %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, n, tmp . str () . c_str ());
      rc = 1;
    }

    // The rest of these shifts will be destructive, since the size of
    // the value may not grow.
    tmp = (a << rn) >> rn;
    if (tmp != b) {
      printf ("Error occurred in shifting %s(%d) by %s; produced %s\n", a . str () . c_str (), size1, rn.str().c_str(), tmp . str () . c_str ());
      rc = 1;
    }

    tmp = a;
    tmp <<= n;
    tmp >>= n;
    if (tmp != b) {
      printf ("Error occurred in shift/equaling %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, n, tmp . str () . c_str ());
      rc = 1;
    }

    tmp = a << size1;
    if (tmp != 0) {
      printf ("Error occurred in shifting %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, size1, tmp . str () . c_str ());
      rc = 1;
    }
    tmp = a >> size1;
    if (tmp != 0) {
      printf ("Error occurred in right shifting %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, size1, tmp . str () . c_str ());
      rc = 1;
    }

    tmp = a;
    tmp <<= size1;
    if (tmp != 0) {
      printf ("Error occurred in left shift/equaling %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, size1, tmp . str () . c_str ());
      rc = 1;
    }
    tmp = a;
    tmp >>= size1;
    if (tmp != 0) {
      printf ("Error occurred in right shift/equaling %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, size1, tmp . str () . c_str ());
      rc = 1;
    }

    if (size1 > 32) {
      n = ((n + 31) / 32) * 32;
      if (n == 0)
        n = 32;
      if (n > size1)
        n -= 32;
      if (n == size1)
        n--;
      RNumber c (0, size1 - n);
      c . setAll ();
      tmp = (a << n) >> n;
      if (tmp != c) {
        printf ("Error occurred in shifting %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, n, tmp . str () . c_str ());
        rc = 1;
      }

      tmp = a;
      tmp <<= n;
      tmp >>= n;
      if (tmp != c) {
        printf ("Error occurred in shift/equaling %s(%d) by %d; produced %s\n", a . str () . c_str (), size1, n, tmp . str () . c_str ());
        rc = 1;
      }
    }

  }

  return rc;
}

static unsigned checkSetAlls (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : Random::getFromRange (1, 100);
    RNumber a (0, size1);
    a . setAll ();
    RNumber b (0, size1);
    b -= 1;

    if (a != b ) {
      printf ("Error occurred in setAll(%d); produced %s\n", size1, a . str () . c_str ());
      rc = 1;
    }
  }

  return rc;
}

static unsigned checkClearAlls (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : Random::getFromRange (1, 100);
    RNumber a (0, size1);
    a . setAll ();
    a . clearAll ();

    if (a != 0) {
      printf ("Error occurred in clearAll(%d); produced %s\n", size1, a . str () . c_str ());
      rc = 1;
    }
  }

  return rc;
}

static unsigned checkGetInts (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : Random::getFromRange (1, 100);
    RNumber a = Random::getRNumber (size1);
    unsigned ai = a . getInt ();
    unsigned shift = (size1 > 32) ? size1 - 32 : 0;
    RNumber b = (a << shift) >> shift;

    if (b != ai) {
      printf ("Error occurred in getInt on %s(%d); produced %x\n", a . str () . c_str (), size1, ai);
      rc = 1;
    }
  }

  return rc;
}

static unsigned checkLogicalOp (const RNumber& a, const RNumber& b, const RNumber& res1, const RNumber& res2, char *op)
{
  unsigned rc = (res1 != res2);
  if (rc) {
    printf ("Error (1) occurred in expression:  %s(%d) %s(%d) %s\n", a . str () . c_str (), a . size (),
            b . str () . c_str (), b . size (), op);
    printf ("  RNumber res = %s, expected res = %s\n", res1 . str () . c_str (), res2 . str () . c_str ());
  }
  return rc;
}

static unsigned checkLogicalOp (const RNumber& a, unsigned b, const RNumber& res1, const RNumber& res2, char *op)
{
  unsigned rc = (res1 != res2);
  if (rc) {
    printf ("Error (2) occurred in expression:  %s(%d) %x %s\n", a . str () . c_str (), a . size (), b, op);
    printf ("  RNumber res = %s, expected res = %s\n", res1 . str () . c_str (), res2 . str () . c_str ());
  }
  return rc;
}

static unsigned checkLogicals ()
{
  unsigned rc = 0;
  unsigned i;

  // and
  for (i = 0; i < maxIter; i++) {
    unsigned size1 = Random::getFromRange (1, 90);
    unsigned size2 = Random::getFromRange (91, 100);
    RNumber a = Random::getRNumber (size1);
    RNumber b = Random::getRNumber (size2);
    RNumber b0 (0, size1);
    RNumber b1 (0, size1);
    b1 . setAll ();
    RNumber c0 (0, size2);
    RNumber c1 (0, size2);
    c1 . setAll ();
    RNumber tmpa = a;
    RNumber tmpb = b;
    RNumber tmpc0 = c0;
    RNumber tmpc1 = c1;

    // check & and &= using (x & zero), (x & ones), (zero & x), and (ones & x) with
    // different sizes of x, zero, and ones:
    //   & operands have same size
    rc |= checkLogicalOp (a, b0, a & b0, 0, "&");
    a &= b0;
    rc |= checkLogicalOp (tmpa, b0, a, 0, "&=");
    a = tmpa;
    rc |= checkLogicalOp (a, b1, a & b1, a, "&");
    a &= b1;
    rc |= checkLogicalOp (tmpa, b1, a, tmpa, "&=");
    //   smaller & larger
    rc |= checkLogicalOp (a, c0, a & c0, 0, "&");
    a &= c0;
    rc |= checkLogicalOp (tmpa, c0, a, 0, "&=");
    a = tmpa;
    rc |= checkLogicalOp (a, c1, a & c1, a, "&");
    a &= c1;
    rc |= checkLogicalOp (tmpa, c1, a, tmpa, "&=");
    a = tmpa;
    //   larger & smaller
    rc |= checkLogicalOp (c0, a, c0 & a, 0, "&");
    c0 &= a;
    rc |= checkLogicalOp (tmpc0, a, c0, 0, "&=");
    c0 = tmpc0;
    rc |= checkLogicalOp (c1, a, c1 & a, a, "&");
    c1 &= a;
    rc |= checkLogicalOp (tmpc1, a, c1, a, "&=");
    c1 = tmpc1;
    //   & with integer
    rc |= checkLogicalOp (b, 0, b & 0, 0, "&");
    b &= 0;
    rc |= checkLogicalOp (tmpb, 0, b, 0, "&=");
    b = tmpb;
    rc |= checkLogicalOp (b, -1, b & (-1), b . getInt (), "&");
    b &= (-1);
    rc |= checkLogicalOp (tmpb, -1, b, tmpb . getInt (), "&=");
    b = tmpb;

    // check | and |= using (x | ones) and (ones | x) with
    // different sizes of x and ones:
    //   | operands have same size
    rc |= checkLogicalOp (a, b1, a | b1, b1, "|");
    a |= b1;
    rc |= checkLogicalOp (tmpa, b1, a, b1, "|=");
    a = tmpa;
    //   smaller | larger
    rc |= checkLogicalOp (a, c1, a | c1, c1, "|");
    a |= c1;
    rc |= checkLogicalOp (tmpa, c1, a, b1, "|=");
    a = tmpa;
    //   larger | smaller
    rc |= checkLogicalOp (c1, a, c1 | a, c1, "|");
    c1 |= a;
    rc |= checkLogicalOp (tmpc1, a, c1, tmpc1, "|=");
    c1 = tmpc1;
    //   | with integer
    RNumber tmp1 = b;
    tmp1 . setField (size2 - 32, size2 - 1, -1);
    rc |= checkLogicalOp (b, -1, b | (-1), tmp1, "|");
    b |= (-1);
    rc |= checkLogicalOp (tmpb, -1, b, tmp1, "|=");
    b = tmpb;

    // check ^ and ^= using (x ^ x), (x ^ zero), (x ^ ones), (zero ^ x), and (ones ^ x) with
    // different sizes of x, zero, and ones:
    //   ^ operands have same size
    rc |= checkLogicalOp (a, a, a ^ a, 0, "^");
    a ^= a;
    rc |= checkLogicalOp (tmpa, tmpa, a, 0, "^=");
    a = tmpa;
    rc |= checkLogicalOp (a, b0, a ^ b0, a, "^");
    a ^= b0;
    rc |= checkLogicalOp (tmpa, b0, a, tmpa, "^=");
    a = tmpa;
    rc |= checkLogicalOp (a, b1, a ^ b1, ~a, "^");
    a ^= b1;
    rc |= checkLogicalOp (tmpa, b1, a, ~tmpa, "^=");
    a = tmpa;
    //   smaller ^ larger
    rc |= checkLogicalOp (a, c0, a ^ c0, a, "^");
    a ^= c0;
    rc |= checkLogicalOp (tmpa, c0, a, tmpa, "^=");
    a = tmpa;
    RNumber aa( a, c1.size());
    rc |= checkLogicalOp (a, c1, a ^ c1, ~aa, "^");
    a ^= c1;
    rc |= checkLogicalOp (tmpa, c1, a, ~tmpa, "^=");
    a = tmpa;
    //   larger ^ smaller
    rc |= checkLogicalOp (c0, a, c0 ^ a, a, "^");
    c0 ^= a;
    rc |= checkLogicalOp (tmpc0, a, c0, a, "^=");
    c0 = tmpc0;
    RNumber tmp2 = c1;
    tmp2 . setField (size2 - size1, size2 - 1, ~a);
    rc |= checkLogicalOp (c1, a, c1 ^ a, tmp2, "^");
    c1 ^= a;
    rc |= checkLogicalOp (tmpc1, a, c1, tmp2, "^=");
    c1 = tmpc1;
    //   ^ with integer
    RNumber tmp3 = b;
    tmp3 . setField (size2 - 32, size2 - 1, -1);
    unsigned num3 = ~(b . getInt ());
    rc |= checkLogicalOp (b, num3, b ^ num3, tmp3, "^");
    b ^= num3;
    rc |= checkLogicalOp (tmpb, num3, b, tmp3, "^=");
    b = tmpb;
    rc |= checkLogicalOp (b, 0, b ^ 0, b, "^");
    b ^= 0;
    rc |= checkLogicalOp (tmpb, 0, b, tmpb, "^=");
    b = tmpb;
  }

  return rc;
}

int _argc;
char **_argv;
int _cur;

const char *curArg()
{
  return _argv[_cur];
}

const char *nextArg()
{
  ++_cur;
  if (_cur >= _argc) {
	 throw runtime_error(string("Error:  Expected an argument for option '")+_argv[_cur-1]+"'.");
  }
  return _argv[_cur];
}

int main (int argc, char **argv)
{
  const unsigned sizes[] = { 32, 64, 128, 0 };
  const unsigned n = 4;
  unsigned i;
  unsigned rc = 0;

  _cur = 1;
  _argc = argc;
  _argv = argv;

  string path = "/bin";
  string prog = "dc";
  string pgm;
  unsigned seed = 0;

  try {
	 for ( ; _cur < _argc; ++_cur) {
		if (!strcmp (curArg(), "-seed")) {
		  seed = atoi (nextArg());
		}
		else if (!strcmp (curArg(), "-n")) {
		  maxIter = atoi (nextArg());
		}
		else if (!strcmp (curArg(), "-dcpath")) {
		  path = nextArg();
		}
		else if (!strcmp (curArg(), "-dc")) {
		  pgm = nextArg();
		}
		else {
		  usage (argv[0]);
		}
	 }	
  }
  catch (runtime_error &err) {
	 cerr << err.what() << endl;
  }

  if (pgm.empty())
	 pgm = path + "/" + prog;

  seed = Random::init(seed);

  Calculator calc(pgm.c_str());

  // construct/resize/set/operator=
  printf ("Starting constructors...");
  fflush (stdout);
  rc |= checkConstructors ();
  printf (" finished.\n");

  // add
  printf ("Starting adds...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "+.", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "+", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "+", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "+.", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkMutator (sizes[i], "+=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntMutator (sizes[i], "+=", &calc);
  printf (" finished.\n");

  // subtract
  printf ("Starting subtracts...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "-", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "-", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkMutator (sizes[i], "-=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntMutator (sizes[i], "-=", &calc);
  printf (" finished.\n");

  // multiply
  printf ("Starting multiplies...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "*.", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "*", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "*", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "*.", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkMutator (sizes[i], "*=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntMutator (sizes[i], "*=", &calc);
  rc |= checkMultSpecialCases (&calc);
  printf (" finished.\n");

  // divide
  printf ("Starting divides...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "/", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "/", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkMutator (sizes[i], "/=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntMutator (sizes[i], "/=", &calc);
  rc |= checkDivideSpecialCases (&calc);
  printf (" finished.\n");

  // modulus 
  printf ("Starting mods...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkOperator (sizes[i], "%", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntOperator (sizes[i], "%", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkMutator (sizes[i], "%=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntMutator (sizes[i], "%=", &calc);
  printf (" finished.\n");

  // unsigned <
  printf ("Starting <...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], "<", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntComparator (sizes[i], "<", &calc);
  printf (" finished.\n");

  // unsigned <=
  printf ("Starting <=...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], "<=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntComparator (sizes[i], "<=", &calc);
  printf (" finished.\n");

  // unsigned >
  printf ("Starting >...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], ">", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntComparator (sizes[i], ">", &calc);
  printf (" finished.\n");

  // unsigned >=
  printf ("Starting >=...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], ">=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntComparator (sizes[i], ">=", &calc);
  printf (" finished.\n");

  // ==
  printf ("Starting ==...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], "==", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntComparator (sizes[i], "==", &calc);
  printf (" finished.\n");

  // !=
  printf ("Starting !=...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], "!=", &calc);
  for (i = 0; i < n; i++) 
    rc |= checkIntComparator (sizes[i], "!=", &calc);
  printf (" finished.\n");

  // compare
  printf ("Starting compare...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkComparator (sizes[i], "compare", &calc);
  printf (" finished.\n");

  // signedGT
  printf ("Starting signedGT...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkSignedComparator (sizes[i], "GT", &calc);
  printf (" finished.\n");

  // signedGE
  printf ("Starting signedGE...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkSignedComparator (sizes[i], "GE", &calc);
  printf (" finished.\n");

  // signedLT
  printf ("Starting signedLT...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkSignedComparator (sizes[i], "LT", &calc);
  printf (" finished.\n");

  // signedLE
  printf ("Starting signedLE...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkSignedComparator (sizes[i], "LE", &calc);
  printf (" finished.\n");

  // get bit
  // set bit
  printf ("Starting bit accessors...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkBitAccessors (sizes[i]);
  printf (" finished.\n");

  // get field
  // set field
  printf ("Starting field accessors...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkFieldAccessors (sizes[i]);
  printf (" finished.\n");

  // sign extend
  printf ("Starting sign extensions...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkSignExtends (sizes[i]);
  printf (" finished.\n");

  // invert
  // negate
  // not
  printf ("Starting inversions...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkInversions (sizes[i]);
  printf (" finished.\n");

  // left shift
  // right shift
  printf ("Starting shifts...");
  fflush (stdout);
  for (i = 0; i < n; i++) 
    rc |= checkShifts (sizes[i]);
  printf (" finished.\n");

  // setAll
  printf ("Starting setAlls...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkSetAlls (sizes[i]);
  printf (" finished.\n");

  // clearAll
  printf ("Starting clearAlls...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkClearAlls (sizes[i]);
  printf (" finished.\n");

  // getInt
  printf ("Starting getInts...");
  fflush (stdout);
  for (i = 0; i < n; i++)
    rc |= checkGetInts (sizes[i]);
  printf (" finished.\n");

  // and
  // or
  // xor
  printf ("Starting logicals...");
  fflush (stdout);
  rc |= checkLogicals ();
  printf (" finished.\n");

  if (rc)
    printf ("Errors were found.  Seed used was %d\n", seed);
  else
    printf ("All tests passed.\n");

  return rc;
}



Calculator::Calculator (const char *pgm)
{
  _pgm = pgm;

  if (pipe (_fd1) < 0 || pipe (_fd2) < 0) {
    printf ("Error creating pipe\n");
    exit (1);
  }
  
  pid_t pid;
  if ((pid = fork ()) < 0) {
    printf ("Fork error\n");
    exit (1);
  }
  else if (pid > 0) {    // parent
    close (_fd1[0]);
    close (_fd2[1]);
  }
  else {                 // child
    close (_fd1[1]);
    close (_fd2[0]);
    if (_fd1[0] != 0)
      dup2 (_fd1[0], 0);
    if (_fd2[1] != 2)
      dup2 (_fd2[1], 1);
    if (execl (pgm, _pgm, NULL) < 0) {
      printf ("Exec error\n");
      exit (1);
    }
  }

  init ();
}

Calculator::~Calculator ()
{
  terminate ();
}

static void uppercase (char *str)
{
  char *p = str;
  while (*p) {
    *p = toupper (*p);
    p++;
  }
}

// Verify arithmetic using the external calculator.  This is for all-RNumber tests.
// If ext is true, we allow for resizing.
unsigned Calculator::checkArith (const RNumber& a, const RNumber& b, 
                                 const RNumber& c, char *op, bool ext)
{
  char astr[256];
  char bstr[256];

  assert (a . size () <= 1024 && b . size () <= 1024);
  // dc requires uppercase hex; right now RNumbers print hex in lower case
  strcpy (astr, a . str () . c_str ());
  uppercase (astr);
  strcpy (bstr, b . str () . c_str ());
  uppercase (bstr);

  // Sanity checking if we're not allowing for resizing.
  if ( !ext && (op[0] != '%' && c.size() != max( a.size(), b.size() )) )
  {
    printf ("Result size error (1)  occurred in expression:  %s(%d) %s(%d) (%d) %s\n",
            astr, a.size(), bstr, b.size(), c.size(), op);
  }

  return arithCalc(astr,a.size(),bstr,b.size(),c,op,ext);
}

unsigned Calculator::checkArith (const RNumber& a, unsigned b, const RNumber& c, 
                                 char *op, bool ext)
{
  char astr[256];
  char bstr[256];
  
  strcpy (astr, a . str () . c_str ());

  uppercase (astr);
  sprintf (bstr, "%X", b);

  if ( !ext && (op[0] != '%' && c.size() != max( a.size(), (unsigned int) 32 ) ))
  {
    printf ("Result size error (2) occurred in expression:  %s(%d) %s(%d) (%d) %s\n",
            astr, a.size(), bstr, 32, c.size(), op);
    return 1;
  }

  return arithCalc(astr,a.size(),bstr,sizeof(unsigned)*8,c,op,ext);
}

// Performs the specified calculation and compares the result
// to c.
// astr:  Printed number ready to hand to calculator.
// asize: a's size in bits.
// bstr:  Printed number ready to hand to calculator.
// bsize: b's size in bits.
// c:     Expected result.
// op:    Operator to use in calculation.
unsigned Calculator::arithCalc (const char *astr,unsigned asize,
                                const char *bstr,unsigned bsize,
                                const RNumber &c,const char *op,
                                bool ext)
{
  unsigned rc = 0;

  char cmd[1024];
  char buf[1024];
  sprintf (cmd, "%s %s %c p c\n", astr, bstr, op[0]);
  int n = strlen (cmd);
  if (write (_fd1[1], cmd, strlen (cmd)) != n) {
    printf ("Write error\n");
    exit (1);
  }
  n = 0;
  buf[0] = '\0';
  do {
    int len = read (_fd2[0], buf + n, 1024);
    if (len < 0) {
      printf ("Read error\n");
      exit (1);
    }
    n += len;
  } while (n == 0 || buf[n-1] != '\n');
  buf[n] = '\0';

  RNumber res( 0, c.size(), (ext) ? RNumber::dynamic : RNumber::fixed );

  if (!ext) {
    // Fixed size case.
    if (buf[0] == '-') {
      res = RNumber( buf + 1, c.size(), RNumber::rhex );
      res.negate();
    }
    else
      res = RNumber( buf, c.size(), RNumber::rhex );
  } else {
    // Dynamically sized case.
    if (buf[0] == '-') {
      res = RNumber( buf + 1,RNumber::rhex, RNumber::dynamic );
      res.negate();
    }
    else
      res = RNumber( buf, RNumber::rhex, RNumber::dynamic );
  }

  if (res != c) {
    printf ("Error (3) occurred in expression:  %s(%d) %s(%d) %s\n", astr, asize, bstr, bsize, op);
    printf ("  RNumber res = %s, dc res = %s\n", c . str () . c_str (), res . str () . c_str ());
    rc = 1;
  }
  
  if (Verbose) {
    cout << "Calc Result: " << res << endl;
  }

  return rc;
}

unsigned Calculator::checkComparator (const RNumber& a, const RNumber& b, int res, char *op)
{
  char astr[256];
  char bstr[256];
  unsigned rc = 0;

  strcpy (astr, a . str () . c_str ());
  uppercase (astr);
  strcpy (bstr, b . str () . c_str ());
  uppercase (bstr);

  char cmd[1024];
  char buf[1024];
  sprintf (cmd, "%s %s - p c\n", astr, bstr);
  int n = strlen (cmd);
  if (write (_fd1[1], cmd, strlen (cmd)) != n) {
    printf ("Write error\n");
    exit (1);
  }
  n = 0;
  buf[0] = '\0';
  do {
    int len = read (_fd2[0], buf + n, 1024);
    if (len < 0) {
      printf ("Read error\n");
      exit (1);
    }
    n += len;
  } while (n == 0 || buf[n-1] != '\n');
  buf[n] = '\0';

  if (strcmp (op, "<") == 0 ) {
    if (res)
      rc = (buf[0] == '-');
    else
      rc = (buf[0] != '-' || strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, "<=") == 0) {
    if (res)
      rc = (buf[0] == '-' || strcmp (buf, "0\n") == 0);
    else
      rc = (buf[0] != '-' && strcmp (buf, "0\n") != 0);
  }
  else if (strcmp (op, ">") == 0) {
    if (res)
      rc = (buf[0] != '-');
    else
      rc = (buf[0] == '-' || strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, ">=") == 0) {
    if (res)
      rc = (buf[0] != '-');
    else
      rc = (buf[0] == '-' || strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, "==") == 0) {
    if (res)
      rc = (strcmp (buf, "0\n") == 0);
    else
      rc = (strcmp (buf, "0\n") != 0);
  }
  else if (strcmp (op, "!=") == 0) {
    if (res)
      rc = (strcmp (buf, "0\n") != 0);
    else
      rc = (strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, "compare") == 0) {
    if (res < 0)
      rc = (buf[0] == '-');
    else if (res == 0)
      rc = (strcmp (buf, "0\n") == 0);
    else
      rc = (buf[0] != '-' && strcmp (buf, "0\n") != 0);
  }
  else
    assert (0);

  if (! rc) {
    printf ("Error (4) occurred in expression:  %s(%d) %s(%d) %s\n", astr, a . size (), bstr, b . size (), op);
    printf ("  RNumber res = %d, subtract output = %s", res, buf);
    rc = 1;
  }
  else
    rc = 0;

  return rc;
}

unsigned Calculator::checkComparator (const RNumber& a, unsigned b, int res, char *op)
{
  char astr[256];
  char bstr[256];
  unsigned rc = 0;

  strcpy (astr, a . str () . c_str ());
  uppercase (astr);
  sprintf (bstr, "%X", b);

  char cmd[1024];
  char buf[1024];
  sprintf (cmd, "%s %s - p c\n", astr, bstr);
  int n = strlen (cmd);
  if (write (_fd1[1], cmd, strlen (cmd)) != n) {
    printf ("Write error\n");
    exit (1);
  }
  n = 0;
  buf[0] = '\0';
  do {
    int len = read (_fd2[0], buf + n, 1024);
    if (len < 0) {
      printf ("Read error\n");
      exit (1);
    }
    n += len;
  } while (n == 0 || buf[n-1] != '\n');
  buf[n] = '\0';

  if (strcmp (op, "<") == 0 ) {
    if (res)
      rc = (buf[0] == '-');
    else
      rc = (buf[0] != '-' || strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, "<=") == 0) {
    if (res)
      rc = (buf[0] == '-' || strcmp (buf, "0\n") == 0);
    else
      rc = (buf[0] != '-' && strcmp (buf, "0\n") != 0);
  }
  else if (strcmp (op, ">") == 0) {
    if (res)
      rc = (buf[0] != '-');
    else
      rc = (buf[0] == '-' || strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, ">=") == 0) {
    if (res)
      rc = (buf[0] != '-');
    else
      rc = (buf[0] == '-' || strcmp (buf, "0\n") == 0);
  }
  else if (strcmp (op, "==") == 0) {
    if (res)
      rc = (strcmp (buf, "0\n") == 0);
    else
      rc = (strcmp (buf, "0\n") != 0);
  }
  else if (strcmp (op, "!=") == 0) {
    if (res)
      rc = (strcmp (buf, "0\n") != 0);
    else
      rc = (strcmp (buf, "0\n") == 0);
  }
  else
    assert (0);

  if (! rc) {
    printf ("Error (5) occurred in expression:  %s(%d) %s %s\n", astr, a . size (), bstr, op);
    printf ("  RNumber res = %d, subtract output = %s", res, buf);
    rc = 1;
  }
  else
    rc = 0;

  return rc;
}

void Calculator::init ()
{
  char *str = "16 o 16 i\n";
  int n = strlen (str);
  if (write (_fd1[1], str, strlen (str)) != n) {
    printf ("Write error in init\n");
    exit (1);
  }
}

void Calculator::terminate ()
{
  char *str = "q\n";
  int n = strlen (str);
  if (write (_fd1[1], str, strlen (str)) != n) {
    printf ("Write error in init\n");
    exit (1);
  }
}
