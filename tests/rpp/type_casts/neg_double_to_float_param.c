/* run.config
   OPT: -rpp
*/

/* Negative test: double -> float parameter is a narrowing cast.
   A double can represent values that a float cannot (larger range and
   53-bit vs 24-bit mantissa). Passing double where float is expected
   is lossy and must be rejected. */

/*@ assigns \result \from x;
*/
float id_float2(float x) { return x; }

/*@ relational
      \forall double a, double b;
      a < b ==>
      \callpure(id_float2, a) < \callpure(id_float2, b);
*/
