/* run.config
   OPT: -rpp
*/

/* Negative test: \callresult with a non-identifier argument.
   \callresult expects a plain identifier (the call id), not an expression. */

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
      \callset(\call(step, &inc, x1, id1)) ==>
      x1 == x2 ==>
      \callresult(x1 + 1) == 0;
*/
