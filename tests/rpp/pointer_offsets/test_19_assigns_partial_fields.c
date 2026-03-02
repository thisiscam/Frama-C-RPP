/* run.config
   OPT: -rpp
*/
/* What this tests: Category D — assigns p->field where only some fields modified, others preserved */

typedef struct { int x; int y; int z; } Vec3;

/*@ requires \valid(v);
  @ assigns v->x \from v->x;
  @ assigns v->y \from v->y;
*/
void negate_xy(Vec3 *v) {
  v->x = -v->x;
  v->y = -v->y;
}

/*@ relational
      \forall Vec3 *v1, *v2;
      \callset(\call(negate_xy, v1, id1), \call(negate_xy, v2, id2)) ==>
      \at(v1->x, Pre_id1) == \at(v2->x, Pre_id2) ==>
      \at(v1->y, Pre_id1) == \at(v2->y, Pre_id2) ==>
      \at(v1->x, Post_id1) == \at(v2->x, Post_id2);
*/
