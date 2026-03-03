/* run.config
   OPT: -rpp
*/
/* What this tests: Category G — mix of \at(..., Pre_id) and \at(..., Post_id) for same field */

typedef struct { int val; } Box;

/*@ requires \valid(b);
  @ assigns b->val \from b->val, inc;
*/
void increment(Box *b, int inc) {
  b->val += inc;
}

/*@ relational
      \forall Box *b1, *b2, int inc;
      \callset(\call(increment, b1, inc, id1), \call(increment, b2, inc, id2)) ==>
      \at(b1->val, Pre_id1) == \at(b2->val, Pre_id2) ==>
      \at(b1->val, Post_id1) == \at(b2->val, Post_id2);
*/
