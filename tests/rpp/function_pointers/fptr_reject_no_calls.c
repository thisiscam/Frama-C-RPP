/* run.config
   OPT: -rpp
*/

/* Test: function pointer resolution works even without a calls annotation,
   because the concrete target is determined from the \callpure arguments. */

/*@ assigns \result \from x; */
int add_one(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int invoke(unary_fn fn, int x) {
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(invoke, &add_one, x1) == \callpure(invoke, &add_one, x2);
*/
