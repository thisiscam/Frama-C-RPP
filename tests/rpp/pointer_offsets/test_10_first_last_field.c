/* run.config
   OPT: -rpp
*/
/* What this tests: Category A — first vs last field of a large struct (offset zero vs non-zero) */

typedef struct { int a; int b; int c; int d; int e; } Big;

/*@ requires \valid(s);
  @ assigns \result \from s->a, s->e;
*/
int first_last(Big *s) {
  return s->a + s->e;
}

/*@ relational
      \forall Big *s1, *s2;
      \callset(\call(first_last, s1, id1), \call(first_last, s2, id2)) ==>
      \at(s1->a, Pre_id1) == \at(s2->a, Pre_id2) ==>
      \at(s1->e, Pre_id1) == \at(s2->e, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
