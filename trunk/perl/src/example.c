/* example.c : from swig user's manual version 1.1, page 12 */

double My_variable = 3.0;

/* compute factorial of n */
int fact (int n) {
  if (n <= 1) 
    return 1;
  else
    return n * fact(n-1);
}

/* compute n mod m */
int my_mod(int n, int m) {
  return (n % m);
}

