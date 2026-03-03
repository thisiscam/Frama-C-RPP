/* run.config
   OPT: -rpp
*/
/* What this tests: Category A — write to one struct field, read another unchanged field */

typedef struct { int x; int y; } Pair;

/*@ requires \valid(p);
  @ assigns p->x \from p->x, v;
*/
void set_x(Pair *p, int v) {
  p->x = v;
}

/*@ relational
      \forall Pair *p1, *p2, int v;
      \callset(\call(set_x, p1, v, id1), \call(set_x, p2, v, id2)) ==>
      \at(p1->x, Pre_id1) == \at(p2->x, Pre_id2) ==>
      \at(p1->x, Post_id1) == \at(p2->x, Post_id2);
*/
