/* run.config
   OPT: -rpp
*/

/* Negative test: narrowing cast long long -> int parameter should be rejected.
   A long long may hold values that do not fit in int; this is a lossy cast. */

/*@ assigns \result \from x;
*/
int identity_int(int x) { return x; }

/*@ relational
      \forall long long a, long long b;
      a == b ==>
      \callpure(identity_int, a) == \callpure(identity_int, b);
*/
