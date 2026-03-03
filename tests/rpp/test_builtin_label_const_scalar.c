/* run.config
   OPT: -rpp
*/

const int MAX_VAL = 100;

/*@ predicate in_range(int x) = 0 <= x && x <= MAX_VAL; */

/*@ requires in_range(x);
  @ assigns \result \from x;
*/
int identity_orig(int x) { return x; }

/*@ assigns \result \from x; */
int identity_fixed(int x) {
  if (x < 0 || x > MAX_VAL) return 0;
  return x;
}

/*@ relational
      \forall int v;
        in_range(v) ==> \callpure(identity_orig, v) == \callpure(identity_fixed, v);
*/
