(module number-test
	(main main)
	(library bl-rnumber))


(define (main argv)
  (let ((a (rnumber-create-from-unsigned 10))
	(b (rnumber-create-from-unsigned 15))
	(c (rnumber-create-from-unsigned 10)))
    (print "rnumber-rn-equal-rn a b " (rnumber-rn-equal-rn a b))
    (print "rnumber-rn-equal-rn a c " (rnumber-rn-equal-rn a c))))
    
