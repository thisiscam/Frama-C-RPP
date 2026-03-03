/* run.config
   OPT: -rpp
*/

/* Test: behavior on a function with requires + \callpure.
 * The function has a precondition in the default behavior and
 * named behaviors that partition the input space. */

/*@ requires x >= 0;
  @ assigns \result \from x;
  @
  @ behavior small:
  @   assumes x < 10;
  @   ensures \result == x + 1;
  @
  @ behavior large:
  @   assumes x >= 10;
  @   ensures \result == x;
*/
int clamp_inc(int x) {
  if (x < 10) return x + 1;
  return x;
}

/*@ requires y >= 0;
  @ assigns \result \from y;
*/
int clamp_inc2(int y) {
  if (y < 10) return y + 1;
  return y;
}

/*@ relational
      \forall int x;
        x >= 0 ==>
          \callpure(clamp_inc, x) == \callpure(clamp_inc2, x);
*/
