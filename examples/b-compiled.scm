;
; Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
;
; You may distribute under the terms of the Artistic License, as specified in
; the COPYING file.
;

; To compile this file use the command:
;
; bigloo -L ../bigloo/src -o b-compiled b-compiled.scm b-example.scm
;
;;;; bigloo -o b-compiled b-compiled.scm b-example.scm
;
; If b-compiled can't find libbigloo_s-2.8c.so or similar file, you may need to
; do something like this
;
;bigloo -L ../bigloo/src -o b-compiled b-compiled.scm b-example.scm \
; -ldopt "-Wl,-R <path-to-libbigloo_s-2.8c.so>"
;
;



(module b-compiled
   (library bl-rnumber)
   (main main))

(define (main args)
   (b-example args))

