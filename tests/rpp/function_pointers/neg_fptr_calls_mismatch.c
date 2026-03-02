/* run.config
   OPT: -rpp
*/

/* Negative test: duplicate call IDs in \callset.
   Both \call entries use the same id "id1". */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
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
      \callset(\call(step, &inc, x1, id1), \call(step, &inc, x2, id1)) ==>
      x1 == x2 ==>
      \callresult(id1) == \callresult(id1);
*/
