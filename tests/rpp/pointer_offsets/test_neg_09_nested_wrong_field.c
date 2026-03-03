/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Wrong field at nested level.
   Outer has two inner pointers: 'left' and 'right'.
   Function reads o->left->val but property constrains o->right->val.
   Tests that RPP preserves the correct field at the first dereference level
   when generating nested TMem chains. */

typedef struct { int val; } Leaf;
typedef struct { Leaf *left; Leaf *right; } Tree;

/*@ requires \valid(t) && \valid(t->left) && \valid(t->right);
  @ assigns \result \from t->left->val;
*/
int read_left(Tree *t) {
  return t->left->val;
}

/*@ relational
      \forall Tree *t1, *t2;
      \callset(\call(read_left, t1, id1), \call(read_left, t2, id2)) ==>
      \at(t1->right->val, Pre_id1) == \at(t2->right->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
