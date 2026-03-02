/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Off-by-one array index.
   Function reads a[0] but property constrains a[1] equal.
   This targets array indexing (TIndex) with a concrete wrong index.
   RPP generates the wrapper; WP cannot prove it. */

/*@ requires n >= 2 && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], n;
*/
int first(int *a, int n) {
  return a[0];
}

/*@ relational
      \forall int *a1, *a2, int n;
      \callset(\call(first, a1, n, id1), \call(first, a2, n, id2)) ==>
      \at(a1[1], Pre_id1) == \at(a2[1], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
