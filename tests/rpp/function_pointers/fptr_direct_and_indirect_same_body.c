/* run.config
   OPT: -rpp
*/

/* Category G edge case: same function body has BOTH a direct call
   AND an indirect call through function pointer.
   inc is called directly (double_apply calls inc directly) and also
   appears as a calls target for the indirect call.
   This tests interaction between direct and indirect call handling. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int double_apply(unary_fn fn, int x) {
  int a, b;
  a = inc(x);            /* direct call to inc */
  /*@ calls inc; */
  b = fn(a);             /* indirect call through fn */
  return b;
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(double_apply, &inc, x1) == \callpure(double_apply, &inc, x2);
*/
