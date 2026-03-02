/* run.config
   OPT: -rpp
*/
/* What this tests: Category E — pure function taking two struct-typed value parameters */

typedef struct { int x; int y; } Point;

/*@ assigns \result \from a.x, a.y, b.x, b.y; */
int manhattan(Point a, Point b) {
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  if (dx < 0) dx = -dx;
  if (dy < 0) dy = -dy;
  return dx + dy;
}

/*@ relational
      \forall Point a1, a2, Point b1, b2;
      a1.x == a2.x ==> a1.y == a2.y ==>
      b1.x == b2.x ==> b1.y == b2.y ==>
      \callpure(manhattan, a1, b1) == \callpure(manhattan, a2, b2);
*/
