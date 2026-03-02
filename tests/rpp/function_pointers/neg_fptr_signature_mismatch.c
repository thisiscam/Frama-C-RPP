/* run.config
   OPT: -rpp
*/

/* Negative test: function pointer target has a different signature
   than the expected typedef. my_add takes (int, int) but the typedef
   expects (int). The type checker should reject this mismatch. */

/*@ assigns \result \from a, b; */
int my_add(int a, int b) { return a + b; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  /*@ calls my_add; */
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply, &my_add, x1) == \callpure(apply, &my_add, x2);
*/
