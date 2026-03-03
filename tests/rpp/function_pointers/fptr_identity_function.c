/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x;
  @ ensures \result == x;
*/
int id(int x) { return x; }

typedef int (*fn_type)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int wrap(fn_type fn, int x) {
  /*@ calls id; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(wrap, &id, x1) == \callpure(wrap, &id, x2);
*/
