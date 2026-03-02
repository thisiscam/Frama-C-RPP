/* run.config
   OPT: -rpp
*/

/* Genuine negative: two indirect calls in sequence in the same body.
   The first call goes through the formal parameter fn (resolvable).
   The second call goes through a local variable g (aliased from fn).
   RPP can resolve the first but NOT the second because g is a
   local variable, not a formal parameter in fptr_targets. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int double_call(unary_fn fn, int x) {
  int a;
  unary_fn g;
  /*@ calls inc; */
  a = fn(x);          /* resolvable: fn is a formal */
  g = fn;             /* alias */
  /*@ calls inc; */
  return g(a);         /* unresolvable: g is a local */
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(double_call, &inc, x1) == \callpure(double_call, &inc, x2);
*/
