/* run.config
   OPT: -rpp
*/

/* Negative test: wrapper function used in \callset has no assigns/from spec.
   RPP requires assigns/from annotations for functions used in \call. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/* apply has NO assigns/from contract */
int apply(unary_fn fn, int x) {
  /*@ calls inc; */
  return fn(x);
}

/*@ relational
      \forall int x1, int x2;
      \callset(\call(apply, &inc, x1, id1), \call(apply, &inc, x2, id2)) ==>
      x1 == x2 ==>
      \callresult(id1) == \callresult(id2);
*/
