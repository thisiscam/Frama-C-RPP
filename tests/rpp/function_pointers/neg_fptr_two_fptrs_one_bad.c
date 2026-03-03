/* run.config
   OPT: -rpp
*/

/* Negative test: function with two function pointer parameters, one resolved
   via &concrete and one passed as a bare variable.
   RPP can resolve the first fptr but NOT the second.
   The calls annotation covers both indirect call sites. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(f);
  @ requires \valid_function(g);
  @ assigns \result \from f, g, x;
*/
int compose(unary_fn f, unary_fn g, int x) {
  int tmp;
  /*@ calls inc; */
  tmp = f(x);
  /*@ calls inc; */
  return g(tmp);
}

/* f is concrete (&inc) but g is universally quantified - unresolvable */
/*@ relational
      \forall unary_fn g1, int x1, int x2;
      x1 == x2 ==>
      \callpure(compose, &inc, g1, x1) == \callpure(compose, &inc, g1, x2);
*/
