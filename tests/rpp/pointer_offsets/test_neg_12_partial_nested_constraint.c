/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Partial constraint on nested struct.
   Function reads BOTH o->inner->val AND o->tag, but the property
   only constrains o->inner->val equal across calls.
   The missing o->tag constraint makes the property false.
   This is the nested-pointer version of test_neg_03. */

typedef struct { int val; } Inner;
typedef struct { Inner *inner; int tag; } Outer;

/*@ requires \valid(o) && \valid(o->inner);
  @ assigns \result \from o->inner->val, o->tag;
*/
int tagged_read(Outer *o) {
  return o->inner->val + o->tag;
}

/*@ relational
      \forall Outer *o1, *o2;
      \callset(\call(tagged_read, o1, id1), \call(tagged_read, o2, id2)) ==>
      \at(o1->inner->val, Pre_id1) == \at(o2->inner->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
