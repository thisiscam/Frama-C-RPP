/* run.config
   OPT: -rpp
*/

/* Category A: mixed promotions - first arg needs promotion, second is exact match */

/*@ requires y != 0;
  @ assigns \result \from x, y;
*/
long divide(long x, long y) {
  return x / y;
}

/*@ relational
      \forall int a, long b;
      0 < b ==>
      \callpure(divide, a, b) <= \callpure(divide, a, b);
*/
