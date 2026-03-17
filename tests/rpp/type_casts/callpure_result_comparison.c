/* run.config
   OPT: -rpp
*/

/* Category C: two callpures with different arg types, both promoted to same param type. */

/*@ requires x >= 0;
  @ assigns \result \from x;
*/
long increment_long(long x) {
  return x + 1;
}

/*@ requires x >= 0;
  @ assigns \result \from x;
*/
long also_increment_long(long x) {
  return 1 + x;
}

/*@ relational
      \forall int a;
      a >= 0 ==>
      \callpure(increment_long, a) == \callpure(also_increment_long, a);
*/
