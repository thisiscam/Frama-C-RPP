/* run.config
   OPT: -rpp
*/

/* Category A: int argument to long long parameter */

/*@ requires x >= 0;
  @ assigns \result \from x;
*/
long long square_ll(long long x) {
  return x * x;
}

/*@ relational
      \forall int a, int b;
      0 <= a && a < b ==>
      \callpure(square_ll, a) < \callpure(square_ll, b);
*/
