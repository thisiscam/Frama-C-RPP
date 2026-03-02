/* run.config
   OPT: -rpp
*/
/* What this tests: Category B — constant index other than 0 (a[3]) */

/*@ requires n > 3 && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], n;
*/
int fourth_elem(int *a, int n) {
  return a[3];
}

/*@ relational
      \forall int *a1, *a2, int n;
      \callset(\call(fourth_elem, a1, n, id1), \call(fourth_elem, a2, n, id2)) ==>
      \at(a1[3], Pre_id1) == \at(a2[3], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
