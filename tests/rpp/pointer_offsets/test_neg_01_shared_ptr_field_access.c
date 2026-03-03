/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST: RPP must reject — same struct pointer shared across two traces.
   This is the field-offset version of pointer_exception.c.
   Tests that extract_base_lvar correctly identifies 'p' as the base pointer
   even when the relational property references p->x (TMem with TField). */

typedef struct { int x; int y; } Point;

/*@ requires \valid(p);
  @ assigns p->x \from p->x, delta;
*/
void shift_x(Point *p, int delta) {
  p->x += delta;
}

/*@ relational
      \forall Point *p, int delta;
      \callset(\call(shift_x, p, delta, id1), \call(shift_x, p, delta, id2)) ==>
      \at(p->x, Pre_id1) == \at(p->x, Pre_id2) ==>
      \at(p->x, Post_id1) == \at(p->x, Post_id2);
*/
