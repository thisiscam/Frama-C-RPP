/* run.config
   OPT: -rpp
*/

static const int arr[3] = {10, 20, 30};

/*@ predicate valid_entry(int i) = 0 <= i && i <= 2 && arr[i] > 0; */

/*@ requires valid_entry(x);
  @ assigns \result \from x;
*/
int lookup_orig(int x) { return arr[x]; }

/*@ assigns \result \from x; */
int lookup_fixed(int x) {
  if (x < 0 || x > 2) return 0;
  return arr[x];
}

/*@ relational
      \forall int v;
        valid_entry(v) ==> \callpure(lookup_orig, v) == \callpure(lookup_fixed, v);
*/
