/* run.config
   OPT: -rpp
*/

/* Category E: float to int - should be rejected (lossy, not a safe widening) */

/*@ assigns \result \from x;
*/
int identity(int x) { return x; }

/*@ relational
      \forall float f;
      \callpure(identity, f) >= 0;
*/
