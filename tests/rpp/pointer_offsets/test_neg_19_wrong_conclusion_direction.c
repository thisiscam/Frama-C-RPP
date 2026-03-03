/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Correct preconditions but wrong conclusion direction.
   Function get_x returns p->x. The property correctly constrains p1->x == p2->x
   but then claims \callresult(id1) > \callresult(id2) (strict inequality).
   Since both calls return the same value when p->x is equal,
   the strict inequality is impossible.
   This tests that the relational property is checked faithfully —
   RPP must not accidentally weaken > to == or >=. */

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
      \at(p1->x, Pre_id1) == \at(p2->x, Pre_id2) ==>
      \callresult(id1) > \callresult(id2);
*/
