
#include "rnumber_proxy.h"

extern int GC_finalize_on_demand;

void set_GC_call_finalizers_to_zero()
{
  GC_finalize_on_demand = 0;
}

void rnumber_finalize( RNumber_proxy_t array ) {
  printf("%s:%d %s()", __FILE__, __LINE__, __FUNCTION__);
  rnumber_destroy(array->a_t.rnumber);
  array->a_t.rnumber = 0;
}

/* from bigloo2.5a/runtime/Clib/ccustom.c */
obj_t create_custom( long len );

rnumber_proxy_t proxy_from_rnumber( struct RNumber * rnumber);
{
  RNumber_proxy_t array;

  if( array = (RNumber_proxy_t)create_custom( sizeof(struct RNumber_proxy_a))) {

#ifdef BIGLOO
    array->custom.to_string  = simple_to_string;
#endif
    /*    array->custom.output     = (hol_t (*)())simple_output; */
    array->custom.output     = 0;
    array->custom.final      = (void (*)(hol_t))rnumber_finalize;
    array->custom.identifier = RNUMBER_IDENTIFIER;
    array->a_t.rnumber = rnumber;
    GC_register_finalizer( array, rnumber_finalize, 0, 0, 0 );
    return HOL_REF( array );
  } else {
    goto error;
  }

 error:
  RNUMBER_PROXY_ERROR( "proxy_from_rnumber" );
}

