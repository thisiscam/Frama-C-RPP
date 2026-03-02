/* run.config
   OPT: -rpp
*/

typedef struct { int val; } Inner;
typedef struct { Inner *inner; int tag; } Outer;

/*@ requires \valid(o) && \valid(o->inner);
  @ assigns \result \from o->inner->val, o->tag;
*/
int read_nested(Outer *o) {
  return o->inner->val + o->tag;
}

/*@ relational
      \forall Outer *o1, *o2;
      \callset(\call(read_nested, o1, id1), \call(read_nested, o2, id2)) ==>
      \at(o1->tag, Pre_id1) == \at(o2->tag, Pre_id2) ==>
      \at(o1->inner->val, Pre_id1) == \at(o2->inner->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
