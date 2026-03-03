/* run.config
   OPT: -rpp
*/

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
      \at(p1->y, Pre_id1) == \at(p2->y, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
