/* run.config
   OPT: -rpp
*/

/* Category G edge case: multi-level wrapping.
   outer() calls inner() via direct call. inner() has an indirect call
   through function pointer fn(x) with a calls annotation.
   The relational property calls outer(&inc, x1).

   When RPP inlines outer's body, it substitutes outer's fptr formal
   with &inc. Then it inlines inner's body, which contains fn(x).
   But fptr_targets was built from outer's formal parameters — after
   two levels of inlining, the indirect call in inner may reference
   a different local variable not in fptr_targets.
   This tests whether function pointer resolution propagates through
   multi-level inlining. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int inner(unary_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int outer(unary_fn fn, int x) {
  return inner(fn, x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(outer, &inc, x1) == \callpure(outer, &inc, x2);
*/
