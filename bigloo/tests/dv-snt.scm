#!./driver

(let ((a (rnumber-ctor 10))
      (b (rnumber-ctor 15))
      (c (rnumber-ctor 10)))
  (print "rnumber-rn-equal-rn a b " (rnumber-equal a b))
  (print "rnumber-rn-equal-rn a c " (rnumber-equal a c)))
    
