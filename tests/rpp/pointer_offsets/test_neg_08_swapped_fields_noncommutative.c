/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Swapped fields with non-commutative operation.
   The function computes p->x - p->y (NOT commutative).
   The property constrains p1->x == p2->y AND p1->y == p2->x (swapped).
   If x=3, y=1: call1 returns 3-1=2, call2 returns 1-3=-2.
   So the conclusion \callresult(id1) == \callresult(id2) is FALSE.
   This tests that RPP faithfully preserves distinct field offsets
   rather than treating all fields interchangeably. */

typedef struct { int x; int y; } Pair;

/*@ requires \valid(p);
  @ assigns \result \from p->x, p->y;
*/
int diff_xy(Pair *p) {
  return p->x - p->y;
}

/*@ relational
      \forall Pair *p1, *p2;
      \callset(\call(diff_xy, p1, id1), \call(diff_xy, p2, id2)) ==>
      \at(p1->x, Pre_id1) == \at(p2->y, Pre_id2) ==>
      \at(p1->y, Pre_id1) == \at(p2->x, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
