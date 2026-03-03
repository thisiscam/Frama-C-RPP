/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int negate(int x) { return -x; }

/*@ assigns \result \from x; */
int identity(int x) { return x; }

typedef int (*transform_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int transform(transform_fn fn, int x) {
  /*@ calls negate, identity; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      \callset(\call(transform, &negate, x1, id1),
               \call(transform, &negate, x2, id2)) ==>
      x1 == x2 ==> \callresult(id1) == \callresult(id2);
*/
