/* run.config
   OPT: -rpp
*/

/* Negative test: \call with wrong number of function parameters.
   step takes (fn, x) but we only pass the fn argument plus id. */

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
      \callset(\call(step, &inc, id1)) ==>
      x1 == x2;
*/
