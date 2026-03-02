/* run.config
   OPT: -rpp
*/
/* What this tests: Category G — 4+ levels deep type to test recursion depth */

typedef struct { int v; } L4;
typedef struct { L4 *d; } L3;
typedef struct { L3 *c; } L2;
typedef struct { L2 *b; } L1;

/*@ requires \valid(p) && \valid(p->b) && \valid(p->b->c) && \valid(p->b->c->d);
  @ assigns \result \from p->b->c->d->v;
*/
int read_deep4(L1 *p) {
  return p->b->c->d->v;
}

/*@ relational
      \forall L1 *p1, *p2;
      \callset(\call(read_deep4, p1, id1), \call(read_deep4, p2, id2)) ==>
      \at(p1->b->c->d->v, Pre_id1) == \at(p2->b->c->d->v, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
