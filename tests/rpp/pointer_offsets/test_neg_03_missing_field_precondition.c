/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Missing field precondition.
   Function result depends on BOTH p->x and p->y, but the relational
   property only constrains p->x equal across calls.
   RPP should process this fine, but WP cannot prove the resulting
   check because p->y can differ between calls. */

typedef struct { int x; int y; } Point;

/*@ requires \valid(p);
  @ assigns \result \from p->x, p->y;
*/
int sum_point(Point *p) {
  return p->x + p->y;
}

/*@ relational
      \forall Point *p1, *p2;
      \callset(\call(sum_point, p1, id1), \call(sum_point, p2, id2)) ==>
      \at(p1->x, Pre_id1) == \at(p2->x, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
