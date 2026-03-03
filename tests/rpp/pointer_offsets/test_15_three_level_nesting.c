/* run.config
   OPT: -rpp
*/
/* What this tests: Category C — three levels of nesting: p->a->b->val */

typedef struct { int val; } Leaf;
typedef struct { Leaf *b; } Mid;
typedef struct { Mid *a; } Top;

/*@ requires \valid(p) && \valid(p->a) && \valid(p->a->b);
  @ assigns \result \from p->a->b->val;
*/
int deep_read(Top *p) {
  return p->a->b->val;
}

/*@ relational
      \forall Top *p1, *p2;
      \callset(\call(deep_read, p1, id1), \call(deep_read, p2, id2)) ==>
      \at(p1->a->b->val, Pre_id1) == \at(p2->a->b->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
