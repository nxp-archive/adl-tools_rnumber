/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** Handwritten functions for perl wrapper.
** ===========================================================================
*/

#ifdef __cplusplus
#include <math.h>
#include <stdlib.h>
extern "C" {
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include <string.h>
#ifdef __cplusplus
}
#endif

XS(_wrap_stringp) {
    int  _result;
    unsigned int  _arg0;
    int argvi = 0;
    dXSARGS ;

    cv = cv;
    if ((items < 1) || (items > 1)) 
        croak("Usage: stringp(scalar);");

    _result = (SvPOK(ST(0)) != 0) && (SvNOK(ST(0)) == 0);
    ST(argvi) = sv_newmortal();
    sv_setiv(ST(argvi++),(IV) _result);
    XSRETURN(argvi);
}

XS(_wrap_integerp) {
    int  _result;
    unsigned int  _arg0;
    int argvi = 0;
    dXSARGS ;

    cv = cv;
    if ((items < 1) || (items > 1)) 
        croak("Usage: stringp(scalar);");

    _result = (SvIOK(ST(0)) != 0);
    ST(argvi) = sv_newmortal();
    sv_setiv(ST(argvi++),(IV) _result);
    XSRETURN(argvi);
}
XS(_wrap_numericp) {
    int  _result;
    unsigned int  _arg0;
    int argvi = 0;
    dXSARGS ;

    cv = cv;
    if ((items < 1) || (items > 1)) 
        croak("Usage: stringp(scalar);");

    _result = (SvNOK(ST(0)) != 0) || (SvIOK(ST(0)));
    ST(argvi) = sv_newmortal();
    sv_setiv(ST(argvi++),(IV) _result);
    XSRETURN(argvi);
}


#ifdef __cplusplus
extern "C"
#endif
int rnumber_predicate_init()
{
  char *file = __FILE__;
  newXS("rnumber::stringp", _wrap_stringp, file);
  newXS("rnumber::integerp", _wrap_integerp, file);
  newXS("rnumber::numericp", _wrap_numericp, file);
  return 1;
}
