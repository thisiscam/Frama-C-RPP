/* run.config
   OPT: -rpp
*/
/* What this tests: Category B — pointer arithmetic style access *(a + i) vs a[i] */

/*@ requires 0 <= i < n && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], i;
*/
int get_via_ptr(int *a, int n, int i) {
  return *(a + i);
}

/*@ relational
      \forall int *a1, *a2, int n, int i;
      \callset(\call(get_via_ptr, a1, n, i, id1), \call(get_via_ptr, a2, n, i, id2)) ==>
      \at(*(a1 + i), Pre_id1) == \at(*(a2 + i), Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
