#!../bigloo/tests/driver

;//
;// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
;//
;// You may distribute under the terms of the Artistic License, as specified in
;// the COPYING file.
;//

; to run interpreted this you need to have run 'make check' in the bigloo/tests
; directory to build driver.


;// To compile this file use the command:
;//
;
;// The C++ tracing utilities are not available to bigloo. 
;// #include "rnumber/trace.h"

(define (b-example . args)
   (let (; rnumbers can be created from integers 
	 (a (rn-ctor #x10))
	 ; rnumbers can be created from strings
	 (b (rn-ctor "0x102344356553"))
	 ; underscores may be placed into strings to increase readability 
	 (c (rn-ctor "0x1023_4435_6553"))
	 ; Unfortunately rnumbers can NOT be created with a specified size with bigloo
	 ; However, they may be resized with (rn-resize! rn)
	 (d (rn-ctor 0))
	 ; rnumbers can be allowed to grow instead of wrap. This cannot be
	 ; set in ctor with bigloo bindings. The wrap state is set by using
	 ; (rn-set-dynamic! rn) and (rn-set-fixed! rn)
	 (e (rn-ctor 0)))
	 
      (rn-resize! d 128)
      (rn-resize! e 128)
      (rn-set-dynamic! e)

      (print "you can just print and pretty print rnumbers")
      (print "a " a)
      (print "pretty print (a b)")
      (pp (list a b))
      
      (print "Use rn->string to print formated rnumbers")

      (print "a " (rn->string a) " (" (rn->string a 16 #t) ")")

      (print "b " (rn->string b) " " (rn->string b 16 #f) " " (rn->string b 16 #t))

      ; the underscores in the ctor are not remembered by the number. This gives the
      ; same output as b. 
      (print "c " (rn->string c) " "  (rn->string c 16 #f) " " rn->string c 16 #t)

      ; rnumber_cstr_radix supports radix or 2, 10, and 16
      (print "a " (rn->string a 10 #t) " " (rn->string a 2 #t) " " (rn->string a 16 #t))

      ; d is a wide number
      (print "d " (rn->string d) " " (rn->string d 16#t))

      ; set all of the bits in d and e.
      (rn-set-all! d)
      (rn-set-all! e)

      (print "d " d " e " e)

      ;The normal overloaded operators currently always wrap.
      (set! d (rn+ d 1))
      (set! e (rn+ e 1))

      (print "d " d " e " e)
   
      ; operator equal does not copy the size for fixed numbers or sizing for either. Howevery, the
      ; assign method does

      (let ((f-fixed (rn-ctor 0))
	    (f-dynamic (rn-ctor 0))
	    (g (rn-ctor 0)))
	 (rn-set-dynamic! f-dynamic)
	 (rn-resize! g 64)
	 

	 (print "f-fixed " (rn-size f-fixed) " " (rn-sizing f-fixed)
		" f-dynamic " (rn-size f-dynamic) " " (rn-sizing f-dynamic))

	 ;   /* the operator= is not available in C. */
	 (rn-assign! f-fixed g)
	 (rn-assign! f-dynamic g)

	 (print "f-fixed " (rn-size f-fixed) " " (rn-sizing f-fixed)
		" f-dynamic " (rn-size f-dynamic) " " (rn-sizing f-dynamic)))

      
      ; the add function can be used with the extend parameter to have 'growing' numbers
      (let ((d (rn-ctor 0))
	    (e (rn-ctor 0)))

	    (rn-resize! d 128)
	    (rn-resize! e 128)
	    (rn-set-dynamic! e)

	    (rn-set-all! d)
	    (rn-set-all! e)

	    (print "d " d " " (rn-size d) " " (rn-sizing d))
	    (print "e " e " " (rn-size e) " " (rn-sizing e))
	    
	    (print "extending arithmetic is not currently supported with bigloo bindings")
	    (rn-assign! d (rn+ d 1))
	    (rn-assign! e (rn+ e 1))

	    (print "d " d " " (rn-size d) " " (rn-sizing d))
	    (print "e " e " " (rn-size e) " " (rn-sizing e)))

      (let ((big-number1 (rn-ctor "1"))
	    (big-number2 (rn-ctor "1")))
	 (rn-resize! big-number1 4096)
	 (rn-resize! big-number2 4096)
	 (set! big-number1 (rn<< big-number1 2047))
	 (set! big-number2 (rn* big-number1 3))

	 (print "However, very large numbers may be used")
	 (print big-number1 " * " big-number2 " = " (rn* big-number1 big-number2)))))
	    
