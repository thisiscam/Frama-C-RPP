/* run.config
   OPT: -rpp
*/
/* What this tests: Category E — nested struct passed by value */

typedef struct { int lo; int hi; } Bound;
typedef struct { Bound x; Bound y; } Rect;

/*@ assigns \result \from r.x.lo, r.x.hi, r.y.lo, r.y.hi; */
int rect_area(Rect r) {
  return (r.x.hi - r.x.lo) * (r.y.hi - r.y.lo);
}

/*@ relational
      \forall Rect r1, r2;
      r1.x.lo == r2.x.lo ==> r1.x.hi == r2.x.hi ==>
      r1.y.lo == r2.y.lo ==> r1.y.hi == r2.y.hi ==>
      \callpure(rect_area, r1) == \callpure(rect_area, r2);
*/
