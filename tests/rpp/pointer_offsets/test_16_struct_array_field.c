/* run.config
   OPT: -rpp
*/
/* What this tests: Category C — struct containing array field: p->arr[i] */

typedef struct { int arr[10]; int len; } Vec;

/*@ requires \valid(p) && p->len > 0 && p->len <= 10;
  @ assigns \result \from p->arr[0..p->len-1], p->len;
*/
int vec_first(Vec *p) {
  return p->arr[0];
}

/*@ relational
      \forall Vec *v1, *v2;
      \callset(\call(vec_first, v1, id1), \call(vec_first, v2, id2)) ==>
      \at(v1->arr[0], Pre_id1) == \at(v2->arr[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
