/* run.config
   OPT: -rpp
*/

/* Genuine negative: function pointer stored in a struct field.
   The indirect call `ops->fn(x)` produces Mem(Lval(Mem(...), Field(...)))
   in CIL, which is NOT the Mem(Lval(Var(_), NoOffset)) pattern that
   RPP's fptr resolution recognizes.
   This is a genuine limitation of the current implementation. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

struct ops_t {
  unary_fn fn;
};

/*@ requires \valid(ops);
  @ requires \valid_function(ops->fn);
  @ assigns \result \from ops->fn, x;
*/
int apply_via_struct(struct ops_t *ops, int x) {
  /*@ calls inc; */
  return ops->fn(x);
}

struct ops_t g_ops = { &inc };

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_via_struct, &g_ops, x1) ==
        \callpure(apply_via_struct, &g_ops, x2);
*/
