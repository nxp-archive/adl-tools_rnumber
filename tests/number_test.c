
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "C-RNumber.h"
#include "C-Random.h"
#include "c-io.h"

unsigned maxIter = 100;

const int Verbose = 0;

typedef struct Calculator 
{
  char *_pgm;
  int _fd1[2];
  int _fd2[2];
} Calculator;

struct Calculator * calculator_create (const char *pgm);
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
unsigned calculator_private_arith_calc ( struct Calculator * calc,const char *astr,unsigned asize, 
					 const char *bstr,unsigned bsize, const struct RNumber * c,
					 const char *op, int bool_ext);

static void usage (char *pgm)
{
  printf ("Usage:  %s [-seed n] [-n] [-dcpath <path to dc] [-dc <dc program>]\n", pgm);
  exit (1);
}

static unsigned checkOperator (unsigned size, char *op, struct Calculator *calc)
{
  unsigned i;
  unsigned rc = 0;

  printf("%s:%d %s()\n", __FILE__, __LINE__, __FUNCTION__);
  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    unsigned size2 = (size == 0) ? random_get_from_range_unsigned(1, 100) : size;
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size(0, size2);
    struct RNumber * c = rnumber_create_from_unsigned_of_size_variable_sizing(0, 1);
    int ext = 0;    

    //printf("%s:%d\n", __FILE__, __LINE__);
    a = random_get_rnumber(size1);
    //printf("%s:%d\n", __FILE__, __LINE__);
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
      b = random_get_integer ();
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
    case '+': rnumber_plus_assign_from_unsigned(a, b); break;
    case '-': rnumber_minus_assign_from_unsigned(a, b); break;
    case '*': rnumber_multiply_assign_from_unsigned(a, b); break;
    case '/': rnumber_divide_assign_from_unsigned(a, b); break;
    case '%': rnumber_mod_assign_from_unsigned(a, b); break;
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
    rnumber_multiply_assign(tmp, y);
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
    struct RNumber * y = random_get_rnumber(random_get_from_range_unsigned (1, 100));
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_multiply_rn(x, y), "*", 0);
    rnumber_multiply_assign(tmp, y);
    rc |= calculator_check_arith(calc, x, y, tmp, "*=",0);
  }

  // second op is 1
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber(random_get_from_range_unsigned (1, 100));
    struct RNumber * y = rnumber_create_from_unsigned_of_size(1, random_get_from_range_unsigned (33, 100));
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
    unsigned size2 = random_get_from_range_unsigned (1, 100);
    struct RNumber * y = rnumber_create_from_unsigned_of_size (0, size2);
    struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
    do {
      y = random_get_rnumber (size2);
    } while (rnumber_rn_equal_ui(y, 0));
    rc |= calculator_check_arith(calc,x, y, rnumber_rn_divide_rn(x, y), "/",0);
    rnumber_divide_assign(tmp, y);
    rc |= calculator_check_arith(calc, x, y, tmp, "/=",0);
  }

  // second op is 1
  for (i = 0; i < maxIter; i++) {
    struct RNumber * x = random_get_rnumber(random_get_from_range_unsigned(1, 100));
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
    unsigned size2 = random_get_from_range_unsigned (33, 100);
    unsigned s, n;
    struct RNumber * y = rnumber_create_from_unsigned_of_size(0, size2);
    do {
      y = random_get_rnumber (size2);
      s = rnumber_size(y);
      n = random_get_from_range_unsigned(s - 32, s - 1);
      rnumber_rightshift_assign(y, rnumber_create_from_unsigned(n));
    } while ( rnumber_rn_equal_ui(y, 0));
    s = rnumber_size(x);
    n = random_get_from_range_unsigned (s - 32, s - 1);
    rnumber_rn_rightshift_ui(x, n);
    rc |= calculator_check_arith(calc, x, y, rnumber_rn_divide_rn(x, y), "/",0);
    {
      struct RNumber * tmp = rnumber_copy_to_size_variable_sizing(x, rnumber_size(x));
      rnumber_divide_assign(tmp, y);
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
      rnumber_rightshift_assign(y, rnumber_create_from_unsigned(n));
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
      rnumber_assign(a, rnumber_create_from_unsigned(c));
    }

    if (strcmp (op, ">") == 0) {
      res1 = rnumber_rn_greaterthan_ui(a, b);
      res2 = rnumber_rn_greaterthan_ui(a, c);
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
    unsigned b = random_get_integer ();
    int res;
    if (size1 < 32) {
      rnumber_assign_from_uint(a, b);
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
    unsigned size2 = (size == 0) ? random_get_from_range_unsigned (1, 100) : size;
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
    rnumber_leftshift_assign(b, rnumber_create_from_unsigned(shift));
    rnumber_leftshift_assign(c, rnumber_create_from_unsigned(n));

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
      printf ("Error occurred in setting bit %d of 0 to produce %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }
    if (rnumber_getbit_lsb(a, n) != 1) {
      printf ("Error occurred in getting bit %d of %s(%d)\n", n, rnumber_cstr(a), size1);
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
    rnumber_leftshift_assign(b, rnumber_create_from_unsigned(shift));

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
    if (rnumber_get_uint_field(a, n1, n2) != 0) {
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
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    unsigned n = random_get_integer(size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size (0, size1);
    unsigned shift = size1 - n - 1;
    rnumber_set_all(b);
    rnumber_leftshift_assign(b, rnumber_create_from_unsigned(shift));

    rnumber_setbit(a,n, 1);
    rnumber_sign_extend(a,n);
    if (rnumber_rn_notequal_rn(a, b)) {
      printf ("Error occurred in extending bit %d; produced %s(%d)\n", n, rnumber_cstr(a), size1);
      rc = 1;
    }

    rnumber_set_all(a);
    rnumber_setbit(a,n, 0);
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
  /*  printf("%s:%d rnumber_cstr_radix(numa, %d) %s\n", __FILE__, __LINE__, radix, rnumber_cstr_radix(numa,radix,0)); */

  {
    char *str1;
    str1 = ss_str(ss1);
    {
      struct RNumber * num1 = rnumber_create_from_string(str1);
      
      if (rnumber_rn_notequal_rn(numa, num1)) {
	printf ("Error in reading/writing of %s(%d) with implied radix %d. num1 is %s\n", 
		rnumber_cstr_radix(numa,radix,1), size1, radix, rnumber_cstr_radix(num1,radix,1));
	rc = 1;
	exit(1);
      }
      if (size1 > 1) {
	// construct a smaller number with the string
	unsigned size2 = random_get_from_range_unsigned(1, size1 - 1);
	struct RNumber * numb = rnumber_create_from_rnumber(numa);
	rnumber_assign (numb, rnumber_rn_rightshift_ui( rnumber_rn_leftshift_ui(numb, (size1 - size2)), (size1 - size2)));
 
	{
	  struct RNumber * nums1 = rnumber_create_from_string_of_size(str1, size2);
	  if ( rnumber_rn_notequal_rn(nums1, numb) || rnumber_size(nums1) != size2) {
	    printf ("Error in reading/writing of %s(%d) to %d with implied radix %d\n", 
		    rnumber_cstr(numa), size1, size2, radix);
	    rc = 1;
	  }

	  {
	    // construct a larger number with the string
	    unsigned size3 = random_get_from_range_unsigned(size1 + 1, 100);
	    struct RNumber * nums2 = rnumber_create_from_string_of_size(str1, size3);
	    if ( rnumber_rn_notequal_rn(nums2, numa) || rnumber_size(nums2) != size3) {
	      printf ("Error in reading/writing of %s(%d) to %d with implied radix %d\n", 
		      rnumber_cstr(numa), size1, size3, radix);
	      rc = 1;
	    }
	  }
	}
      }
    }
  }
  {
    void * ss3 = ss_create();
    rnumber_print_with_radix(numa, ss3, radix,0);
    {
      char * str3 = ss_str(ss3);
      /* printf("%s:%d str3 %s\n", __FILE__, __LINE__, str3); */
      ss_ends(ss3);
      {
	struct RNumber * num3 = rnumber_create_from_string_of_radix (str3, radix);
	if (rnumber_rn_notequal_rn(numa, num3)) {
	  printf ("%s:%d Error in hex reading/writing of %s(%d) with explicit radix %d\n", 
		  __FILE__, __LINE__, rnumber_cstr(numa), rnumber_size(numa), radix);
	  rc = 1;
	  exit (1);
	}
      }
      if (size1 > 1) {
	// construct a smaller number with the string
	unsigned size2 = random_get_from_range_unsigned(1, size1 - 1);
	struct RNumber * numb = rnumber_create_from_rnumber(numa);
	rnumber_assign(numb, rnumber_rn_rightshift_ui(rnumber_rn_leftshift_ui(numb, (size1 - size2)), (size1 - size2)));
 
	{
	  struct RNumber * nums1 = rnumber_create_from_string_of_size_of_radix(str3, size2, radix);
	  if ( rnumber_rn_notequal_rn(nums1, numb) || 
	       rnumber_size(nums1) != size2) {
	    printf ("Error in reading/writing of %s(%d) to %d with explicit radix %d\n", rnumber_cstr(numa), size1, size2, radix);
	    rc = 1;
	  }
	}
	{
	  // construct a larger number with the string
	  unsigned size3 = random_get_from_range_unsigned(size1 + 1, 100);
	  struct RNumber * nums2 = rnumber_create_from_string_of_size_of_radix(str3, size3, radix);
	  if (rnumber_rn_notequal_rn(nums2, numa) || rnumber_size(nums2) != size3) {
	    printf ("Error in reading/writing of %s(%d) to %d with explicit radix %d\n", rnumber_cstr(numa), size1, size3, radix);
	    rc = 1;
	  }
	}
      }
    }
  }
  return rc;
}

static unsigned checkConstructors ()
{
  unsigned i;
  unsigned rc = 0;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = random_get_from_range_unsigned(1, 90);
    unsigned size2 = random_get_from_range_unsigned(91, 100);
    struct RNumber * x0 = random_get_rnumber(size1);
    struct RNumber * y0 = random_get_rnumber(size2);
    struct RNumber * tmp = rnumber_create_from_unsigned_of_size (0, size2);

    {
      // basic copy constructor
      struct RNumber * z1 = rnumber_create_from_rnumber(x0);
      if (rnumber_rn_notequal_rn(z1, x0) || rnumber_size(z1) != size1) {
	printf ("Error occurred in basic copy constructor of %s(%d)\n", rnumber_cstr(x0), size1);
	rc = 1;
      }
    }
    {
      // construct larger number
      struct RNumber * z2 = rnumber_copy_to_size (x0, size2);
      if (rnumber_rn_notequal_rn(z2, x0) || rnumber_size(z2) != size2) {
	printf ("Error occurred in sized copy constructor of %s(%d) to %d\n", rnumber_cstr(x0), size1, size2);
	rc = 1;
      }
    }
    {
      // construct smaller number
      struct RNumber * z3 = rnumber_copy_to_size(y0, size1);
      rnumber_assign(tmp, y0);
      rnumber_leftshift_assign(tmp,rnumber_create_from_unsigned(size2 - size1));
      rnumber_rightshift_assign(tmp, rnumber_create_from_unsigned(size2 - size1));
      if (rnumber_rn_notequal_rn(z3, tmp) || rnumber_size(z3) != size1) {
	printf ("Error occurred in sized copy constructor of %s(%d) to %d\n", rnumber_cstr(y0), size2, size1);
	rc = 1;
      }
    }
    {
      // construct from integer
      unsigned num = random_get_integer ();
      {
	struct RNumber * z31 = rnumber_create_from_unsigned(num);
	if (rnumber_rn_notequal_ui(z31, num) || rnumber_size(z31) != 32) {
	  printf ("Error occurred in constructing from integer %x\n", num);
	  rc = 1;
	}
      }
      {
	// construct to larger from integer
	struct RNumber * z32 = rnumber_create_from_unsigned_of_size (num, size2);
	if (rnumber_rn_notequal_ui(z32, num) || rnumber_size(z32) != size2) {
	  printf ("Error occurred in constructing larger number (%d) from integer %x\n", size2, num);
	  rc = 1;
	}
      }
      {
	// construct to smaller from integer
	unsigned size3 = random_get_from_range_unsigned (1, 31);
	struct RNumber * z33 = rnumber_create_from_unsigned_of_size(num, size3);
	unsigned diff = 32 - size3;
	unsigned num2 = (num << diff) >> diff;
	if (rnumber_rn_notequal_ui(z33, num2) || rnumber_size(z33) != size3) {
	  printf ("Error occurred in constructing smaller number (%d) from integer %x\n", size3, num);
	  rc = 1;
	}
      }
    }
#if 0
      // depricated
	// basic set, 
	struct RNumber * z4 = random_get_rnumber(size1);
	rnumber_set(z4,x0);
	if (rnumber_rn_ z4 != x0 || z4 . size () != x0 . size ()) {
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
#endif
    {
      // basic operator=
      struct RNumber * z7 = random_get_rnumber (size1);
      rnumber_assign(z7, x0);
      if (rnumber_rn_notequal_rn(z7, x0) || rnumber_size(z7) != size1) {
	printf ("Error occurred in basic operator= of %s(%d)\n", rnumber_cstr(x0), size1);
	rc = 1;
      }
    }
    {
      // operator= from smaller
      struct RNumber * z8 = random_get_rnumber (size2);
      rnumber_assign(z8, x0);
      if (rnumber_rn_notequal_rn(z8, x0) || rnumber_size(z8) != size2) {
	printf ("Error occurred in sized operator= of %s(%d) to %d\n", rnumber_cstr(x0), size1, size2);
	rc = 1;
      }
    }
    {
      // operator= from larger
      struct RNumber * z9 = random_get_rnumber (size1);
      rnumber_assign(z9, y0);
      if ((rnumber_sizing(z9) == rnumber_dynamic() && ( rnumber_rn_notequal_rn(z9, y0) || (rnumber_size(z9) != rnumber_size(y0)))) ||
	  (rnumber_sizing(z9) == rnumber_fixed() && rnumber_size(z9) != size1)) {
	printf ("Error occurred in sized operator= of %s(%d) to %d\n", rnumber_cstr(y0), size2, size1);
	rc = 1;
      }
    }
    {
      // operator= from integer
      struct RNumber * z91 = rnumber_create_from_unsigned_of_size(0, 32);
      unsigned num91 = random_get_integer ();
      rnumber_assign_from_uint(z91, num91);
      if (rnumber_rn_notequal_ui(z91, num91) || rnumber_size(z91) != 32) {
	printf ("Error occurred in operator= of %x\n", num91);
	rc = 1;
      }
    }
    {
      // operator= to larger from integer
      struct RNumber * z92 = random_get_rnumber (size2);
      unsigned num92 = random_get_integer ();
      rnumber_assign_from_uint(z92, num92);
      if (rnumber_rn_notequal_ui(z92, num92) || rnumber_size(z92) != size2) {
	printf ("Error occurred in operator= of %x to size %d\n", num92, size2);
	rc = 1;
      }
    }
    {
      // operator= to smaller from integer
      unsigned size93 = random_get_from_range_unsigned (1, 31);
      struct RNumber * z93 = random_get_rnumber (size93);
      rnumber_set_dynamic(z93);
      {
	unsigned num93 = random_get_integer ();
	rnumber_assign_from_uint(z93, num93);
	{
	  unsigned mask = 0x1;
	  unsigned count = 0;
	  while (mask <= num93 && mask != 0) {
	    mask <<= 1;
	    count++;
	  }
	  if (rnumber_rn_notequal_ui(z93, num93) || rnumber_size(z93) < count) {
	    printf ("Error occurred in operator= of %x to size %d\n", num93, size93);
	    rc = 1;
	  }
	}
      }
    }
    {
      // resize to larger
      struct RNumber * z10 = random_get_rnumber (size1);
      struct RNumber * largerValue = rnumber_copy_to_size( z10, size2 );

      rnumber_resize(z10, size2);

      if (rnumber_rn_notequal_rn(z10, largerValue) || rnumber_size(z10) != size2) {
	printf ("Error occurred in resize from %d to %d\n", size1, size2);
	rc = 1;
      }
    }
    {
      // resize to smaller
      struct RNumber * z11 = random_get_rnumber (size2);
      struct RNumber * smallerValue = rnumber_copy_to_size( z11, size1 );

      rnumber_resize(z11,size1);

      if (rnumber_rn_notequal_rn(z11, smallerValue) || rnumber_size(z11) != size1) {
	printf ("Error occurred in resize from %d to %d\n", size2, size1);
	rc = 1;
      }
    }
    {
      // test various string constructors
      struct RNumber * num1a = random_get_rnumber(size1);
      rc |= checkReadWrite (num1a, rnumber_rhex());
      rc |= checkReadWrite (num1a, rnumber_rbin());
      rc |= checkReadWrite (num1a, rnumber_rdec());
    }
  }

  return rc;
}

static unsigned checkInversions (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = random_get_rnumber (size1);
    struct RNumber * tmp = rnumber_create_from_rnumber(a);
    struct RNumber * ones = rnumber_create_from_unsigned_of_size (0, size1);
    rnumber_set_all(ones);

    rnumber_negate(a);
    if (rnumber_rn_notequal_ui(rnumber_rn_plus_rn(a, tmp), 0)) {
      printf ("Error occurred in negating %s; produced %s(%d)\n", rnumber_cstr(tmp), rnumber_cstr(a), size1);
      rc = 1;
    }
    rnumber_assign(a, rnumber_unary_minus(tmp));
    if (rnumber_rn_notequal_ui(rnumber_rn_plus_rn(a, tmp), 0)) {
      printf ("Error occurred in negating %s; produced %s(%d)\n", rnumber_cstr(tmp), rnumber_cstr(a), size1);
      rc = 1;
    }

    rnumber_assign(a, tmp);
    rnumber_invert(a);
    if (rnumber_rn_notequal_rn(rnumber_rn_bitor_rn(a, tmp), ones)) {
      printf ("Error occurred in inverting %s; produced %s(%d)\n", rnumber_cstr(tmp), rnumber_cstr(a), size1);
      rc = 1;
    }

    rnumber_assign(a, rnumber_unary_tilde(tmp));
    if ( rnumber_rn_notequal_rn(rnumber_rn_bitor_rn(a, tmp), ones)) {
      printf ("Error occurred in inverting %s; produced %s(%d)\n", rnumber_cstr(tmp), rnumber_cstr(a), size1);
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
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned(1, 100);
    unsigned n = random_get_integer (size1);
    struct RNumber * rn = rnumber_create_from_unsigned(n);
    struct RNumber * a = rnumber_create_from_unsigned_of_size (0, size1);
    struct RNumber * b = rnumber_create_from_unsigned_of_size (0, size1 - n);
    rnumber_set_all(b);

    // This group of shifts should not be destructive, since we're allowing
    // the result to grow.
    {
      struct RNumber * tmpe = rnumber_rn_rightshift_ui(rnumber_rn_leftshift_ext_ui(a,n), n);
      if (rnumber_rn_notequal_rn(tmpe, a)) {
	printf ("Error occurred in extendable shifting %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, n, rnumber_cstr(tmpe));
	printf ("  Expected %s\n", rnumber_cstr(a));
	rc = 1;
      }

      // This group of shifts should not be destructive, since we're allowing
      // the result to grow.
      rnumber_assign(tmpe, rnumber_rn_rightshift_rn(rnumber_rn_leftshift_ext_rn(a,rn),rn));
      if (rnumber_rn_notequal_rn(tmpe, a)) {
	printf ("Error occurred in extendable shifting %s(%d) by %s; produced %s\n", 
		rnumber_cstr(a), size1, rnumber_cstr(rn), rnumber_cstr(tmpe));
	printf ("  Expected %s\n", rnumber_cstr(a));
	rc = 1;
      }
    }
    // The rest of these shifts will be destructive, since the size of
    // the value may not grow.
    {
      struct RNumber * tmp = rnumber_rn_rightshift_ui(rnumber_rn_leftshift_ui(a, n), n);
      if (rnumber_rn_notequal_rn(tmp, b)) {
	printf ("Error occurred in shifting %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, n, rnumber_cstr(tmp));
	rc = 1;
      }

      // The rest of these shifts will be destructive, since the size of
      // the value may not grow.
      rnumber_assign(tmp, rnumber_rn_rightshift_rn (rnumber_rn_leftshift_rn(a, rn), rn));
      if (rnumber_rn_notequal_rn(tmp, b)) {
	printf ("Error occurred in shifting %s(%d) by %s; produced %s\n", 
		rnumber_cstr(a), size1, rnumber_cstr(rn), rnumber_cstr(tmp));
	rc = 1;
      }

      rnumber_assign(tmp, a);
      rnumber_leftshift_assign(tmp, rnumber_create_from_unsigned(n));
      rnumber_rightshift_assign(tmp, rnumber_create_from_unsigned(n));
      if (rnumber_rn_notequal_rn(tmp, b)) {
	printf ("Error occurred in shift/equaling %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, n, rnumber_cstr(tmp));
	rc = 1;
      }

      rnumber_assign(tmp, rnumber_rn_leftshift_ui(a, size1));
      if (rnumber_rn_notequal_ui(tmp, 0)) {
	printf ("Error occurred in shifting %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, size1, rnumber_cstr(tmp));
	rc = 1;
      }
      rnumber_assign(tmp, rnumber_rn_rightshift_ui(a, size1));
      if (rnumber_rn_notequal_ui(tmp, 0)) {
	printf ("Error occurred in right shifting %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, size1, rnumber_cstr(tmp));
	rc = 1;
      }

      rnumber_assign(tmp, a);
      rnumber_leftshift_assign(tmp, rnumber_create_from_unsigned(size1));
      if (rnumber_rn_notequal_ui(tmp, 0)) {
	printf ("Error occurred in left shift/equaling %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, size1, rnumber_cstr(tmp));
	rc = 1;
      }
      rnumber_assign(tmp, a);
      rnumber_rightshift_assign(tmp, rnumber_create_from_unsigned(size1));
      if (rnumber_rn_notequal_ui(tmp, 0)) {
	printf ("Error occurred in right shift/equaling %s(%d) by %d; produced %s\n", 
		rnumber_cstr(a), size1, size1, rnumber_cstr(tmp));
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
	{
	  struct RNumber * c = rnumber_create_from_unsigned_of_size(0, size1 - n);
	  rnumber_set_all(c);
	  rnumber_assign(tmp, rnumber_rn_rightshift_ui( rnumber_rn_leftshift_ui(a, n), n));
	  if (rnumber_rn_notequal_rn(tmp, c)) {
	    printf ("Error occurred in shifting %s(%d) by %d; produced %s\n", 
		    rnumber_cstr(a), size1, n, rnumber_cstr(tmp));
	    rc = 1;
	  }

	  rnumber_assign(tmp, a);
	  rnumber_leftshift_assign(tmp, rnumber_create_from_unsigned(n));
	  rnumber_rightshift_assign(tmp, rnumber_create_from_unsigned(n));
	  if (tmp != c) {
	    printf ("Error occurred in shift/equaling %s(%d) by %d; produced %s\n", 
		    rnumber_cstr(a), size1, n, rnumber_cstr(tmp));
	    rc = 1;
	  }
	}
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
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    rnumber_set_all(a);
    {    struct RNumber * b = rnumber_create_from_unsigned_of_size(0, size1);
    rnumber_minus_assign(b, rnumber_create_from_unsigned(1));

    if (rnumber_rn_notequal_rn(a, b) ) {
      printf ("Error occurred in setAll(%d); produced %s\n", size1, rnumber_cstr(a));
      rc = 1;
    }
    }
  }
  return rc;
}

static unsigned checkClearAlls (unsigned size)
{
  unsigned rc = 0;
  unsigned i;

  for (i = 0; i < maxIter; i++) {
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = rnumber_create_from_unsigned_of_size(0, size1);
    rnumber_set_all(a);
    rnumber_clear_all(a);

    if (rnumber_rn_notequal_ui(a, 0)) {
      printf ("Error occurred in clearAll(%d); produced %s\n", size1, rnumber_cstr(a));
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
    unsigned size1 = (size > 0) ? size : random_get_from_range_unsigned (1, 100);
    struct RNumber * a = random_get_rnumber (size1);
    unsigned ai = rnumber_get_uint(a);
    unsigned shift = (size1 > 32) ? size1 - 32 : 0;
    struct RNumber * b = rnumber_rn_rightshift_ui( rnumber_rn_leftshift_ui(a, shift), shift);

    if ( rnumber_rn_notequal_ui(b, ai)) {
      printf ("Error occurred in getInt on %s(%d); produced %x\n", rnumber_cstr(a), size1, ai);
      rc = 1;
    }
  }

  return rc;
}

static unsigned check_logical_op_rn_rn (const struct RNumber * a, const struct RNumber * b, 
				const struct  RNumber * res1, const struct RNumber * res2, 
				char *op)
{
  unsigned rc = (res1 != res2);
  if (rc) {
    printf ("Error (1) occurred in expression:  %s(%d) %s(%d) %s\n", rnumber_cstr(a), rnumber_size(a),
            rnumber_cstr(b), rnumber_size(b), op);
    printf ("  RNumber res = %s, expected res = %s\n", rnumber_cstr(res1), rnumber_cstr(res2));
  }
  return rc;
}

static unsigned check_logical_op_rn_ui (const struct RNumber * a, unsigned b, const struct RNumber * res1, 
				const struct RNumber * res2, char *op)
{
  unsigned rc = (rnumber_rn_notequal_rn(res1, res2));
  if (rc) {
    printf ("Error (2) occurred in expression:  %s(%d) %x %s\n", rnumber_cstr(a), rnumber_size(a), b, op);
    printf ("  RNumber res = %s, expected res = %s\n", rnumber_cstr(res1), rnumber_cstr(res2));
  }
  return rc;
}

static unsigned checkLogicals ()
{
  unsigned rc = 0;
  unsigned i;

  // and
  for (i = 0; i < maxIter; i++) {
    unsigned size1 = random_get_from_range_unsigned (1, 90);
    unsigned size2 = random_get_from_range_unsigned (91, 100);
    struct RNumber * a = random_get_rnumber (size1);
    struct RNumber * b = random_get_rnumber (size2);
    struct RNumber * b0 = rnumber_create_from_unsigned_of_size(0, size1);
    struct RNumber * b1 = rnumber_create_from_unsigned_of_size(0, size1);
    rnumber_set_all(b1);
    {
      struct RNumber * c0 = rnumber_create_from_unsigned_of_size (0, size2);
      struct RNumber * c1 = rnumber_create_from_unsigned_of_size (0, size2);
      rnumber_set_all(c1);
      {
	struct RNumber * tmpa = rnumber_create_from_rnumber(a);
	struct RNumber * tmpb = rnumber_create_from_rnumber(b);
	struct RNumber * tmpc0 = rnumber_create_from_rnumber(c0);
	struct RNumber * tmpc1 = rnumber_create_from_rnumber(c1);

	// check & and &= using (x & zero), (x & ones), (zero & x), and (ones & x) with
	// different sizes of x, zero, and ones:
	//   & operands have same size
	rc |= check_logical_op_rn_rn (a, b0, rnumber_rn_bitand_rn(a, b0), 0, "&");
	rnumber_bitand_assign(a,b0);
	rc |= check_logical_op_rn_rn (tmpa, b0, a, 0, "&=");
	rnumber_assign(a, tmpa);
	rc |= check_logical_op_rn_rn (a, b1, rnumber_rn_bitand_rn(a, b1), a, "&");
	rnumber_bitand_assign(a, b1);
	rc |= check_logical_op_rn_rn (tmpa, b1, a, tmpa, "&=");
	//   smaller & larger
	rc |= check_logical_op_rn_rn (a, c0, rnumber_rn_bitand_rn(a, c0), 0, "&");
	rnumber_bitand_assign(a, c0);
	rc |= check_logical_op_rn_rn (tmpa, c0, a, 0, "&=");
	rnumber_assign(a, tmpa);
	rc |= check_logical_op_rn_rn (a, c1, rnumber_rn_bitand_rn(a, c1), a, "&");
	rnumber_bitand_assign(a, c1);
	rc |= check_logical_op_rn_rn (tmpa, c1, a, tmpa, "&=");
	rnumber_assign(a, tmpa);
	//   larger & smaller
	rc |= check_logical_op_rn_rn (c0, a, rnumber_rn_bitand_rn(c0, a), 0, "&");
	rnumber_bitand_assign(c0, a);
	rc |= check_logical_op_rn_rn (tmpc0, a, c0, 0, "&=");
	rnumber_assign(c0, tmpc0);
	rc |= check_logical_op_rn_rn (c1, a, rnumber_rn_bitand_rn(c1, a), a, "&");
	rnumber_bitand_assign(c1, a);
	rc |= check_logical_op_rn_rn (tmpc1, a, c1, a, "&=");
	rnumber_assign(c1, tmpc1);
	//   & with integer
	rc |= check_logical_op_rn_rn (b, 0, rnumber_rn_bitand_ui(b, 0), 0, "&");
	rnumber_bitand_assign(b, rnumber_create_from_unsigned(0));
	rc |= check_logical_op_rn_rn (tmpb, 0, b, 0, "&=");
	rnumber_assign(b, tmpb);
	rc |= check_logical_op_rn_ui (b, (-1), rnumber_rn_bitand_ui(b, (-1)), b, "&");
	rnumber_bitand_assign(b, rnumber_create_from_unsigned(-1));
	rc |= check_logical_op_rn_ui (tmpb, (-1), b, tmpb, "&=");
	rnumber_assign(b, tmpb);

	// check | and |= using (x | ones) and (ones | x) with
	// different sizes of x and ones:
	//   | operands have same size
	rc |= check_logical_op_rn_rn (a, b1, rnumber_rn_bitor_rn(a, b1), b1, "|");
	rnumber_bitor_assign(a, b1);
	rc |= check_logical_op_rn_rn (tmpa, b1, a, b1, "|=");
	rnumber_assign(a, tmpa);
	//   smaller | larger
	rc |= check_logical_op_rn_rn (a, c1, rnumber_rn_bitor_rn(a, c1), c1, "|");
	rnumber_bitor_assign(a, c1);
	rc |= check_logical_op_rn_rn (tmpa, c1, a, b1, "|=");
	rnumber_assign(a, tmpa);
	//   larger | smaller
	rc |= check_logical_op_rn_rn (c1, a, rnumber_rn_bitor_rn(c1, a), c1, "|");
	rnumber_bitor_assign(c1, a);
	rc |= check_logical_op_rn_rn (tmpc1, a, c1, tmpc1, "|=");
	rnumber_assign(c1, tmpc1);
	//   | with integer
	{
	  struct RNumber * tmp1 = rnumber_create_from_rnumber(b);
	  rnumber_set_field(tmp1, size2 - 32, size2 - 1, rnumber_create_from_unsigned(-1));
	  rc |= check_logical_op_rn_ui (b, -1, rnumber_rn_bitor_ui(b,-1), tmp1, "|");
	  rnumber_bitor_assign(b,rnumber_create_from_unsigned(-1));
	  rc |= check_logical_op_rn_ui (tmpb, -1, b, tmp1, "|=");
	  rnumber_assign(b, tmpb);
	}
	// check ^ and ^= using (x ^ x), (x ^ zero), (x ^ ones), (zero ^ x), and (ones ^ x) with
	// different sizes of x, zero, and ones:
	//   ^ operands have same size
	rc |= check_logical_op_rn_rn (a, a, rnumber_rn_bitxor_rn(a, a), 0, "^");
	rnumber_bitxor_assign(a, a);
	rc |= check_logical_op_rn_rn (tmpa, tmpa, a, 0, "^=");
	rnumber_assign(a, tmpa);
	rc |= check_logical_op_rn_rn (a, b0, rnumber_rn_bitxor_rn(a, b0), a, "^");
	rnumber_bitxor_assign(a, b0);
	rc |= check_logical_op_rn_rn (tmpa, b0, a, tmpa, "^=");
	rnumber_assign(a, tmpa);
	rc |= check_logical_op_rn_rn (a, b1, rnumber_rn_bitxor_rn(a, b1), rnumber_unary_tilde(a), "^");
	rnumber_bitxor_assign(a, b1);
	rc |= check_logical_op_rn_rn (tmpa, b1, a, rnumber_unary_tilde(tmpa), "^=");
	rnumber_assign(a, tmpa);
	//   smaller ^ larger
	rc |= check_logical_op_rn_rn (a, c0, rnumber_rn_bitxor_rn(a, c0), a, "^");
	rnumber_bitxor_assign(a, c0);
	rc |= check_logical_op_rn_rn (tmpa, c0, a, tmpa, "^=");
	rnumber_assign(a, tmpa);
	{
	  struct RNumber * aa = rnumber_copy_to_size( a, rnumber_size(c1));
	  rc |= check_logical_op_rn_rn (a, c1, rnumber_rn_bitxor_rn(a, c1), rnumber_unary_tilde(aa), "^");
	  rnumber_bitxor_assign(a, c1);
	  rc |= check_logical_op_rn_rn (tmpa, c1, a, rnumber_unary_tilde(tmpa), "^=");
	  rnumber_assign(a, tmpa);
	  //   larger ^ smaller
	  rc |= check_logical_op_rn_rn (c0, a, rnumber_rn_bitxor_rn(c0, a), a, "^");
	  rnumber_bitxor_assign(c0, a);
	  rc |= check_logical_op_rn_rn (tmpc0, a, c0, a, "^=");
	  rnumber_assign(c0, tmpc0);
	  {
	    struct RNumber * tmp2 = rnumber_create_from_rnumber(c1);
	    rnumber_set_field(tmp2,size2 - size1, size2 - 1, rnumber_unary_tilde(a));
	    rc |= check_logical_op_rn_rn (c1, a, rnumber_rn_bitxor_rn(c1, a), tmp2, "^");
	    rnumber_bitxor_assign(c1, a);
	    rc |= check_logical_op_rn_rn (tmpc1, a, c1, tmp2, "^=");
	    rnumber_assign(c1, tmpc1);
	    //   ^ with integer
	    {
	      struct RNumber * tmp3 = rnumber_create_from_rnumber(b);
	      rnumber_set_field(tmp3, size2 - 32, size2 - 1, rnumber_create_from_unsigned(-1));
	      {
		unsigned num3 = ~(rnumber_get_uint(b));
		rc |= check_logical_op_rn_ui (b, num3, rnumber_rn_bitxor_ui(b, num3), tmp3, "^");
		rnumber_bitxor_assign(b, rnumber_create_from_unsigned(num3));
		rc |= check_logical_op_rn_ui (tmpb, num3, b, tmp3, "^=");
		rnumber_assign(b, tmpb);
		rc |= check_logical_op_rn_rn (b, 0, rnumber_rn_bitxor_ui(b, 0), b, "^");
		rnumber_bitxor_assign(b, rnumber_create_from_unsigned(0));
		rc |= check_logical_op_rn_rn (tmpb, 0, b, tmpb, "^=");
		rnumber_assign(b, tmpb);
	      }
	    }
	  }
	}
      }
    }
  }
  return rc;
}

int _argc;
char **_argv;
int _cur;

char * curArg()
{
  return _argv[_cur];
}

char * nextArg()
{
  ++_cur;
  if (_cur >= _argc) {
	 printf("Error:  Expected an argument for option '%s'.\n",_argv[_cur-1]);
  }
  return _argv[_cur];
}

int main (int argc, char **argv)
{
  const unsigned sizes[] = { 32, 64, 128, 0 };
  const unsigned n = 4;
  unsigned i;
  unsigned rc = 0;

  printf("number_test\n");
  _cur = 1;
  _argc = argc;
  _argv = argv;

  {
    char * path = "/bin";
    char * prog = "dc";
    char * pgm;
    unsigned seed = 0;

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

    if (strlen(pgm) == 0) {
      pgm = malloc(strlen(path) + strlen("/") + strlen(prog) + 1);
      strcpy(pgm,path);
      strcat(pgm, "/");
      strcat(pgm, prog);
    }
    seed = random_init(seed);

    {
      struct Calculator * calc = calculator_create(pgm);

      // construct/resize/set/operator=
      printf ("Starting constructors...");
      fflush (stdout);
      rc |= checkConstructors ();
      printf (" finished.\n");

      // add
      printf ("Starting adds...");
      fflush (stdout);
      printf("%s:%d\n", __FILE__, __LINE__);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "+.", calc);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "+", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "+", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "+.", calc);
      for (i = 0; i < n; i++) 
	rc |= checkMutator (sizes[i], "+=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntMutator (sizes[i], "+=", calc);
      printf (" finished.\n");

      // subtract
      printf ("Starting subtracts...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "-", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "-", calc);
      for (i = 0; i < n; i++) 
	rc |= checkMutator (sizes[i], "-=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntMutator (sizes[i], "-=", calc);
      printf (" finished.\n");

      // multiply
      printf ("Starting multiplies...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "*.", calc);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "*", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "*", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "*.", calc);
      for (i = 0; i < n; i++) 
	rc |= checkMutator (sizes[i], "*=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntMutator (sizes[i], "*=", calc);
      rc |= checkMultSpecialCases (calc);
      printf (" finished.\n");

      // divide
      printf ("Starting divides...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "/", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "/", calc);
      for (i = 0; i < n; i++) 
	rc |= checkMutator (sizes[i], "/=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntMutator (sizes[i], "/=", calc);
      rc |= checkDivideSpecialCases (calc);
      printf (" finished.\n");

      // modulus 
      printf ("Starting mods...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkOperator (sizes[i], "%", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntOperator (sizes[i], "%", calc);
      for (i = 0; i < n; i++) 
	rc |= checkMutator (sizes[i], "%=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntMutator (sizes[i], "%=", calc);
      printf (" finished.\n");

      // unsigned <
      printf ("Starting <...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], "<", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntComparator (sizes[i], "<", calc);
      printf (" finished.\n");

      // unsigned <=
      printf ("Starting <=...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], "<=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntComparator (sizes[i], "<=", calc);
      printf (" finished.\n");

      // unsigned >
      printf ("Starting >...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], ">", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntComparator (sizes[i], ">", calc);
      printf (" finished.\n");

      // unsigned >=
      printf ("Starting >=...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], ">=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntComparator (sizes[i], ">=", calc);
      printf (" finished.\n");

      // ==
      printf ("Starting ==...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], "==", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntComparator (sizes[i], "==", calc);
      printf (" finished.\n");

      // !=
      printf ("Starting !=...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], "!=", calc);
      for (i = 0; i < n; i++) 
	rc |= checkIntComparator (sizes[i], "!=", calc);
      printf (" finished.\n");

      // compare
      printf ("Starting compare...");
      fflush (stdout);
      for (i = 0; i < n; i++) 
	rc |= checkComparator (sizes[i], "compare", calc);
      printf (" finished.\n");

      // signedGT
      printf ("Starting signedGT...");
      fflush (stdout);
      for (i = 0; i < n; i++)
	rc |= checkSignedComparator (sizes[i], "GT", calc);
      printf (" finished.\n");

      // signedGE
      printf ("Starting signedGE...");
      fflush (stdout);
      for (i = 0; i < n; i++)
	rc |= checkSignedComparator (sizes[i], "GE", calc);
      printf (" finished.\n");

      // signedLT
      printf ("Starting signedLT...");
      fflush (stdout);
      for (i = 0; i < n; i++)
	rc |= checkSignedComparator (sizes[i], "LT", calc);
      printf (" finished.\n");

      // signedLE
      printf ("Starting signedLE...");
      fflush (stdout);
      for (i = 0; i < n; i++)
	rc |= checkSignedComparator (sizes[i], "LE", calc);
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
    }
  }
  return rc;
}

struct Calculator * calculator_create (const char *pgm)
{
  struct Calculator * calc = (struct Calculator*) malloc(sizeof(struct Calculator));

  printf("%s\n", __FUNCTION__);
  calc->_pgm = malloc (strlen(pgm) + 1);
  strcpy(calc->_pgm, pgm);

  if (pipe (calc->_fd1) < 0 || pipe (calc->_fd2) < 0) {
    printf ("Error creating pipe\n");
    exit (1);
  }
  printf("calc %p calc->_fd1[0] %d calc->_fd1[1] %d calc->_fd2[0] %d calc->_fd2[1] %d\n",
	 calc,  calc->_fd1[0], calc->_fd1[1], calc->_fd2[0], calc->_fd2[1]);
  {
    pid_t pid;
    printf("%s:%d %s() %s\n",__FILE__, __LINE__,  __FUNCTION__, "forking");
    if ((pid = fork ()) < 0) {
      printf ("Fork error\n");
      exit (1);
    }
    else if (pid > 0) {    // parent
      printf("%s:%d %s() parent pid %d getpid %d\n",__FILE__, __LINE__,  __FUNCTION__, pid, getpid());
      close (calc->_fd1[0]);
      close (calc->_fd2[1]);
      printf("%s:%d %s()\n",__FILE__, __LINE__,  __FUNCTION__);
    }
    else {                 // child
      printf("%s:%d %s() child pid %d getpid %d\n",__FILE__, __LINE__,  __FUNCTION__, pid, getpid());
      close (calc->_fd1[1]);
      close (calc->_fd2[0]);
      if (calc->_fd1[0] != 0)
	dup2 (calc->_fd1[0], 0);
      if (calc->_fd2[1] != 2)
	dup2 (calc->_fd2[1], 1);
      if (execl (pgm, calc->_pgm, NULL) < 0) {
	printf ("Exec error\n");
	exit (1);
      }
      printf("%s:%d %s()\n",__FILE__, __LINE__,  __FUNCTION__);
    }
  }
  printf("%s:%d %s()\n",__FILE__, __LINE__,  __FUNCTION__);
  calculator_private_init (calc);
  printf("%s:%d %s()\n",__FILE__, __LINE__,  __FUNCTION__);
  return calc;
}

void calculator_private_destroy ( struct Calculator * calc)
{
  printf("calculator_private_destroy\n");
  printf("%s\n", __FUNCTION__);
  calculator_private_terminate ( calc);
  free (calc);
}

static void uppercase (char *str)
{
  char *p = str;
  while (*p) {
    *p = toupper (*p);
    p++;
  }
}

unsigned max ( unsigned a, unsigned b)
{
  if ( a >= b ) {
    return a;
  }
  return b;
}

// Verify arithmetic using the external calculator.  This is for all-RNumber tests.
// If ext is true, we allow for resizing.
unsigned calculator_check_arith (struct Calculator * calc, const struct RNumber * a, const struct RNumber * b,
                                 const struct RNumber * c, char * op, int ext)
{
  char astr[256];
  char bstr[256];

  printf("%s:%d\n", __FILE__, __LINE__);

  assert (rnumber_size(a) <= 1024 && rnumber_size(b) <= 1024);
  // dc requires uppercase hex; right now RNumbers print hex in lower case
  strcpy (astr, rnumber_cstr(a));
  uppercase (astr);
  strcpy (bstr, rnumber_cstr(b));
  uppercase (bstr);

  printf("%s:%d\n", __FILE__, __LINE__);

  // Sanity checking if we're not allowing for resizing.
  if ( !ext && (op[0] != '%' && rnumber_size(c) != max( rnumber_size(a), rnumber_size(b) )) )
  {
    printf ("Result size error (1)  occurred in expression:  %s(%d) %s(%d) (%d) %s\n",
            astr, rnumber_size(a), bstr, rnumber_size(b), rnumber_size(c), op);
  }
  printf("%s:%d\n", __FILE__, __LINE__);
  return calculator_private_arith_calc(calc,astr,rnumber_size(a),bstr,rnumber_size(b),c,op,ext);
}

unsigned calculator_check_arith_unsigned (struct Calculator * calc, const struct RNumber * a, unsigned b, 
					  const struct RNumber * c, char * op, int ext)
{
  char astr[256];
  char bstr[256];
  
  strcpy (astr, rnumber_cstr(a));

  uppercase (astr);
  sprintf (bstr, "%X", b);

  if ( !ext && (op[0] != '%' && rnumber_size(c) != max( rnumber_size(a), (unsigned int) 32 ) ))
  {
    printf ("Result size error (2) occurred in expression:  %s(%d) %s(%d) (%d) %s\n",
            astr, rnumber_size(a), bstr, 32, rnumber_size(c), op);
    return 1;
  }

  return calculator_private_arith_calc(calc, astr,rnumber_size(a),bstr,sizeof(unsigned)*8,c,op,ext);
}

// Performs the specified calculation and compares the result
// to c.
// astr:  Printed number ready to hand to calculator.
// asize: a's size in bits.
// bstr:  Printed number ready to hand to calculator.
// bsize: b's size in bits.
// c:     Expected result.
// op:    Operator to use in calculation.
unsigned calculator_private_arith_calc (Calculator * calc,const char *astr,unsigned asize,
					const char *bstr,unsigned bsize,
					const struct RNumber * c,const char *op,
					int ext)
{
  unsigned rc = 0;

  char cmd[1024];
  char buf[1024];
  printf("%s:%d\n", __FILE__, __LINE__);
  sprintf (cmd, "%s %s %c p c\n", astr, bstr, op[0]);
  printf("%s:%d %d\n", __FILE__, __LINE__, getpid());
  {
    int n = strlen (cmd);
    printf("%s:%d calc pid %d %p calc->_fd1[1] %d\n", __FILE__, __LINE__, getpid(), calc, calc->_fd1[1]);
    if (write (calc->_fd1[1], cmd, strlen (cmd)) != n) {
      printf ("Write error\n");
      exit (1);
    }
    printf("%s:%d\n", __FILE__, __LINE__);
    n = 0;
    buf[0] = '\0';
    printf("%s:%d\n", __FILE__, __LINE__);
    do {
      int len = read (calc->_fd2[0], buf + n, 1024);
      printf("%s:%d\n", __FILE__, __LINE__);
      if (len < 0) {
	printf ("Read error\n");
	exit (1);
      }
      n += len;
    } while (n == 0 || buf[n-1] != '\n');
    buf[n] = '\0';
  }
  {
    struct RNumber * res =  ext ? rnumber_create_from_unsigned_of_size_variable_sizing( 0, rnumber_size(c)) :
      rnumber_create_from_unsigned_of_size( 0, rnumber_size(c));

  printf("%s:%d\n", __FILE__, __LINE__);
    if (!ext) {
      // Fixed size case.
      if (buf[0] == '-') {
	res = rnumber_create_from_string_of_size_of_radix( buf + 1, rnumber_size(c), rnumber_rhex() );
	rnumber_negate(res);
      } else {
	res = rnumber_create_from_string_of_size_of_radix( buf, rnumber_size(c), rnumber_rhex() );
      }
    } else {
      // Dynamically sized case.
  printf("%s:%d\n", __FILE__, __LINE__);
      if (buf[0] == '-') {
	res = rnumber_create_from_string_of_radix_variable_sizing( buf + 1,rnumber_rhex());
	rnumber_negate(res);
      } else {
	res = rnumber_create_from_string_of_radix_variable_sizing( buf, rnumber_rhex());
      }
    }

  printf("%s:%d\n", __FILE__, __LINE__);
    if (res != c) {
      printf ("Error (3) occurred in expression:  %s(%d) %s(%d) %s\n", astr, asize, bstr, bsize, op);
      printf ("  RNumber res = %s, dc res = %s\n", rnumber_cstr(c), rnumber_cstr(res));
      rc = 1;
    }
  
  printf("%s:%d\n", __FILE__, __LINE__);
    if (Verbose) {
      printf("Calc Result: %s\n",  rnumber_cstr(res));
    }
  }
  printf("%s:%d\n", __FILE__, __LINE__);
  return rc;
}

unsigned calculator_check_comparator (Calculator * calc, const struct RNumber * a, const struct RNumber * b, int res, char *op)
{
  char astr[256];
  char bstr[256];
  unsigned rc = 0;
  char cmd[1024];
  char buf[1024];
  int  n;

  strcpy (astr, rnumber_cstr(a));
  uppercase (astr);
  strcpy (bstr, rnumber_cstr(b));
  uppercase (bstr);

  sprintf (cmd, "%s %s - p c\n", astr, bstr);
  n = strlen (cmd);
  if (write (calc->_fd1[1], cmd, strlen (cmd)) != n) {
    printf ("Write error\n");
    exit (1);
  }
  n = 0;
  buf[0] = '\0';
  do {
    int len = read (calc->_fd2[0], buf + n, 1024);
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
    printf ("Error (4) occurred in expression:  %s(%d) %s(%d) %s\n", astr, rnumber_size(a), bstr, rnumber_size(b), op);
    printf ("  RNumber res = %d, subtract output = %s", res, buf);
    rc = 1;
  }
  else
    rc = 0;

  return rc;
}

unsigned calculator_check_comparator_unsigned (Calculator * calc, const struct RNumber * a, 
					       unsigned b, int res, char *op)
{
  char astr[256];
  char bstr[256];
  unsigned rc = 0;
  char cmd[1024];
  char buf[1024];
  int n;
  strcpy (astr, rnumber_cstr(a));
  uppercase (astr);
  sprintf (bstr, "%X", b);

  sprintf (cmd, "%s %s - p c\n", astr, bstr);
  n = strlen (cmd);
  if (write (calc->_fd1[1], cmd, strlen (cmd)) != n) {
    printf ("Write error\n");
    exit (1);
  }
  n = 0;
  buf[0] = '\0';
  do {
    int len = read (calc->_fd2[0], buf + n, 1024);
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
    printf ("Error (5) occurred in expression:  %s(%d) %s %s\n", astr, rnumber_cstr(a) , bstr, op);
    printf ("  RNumber res = %d, subtract output = %s", res, buf);
    rc = 1;
  }
  else
    rc = 0;

  return rc;
}

void calculator_private_init ( struct Calculator * calc)
{
  char *str = "16 o 16 i\n";
  int n = strlen (str);
  if (write (calc->_fd1[1], str, strlen (str)) != n) {
    printf ("Write error in init\n");
    exit (1);
  }
}

void calculator_private_terminate ( struct Calculator * calc)
{
  char *str = "q\n";
  int n = strlen (str);
  printf("%s\n", __FUNCTION__);
  if (write (calc->_fd1[1], str, strlen (str)) != n) {
    printf ("Write error in init\n");
    exit (1);
  }
}
