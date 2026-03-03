/* run.config
   OPT: -rpp
*/

/* Category D: two arguments both needing promotion */

/*@ assigns \result \from x, y;
*/
long add_long(long x, long y) {
  return x + y;
}

/*@ relational
      \forall int a, int b, int c, int d;
      a == c && b == d ==>
      \callpure(add_long, a, b) == \callpure(add_long, c, d);
*/
