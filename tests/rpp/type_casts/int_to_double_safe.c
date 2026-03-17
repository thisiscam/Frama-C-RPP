/* run.config
   OPT: -rpp
*/

/* Positive test: int (32-bit) -> double is safe.
   A double has 53 bits of mantissa (IEEE 754), which is more than enough
   to represent all 32-bit int values exactly. This widening should be accepted. */

/*@ assigns \result \from x;
*/
double scale(double x) { return x * 2.0; }

/*@ relational
      \forall int a, int b;
      a == b ==>
      \callpure(scale, a) == \callpure(scale, b);
*/
