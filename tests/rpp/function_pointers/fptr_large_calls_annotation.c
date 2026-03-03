/* run.config
   OPT: -rpp
*/

/* Category G stress test: large calls annotation with 6 targets.
   Tests scalability of branch generation with many possible callees. */

/*@ assigns \result \from x; ensures \result == x + 1; */
int f1(int x) { return x + 1; }
/*@ assigns \result \from x; ensures \result == x + 2; */
int f2(int x) { return x + 2; }
/*@ assigns \result \from x; ensures \result == x + 3; */
int f3(int x) { return x + 3; }
/*@ assigns \result \from x; ensures \result == x + 4; */
int f4(int x) { return x + 4; }
/*@ assigns \result \from x; ensures \result == x + 5; */
int f5(int x) { return x + 5; }
/*@ assigns \result \from x; ensures \result == x + 6; */
int f6(int x) { return x + 6; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int dispatch(unary_fn fn, int x) {
  /*@ calls f1, f2, f3, f4, f5, f6; */
  return fn(x);
}

/* Test 1: same target in both traces */
/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(dispatch, &f1, x1) == \callpure(dispatch, &f1, x2);
*/

/* Test 2: different targets, known difference */
/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(dispatch, &f6, x1) - \callpure(dispatch, &f1, x2) == 5;
*/

/* Test 3: callset across two different targets from the 6 */
/*@ relational
      \forall int x1, int x2;
      \callset(\call(dispatch, &f3, x1, id1),
               \call(dispatch, &f5, x2, id2)) ==>
      x1 == x2 ==>
      \callresult(id2) - \callresult(id1) == 2;
*/
