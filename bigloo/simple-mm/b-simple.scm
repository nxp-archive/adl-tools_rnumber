(module simple-mm
   (main main)
   (extern
    ;; beginning of simple.h
    (include "simple.h")
    (simple-create::s-Simple* () "simple_create")
    (simple-destroy::void (s-Simple*) "simple_destroy")
    (simple-create-from-int::s-Simple* (int) "simple_create_from_int")
    (simple-set-x::void (s-Simple* int) "simple_set_x")
    (simple-get-x::int (s-Simple*) "simple_get_x")
    (finalize::int () "GC_invoke_finalizers")
    (make-simple-t::s-Simple* () "make_simple_t")
    (type s-Simple (struct) "struct Simple")
    (type ->s-Simple* "struct Simple *($())")
    (type s-Simple*->void "void ($(struct Simple *))")
    (type s-Simple*,int->s-Simple* "struct Simple *($(struct Simple *,int))")
    (type s-Simple*,int->void "void ($(struct Simple *,int))")
    (type s-Simple*->int "int ($(struct Simple *))")
    ;; end of simple.h
    ;; beginning of s.h
    (simple-set-call-finalizers::void () "simple_set_call_finalizers")
    (type ->void "void ($())")
    ;; end of s.h
    ))

(define (use-simple)
   (let ((a (make-simple-t)))
      (simple-set-x a 5)
      (print " getx " (simple-get-x a))
      (newline)))

(define (test-simple)
   (define (t-l b)
      (print "b " b)
      (use-simple)
      (if (< b 1000000)
	  (t-l (+ b 1))))
   (t-l 0))


(define (moo argv)
   (simple-set-call-finalizers)
   (test-simple))


(define (main argv)
   (if (pair? (cdr argv))
       (test-simple-mm (string->integer (cadr argv)))
       (test-simple-mm 10000000)))

(define (test-simple-mm l)
   (simple-set-call-finalizers)
  (let ((a (make-simple-t)))
    (simple-set-x a 5)
    (print (simple-get-x a))
    (let loop ((i l))
       (if (>fx i 0)
	   (begin
	      (set! a (make-simple-t))
	      (loop (-fx i 1)))))
    (newline)))
