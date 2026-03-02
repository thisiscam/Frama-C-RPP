/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Cross-field post-state comparison.
   Function assigns BOTH p->a and p->b (sets a=x, b=y).
   Property constrains pre-state of a and b equal across calls,
   but then claims p1->a in post-state equals p2->b in post-state.
   With a=x, b=y: post a1=x, post b2=y. These are NOT necessarily equal
   even if pre-states match, because a and b are set to DIFFERENT values.
   If x != y, then post a != post b. */

typedef struct { int a; int b; } Pair;

/*@ requires \valid(p);
  @ assigns p->a \from x;
  @ assigns p->b \from y;
*/
void set_both(Pair *p, int x, int y) {
  p->a = x;
  p->b = y;
}

/*@ relational
      \forall Pair *p1, *p2, int x, int y;
      \callset(\call(set_both, p1, x, y, id1), \call(set_both, p2, x, y, id2)) ==>
      \at(p1->a, Pre_id1) == \at(p2->a, Pre_id2) ==>
      \at(p1->b, Pre_id1) == \at(p2->b, Pre_id2) ==>
      \at(p1->a, Post_id1) == \at(p2->b, Post_id2);
*/
