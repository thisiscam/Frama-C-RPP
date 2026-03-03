/* run.config
   OPT: -rpp
*/
/* What this tests: Category B — pointer-to-pointer indexing (*a)[i] */

/*@ requires \valid(a) && \valid((*a)+(0..n-1)) && n > 0;
  @ assigns \result \from (*a)[0..n-1], n;
*/
int deref_first(int **a, int n) {
  return (*a)[0];
}

/*@ relational
      \forall int **a1, **a2, int n;
      \callset(\call(deref_first, a1, n, id1), \call(deref_first, a2, n, id2)) ==>
      \at((*a1)[0], Pre_id1) == \at((*a2)[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
