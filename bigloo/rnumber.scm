(module rnumber
   (export *rnumber-version*
	   (rnumber? a)
	   (rnumber-ctor arg)
	   (rnumber-cstr arg)
	   (rnumber-parse-string str)
	   (rn=? a b)
	   (rn!=? a b)
	   (rn<? a b)
	   (rn<=? a b)
	   (rn>? a b)
	   (rn>=? a b)
	   (rn<< a b)
	   (rn>> a b)
	   (rn- a b)
	   (rn+ a b)
	   (rn-bitand a b)
	   (rn-bitor a b))
   (eval (export-exports))
   (type (subtype RNumber_proxy_t "obj_t" (obj))
	 (coerce RNumber_proxy_t obj () ())
	 (coerce obj RNumber_proxy_t (bgl_rnumber_proxy_t?) ())
	 (coerce RNumber_proxy_t bool () ((lambda (x) #t))))
   (extern
    (macro RNumber_proxy_t?::bool (::obj) "rnumber_proxyp")
    (macro bgl_rnumber_proxy_t?::bool (::obj) "rnumber_proxyp")
    ;; beginning of cl-bl-rnumber.h
    (bl-rnumber-create::RNumber_proxy_t () "bl_rnumber_create")
    (bl-rnumber-create-from-unsigned::RNumber_proxy_t (uint) "bl_rnumber_create_from_unsigned")
    (rnumber-create-from-unsigned_variable_sizing::RNumber_proxy_t (uint) "bl_rnumber_create_from_unsigned_variable_sizing")
    (rnumber-create-from-unsigned_of_size::RNumber_proxy_t (uint uint) "bl_rnumber_create_from_unsigned_of_size")
    (rnumber-create-from-unsigned_of_size_variable_sizing::RNumber_proxy_t 
     (uint uint) "bl_rnumber_create_from_unsigned_of_size_variable_sizing")
    (bl-rnumber-create-from-string::RNumber_proxy_t (string) "bl_rnumber_create_from_string")
    (rnumber-create-from-string-variable-sizing::RNumber_proxy_t (string) "bl_rnumber_create_from_string_variable_sizing")
    (rnumber-create-from-string-of-size::RNumber_proxy_t (string uint) "bl_rnumber_create_from_string_of_size")
    (rnumber-create-from-string-of-size_variable_sizing::RNumber_proxy_t 
     (string uint) "bl_rnumber_create_from_string_of_size_variable_sizing")
    (bl-rnumber-create-from-string-of-radix::RNumber_proxy_t (string int) "bl_rnumber_create_from_string_of_radix")
    (rnumber-create-from-string-of-radix_variable_sizing::RNumber_proxy_t
     (string int) "bl_rnumber_create_from_string_of_radix_variable_sizing")
    (rnumber-create-from-string-of-size-of-radix::RNumber_proxy_t
     (string uint int) "bl_rnumber_create_from_string_of_size_of_radix")
    (rnumber-create-from-string-of-size-of-radix-variable-sizing::RNumber_proxy_t 
     (string uint int) "bl_rnumber_create_from_string_of_size_of_radix_variable_sizing")
    (rnumber-create-from-numVector::RNumber_proxy_t (uint* uint uint) "bl_rnumber_create_from_numVector")
    (rnumber-create-from-numVector-variable-sizing::RNumber_proxy_t
     (uint* uint uint) "bl_rnumber_create_from_numVector_variable_sizing")
    (bl-rnumber-create-from-rnumber::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_create_from_rnumber")

    (rnumber-copy-to-size::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_copy_to_size")
    (rnumber-copy-to-size-variable-sizing::RNumber_proxy_t
     (RNumber_proxy_t uint) "bl_rnumber_copy_to_size_variable_sizing")
    (rnumber-unary-minus::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_unary_minus")
    (rnumber-unary-tilde::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_unary_tilde")
    (rnumber-getfield::RNumber_proxy_t (RNumber_proxy_t uint uint) "bl_rnumber_getfield")
    (rnumber-rn-plus-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_plus_rn")
    (rnumber-rn-plus-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_plus_ui")
    (rnumber-ui-plus-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_plus_rn")
    (rnumber-rn-add-ext_rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_add_ext_rn")
    (rnumber-rn-add-ext_ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_add_ext_ui")
    (rnumber-ui-add-ext_rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_add_ext_rn")
    (rnumber-rn-minus-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_minus_rn")
    (rnumber-rn-minus-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_minus_ui")
    (rnumber-ui-minus-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_minus_rn")
    (rnumber-rn-multiply-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_multiply_rn")
    (rnumber-rn-multiply-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_multiply_ui")
    (rnumber-ui-multiply-ui::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_multiply_ui")
    (rnumber-rn-multiply-ext_rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_multiply_ext_rn")
    (rnumber-rn-multiply-ext_ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_multiply_ext_ui")
    (rnumber-ui-multiply-ext_rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_multiply_ext_rn")
    (rnumber-rn-divide-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_divide_rn")
    (rnumber-rn-divide-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_divide_ui")
    (rnumber-ui-divide-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_divide_rn")
    (rnumber-rn-mod-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_mod_rn")
    (rnumber-rn-mod-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_mod_ui")
    (rnumber-ui-mod-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_mod_rn")
    (rnumber-rn-bitand-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_bitand_rn")
    (rnumber-rn-bitand-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_bitand_ui")
    (rnumber-ui-bitand-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_bitand_rn")
    (rnumber-rn-bitor-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_bitor_rn")
    (rnumber-rn-bitor-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_bitor_ui")
    (rnumber-ui-bitor-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_bitor_rn")
    (rnumber-rn-bitxor-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_bitxor_rn")
    (rnumber-rn-bitxor-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_bitxor_ui")
    (rnumber-ui-bitxor-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_bitxor_rn")
    (rnumber-rn-leftshift-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_leftshift_rn")
    (rnumber-rn-leftshift-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_leftshift_ui")
    (rnumber-ui-leftshift-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_leftshift_rn")
    (rnumber-rn-leftshift-ext-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_leftshift_ext_rn")
    (rnumber-rn-leftshift-ext-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_leftshift_ext_ui")
    (rnumber-ui-leftshift-ext-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_leftshift_ext_rn")
    (rnumber-rn-rightshift-rn::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_rightshift_rn")
    (rnumber-rn-rightshift-ui::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rn_rightshift_ui")
    (rnumber-ui-rightshift-rn::RNumber_proxy_t (uint RNumber_proxy_t) "bl_rnumber_ui_rightshift_rn")
    ;   (type s-RNumber_proxy (opaque) "struct RNumber_proxy")
    ;   (type RNumber_proxy_t (pointer s-RNumber_proxy) "RNumber_proxy_t")
    (type ->RNumber_proxy_t "RNumber_proxy_t ($())")
    (type uint->RNumber_proxy_t "RNumber_proxy_t ($(unsigned int))")
    (type uint,uint->RNumber_proxy_t "RNumber_proxy_t ($(unsigned int,unsigned int))")
    (type string->RNumber_proxy_t "RNumber_proxy_t ($(char *))")
    (type string,uint->RNumber_proxy_t "RNumber_proxy_t ($(char *,unsigned int))")
    (type string,int->RNumber_proxy_t "RNumber_proxy_t ($(char *,int))")
    (type string,uint,int->RNumber_proxy_t "RNumber_proxy_t ($(char *,unsigned int,int))")
    (type uint*,uint,uint->RNumber_proxy_t "RNumber_proxy_t ($(unsigned int *,unsigned int,unsigned int))")
    ;; end of cl-bl-rnumber.h
    ;; beginning of cl-C-RNumber.h
    (rnumber-destroy::void (RNumber_proxy_t) "bl_rnumber_destroy")
    (rnumber-assign_from_uint::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_assign_from_uint")
    (rnumber-assign_from_string::RNumber_proxy_t (RNumber_proxy_t string) "bl_rnumber_assign_from_string")
    (rnumber-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_assign")
    (rnumber-copy::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_copy")
    (rnumber-resize::void (RNumber_proxy_t uint) "bl_rnumber_resize")
    (rnumber-plus-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_plus_assign")
    (rnumber-plus-assign_from_unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_plus_assign_from_unsigned")
    (rnumber-minus-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_minus_assign")
    (rnumber-minus-assign_from_unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_minus_assign_from_unsigned")
    (rnumber-multiply-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_multiply_assign")
    (rnumber-multiply-assign_from_unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_multiply_assign_from_unsigned")
    (rnumber-divide-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_divide_assign")
    (rnumber-divide-assign-from-unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_divide_assign_from_unsigned")
    (rnumber-mod-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_mod_assign")
    (rnumber-mod-assign-from-unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_mod_assign_from_unsigned")
    (rnumber-bitand-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_bitand_assign")
    (rnumber-bitand-assign_from_unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_bitand_assign_from_unsigned")
    (rnumber-bitor-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_bitor_assign")
    (rnumber-bitor-assign_from_unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_bitor_assign_from_unsigned")
    (rnumber-bitxor-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_bitxor_assign")
    (rnumber-bitxor-assign-from-unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_bitxor_assign_from_unsigned")
    (rnumber-leftshift-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_leftshift_assign")
    (rnumber-leftshift-assign-from-unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_leftshift_assign_from_unsigned")
    (rnumber-rightshift-assign::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rightshift_assign")
    (rnumber-rightshift-assign_from_unsigned::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_rightshift_assign_from_unsigned")
    (rnumber-not::int (RNumber_proxy_t) "bl_rnumber_not")
    (rnumber-signed-lessthan::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_signed_lessthan")
    (rnumber-signed-lessequal::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_signed_lessequal")
    (rnumber-signed-greaterthan::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_signed_greaterthan")
    (rnumber-signed-greaterequal::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_signed_greaterequal")
    (rnumber-compare::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_compare")
    (rnumber-invert::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_invert")
    (rnumber-negate::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_negate")
    (rnumber-set-all::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_set_all")
    (rnumber-clear-all::RNumber_proxy_t (RNumber_proxy_t) "bl_rnumber_clear_all")
    (rnumber-sign-extend::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_sign_extend")
    (rnumber-truncate::RNumber_proxy_t (RNumber_proxy_t uint) "bl_rnumber_truncate")
    (rnumber-getbit::uint (RNumber_proxy_t uint) "bl_rnumber_getbit")
    (rnumber-getbit-lsb::uint (RNumber_proxy_t uint) "bl_rnumber_getbit_lsb")
    (rnumber-setbit::void (RNumber_proxy_t uint uint) "bl_rnumber_setbit")
    (rnumber-setbit-lsb::void (RNumber_proxy_t uint uint) "bl_rnumber_setbit_lsb")
    (rnumber-assignbit::void (RNumber_proxy_t uint uint) "bl_rnumber_assignbit")
    (rnumber-assignbit-lsb::void (RNumber_proxy_t uint uint) "bl_rnumber_assignbit_lsb")
    (rnumber-get_uint::uint (RNumber_proxy_t) "bl_rnumber_get_uint")
    (bl-rnumber-cstr::string (RNumber_proxy_t) "bl_rnumber_cstr")
    (rnumber-cstr-radix::string (RNumber_proxy_t int int) "bl_rnumber_cstr_radix")
    (rnumber-get-int-field::int (RNumber_proxy_t uint uint) "bl_rnumber_get_int_field")
    (rnumber-get-uint-field::uint (RNumber_proxy_t uint uint) "bl_rnumber_get_uint_field")
    (rnumber-set-field::void (RNumber_proxy_t uint uint RNumber_proxy_t) "bl_rnumber_set_field")
    (rnumber-size::uint (RNumber_proxy_t) "bl_rnumber_size")
    (rnumber-wordcount::uint (RNumber_proxy_t) "bl_rnumber_wordcount")
    (rnumber-buffer::uint* (RNumber_proxy_t) "bl_rnumber_buffer")
    (rnumber-get-default_size::uint () "bl_rnumber_get_default_size")
    (rnumber-set-default_size::void (uint) "bl_rnumber_set_default_size")
    (rnumber-sizing::int (RNumber_proxy_t) "bl_rnumber_sizing")
    (rnumber-dynamic::int () "bl_rnumber_dynamic")
    (rnumber-fixed::int () "bl_rnumber_fixed")
    (rnumber-set-dynamic::void (RNumber_proxy_t) "bl_rnumber_set_dynamic")
    (rnumber-set-fixed::void (RNumber_proxy_t) "bl_rnumber_set_fixed")
    (rnumber-print-to-os::void (RNumber_proxy_t void*) "bl_rnumber_print_to_os")
    (rnumber-print-with-radix::void (RNumber_proxy_t void* int int) "bl_rnumber_print_with_radix")
    (rnumber-read_from-is::void (RNumber_proxy_t void*) "bl_rnumber_read_from_is")
    (rnumber-write-to-os::void (RNumber_proxy_t void*) "bl_rnumber_write_to_os")
    (bl-rnumber-rn-notequal-rn::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_notequal_rn")
    (bl-rnumber-rn-notequal-ui::int (RNumber_proxy_t uint) "bl_rnumber_rn_notequal_ui")
    (bl-rnumber-ui-notequal-rn::int (uint RNumber_proxy_t) "bl_rnumber_ui_notequal_rn")
    (bl-rnumber-rn-equal-rn::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_equal_rn")
    (bl-rnumber-rn-equal-ui::int (RNumber_proxy_t uint) "bl_rnumber_rn_equal_ui")
    (bl-rnumber-ui-equal-rn::int (uint RNumber_proxy_t) "bl_rnumber_ui_equal_rn")
    (bl-rnumber-rn-lessthan-rn::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_lessthan_rn")
    (bl-rnumber-rn-lessthan-ui::int (RNumber_proxy_t uint) "bl_rnumber_rn_lessthan_ui")
    (bl-rnumber-ui-lessthan-rn::int (uint RNumber_proxy_t) "bl_rnumber_ui_lessthan_rn")
    (bl-rnumber-rn-lessequal-rn::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_lessequal_rn")
    (bl-rnumber-rn-lessequal-ui::int (RNumber_proxy_t uint) "bl_rnumber_rn_lessequal_ui")
    (bl-rnumber-ui-lessequal-rn::int (uint RNumber_proxy_t) "bl_rnumber_ui_lessequal_rn")
    (bl-rnumber-rn-greaterthan-rn::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_greaterthan_rn")
    (bl-rnumber-rn-greaterthan-ui::int (RNumber_proxy_t uint) "bl_rnumber_rn_greaterthan_ui")
    (bl-rnumber-ui-greaterthan-rn::int (uint RNumber_proxy_t) "bl_rnumber_ui_greaterthan_rn")
    (bl-rnumber-rn-greaterequal-rn::int (RNumber_proxy_t RNumber_proxy_t) "bl_rnumber_rn_greaterequal_rn")
    (bl-rnumber-rn-greaterequal-ui::int (RNumber_proxy_t uint) "bl_rnumber_rn_greaterequal_ui")
    (bl-rnumber-ui-greaterequal-rn::int (uint RNumber_proxy_t) "bl_rnumber_ui_greaterequal_rn")
    (bl-rnumber-rhex::int () "bl_rnumber_rhex")
    (bl-rnumber-rbin::int () "bl_rnumber_rbin")
    (bl-rnumber-rdec::int () "bl_rnumber_rdec")
    (type uint* (pointer uint) "unsigned int *")
    (type ->uint "unsigned int ($())")
    (type uint->void "void ($(unsigned int))")
    (type ->int "int ($())")
    ;; end of cl-C-RNumber.h
    ;; beginning of C-Random.h
    (random-create::void () "random_create")
    (random-set_gate_all::void (int) "random_set_gate_all")
    (random-set_gate::void (int int) "random_set_gate")
    (random-init::uint () "random_init")
    (random-init_from_seed::uint (uint) "random_init_from_seed")
    (random-add_new_gen::int () "random_add_new_gen")
    (random-add_new_gen_with_seed::int (uint) "random_add_new_gen_with_seed")
    (random-pop_gen::void (int) "random_pop_gen")
    (random-set_cur_gen::int (int) "random_set_cur_gen")
    (random-get_cur_gen::int () "random_get_cur_gen")
    (random-get_num_gen::int () "random_get_num_gen")
    (random-get_rnumber::RNumber_proxy_t (int) "random_get_rnumber")
    (random-get_integer::uint () "random_get_integer")
    (random-get_integer_n::uint (uint) "random_get_integer_n")
    (random-get_double::double () "random_get_double")
    (random-get_from_range_rnumber::RNumber_proxy_t (RNumber_proxy_t RNumber_proxy_t) "random_get_from_range_rnumber")
    (random-get_from_range_unsigned::uint (uint uint) "random_get_from_range_unsigned")
    (random-save::void (void*) "random_save")
    (random-load::void (void*) "random_load")
    (random-get_state::void* () "random_get_state")
    (random-set_state::void (void*) "random_set_state")
    (random-get_count::uint () "random_get_count")
    (type ->void "void ($())")
    (type int->void "void ($(int))")
    (type int,int->void "void ($(int,int))")
    (type uint->uint "unsigned ($(unsigned))")
    (type uint->int "int ($(unsigned))")
    (type int->int "int ($(int))")
    (type ->double "double ($())")
    (type uint,uint->uint "unsigned ($(unsigned,unsigned))")
    (type void*->void "void ($(void *))")
    (type ->void* "void *($())")
    ;; end of C-Random.h
    ))

(define *rnumber-version* "1.6.1")

(define (rnumber-ctor arg)
   (cond ((null? arg) (bl-rnumber-create))
         ((integer? arg) (bl-rnumber-create-from-unsigned arg))
	 ((string? arg) (bl-rnumber-create-from-string arg))
	 ((RNumber_proxy_t? arg) (bl-rnumber-create-from-rnumber arg))
         (else (error "rnumber-ctor" "unknown arg type " arg))))

(define (rnumber-cstr args)
   (cond ((RNumber_proxy_t? args) (bl-rnumber-cstr args))
	 (else (error "rnumber-cstr" "unknown args type " args))))

(define (rnumber? a)
   (RNumber_proxy_t? a))

(define *rnumber-two-arg-error* "needs two argument one needs to be a rnumber, the other an rnumber or an int ")

(define (rn=? a b)
   ;(print "(rn=? " a " " b ")")
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      ;(print "(arg-types " first-rn " " first-ui " " second-rn " " second-ui ") args (" a " " b ")")
      (let ((rv  (cond ((and first-rn second-rn) (bl-rnumber-rn-equal-rn a b))
		       ((and first-rn second-ui) (bl-rnumber-rn-equal-ui a b))
		       ((and first-ui second-rn) (bl-rnumber-ui-equal-rn a b))
		       ((and first-ui second-ui) (= a b))
		       (else
			;(print "false")
			0))))
	 ;(print "rv " rv )
	 (if (= rv 0)
	     (begin
		;(print "returning false")
		#f)
	     (begin
		;(print "returning true")
		#t)))))

(define (rn!=? a b)
   (not (rn=? a b)))

(define (rn<? a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (let ((rv (cond ((and first-rn second-rn) (bl-rnumber-rn-lessthan-rn a b))
		      ((and first-rn second-ui) (bl-rnumber-rn-lessthan-ui a b))
		      ((and first-ui second-rn) (bl-rnumber-ui-lessthan-rn a b))
		      ((and first-ui second-ui) (if (< a b) 1 0))
		      (else (error "rn<" *rnumber-two-arg-error* (cons a b))))))
	 (not (= rv 0)))))

(define (rn<=? a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (let ((rv (cond ((and first-rn second-rn) (bl-rnumber-rn-lessequal-rn a b))
		      ((and first-rn second-ui) (bl-rnumber-rn-lessequal-ui a b))
		      ((and first-ui second-rn) (bl-rnumber-ui-lessequal-rn a b))
		      ((and first-ui second-ui) (if (<= a b) 1 0))
		      (else (error "rn<=" *rnumber-two-arg-error* (cons a b))))))
	 (not (= rv 0)))))

(define (rn>? a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (let ((rv (cond ((and first-rn second-rn) (bl-rnumber-rn-greaterthan-rn a b))
		      ((and first-rn second-ui) (bl-rnumber-rn-greaterthan-ui a b))
		      ((and first-ui second-rn) (bl-rnumber-ui-greaterthan-rn a b))
		      ((and first-ui second-ui) (if (> a b) 1 0))
		      (else (error "rn>" *rnumber-two-arg-error* (cons a b))))))
	 (not (= rv 0)))))

(define (rn>=? a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (let ((rv (cond ((and first-rn second-rn) (bl-rnumber-rn-greaterequal-rn a b))
		      ((and first-rn second-ui) (bl-rnumber-rn-greaterequal-ui a b))
		      ((and first-ui second-rn) (bl-rnumber-ui-greaterequal-rn a b))
		      ((and first-ui second-ui) (if (>= a b) 1 0))
		      (else (error "rn>=" *rnumber-two-arg-error* (cons a b))))))
	 (not (= rv 0)))))

(define (rn<< a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (cond ((and first-rn second-rn) (rnumber-rn-leftshift-rn a b))
	    ((and first-rn second-ui) (rnumber-rn-leftshift-ui a b))
	    ((and first-ui second-rn) (rnumber-ui-leftshift-rn a b))
	    (else (error "rn<<" *rnumber-two-arg-error* (cons a b))))))

(define (rn>> a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (cond ((and first-rn second-rn) (rnumber-rn-rightshift-rn a b))
	    ((and first-rn second-ui) (rnumber-rn-rightshift-ui a b))
	    ((and first-ui second-rn) (rnumber-ui-rightshift-rn a b))
	    (else (error "rn>>" *rnumber-two-arg-error* (cons a b))))))

(define (rn- a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (cond ((and first-rn second-rn) (rnumber-rn-minus-rn a b))
	    ((and first-rn second-ui) (rnumber-rn-minus-ui a b))
	    ((and first-ui second-rn) (rnumber-ui-minus-rn a b))
	    (else (error "rn-" *rnumber-two-arg-error* (cons a b))))))

(define (rn+ a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (cond ((and first-rn second-rn) (rnumber-rn-plus-rn a b))
	    ((and first-rn second-ui) (rnumber-rn-plus-ui a b))
	    ((and first-ui second-rn) (rnumber-ui-plus-rn a b))
	    (else (error "rn+" *rnumber-two-arg-error* (cons a b))))))

(define (rn-bitand a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (cond ((and first-rn second-rn) (rnumber-rn-bitand-rn a b))
	    ((and first-rn second-ui) (rnumber-rn-bitand-ui a b))
	    ((and first-ui second-rn) (rnumber-ui-bitand-rn a b))
	    (else (error "rn-bitand" *rnumber-two-arg-error* (cons a b))))))

(define (rn-bitor a b)
   (let ((first-rn (RNumber_proxy_t? a))
	 (first-ui (integer? a))
	 (second-rn (RNumber_proxy_t? b))
	 (second-ui (integer? b)))
      (cond ((and first-rn second-rn) (rnumber-rn-bitor-rn a b))
	    ((and first-rn second-ui) (rnumber-rn-bitor-ui a b))
	    ((and first-ui second-rn) (rnumber-ui-bitor-rn a b))
	    (else (error "rn-bitor" *rnumber-two-arg-error* (cons a b))))))

(define (rnumber-parse-string str)
   ;(print "(rnumber-parse-string " str ")")
   (bind-exit (exit)
      (let ((rnumber-lexer
	     (regular-grammar ()
		((or (: (in ("19")) (* (in ("09"))))
		     #\0)
		 ;(print "dec-integer " (the-string))
		 (cons 'DEC-INTEGER (rnumber-ctor(the-string))))
		((: #\0 (in #\x #\X) (+ (in ("09afAF"))))
		 ;(print "hex-integer " (the-string))
		 (cons 'HEX-INTEGER (rnumber-ctor(the-string))))
		((: #\0 (in #\b #\B) (+ (in "01")))
		 ;(print "bin-integer " (the-string))
		 (cons 'BIN-INTEGER (rnumber-ctor(the-string))))
		(else
		 ;(print "not an rnumber" )
		 (exit #f))))
	    (rnumber-parser
	     (lalr-grammar
		(DEC-INTEGER HEX-INTEGER BIN-INTEGER NOT-AN-RNUMBER) 
		(rnumber-or-not ((rnumber) (exit rnumber))
				((not-rnumber) (exit not-rnumber)))
		(rnumber ((DEC-INTEGER)
			  ;(print "DEC-INTEGER->rnumber(" DEC-INTEGER ")")
			  DEC-INTEGER)
			 ((HEX-INTEGER) HEX-INTEGER))
		(not-rnumber ((NOT-AN-RNUMBER) #f)))))
	 (with-input-from-string str
	    (lambda ()
	       (read/lalrp rnumber-parser rnumber-lexer (current-input-port)))))))
