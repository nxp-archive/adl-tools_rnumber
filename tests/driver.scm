(module  test
 (library bl-rnumber)
 (main main))

(define-macro(push! stack o)
  `(let((_obj ,o))
     (set! ,stack(cons _obj ,stack))
     _obj))

(define-macro(pop! stack)
  `(begin0
    (car ,stack)
    (set! ,stack(cdr ,stack))))
 
(define (main argv)
  (let ((a (rnumber-create-from-unsigned 5)))
    (print "created rnumber " (rnumber-cstr a)))
  (let ((in '()))
       (args-parse
         (cdr argv)
         (section #"Help")
         ((#"--version"
           (help #"Print version info and exit"))
          (exit 0))
         (((#"-h" #"--help")
           (help #"Print this help message and exit"))
          (args-parse-usage #f)
          (exit 0))
         (section #"Options")
         (((#"-I" #"--include")
           ?dir
           (synopsis #"Add  to load file search path"))
          (push! *load-path* dir))
         (else (push! in else)))
       (if (null? in)
	   (let (a (rnumber-create-from-unsigned 5))
	     (repl))
           (let ((args (reverse in))
		 (a (rnumber-create-from-unsigned 5)))
	      (set! *the-command-line* args)
	      (print "the command line " *the-command-line*)
	      (print "loading " (car args))
                (loadq (car args))))))
