/* run.config
   OPT: -rpp
*/

typedef int (*binop_fn)(int, int);

/*@ assigns \result \from a, b; */
int my_add(int a, int b) { return a + b; }

/*@ assigns \result \from a, b; */
int my_mul(int a, int b) { return a * b; }

/*@ requires \valid_function(op);
  @ assigns \result \from a, b, op;
  @ ensures \result == \old(a) + \old(b) || \result == \old(a) * \old(b);
*/
int compute(binop_fn op, int a, int b);

/*@ relational
      \forall int a1, a2, int b;
      \callset(\call(compute, &my_add, a1, b, id1),
               \call(compute, &my_add, a2, b, id2)) ==>
      a1 == a2 ==> \callresult(id1) == \callresult(id2);
*/
