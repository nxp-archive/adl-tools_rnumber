/*===========================================================================*/
/*   (b-simple.scm)                                                          */
/*   Bigloo (2.5a)                                                           */
/*   Manuel Serrano (c)       Tue Apr 23 11:36:11 CEST 2002                  */
/*===========================================================================*/

/* GC selection */
#define THE_GC BOEHM_GC

#include <bigloo.h>
#include <simple.h>

extern obj_t BGl_modulezd2initializa7ationz75zzsimplezd2mmzd2(long, char *);
extern obj_t BGl_modulezd2initializa7ationz75zz__errorz00(long, char *);
extern obj_t BGl_modulezd2initializa7ationz75zz__readerz00(long, char *);
extern obj_t BGl_modulezd2initializa7ationz75zz__r4_numbers_6_5_fixnumz00(long, char *);
extern obj_t BGl_modulezd2initializa7ationz75zz__r4_output_6_10_3z00(long, char *);
extern obj_t open_input_string(obj_t);
extern obj_t BGl_readz00zz__readerz00(obj_t);
static obj_t BGl_testzd2simplezd2mmz00zzsimplezd2mmzd2(long);
extern obj_t BGl_printz00zz__r4_output_6_10_3z00(obj_t);
extern int simple_get_x(struct Simple *);
extern obj_t BGl_modulezd2initzd2errorz00zz__errorz00(char *, char *);
extern long BGl_stringzd2ze3integerz31zz__r4_numbers_6_5_fixnumz00(obj_t, obj_t);
extern obj_t BGl_newlinez00zz__r4_output_6_10_3z00(obj_t);
extern obj_t BGl_mainz00zzsimplezd2mmzd2(obj_t);
static obj_t BGl_cnstzd2initzd2zzsimplezd2mmzd2();
extern void simple_set_x(struct Simple *, int);
extern bool_t BGl_zd3fxzd3zz__r4_numbers_6_5_fixnumz00(long, long);
extern obj_t bigloo_main(obj_t);
static obj_t BGl_requirezd2initializa7ationz75zzsimplezd2mmzd2 = BUNSPEC;
extern long BGl_bitzd2andzd2zz__bitz00(long, long);
extern obj_t BGl_bigloozd2typezd2errorz00zz__errorz00(obj_t, obj_t, obj_t);
extern struct Simple * make_simple_t();
static obj_t BGl_libraryzd2moduleszd2initz00zzsimplezd2mmzd2();
extern void simple_set_call_finalizers();
static obj_t BGl__mainz00zzsimplezd2mmzd2(obj_t, obj_t);
static obj_t __cnst[ 2 ] ;

DEFINE_EXPORT_PROCEDURE( BGl_mainzd2envzd2zzsimplezd2mmzd2, BgL_bgl__mainza700za7za7simpleza7d2mmza7d21081za7, BGl__mainz00zzsimplezd2mmzd2, 0L, 1 );
DEFINE_STRING( BGl_string1061z00zzsimplezd2mmzd2, BgL_bgl_string1061za700za7za7simpleza7d2mmza7d21082za7, "_main main ", 11 );
DEFINE_STRING( BGl_string1060z00zzsimplezd2mmzd2, BgL_bgl_string1060za700za7za7simpleza7d2mmza7d21083za7, "bstring", 7 );
DEFINE_STRING( BGl_string1059z00zzsimplezd2mmzd2, BgL_bgl_string1059za700za7za7simpleza7d2mmza7d21084za7, "pair", 4 );

extern int _bigloo_main();


int bigloo_abort(long n) { return n; }

int BIGLOO_MAIN(int argc, char *argv[], char *env[])
{_bigloo_main(argc, argv,env, &bigloo_main);}



