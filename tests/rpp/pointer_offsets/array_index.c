/* run.config
   OPT: -rpp
*/

/*@ requires n > 0 && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], n;
*/
int first_elem(int *a, int n) {
  return a[0];
}

/*@ relational
      \forall int *a1, *a2, int n;
      \callset(\call(first_elem, a1, n, id1), \call(first_elem, a2, n, id2)) ==>
      \at(a1[0], Pre_id1) == \at(a2[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
