/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

/*@ assigns \result \from x;
  @ ensures \result == x + 10;
*/
int inc10(int x) { return x + 10; }

typedef int (*step_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int step(step_fn fn, int x) {
  /*@ calls inc, inc10; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      \callset(\call(step, &inc, x1, id1),
               \call(step, &inc10, x2, id2)) ==>
      x1 == x2 ==>
      \callresult(id1) + 9 == \callresult(id2);
*/
