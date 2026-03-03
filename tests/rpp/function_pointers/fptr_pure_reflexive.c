/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int succ(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int apply(unary_fn fn, int x) {
  /*@ calls succ; */
  return fn(x);
}

/*@ relational
      \forall int x1;
      \callpure(apply, &succ, x1) == \callpure(apply, &succ, x1);
*/
