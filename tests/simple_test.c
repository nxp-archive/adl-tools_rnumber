#include "C-RNumber.h"

typedef struct RNumber RNumber;

int main ()
{
  char * a_str = "56d98216";
  char * b_str = "56d98216";
  char * c_str = "adb3042c";
  RNumber * a = rnumber_create_from_string_of_radix( a_str, 16);
  RNumber * b = rnumber_create_from_string_of_radix( b_str, 16);
  RNumber * c = 0;
  char * a_res_str;
  char * b_res_str;
  char * c_res_str;

  c = rnumber_rn_add_ext_rn(a,b);
  a_res_str = rnumber_cstr(a);
  b_res_str = rnumber_cstr(b);
  c_res_str = rnumber_cstr(c);
  printf( " a + b = c -> a %s, b %s, c %s\n", a_res_str, b_res_str, c_res_str);
  free(a);
  free(b);
  free(c);
  free(a_res_str);
  free(b_res_str);
  free(c_res_str);
  return 0;
}
