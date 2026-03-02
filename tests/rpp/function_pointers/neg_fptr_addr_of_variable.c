/* run.config
   OPT: -rpp
*/

/* Negative test: passing &global_var (address of a non-function variable)
   as function pointer argument. RPP should reject or fail because
   global_var is not a function. */

int global_var = 42;

typedef int (*unary_fn)(int);

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply, &global_var, x1) == \callpure(apply, &global_var, x2);
*/
