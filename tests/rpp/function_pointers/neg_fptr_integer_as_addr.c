/* run.config
   OPT: -rpp
*/

/* Negative test: passing an integer literal where a function address is expected.
   42 is not a valid function pointer. */

typedef int (*unary_fn)(int);

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

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
      \callpure(apply, 42, x1) == \callpure(apply, 42, x2);
*/
