/* run.config
   OPT: -rpp
*/

/* Test: user-defined behavior on a \callpure function.
 * RPP should skip the named behavior when checking purity
 * and only inspect the default behavior's assigns clause. */

/*@ assigns \result \from x;
  @ ensures \result >= 0;
  @
  @ behavior positive:
  @   assumes x > 0;
  @   ensures \result == x;
  @
  @ behavior negative:
  @   assumes x <= 0;
  @   ensures \result == -x;
*/
int abs_val(int x) {
  return x > 0 ? x : -x;
}

/*@ assigns \result \from x;
  @ ensures \result >= 0;
  @
  @ behavior positive:
  @   assumes x >= 0;
  @   ensures \result == x;
  @
  @ behavior negative:
  @   assumes x < 0;
  @   ensures \result == -x;
*/
int abs_val2(int x) {
  return x >= 0 ? x : -x;
}

/*@ relational \forall int x; \callpure(abs_val, x) == \callpure(abs_val2, x); */
