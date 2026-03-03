/* run.config
   OPT: -rpp
*/

static const int weights[4] = {1, 2, 3, 4};

/*@ logic integer get_weight(integer i) = weights[i]; */

/*@ predicate has_weight(int i) = 0 <= i && i < 4 && get_weight(i) > 0; */

/*@ requires has_weight(x);
  @ assigns \result \from x;
*/
int compute_orig(int x) { return weights[x] * x; }

/*@ assigns \result \from x; */
int compute_fixed(int x) {
  if (x < 0 || x >= 4) return 0;
  return weights[x] * x;
}

/*@ relational
      \forall int v;
        has_weight(v) ==> \callpure(compute_orig, v) == \callpure(compute_fixed, v);
*/
