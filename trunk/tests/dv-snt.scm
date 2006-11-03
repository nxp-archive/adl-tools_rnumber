;
; Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
;
; You may distribute under the terms of the Artistic License, as specified in
; the COPYING file.
;

#!./driver

(let ((a (rnumber-ctor 10))
      (b (rnumber-ctor 15))
      (c (rnumber-ctor 10)))
  (print "rnumber-rn-equal-rn a b " (rnumber-equal a b))
  (print "rnumber-rn-equal-rn a c " (rnumber-equal a c)))
    
