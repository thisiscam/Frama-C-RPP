/* run.config
   OPT: -rpp
*/

/* Category B: float* to int* - incompatible pointer types (should be rejected) */

/*@ assigns \result \from *p;
*/
float identity_float_ptr(float *p) {
  return *p;
}

/*@ relational
      \forall int *p1, int *p2;
      \callpure(identity_float_ptr, p1) == \callpure(identity_float_ptr, p2);
*/
