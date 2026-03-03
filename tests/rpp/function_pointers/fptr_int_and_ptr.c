/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from a, b; */
int add(int a, int b) { return a + b; }

/*@ assigns \result \from a, b; */
int sub(int a, int b) { return a - b; }

typedef int (*binop)(int, int);

/*@ requires \valid_function(op);
  @ assigns \result \from a, b, op;
*/
int compute(binop op, int a, int b) {
  /*@ calls add, sub; */
  return op(a, b);
}

/*@ relational
      \forall int a1, a2, int b1, b2;
      a1 == a2 ==> b1 == b2 ==>
      \callpure(compute, &add, a1, b1) == \callpure(compute, &add, a2, b2);
*/
