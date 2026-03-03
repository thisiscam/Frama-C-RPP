/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST: RPP must reject — same outer struct pointer used in both traces
   with nested field access (o->inner->val).
   Tests that extract_base_lvar recurses through TMem chains to find the
   shared base variable 'o'. */

typedef struct { int val; } Inner;
typedef struct { Inner *inner; } Outer;

/*@ requires \valid(o) && \valid(o->inner);
  @ assigns \result \from o->inner->val;
*/
int read_inner(Outer *o) {
  return o->inner->val;
}

/*@ relational
      \forall Outer *o;
      \callset(\call(read_inner, o, id1), \call(read_inner, o, id2)) ==>
      \at(o->inner->val, Pre_id1) == \at(o->inner->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
