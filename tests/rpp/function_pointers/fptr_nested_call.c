/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int helper(int x) { return x + 10; }

/*@ assigns \result \from x; */
int double_val(int x) { return x * 2; }

/*@ assigns \result \from x; */
int triple_val(int x) { return x * 3; }

typedef int (*scale_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int scale_and_shift(scale_fn fn, int x) {
  int tmp;
  /*@ calls double_val, triple_val; */
  tmp = fn(x);
  return helper(tmp);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(scale_and_shift, &double_val, x1) == \callpure(scale_and_shift, &double_val, x2);
*/
