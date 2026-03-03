/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Wrong field in post-state comparison.
   Function assigns acc->count (increments it), but property compares
   acc->total in post-state. Since total is NOT modified by the function,
   and the property doesn't constrain total's pre-state,
   the post-state comparison is meaningless.
   More precisely: the function only modifies count, and the property
   claims post-state COUNT equality but actually references TOTAL.
   Tests field-level precision in Post_id handling. */

typedef struct { int count; int total; } Accum;

/*@ requires \valid(acc);
  @ assigns acc->count \from acc->count;
*/
void tick(Accum *acc) {
  acc->count += 1;
}

/*@ relational
      \forall Accum *a1, *a2;
      \callset(\call(tick, a1, id1), \call(tick, a2, id2)) ==>
      \at(a1->count, Pre_id1) == \at(a2->count, Pre_id2) ==>
      \at(a1->total, Post_id1) == \at(a2->total, Post_id2);
*/
