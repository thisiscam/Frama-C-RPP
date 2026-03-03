/* run.config
   OPT: -rpp
*/

/* Negative test: long double -> double parameter is a narrowing cast.
   A long double (80-bit on x86-64, 64-bit significand) can represent
   values that double cannot (53-bit significand). This narrowing must
   be rejected. */

/*@ assigns \result \from x;
*/
double id_double2(double x) { return x; }

/*@ relational
      \forall long double a, long double b;
      a < b ==>
      \callpure(id_double2, a) < \callpure(id_double2, b);
*/
