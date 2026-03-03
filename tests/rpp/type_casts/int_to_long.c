/* run.config
   OPT: -rpp
*/

/*@ requires x >= 0;
  @ assigns \result \from x;
*/
long widen(long x) {
  return x + 1;
}

/*@ relational
      \forall int a, int b;
      a < b ==> \callpure(widen, a) < \callpure(widen, b);
*/
