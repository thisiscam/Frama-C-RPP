/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int square(int x) { return x * x; }

/*@ assigns \result \from x; */
int cube(int x) { return x * x * x; }

typedef int (*power_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int apply_power(power_fn fn, int x) {
  /*@ calls square, cube; */
  return fn(x);
}

/*@ relational
      \forall int x1;
      \callpure(apply_power, &square, x1) == \callpure(apply_power, &square, x1);
*/
