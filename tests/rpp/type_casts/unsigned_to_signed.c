/* run.config
   OPT: -rpp
*/

/*@ requires x <= 1000;
  @ assigns \result \from x;
*/
int from_unsigned(unsigned int x) {
  return (int)x;
}

/*@ relational
      \forall int a, int b;
      0 <= a && a < b && b <= 1000 ==>
      \callpure(from_unsigned, a) < \callpure(from_unsigned, b);
*/
