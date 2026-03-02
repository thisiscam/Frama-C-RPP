/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int abs_val(int x) { return (x >= 0) ? x : -x; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int apply(unary_fn fn, int x) {
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(apply, &abs_val, x1) == \callpure(apply, &abs_val, x2);
*/
