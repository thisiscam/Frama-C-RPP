/* run.config
   OPT: -rpp
*/

/* Negative test: \callset containing something other than \call.
   \callset expects only \call(...) elements. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*step_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int step(step_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      \callset(x1 + x2) ==>
      x1 == x2;
*/
