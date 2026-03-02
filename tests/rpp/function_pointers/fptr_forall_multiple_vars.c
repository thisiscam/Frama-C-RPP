/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from a, b; */
int max(int a, int b) { return (a > b) ? a : b; }

/*@ assigns \result \from a, b; */
int min(int a, int b) { return (a < b) ? a : b; }

typedef int (*cmp_fn)(int, int);

/*@ requires \valid_function(fn);
  @ assigns \result \from a, b, fn;
*/
int select(cmp_fn fn, int a, int b) {
  /*@ calls max, min; */
  return fn(a, b);
}

/*@ relational
      \forall int a1, a2, int b1, b2;
      a1 == a2 ==> b1 == b2 ==>
      \callpure(select, &max, a1, b1) == \callpure(select, &max, a2, b2);
*/
