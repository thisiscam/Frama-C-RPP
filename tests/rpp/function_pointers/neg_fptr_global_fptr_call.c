/* run.config
   OPT: -rpp
*/

/* Genuine negative: function reads its fptr from a global variable.
   The formal parameter is not a function pointer — the fptr comes from
   a global. RPP's fptr_targets map only tracks formal parameters,
   so the indirect call through the global is unresolvable. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

unary_fn g_callback = &inc;

/*@ assigns \result \from g_callback, x;
*/
int apply_global(int x) {
  /*@ calls inc; */
  return g_callback(x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_global, x1) == \callpure(apply_global, x2);
*/
