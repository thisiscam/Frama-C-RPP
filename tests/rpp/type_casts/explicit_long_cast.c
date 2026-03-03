/* run.config
   OPT: -rpp
*/

/* Category C: explicit casts in the relational condition (not in callpure args).
   Tests that explicit widening casts in the predicate condition are handled.
   The callpure args use implicit promotion (short to long long). */

/*@ requires x >= 0;
  @ assigns \result \from x;
*/
long long widen_ll(long long x) {
  return x + 1;
}

/*@ relational
      \forall short a, short b;
      (long long)a < (long long)b ==>
      \callpure(widen_ll, a) < \callpure(widen_ll, b);
*/
