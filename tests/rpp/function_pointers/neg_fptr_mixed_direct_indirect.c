/* run.config
   OPT: -rpp
*/

/* Negative test: function has both a direct call (that works) and an
   indirect call through a universally quantified fptr (that fails).
   The function pointer resolution should fail for the second call
   even though the first direct call is fine. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

/*@ assigns \result \from x; */
int double_it(int x) { return x * 2; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(g);
  @ assigns \result \from g, x;
*/
int apply_then_direct(unary_fn g, int x) {
  int a;
  /*@ calls inc; */
  a = g(x);
  return double_it(a);
}

/* g1 is quantified, not &concrete, so RPP can't resolve the indirect call */
/*@ relational
      \forall unary_fn g1, int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_then_direct, g1, x1) ==
        \callpure(apply_then_direct, g1, x2);
*/
