/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

/*@ assigns \result \from x; */
int dec(int x) { return x - 1; }

typedef int (*op_fn)(int);

/*@ requires \valid_function(f) && \valid_function(g);
  @ assigns \result \from x, f, g;
*/
int apply_both(op_fn f, op_fn g, int x) {
  int tmp;
  /*@ calls inc, dec; */
  tmp = f(x);
  /*@ calls inc, dec; */
  return g(tmp);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(apply_both, &inc, &dec, x1) == \callpure(apply_both, &inc, &dec, x2);
*/
