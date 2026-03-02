/* run.config
   OPT: -rpp
*/

/* Category G edge case: indirect call through function pointer
   inside a loop body. RPP's inlining must handle the calls annotation
   in a loop context. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ requires n >= 0;
  @ assigns \result \from fn, x, n;
*/
int apply_n_times(unary_fn fn, int x, int n) {
  int result = x;
  /*@ loop invariant 0 <= i <= n;
    @ loop assigns i, result;
    @ loop variant n - i;
  */
  for (int i = 0; i < n; i++) {
    /*@ calls inc; */
    result = fn(result);
  }
  return result;
}

/*@ relational
      \forall int x1, int x2, int n1;
      x1 == x2 ==> n1 >= 0 ==>
      \callpure(apply_n_times, &inc, x1, n1) ==
        \callpure(apply_n_times, &inc, x2, n1);
*/
