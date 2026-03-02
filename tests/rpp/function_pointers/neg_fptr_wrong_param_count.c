/* run.config
   OPT: -rpp
*/

/* Negative test: \callpure with wrong number of arguments.
   apply takes 2 params (fn, x) but we pass 3. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply, &inc, x1, 42) == \callpure(apply, &inc, x2, 42);
*/
