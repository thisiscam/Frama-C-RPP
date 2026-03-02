/* run.config
   OPT: -rpp
*/

/* Negative test: referring to a function that does not exist in &unknown_fn.
   The parser should reject the unknown name. */

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply, &nonexistent_func, x1) == \callpure(apply, &nonexistent_func, x2);
*/
