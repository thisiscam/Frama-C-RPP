/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int add_one(int x) { return x + 1; }

/*@ assigns \result \from x; */
int add_two(int x) { return x + 2; }

typedef int (*transform_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int apply(transform_fn fn, int x) {
  /*@ calls add_one, add_two; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(apply, &add_one, x1) == \callpure(apply, &add_one, x2);
*/
