(module simple-number-test
   (library bl-rnumber)
   (main simple-number-test))

(define (do-tests a b)
   (print "a " a " b " b)
   (print "a=0x" (rnumber->cstr a) " b=0x" (rnumber->cstr b) " rn=?"  (rn=? a b))
   (print "a=0x" (rnumber->cstr a) " b=0x" (rnumber->cstr b) " rn!=?" (rn!=? a b))
   (print "a=0x" (rnumber->cstr a) " b=0x" (rnumber->cstr b) " rn<?"  (rn<? a b))
   (print "a=0x" (rnumber->cstr a) " b=0x" (rnumber->cstr b) " rn<=?" (rn<=? a b))
   (print "a=0x" (rnumber->cstr a) " b=0x" (rnumber->cstr b) " rn>?"  (rn>? a b))
   (print "a=0x" (rnumber->cstr a) " b=0x" (rnumber->cstr b) " rn>=?" (rn>=? a b)))

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
      (print "a " (rnumber->cstr a))
      (print "b " (rnumber->cstr b))
      (print "c " (rnumber->cstr c))
      (print "a = b " (equal? a b))
      (print "b = c " (equal? b c))
      (print "a = 10 " (equal? a 10))
      (print "10 = a "  (equal? 10 a))
      (print "parse from string qtv -> " (rnumber-parse-string "qtv"))
      (print "parse from string \"10\" -> " (rnumber-parse-string "10"))
      (print "5 - 3 -> " (rn- (rnumber-ctor 5) (rnumber-ctor "3")))
      ))
    
(define (simple-number-test args)
  (let ((rnumber-version *rnumber-version*))
		  (real-main args)))



