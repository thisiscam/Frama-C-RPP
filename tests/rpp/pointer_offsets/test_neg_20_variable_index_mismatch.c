/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Variable index mismatch.
   Function reads a[i], but the property constrains a[j] for a DIFFERENT
   universally quantified variable. Since i != j in general,
   the constraint on a[j] says nothing about a[i].
   Tests that TIndex with variable offsets is preserved correctly
   and not collapsed or ignored. */

/*@ requires 0 <= i < n && 0 <= j < n && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], i;
*/
int read_at(int *a, int n, int i, int j) {
  return a[i];
}

/*@ relational
      \forall int *a1, *a2, int n, int i, int j;
      \callset(\call(read_at, a1, n, i, j, id1), \call(read_at, a2, n, i, j, id2)) ==>
      \at(a1[j], Pre_id1) == \at(a2[j], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
