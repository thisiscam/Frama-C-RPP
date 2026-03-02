/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int increment(int x) { return x + 1; }

typedef int (*fn_type)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int invoke(fn_type fn, int x) {
  /*@ calls increment; */
  return fn(x);
}

/*@ relational
      \forall int x1;
      \callset(\call(invoke, &increment, x1, id1)) ==>
      \callresult(id1) == x1 + 1;
*/
