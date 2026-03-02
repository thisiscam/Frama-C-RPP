/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int plus_one(int x) { return x + 1; }

/*@ assigns \result \from x;
  @ ensures \result == x + 2;
*/
int plus_two(int x) { return x + 2; }

typedef int (*step_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int step(step_fn fn, int x) {
  /*@ calls plus_one, plus_two; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(step, &plus_one, x1) + 1 == \callpure(step, &plus_two, x2);
*/
