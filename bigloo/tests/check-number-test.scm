;
; Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
;
; You may distribute under the terms of the Artistic License, as specified in
; the COPYING file.
;

(module check-number-test
   (main check-number-test))

(define (check-number-test args)
   (let* ((process (run-process "./simple-number-test" output: "simple-number-test.out" wait: #t))
	  (pes (process-exit-status process)))
      (print "simple-number-test exit status " pes)
      (print "simple-number-test exit status " (process-exit-status process))
      (unless (= pes 0)
	 (print "FAIL -- failed to run ./simple-number-test")
	 (exit 1)))
   (let ((pes (process-exit-status
	       (run-process "diff" "simple-number-test.out" "simple-number-test.golden"
			    output: "diff.out" wait: #t))))
      (print "diff status " pes)
      (unless (= pes 0)
	 (print "FAIL -- diff returned " pes " please see diff in diff.out")
	 (exit 1))))
