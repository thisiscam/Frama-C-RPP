/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Impossible post-state claim.
   The function increments p->val, but the property claims the post-state
   value equals the pre-state value (i.e., claims the function is identity).
   RPP processes this; WP cannot prove it because val changes. */

typedef struct { int val; } Counter;

/*@ requires \valid(c);
  @ assigns c->val \from c->val;
*/
void increment(Counter *c) {
  c->val += 1;
}

/*@ relational
      \forall Counter *c1, *c2;
      \callset(\call(increment, c1, id1), \call(increment, c2, id2)) ==>
      \at(c1->val, Pre_id1) == \at(c2->val, Pre_id2) ==>
      \at(c1->val, Post_id1) == \at(c1->val, Pre_id1);
*/
