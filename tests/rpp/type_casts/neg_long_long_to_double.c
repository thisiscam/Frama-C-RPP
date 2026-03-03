/* run.config
   OPT: -rpp
*/

/* Negative test: long long (64-bit) -> double (53-bit mantissa) is lossy.
   A double has only 53 bits of mantissa (IEEE 754 double precision).
   long long has 64 bits, so values > 2^53 cannot be represented exactly.
   This cast must be rejected on all platforms. */

/*@ assigns \result \from x;
*/
double id_double(double x) { return x; }

/*@ relational
      \forall long long a, long long b;
      a == b ==>
      \callpure(id_double, a) == \callpure(id_double, b);
*/
