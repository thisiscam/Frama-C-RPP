/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Wrong array range in precondition.
   Function sums a[0]+a[1]+a[2] (3 elements), but property only
   constrains a[0] and a[1] equal. The missing a[2] constraint
   makes the conclusion false.
   This is a more subtle array test than off-by-one: the constraint
   is partially correct but incomplete. */

/*@ requires n >= 3 && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], n;
*/
int sum3(int *a, int n) {
  return a[0] + a[1] + a[2];
}

/*@ relational
      \forall int *a1, *a2, int n;
      \callset(\call(sum3, a1, n, id1), \call(sum3, a2, n, id2)) ==>
      \at(a1[0], Pre_id1) == \at(a2[0], Pre_id2) ==>
      \at(a1[1], Pre_id1) == \at(a2[1], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
