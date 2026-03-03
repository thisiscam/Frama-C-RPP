/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x; */
int op_add(int x) { return x + 1; }

/*@ assigns \result \from x; */
int op_sub(int x) { return x - 1; }

/*@ assigns \result \from x; */
int op_nop(int x) { return x; }

typedef int (*op_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int do_op(op_fn fn, int x) {
  /*@ calls op_add, op_sub, op_nop; */
  return fn(x);
}

/*@ relational
      \forall int x1, x2;
      x1 == x2 ==>
      \callpure(do_op, &op_nop, x1) == \callpure(do_op, &op_nop, x2);
*/
