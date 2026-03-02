/* run.config
   OPT: -rpp
*/
/* What this tests: Category A — multiple (3+) fields read in a single relational predicate */

typedef struct { int r; int g; int b; int a; } Color;

/*@ requires \valid(c);
  @ assigns \result \from c->r, c->g, c->b;
*/
int luminance(Color *c) {
  return c->r + c->g + c->b;
}

/*@ relational
      \forall Color *c1, *c2;
      \callset(\call(luminance, c1, id1), \call(luminance, c2, id2)) ==>
      \at(c1->r, Pre_id1) == \at(c2->r, Pre_id2) ==>
      \at(c1->g, Pre_id1) == \at(c2->g, Pre_id2) ==>
      \at(c1->b, Pre_id1) == \at(c2->b, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
