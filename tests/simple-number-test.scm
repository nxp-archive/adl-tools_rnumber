#!./driver

(define (do-tests a b)
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn=?"  (rn=? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn!=?" (rn!=? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn<?"  (rn<? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn<=?" (rn<=? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn>?"  (rn>? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn>=?" (rn>=? a b)))

(define (real-main argv)
   (print "create from int")
   (let ((a (rnumber-ctor 10))
	 (b (rnumber-ctor 15)))
      (do-tests a b))

   (print "create from string")
   (let ((a (rnumber-ctor "10"))
	 (b (rnumber-ctor "15")))
      (do-tests a b))

   (print "equal numbers")
   (let ((a (rnumber-ctor "10")))
      (do-tests a a))

   (let ((a (rnumber-ctor "10"))
	 (b (rnumber-ctor "0xff"))
	 (c (rnumber-ctor "0xff")))
      (print "a " a)
      (print "a " (rnumber-cstr a))
      (print "b " (rnumber-cstr b))
      (print "c " (rnumber-cstr c))))
    
(define (simple-number-test . args)
   (real-main args))