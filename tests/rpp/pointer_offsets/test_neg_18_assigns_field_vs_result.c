/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Assigns clause targets one field, property queries another.
   Function assigns acc->total (adds v to total), but the relational property
   compares acc->count in post-state. Since the function does NOT modify count,
   and the property doesn't constrain count's pre-state to be equal,
   the conclusion is unprovable.
   Tests that RPP correctly tracks which fields are modified vs. read
   through the assigns/from side-effect analysis. */

typedef struct { int count; int total; } Accum;

/*@ requires \valid(acc);
  @ assigns acc->total \from acc->total, v;
*/
void add_to_total(Accum *acc, int v) {
  acc->total += v;
}

/*@ relational
      \forall Accum *a1, *a2, int v;
      \callset(\call(add_to_total, a1, v, id1), \call(add_to_total, a2, v, id2)) ==>
      \at(a1->total, Pre_id1) == \at(a2->total, Pre_id2) ==>
      \at(a1->count, Post_id1) == \at(a2->count, Post_id2);
*/
