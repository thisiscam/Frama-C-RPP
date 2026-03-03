/* run.config
   OPT: -rpp
*/

/* Test: named behavior WITH its own assigns clause.
 * RPP should skip the named behavior's assigns and only check
 * the default behavior's assigns for purity. */

/*@ assigns \result \from x;
  @
  @ behavior zero:
  @   assumes x == 0;
  @   assigns \result \from \nothing;
  @   ensures \result == 0;
*/
int identity(int x) {
  return x;
}

/*@ assigns \result \from x; */
int identity2(int x) {
  return x;
}

/*@ relational \forall int x; \callpure(identity, x) == \callpure(identity2, x); */
