/* run.config
   OPT: -rpp
*/

/* Negative test: \call with a label, which is not allowed.
   \call must be used without labels. */

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
      \callset(\call{Pre}(step, &inc, x1, id1)) ==>
      x1 == x2;
*/
