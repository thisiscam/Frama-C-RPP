/* run.config
   OPT: -rpp
*/

/* Category A: short to int promotion */

/*@ assigns \result \from x;
*/
int double_it(int x) {
  return x * 2;
}

/*@ relational
      \forall short a, short b;
      a < b ==> \callpure(double_it, a) < \callpure(double_it, b);
*/
