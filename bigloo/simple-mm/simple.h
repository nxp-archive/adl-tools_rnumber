
#ifndef Simple_h
#define Simple_h

#ifdef __cplusplus 
extern "C" 
{ 
  class Simple; 
#else 
  struct Simple;
#endif 

  struct Simple * simple_create();

  void simple_destroy(struct Simple * simple);

  struct Simple * simple_create_from_int( int x);

  void simple_set_x(struct Simple * simple, int x) ;
  int simple_get_x(struct Simple * simple);

#ifdef __cplusplus
}
#endif

#endif
