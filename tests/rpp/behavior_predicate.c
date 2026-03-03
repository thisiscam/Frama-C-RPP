/* run.config
   OPT: -rpp
*/

/* Test: behavior using ACSL predicates in assumes/ensures,
 * combined with relational annotations using the same predicates.
 * This is the pattern from our ARVO proof artifacts. */

#define SIZE 4

static const int table[SIZE] = {10, 20, 30, 0};

/*@ predicate guard_fires(unsigned int i) = i > SIZE; */
/*@ predicate crashes(unsigned int i) =
      !guard_fires(i) && i >= SIZE; */

/*@ requires !crashes(idx);
  @ assigns \result \from idx;
  @
  @ behavior guard_does_not_fire:
  @   assumes !guard_fires(idx);
  @   ensures idx < SIZE;
*/
int check_orig(unsigned int idx) {
  if (idx > SIZE) return 0;
  if (table[idx] == 0) return 0;
  return 1;
}

/*@ assigns \result \from idx; */
int check_fixed(unsigned int idx) {
  if (idx >= SIZE) return 0;
  if (table[idx] == 0) return 0;
  return 1;
}

/*@ relational
      \forall unsigned int x;
        crashes(x) ==> \callpure(check_fixed, x) == 0;
*/

/*@ relational
      \forall unsigned int x;
        !crashes(x) ==>
          \callpure(check_orig, x) == \callpure(check_fixed, x);
*/
