/* run.config
   OPT: -rpp
*/
/* What this tests: Category D — assigns a[i]: single array element as side-effect location */

/*@ requires \valid(a+(0..n-1)) && 0 <= i < n;
  @ assigns a[0..n-1] \from a[0..n-1], v;
*/
void set_elem(int *a, int n, int i, int v) {
  a[i] = v;
}

/*@ relational
      \forall int *a1, *a2, int n, int i, int v;
      \callset(\call(set_elem, a1, n, i, v, id1), \call(set_elem, a2, n, i, v, id2)) ==>
      \at(a1[i], Pre_id1) == \at(a2[i], Pre_id2) ==>
      \at(a1[i], Post_id1) == \at(a2[i], Post_id2);
*/
