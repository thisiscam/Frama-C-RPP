/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Two struct args to callpure with mismatched fields.
   The pure function add_components computes a.x + b.y.
   Property constrains a1.x == a2.x AND b1.x == b2.x (constraining b.x
   instead of b.y). Since the function reads b.y, not b.x, this is wrong.
   Tests field-level precision in callpure with multiple struct arguments. */

typedef struct { int x; int y; } Vec;

/*@ assigns \result \from a.x, b.y; */
int cross_add(Vec a, Vec b) {
  return a.x + b.y;
}

/*@ relational
      \forall Vec a1, a2, Vec b1, b2;
      a1.x == a2.x ==>
      b1.x == b2.x ==>
      \callpure(cross_add, a1, b1) == \callpure(cross_add, a2, b2);
*/
