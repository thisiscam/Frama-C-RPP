/* run.config
   OPT: -rpp
*/

/* Category A: unsigned char to int promotion */

/*@ assigns \result \from x;
*/
int negate(int x) {
  return -x;
}

/*@ relational
      \forall unsigned char a, unsigned char b;
      a == b ==> \callpure(negate, a) == \callpure(negate, b);
*/
