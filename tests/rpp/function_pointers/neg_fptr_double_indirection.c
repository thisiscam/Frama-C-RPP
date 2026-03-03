/* run.config
   OPT: -rpp
*/

/* Negative test: indirect call through a double pointer (**fpp)(x).
   RPP only handles single-level function pointers fn(x), not **fpp. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid(fpp);
  @ requires \valid_function(*fpp);
  @ assigns \result \from *fpp, x;
*/
int apply_indirect(unary_fn *fpp, int x) {
  /*@ calls inc; */
  return (*fpp)(x);
}

unary_fn g_fn = &inc;

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_indirect, &g_fn, x1) == \callpure(apply_indirect, &g_fn, x2);
*/
