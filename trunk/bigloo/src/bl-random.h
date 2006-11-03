//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

(directives
 (extern
   ;; beginning of C-Random.h
   (random_create::void () "random_create")
   (random_set_gate_all::void (int) "random_set_gate_all")
   (random_set_gate::void (int int) "random_set_gate")
   (random_init::uint () "random_init")
   (random_init_from_seed::uint (uint) "random_init_from_seed")
   (random_add_new_gen::int () "random_add_new_gen")
   (random_add_new_gen_with_seed::int (uint) "random_add_new_gen_with_seed")
   (random_pop_gen::void (int) "random_pop_gen")
   (random_set_cur_gen::int (int) "random_set_cur_gen")
   (random_get_cur_gen::int () "random_get_cur_gen")
   (random_get_num_gen::int () "random_get_num_gen")
   (random_get_rnumber::s-RNumber* (int) "random_get_rnumber")
   (random_get_integer::uint () "random_get_integer")
   (random_get_integer_n::uint (uint) "random_get_integer_n")
   (random_get_double::double () "random_get_double")
   (random_get_from_range_rnumber::s-RNumber* (s-RNumber* s-RNumber*) "random_get_from_range_rnumber")
   (random_get_from_range_unsigned::uint (uint uint) "random_get_from_range_unsigned")
   (random_save::void (void*) "random_save")
   (random_load::void (void*) "random_load")
   (random_get_state::void* () "random_get_state")
   (random_set_state::void (void*) "random_set_state")
   (random_get_count::uint () "random_get_count")
   (type ->void "void ($())")
   (type int->void "void ($(int))")
   (type int,int->void "void ($(int,int))")
   (type ->uint "unsigned ($())")
   (type uint->uint "unsigned ($(unsigned))")
   (type ->int "int ($())")
   (type uint->int "int ($(unsigned))")
   (type int->int "int ($(int))")
   (type s-RNumber (struct) "struct RNumber")
   (type int->s-RNumber* "struct RNumber *($(int))")
   (type ->double "double ($())")
   (type s-RNumber*,s-RNumber*->s-RNumber* "struct RNumber *($(struct RNumber *,struct RNumber *))")
   (type uint,uint->uint "unsigned ($(unsigned,unsigned))")
   (type void* (pointer void) "void *")
   (type void*->void "void ($(void *))")
   (type ->void* "void *($())")
   ;; end of C-Random.h
   ))
