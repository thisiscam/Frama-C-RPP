/* run.config
   OPT: -rpp
*/
/* What this tests: Category F — same struct pointer appearing in two calls with different field access */

typedef struct { int a; int b; } AB;

/*@ requires \valid(p);
  @ assigns \result \from p->a;
*/
int get_a(AB *p) {
  return p->a;
}

/*@ relational
      \forall AB *p1, *p2;
      \callset(\call(get_a, p1, id1), \call(get_a, p2, id2)) ==>
      \at(p1->a, Pre_id1) == \at(p2->a, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
