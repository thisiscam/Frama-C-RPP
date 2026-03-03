/* run.config
   OPT: -rpp
*/

/* Negative test: \call with a numeric literal instead of an identifier
   as the last parameter. \call requires an identifier for the call ID. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*step_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int step(step_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      \callset(\call(step, &inc, x1, 999)) ==>
      x1 == x2;
*/
