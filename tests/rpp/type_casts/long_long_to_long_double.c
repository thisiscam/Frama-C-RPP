/* run.config
   OPT: -rpp
*/

/* Positive test: long long -> long double.
   On x86-64, long double is 80-bit extended precision with 64 significant
   bits, which is exactly enough to hold all 64-bit long long values.
   This cast should be accepted on x86-64 and rejected on ARM64 (where
   long double is the same as double with only 53 significant bits). */

/*@ assigns \result \from x;
*/
long double id_ldouble(long double x) { return x; }

/*@ relational
      \forall long long a, long long b;
      a == b ==>
      \callpure(id_ldouble, a) == \callpure(id_ldouble, b);
*/
