(module  test
   (library bl-rnumber)
   (main driver-main)
   (eval (export *the-command-line*)))

(define-macro(push! stack o)
   `(let((_obj ,o))
       (set! ,stack(cons _obj ,stack))
       _obj))

(define-macro(pop! stack)
   `(begin0
     (car ,stack)
     (set! ,stack(cdr ,stack))))

(define *the-command-line* '())

(define (print-version-and-quit arg)
   (print "version " arg)
   (quit))

(define (driver-main argv)
   (let ((rnumber-version *rnumber-version*) ; this is required to init library, do not remove it.
	 (in '()))
      (args-parse
	    (cdr argv)
	 (section #"Help")
	 ((#"--version"
	   (print-version-and-quit rnumber-version)
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
	  (begin (print "version " rnumber-version)
		 (repl))
	  (let ((args (reverse in)))
	     (print "version " rnumber-version)
	     (set! *the-command-line* args)
	     (loadq (car args))
	     (let ((cmd (cons (string->symbol (prefix (basename (car *the-command-line*))))
			      (cdr *the-command-line*))))
		(eval cmd))
	     ))))
