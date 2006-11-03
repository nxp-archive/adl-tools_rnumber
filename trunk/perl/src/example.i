//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

/* from swig manual version 1.1, page 13 */
%module example
%{
  /* put headers and other declarations here    */
  extern double My_variable;

  %}

extern double My_variable;
extern int fact(int);
extern int my_mod(int n, int m);

