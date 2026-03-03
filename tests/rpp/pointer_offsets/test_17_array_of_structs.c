/* run.config
   OPT: -rpp
*/
/* What this tests: Category C — array of structs: arr[i].field through a pointer */

typedef struct { int key; int val; } KV;

/*@ requires n > 0 && \valid(arr+(0..n-1));
  @ assigns \result \from arr[0..n-1], n;
*/
int first_key(KV *arr, int n) {
  return arr[0].key;
}

/*@ relational
      \forall KV *a1, *a2, int n;
      \callset(\call(first_key, a1, n, id1), \call(first_key, a2, n, id2)) ==>
      \at(a1[0].key, Pre_id1) == \at(a2[0].key, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
