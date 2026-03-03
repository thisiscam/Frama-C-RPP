/* run.config
   OPT: -rpp
*/

int threshold = 10;

/*@ predicate above_threshold(int x) = x > threshold; */

/*@ requires above_threshold(x);
  @ assigns \result \from x;
*/
int clamp_orig(int x) { return x; }

/*@ assigns \result \from x; */
int clamp_fixed(int x) {
  if (x <= threshold) return threshold;
  return x;
}

/*@ relational
      \forall int v;
        above_threshold(v) ==> \callpure(clamp_orig, v) == \callpure(clamp_fixed, v);
*/
