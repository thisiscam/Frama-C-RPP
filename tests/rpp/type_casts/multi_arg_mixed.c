/* run.config
   OPT: -rpp
*/

/* Category D: multiple arguments, mix of promotions and exact matches */

/*@ assigns \result \from x, y, z;
*/
long sum3(long x, long y, long z) {
  return x + y + z;
}

/*@ relational
      \forall int a, long b, short c;
      a >= 0 && b >= 0 && c >= 0 ==>
      \callpure(sum3, a, b, c) >= 0;
*/
