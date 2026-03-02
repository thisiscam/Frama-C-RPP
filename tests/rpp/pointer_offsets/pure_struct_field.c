/* run.config
   OPT: -rpp
*/

typedef struct { int lo; int hi; } Range;

/*@ assigns \result \from r.lo, r.hi; */
int range_width(Range r) {
  return r.hi - r.lo;
}

/*@ relational
      \forall Range r1, r2;
      r1.lo == r2.lo ==> r1.hi == r2.hi ==>
      \callpure(range_width, r1) == \callpure(range_width, r2);
*/
