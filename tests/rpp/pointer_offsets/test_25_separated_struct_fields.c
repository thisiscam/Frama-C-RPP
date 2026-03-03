/* run.config
   OPT: -rpp
*/
/* What this tests: Category F — two struct pointers with field separation */

typedef struct { int x; int y; } Point;

/*@ requires \valid(p);
  @ assigns p->x \from p->x, dx;
*/
void move_x(Point *p, int dx) {
  p->x += dx;
}

/*@ relational
      \forall Point *p1, *p2, int dx;
      \callset(\call(move_x, p1, dx, id1), \call(move_x, p2, dx, id2)) ==>
      \at(p1->x, Pre_id1) == \at(p2->x, Pre_id2) ==>
      \at(p1->x, Post_id1) == \at(p2->x, Post_id2);
*/
