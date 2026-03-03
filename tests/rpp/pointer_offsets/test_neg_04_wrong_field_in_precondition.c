/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Wrong field in precondition.
   Function reads p->x for its result, but the relational property
   constrains p->y equal. The constraint is on the WRONG field.
   RPP generates the wrapper faithfully; WP cannot prove it. */

typedef struct { int x; int y; } Point;

/*@ requires \valid(p);
  @ assigns \result \from p->x;
*/
int get_x(Point *p) {
  return p->x;
}

/*@ relational
      \forall Point *p1, *p2;
      \callset(\call(get_x, p1, id1), \call(get_x, p2, id2)) ==>
      \at(p1->y, Pre_id1) == \at(p2->y, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
