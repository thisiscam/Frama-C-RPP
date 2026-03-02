/* run.config
   OPT: -rpp
*/
/* What this tests: Category D — multiple assigns clauses with different field offsets + post-state */

typedef struct { int lo; int hi; } Interval;

/*@ requires \valid(iv);
  @ assigns iv->lo \from iv->lo, delta;
  @ assigns iv->hi \from iv->hi, delta;
*/
void shift(Interval *iv, int delta) {
  iv->lo += delta;
  iv->hi += delta;
}

/*@ relational
      \forall Interval *i1, *i2, int delta;
      \callset(\call(shift, i1, delta, id1), \call(shift, i2, delta, id2)) ==>
      \at(i1->lo, Pre_id1) == \at(i2->lo, Pre_id2) ==>
      \at(i1->hi, Pre_id1) == \at(i2->hi, Pre_id2) ==>
      \at(i1->lo, Post_id1) == \at(i2->lo, Post_id2) &&
      \at(i1->hi, Post_id1) == \at(i2->hi, Post_id2);
*/
