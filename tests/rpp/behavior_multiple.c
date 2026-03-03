/* run.config
   OPT: -rpp
*/

/* Test: function with multiple named behaviors and \callpure.
 * All named behaviors lack assigns — RPP must skip all of them. */

/*@ assigns \result \from x;
  @
  @ behavior neg:
  @   assumes x < 0;
  @   ensures \result == -1;
  @
  @ behavior zero:
  @   assumes x == 0;
  @   ensures \result == 0;
  @
  @ behavior pos:
  @   assumes x > 0;
  @   ensures \result == 1;
*/
int sign(int x) {
  if (x < 0) return -1;
  if (x > 0) return 1;
  return 0;
}

/*@ assigns \result \from x; */
int sign2(int x) {
  if (x < 0) return -1;
  if (x > 0) return 1;
  return 0;
}

/*@ relational \forall int x; \callpure(sign, x) == \callpure(sign2, x); */
