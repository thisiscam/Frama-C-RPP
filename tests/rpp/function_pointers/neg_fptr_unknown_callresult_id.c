/* run.config
   OPT: -rpp
*/

/* Negative test: \callset with three \calls but using \callresult
   for an id that doesn't exist (typo/wrong name). */

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
      \callset(\call(step, &inc, x1, id1), \call(step, &inc, x2, id2)) ==>
      x1 == x2 ==>
      \callresult(id_typo) == \callresult(id2);
*/
