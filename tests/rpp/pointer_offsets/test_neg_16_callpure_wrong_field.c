/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Wrong field in callpure context.
   The pure function range_width computes r.hi - r.lo, but
   the property only constrains r1.lo == r2.lo (missing r.hi).
   This tests that RPP preserves field offsets in the callpure
   code path, which is separate from the callset path. */

typedef struct { int lo; int hi; } Range;

/*@ assigns \result \from r.lo, r.hi; */
int range_width(Range r) {
  return r.hi - r.lo;
}

/*@ relational
      \forall Range r1, r2;
      r1.lo == r2.lo ==>
      \callpure(range_width, r1) == \callpure(range_width, r2);
*/
