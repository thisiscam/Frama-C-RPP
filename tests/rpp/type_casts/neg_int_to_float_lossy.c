/* run.config
   OPT: -rpp
*/

/* Negative test: int (32-bit) -> float parameter is lossy.
   A float has only 24 bits of mantissa (IEEE 754 single precision).
   Integers larger than 2^24 cannot be represented exactly, so this
   cast is not safe and must be rejected. */

/*@ assigns \result \from x;
*/
float id_float(float x) { return x; }

/*@ relational
      \forall int a, int b;
      a == b ==>
      \callpure(id_float, a) == \callpure(id_float, b);
*/
