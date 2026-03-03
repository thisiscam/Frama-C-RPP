/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x;
  @ ensures \result >= x;
*/
int clamp_pos(int x) { return (x > 0) ? x : 0; }

/*@ assigns \result \from x;
  @ ensures \result <= x;
*/
int clamp_neg(int x) { return (x < 0) ? x : 0; }

typedef int (*filter_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int filtered(filter_fn fn, int x) {
  /*@ calls clamp_pos, clamp_neg; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      \callset(\call(filtered, &clamp_pos, x1, id1),
               \call(filtered, &clamp_pos, x2, id2)) ==>
      x1 == x2 ==> \callresult(id1) == \callresult(id2);
*/
