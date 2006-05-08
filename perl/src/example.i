/* from swig manual version 1.1, page 13 */
%module example
%{
  /* put headers and other declarations here    */
  extern double My_variable;

  %}

extern double My_variable;
extern int fact(int);
extern int my_mod(int n, int m);

