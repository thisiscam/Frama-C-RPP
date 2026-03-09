/* run.config
   OPT: -rpp
*/
/* What this tests: Por (disjunction) in requires clause with pure arithmetic */

/*@ requires x > 0 || y > 0;
  @ assigns \result \from x, y;
*/
int max_positive(int x, int y) {
  return x > y ? x : y;
}

/*@ requires x > 0 || y > 0;
  @ assigns \result \from x, y;
*/
int max_positive2(int x, int y) {
  return x > y ? x : y;
}

/*@ relational
      \forall int x, y;
        \callpure(max_positive, x, y) == \callpure(max_positive2, x, y);
*/
