/* run.config
   OPT: -rpp
*/

/* Category C: int to unsigned long (mixed signedness and width) */

/*@ assigns \result \from x;
*/
unsigned long to_ulong(unsigned long x) {
  return x;
}

/*@ relational
      \forall int a, int b;
      a == b ==>
      \callpure(to_ulong, a) == \callpure(to_ulong, b);
*/
