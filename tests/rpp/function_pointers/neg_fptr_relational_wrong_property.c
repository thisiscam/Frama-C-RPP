/* run.config
   OPT: -rpp
*/

/* Negative test: the relational property is mathematically FALSE.
   inc adds 1, so the two calls should differ by 0 when given the same input,
   NOT by 42. WP should fail to prove this. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/* This property is provably false: apply(&inc, x1) - apply(&inc, x2) == 42
   when x1 == x2 means 0 == 42 which is false. */
/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply, &inc, x1) - \callpure(apply, &inc, x2) == 42;
*/