/* module-initialization */
obj_t BGl_modulezd2initializa7ationz75zzsimplezd2mmzd2(long BgL_checksumz00_76, char * BgL_fromz00_77)
{ AN_OBJECT;
 { 
   { 
     bool_t BgL_test1078z00_78;
     { 
       obj_t BgL_arg1079z00_79;
       { 
	 long BgL_auxz00_82;
	 BgL_auxz00_82 = 
	   BGl_bitzd2andzd2zz__bitz00(BgL_checksumz00_76, ((long)489556628)); 
	 BgL_arg1079z00_79 = 
	   BINT(BgL_auxz00_82); } 
       BgL_test1078z00_78 = 
	 BGl_zd3fxzd3zz__r4_numbers_6_5_fixnumz00(
						  (long)CINT(BgL_arg1079z00_79), BgL_checksumz00_76); } 
     if(BgL_test1078z00_78)
       { 
	 if(
	    CBOOL(BGl_requirezd2initializa7ationz75zzsimplezd2mmzd2))
	   { 
	     BGl_requirezd2initializa7ationz75zzsimplezd2mmzd2 = 
	       BBOOL(((bool_t)0)); 
	     BGl_libraryzd2moduleszd2initz00zzsimplezd2mmzd2(); 
	     BGl_cnstzd2initzd2zzsimplezd2mmzd2(); 
	     return BUNSPEC;}  else 
	       { 
		 return BUNSPEC;} }  else 
		   { 
		     return 
		       BGl_modulezd2initzd2errorz00zz__errorz00("simple-mm", BgL_fromz00_77);} } } 
}



/* bigloo_main */
obj_t bigloo_main(obj_t BgL_argvz00_80)
{ AN_OBJECT;
 { 
   BGl_modulezd2initializa7ationz75zzsimplezd2mmzd2(((long)0), "simple-mm"); 
   { 
     obj_t BgL_arg1080z00_81;
     BgL_arg1080z00_81 = 
       BGl_mainz00zzsimplezd2mmzd2(BgL_argvz00_80); 
     return 
       BIGLOO_EXIT(BgL_arg1080z00_81);} } 
}



/* library-modules-init */
obj_t BGl_libraryzd2moduleszd2initz00zzsimplezd2mmzd2()
{ AN_OBJECT;
 { /* b-simple.scm 1 */
   BGl_modulezd2initializa7ationz75zz__readerz00(((long)0), "simple-mm"); 
   BGl_modulezd2initializa7ationz75zz__r4_output_6_10_3z00(((long)0), "simple-mm"); 
   BGl_modulezd2initializa7ationz75zz__r4_numbers_6_5_fixnumz00(((long)0), "simple-mm"); 
   BGl_modulezd2initializa7ationz75zz__errorz00(((long)0), "simple-mm"); 
   return BUNSPEC;} 
}



/* cnst-init */
obj_t BGl_cnstzd2initzd2zzsimplezd2mmzd2()
{ AN_OBJECT;
 { /* b-simple.scm 1 */
   { /* b-simple.scm 1 */
     obj_t BgL_cportz00_69;
     BgL_cportz00_69 = 
       open_input_string(BGl_string1061z00zzsimplezd2mmzd2); 
     { 
       long BgL_iz00_70;
       BgL_iz00_70 = ((long)1); 
     BgL_loopz00_71:
       { /* b-simple.scm 1 */
	 bool_t BgL_test1062z00_72;
	 BgL_test1062z00_72 = 
	   (BgL_iz00_70==((long)-1)); 
	 if(BgL_test1062z00_72)
	   { /* b-simple.scm 1 */
	     return BUNSPEC;}  else 
	       { /* b-simple.scm 1 */
		 { /* b-simple.scm 1 */
		   obj_t BgL_arg1071z00_73;
		   { /* b-simple.scm 1 */
		     obj_t BgL_list1072z00_74;
		     BgL_list1072z00_74 = 
		       MAKE_PAIR(BgL_cportz00_69, BNIL); 
		     BgL_arg1071z00_73 = 
		       BGl_readz00zz__readerz00(BgL_list1072z00_74); } 
		   { /* b-simple.scm 1 */
		     int BgL_auxz00_106;
		     BgL_auxz00_106 = 
		       (int)(BgL_iz00_70); 
		     CNST_TABLE_SET(BgL_auxz00_106, BgL_arg1071z00_73); } } 
		 { /* b-simple.scm 1 */
		   int BgL_auxz00_75;
		   { /* b-simple.scm 1 */
		     long BgL_auxz00_109;
		     BgL_auxz00_109 = 
		       (BgL_iz00_70-((long)1)); 
		     BgL_auxz00_75 = 
		       (int)(BgL_auxz00_109); } 
		   { 
		     long BgL_iz00_112;
		     BgL_iz00_112 = 
		       (long)(BgL_auxz00_75); 
		     BgL_iz00_70 = BgL_iz00_112; 
		     goto BgL_loopz00_71;} } } } } } } 
}



