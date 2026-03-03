/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

/*@ assigns \result \from x; */
int dec(int x) { return x - 1; }

typedef int (*step_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int apply_step(step_fn fn, int x) {
  /*@ calls inc, dec; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(apply_step, &inc, x1) == \callpure(apply_step, &inc, x2);
*/

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(apply_step, &dec, x1) == \callpure(apply_step, &dec, x2);
*/
