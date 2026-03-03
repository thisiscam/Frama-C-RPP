/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST: RPP must reject — same pointer shared across traces
   with 3-level deep nested field access (p->b->c->v).
   Tests that extract_base_lvar recurses through 3 levels of TMem
   to correctly identify the shared base variable 'p'. */

typedef struct { int v; } C;
typedef struct { C *c; } B;
typedef struct { B *b; } A;

/*@ requires \valid(p) && \valid(p->b) && \valid(p->b->c);
  @ assigns \result \from p->b->c->v;
*/
int deep_read(A *p) {
  return p->b->c->v;
}

/*@ relational
      \forall A *p;
      \callset(\call(deep_read, p, id1), \call(deep_read, p, id2)) ==>
      \at(p->b->c->v, Pre_id1) == \at(p->b->c->v, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
