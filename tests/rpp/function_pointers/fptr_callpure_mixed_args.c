/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from a, b; */
int add(int a, int b) { return a + b; }

/*@ assigns \result \from a, b; */
int mul(int a, int b) { return a * b; }

typedef int (*op_fn)(int, int);

/*@ requires \valid_function(op);
  @ assigns \result \from x, y, op;
*/
int combine(int x, op_fn op, int y) {
  /*@ calls add, mul; */
  return op(x, y);
}

/*@ relational
      \forall int x1, x2, int y1, y2;
      x1 == x2 ==> y1 == y2 ==>
      \callpure(combine, x1, &add, y1) == \callpure(combine, x2, &add, y2);
*/