/* main */
obj_t BGl_mainz00zzsimplezd2mmzd2(obj_t BgL_argvz00_6)
{ AN_OBJECT;
 { /* b-simple.scm 46 */
   { /* b-simple.scm 47 */
     bool_t BgL_test1025z00_30;
     { /* b-simple.scm 47 */
       obj_t BgL_arg1034z00_34;
       { /* b-simple.scm 47 */
	 obj_t BgL_pairz00_49;
	 BgL_pairz00_49 = BgL_argvz00_6; 
	 BgL_arg1034z00_34 = 
	   CDR(BgL_pairz00_49); } 
       { /* b-simple.scm 47 */
	 obj_t BgL_objz00_50;
	 BgL_objz00_50 = BgL_arg1034z00_34; 
	 BgL_test1025z00_30 = 
	   PAIRP(BgL_objz00_50); } } 
     if(BgL_test1025z00_30)
       { /* b-simple.scm 48 */
	 long BgL_arg1026z00_31;
	 { /* b-simple.scm 48 */
	   obj_t BgL_arg1030z00_32;
	   { /* b-simple.scm 48 */
	     obj_t BgL_pairz00_51;
	     BgL_pairz00_51 = BgL_argvz00_6; 
	     { /* b-simple.scm 48 */
	       obj_t BgL_arg1157z00_52;
	       { /* b-simple.scm 48 */
		 obj_t BgL_pairz00_53;
		 BgL_pairz00_53 = BgL_pairz00_51; 
		 BgL_arg1157z00_52 = 
		   CDR(BgL_pairz00_53); } 
	       { /* b-simple.scm 48 */
		 obj_t BgL_pairz00_54;
		 { /* b-simple.scm 48 */
		   obj_t BgL_aux1050z00_63;
		   BgL_aux1050z00_63 = BgL_arg1157z00_52; 
		   { /* b-simple.scm 48 */
		     bool_t BgL_test1051z00_64;
		     BgL_test1051z00_64 = 
		       PAIRP(BgL_aux1050z00_63); 
		     if(BgL_test1051z00_64)
		       { /* b-simple.scm 48 */
			 BgL_pairz00_54 = BgL_aux1050z00_63; }  else 
			   { /* b-simple.scm 48 */
			     BGl_bigloozd2typezd2errorz00zz__errorz00(
								      CNST_TABLE_REF(((long)0)), BGl_string1059z00zzsimplezd2mmzd2, BgL_aux1050z00_63); 
			     exit( -1 );} } } 
		 BgL_arg1030z00_32 = 
		   CAR(BgL_pairz00_54); } } } 
	   { /* b-simple.scm 48 */
	     obj_t BgL_list1031z00_33;
	     BgL_list1031z00_33 = BNIL; 
	     { /* b-simple.scm 48 */
	       obj_t BgL_auxz00_124;
	       { /* b-simple.scm 48 */
		 obj_t BgL_aux1052z00_65;
		 BgL_aux1052z00_65 = BgL_arg1030z00_32; 
		 { /* b-simple.scm 48 */
		   bool_t BgL_test1054z00_66;
		   BgL_test1054z00_66 = 
		     STRINGP(BgL_aux1052z00_65); 
		   if(BgL_test1054z00_66)
		     { /* b-simple.scm 48 */
		       BgL_auxz00_124 = BgL_aux1052z00_65
			 ; }  else 
			   { /* b-simple.scm 48 */
			     BGl_bigloozd2typezd2errorz00zz__errorz00(
								      CNST_TABLE_REF(((long)0)), BGl_string1060z00zzsimplezd2mmzd2, BgL_aux1052z00_65); 
			     exit( -1 );} } } 
	       BgL_arg1026z00_31 = 
		 BGl_stringzd2ze3integerz31zz__r4_numbers_6_5_fixnumz00(BgL_auxz00_124, BgL_list1031z00_33); } } } 
	 return 
	   BGl_testzd2simplezd2mmz00zzsimplezd2mmzd2(BgL_arg1026z00_31);}  else 
	     { /* b-simple.scm 47 */
	       return 
		 BGl_testzd2simplezd2mmz00zzsimplezd2mmzd2(((long)10000000));} } } 
}



