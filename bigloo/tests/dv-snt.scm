#! ./driver
;
; Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
;
; You may distribute under the terms of the Artistic License, as specified in
; the COPYING file.
;

(define (dv-snt . args)
   (let ((a (rn-ctor 10))
	 (b (rn-ctor 15))
	 (c (rn-ctor 10)))
      (print "rn=? a b " (rn=? a b))
      (print "rn=? a c " (rn=? a c))))
    
