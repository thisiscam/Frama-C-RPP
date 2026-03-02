/* run.config
   OPT: -rpp
*/

/* Negative test: the function pointer target is computed from an array
   rather than being a static &func address. RPP cannot resolve this
   because extract_fptr_target only handles AddrOf(Var vi, NoOffset). */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

/*@ assigns \result \from x; */
int dec(int x) { return x - 1; }

typedef int (*unary_fn)(int);

unary_fn table[2] = { &inc, &dec };

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  /*@ calls inc, dec; */
  return fn(x);
}

/* table[0] is &inc at runtime, but RPP can't see into the array at
   analysis time to resolve the concrete target. */
/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply, table[0], x1) == \callpure(apply, table[0], x2);
*/
