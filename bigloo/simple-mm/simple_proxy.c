
#include "simple_proxy.h"

extern int GC_finalize_on_demand;

void simple_set_call_finalizers()
{
  printf("GC_finalize_on_demand is %d\n", GC_finalize_on_demand);
  GC_finalize_on_demand = 0;
  printf("GC_finalize_on_demand is %d\n", GC_finalize_on_demand);
}


/*---------------------------------------------------------------------*/
/*    void                                                             */
/*    unmake_bigarray ...                                              */
/*---------------------------------------------------------------------*/
void
unmake_simple_t( simple_proxy_t array ) {
  printf("%s:%d %s()", __FILE__, __LINE__, __FUNCTION__);
  simple_destroy(array->a_t.simple);
  array->a_t.simple = 0;
}

/* from bigloo2.5a/runtime/Clib/ccustom.c */
obj_t create_custom( long len );

simple_proxy_t make_simple_t()
{
  simple_proxy_t array;

  if( array = (simple_proxy_t)create_custom( sizeof(struct simple_proxy_a))) {

#ifdef BIGLOO
    array->custom.to_string  = simple_to_string;
#endif
    /*    array->custom.output     = (hol_t (*)())simple_output; */
    array->custom.output     = 0;
    array->custom.final      = (void (*)(hol_t))unmake_simple_t;
    array->custom.identifier = SIMPLE_IDENTIFIER;
    array->a_t.simple = simple_create();
    GC_register_finalizer( array, unmake_simple_t, 0, 0, 0 );
    return HOL_REF( array );
  } else {
    goto error;
  }

 error:
  SIMPLE_PROXY_ERROR( "make_simple_t" );
}

