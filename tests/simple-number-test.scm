#!./driver

; (module number-test
; 	(main main)
; 	(library bl-rnumber))


(define (do-tests a b)
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn=?"  (rn=? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn!=?" (rn!=? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn<?"  (rn<? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn<=?" (rn<=? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn>?"  (rn>? a b))
    (print "a=0x" (rnumber-cstr a) " b=0x" (rnumber-cstr b) " rn>=?" (rn>=? a b)))

;(define (main argv)
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



    
