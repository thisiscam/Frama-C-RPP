/* run.config
   OPT: -rpp
*/
/* What this tests: Category G — struct with single field (offset effectively TNoOffset) */

typedef struct { int val; } Wrapper;

/*@ requires \valid(w);
  @ assigns \result \from w->val;
*/
int unwrap(Wrapper *w) {
  return w->val;
}

/*@ relational
      \forall Wrapper *w1, *w2;
      \callset(\call(unwrap, w1, id1), \call(unwrap, w2, id2)) ==>
      \at(w1->val, Pre_id1) == \at(w2->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