/* _main */
obj_t BGl__mainz00zzsimplezd2mmzd2(obj_t BgL_envz00_59, obj_t BgL_argvz00_60)
{ AN_OBJECT;
 { /* b-simple.scm 46 */
   { /* b-simple.scm 47 */
     obj_t BgL_auxz00_133;
     { /* b-simple.scm 47 */
       obj_t BgL_aux1055z00_67;
       BgL_aux1055z00_67 = BgL_argvz00_60; 
       { /* b-simple.scm 47 */
	 bool_t BgL_test1058z00_68;
	 BgL_test1058z00_68 = 
	   PAIRP(BgL_aux1055z00_67); 
	 if(BgL_test1058z00_68)
	   { /* b-simple.scm 47 */
	     BgL_auxz00_133 = BgL_aux1055z00_67
	       ; }  else 
		 { /* b-simple.scm 47 */
		   BGl_bigloozd2typezd2errorz00zz__errorz00(
							    CNST_TABLE_REF(((long)1)), BGl_string1059z00zzsimplezd2mmzd2, BgL_aux1055z00_67); 
		   exit( -1 );} } } 
     return 
       BGl_mainz00zzsimplezd2mmzd2(BgL_auxz00_133);} } 
}



/* test-simple-mm */
obj_t BGl_testzd2simplezd2mmz00zzsimplezd2mmzd2(long BgL_lz00_7)
{ AN_OBJECT;
 { /* b-simple.scm 51 */
   simple_set_call_finalizers(); 
   { /* b-simple.scm 53 */
     struct Simple * BgL_az00_35;
     BgL_az00_35 = 
       make_simple_t(); 
     { /* b-simple.scm 54 */
       int BgL_auxz00_142;
       BgL_auxz00_142 = 
	 (int)(((long)5)); 
       simple_set_x(BgL_az00_35, BgL_auxz00_142); } 
     { /* b-simple.scm 55 */
       int BgL_arg1035z00_36;
       BgL_arg1035z00_36 = 
	 simple_get_x(BgL_az00_35); 
       { /* b-simple.scm 55 */
	 obj_t BgL_list1036z00_37;
	 { /* b-simple.scm 55 */
	   obj_t BgL_auxz00_146;
	   BgL_auxz00_146 = 
	     BINT(BgL_arg1035z00_36); 
	   BgL_list1036z00_37 = 
	     MAKE_PAIR(BgL_auxz00_146, BNIL); } 
	 BGl_printz00zz__r4_output_6_10_3z00(BgL_list1036z00_37); } } 
     { 
       long BgL_iz00_38;
       BgL_iz00_38 = BgL_lz00_7; 
     BgL_loopz00_39:
       { /* b-simple.scm 57 */
	 bool_t BgL_test1037z00_40;
	 { /* b-simple.scm 57 */
	   long BgL_n1z00_55;long BgL_n2z00_56;
	   BgL_n1z00_55 = BgL_iz00_38; 
	   BgL_n2z00_56 = ((long)0); 
	   BgL_test1037z00_40 = 
	     (BgL_n1z00_55>BgL_n2z00_56); } 
	 if(BgL_test1037z00_40)
	   { /* b-simple.scm 57 */
	     BgL_az00_35 = 
	       make_simple_t(); 
	     { /* b-simple.scm 60 */
	       long BgL_arg1045z00_41;
	       { /* b-simple.scm 60 */
		 long BgL_za71za7_57;long BgL_za72za7_58;
		 BgL_za71za7_57 = BgL_iz00_38; 
		 BgL_za72za7_58 = ((long)1); 
		 BgL_arg1045z00_41 = 
		   (BgL_za71za7_57-BgL_za72za7_58); } 
	       { 
		 long BgL_iz00_154;
		 BgL_iz00_154 = BgL_arg1045z00_41; 
		 BgL_iz00_38 = BgL_iz00_154; 
		 goto BgL_loopz00_39;} } }  else 
		   { /* b-simple.scm 57 */((bool_t)0); } } } 
     { /* b-simple.scm 61 */
       obj_t BgL_list1046z00_42;
       BgL_list1046z00_42 = BNIL; 
       return 
	 BGl_newlinez00zz__r4_output_6_10_3z00(BgL_list1046z00_42);} } } 
}

