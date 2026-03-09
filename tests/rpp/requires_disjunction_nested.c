/* run.config
   OPT: -rpp
*/
/* What this tests: nested Por inside Pand in requires clause */

/*@ requires (a > 0 || b > 0) && c > 0;
  @ assigns \result \from a, b, c;
*/
int combined(int a, int b, int c) {
  return (a > b ? a : b) + c;
}

/*@ requires (a > 0 || b > 0) && c > 0;
  @ assigns \result \from a, b, c;
*/
int combined2(int a, int b, int c) {
  return (a > b ? a : b) + c;
}

/*@ relational
      \forall int a, b, c;
        \callpure(combined, a, b, c) == \callpure(combined2, a, b, c);
*/
