/* run.config
   OPT: -rpp
*/

typedef struct { int count; int total; } Accum;

/*@ requires \valid(acc);
  @ assigns acc->count \from acc->count;
  @ assigns acc->total \from acc->total, v;
*/
void accumulate(Accum *acc, int v) {
  acc->count += 1;
  acc->total += v;
}

/*@ relational
      \forall Accum *a1, *a2, int v;
      \callset(\call(accumulate, a1, v, id1), \call(accumulate, a2, v, id2)) ==>
      \at(a1->count, Pre_id1) == \at(a2->count, Pre_id2) ==>
      \at(a1->total, Pre_id1) == \at(a2->total, Pre_id2) ==>
      \at(a1->count, Post_id1) == \at(a2->count, Post_id2);
*/
