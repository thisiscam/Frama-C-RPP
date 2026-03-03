/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int double_val(int x) { return x * 2; }

/*@ assigns \result \from x; */
int triple_val(int x) { return x * 3; }

typedef int (*scale_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int scale(scale_fn fn, int x) {
  /*@ calls double_val, triple_val; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(scale, &triple_val, x1) == \callpure(scale, &triple_val, x2);
*/
