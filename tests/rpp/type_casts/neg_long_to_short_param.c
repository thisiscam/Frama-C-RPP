/* run.config
   OPT: -rpp
*/

/* Negative test: narrowing cast long -> short parameter should be rejected.
   Passing a wider integer type where a narrower parameter is expected is lossy
   and must not be accepted as a "safe cast". */

/*@ assigns \result \from x;
*/
short clamp_short(short x) { return x; }

/*@ relational
      \forall long a, long b;
      a == b ==>
      \callpure(clamp_short, a) == \callpure(clamp_short, b);
*/
