/* run.config
   OPT: -rpp
*/

/* Category G stress test: THREE levels of function wrapping.
   level3 calls level2, level2 calls level1, level1 has the indirect call.
   This deeply tests whether fptr resolution propagates through
   multiple rounds of inlining. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int level1(unary_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int level2(unary_fn fn, int x) {
  return level1(fn, x);
}

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int level3(unary_fn fn, int x) {
  return level2(fn, x);
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(level3, &inc, x1) == \callpure(level3, &inc, x2);
*/
