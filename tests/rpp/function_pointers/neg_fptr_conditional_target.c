/* run.config
   OPT: -rpp
*/

/* Genuine negative: conditional function pointer selection.
   The function chooses between two targets based on a runtime condition.
   Even though both targets are in the calls annotation, RPP's
   static resolution cannot determine which branch is taken. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

/*@ assigns \result \from x;
  @ ensures \result == x - 1;
*/
int dec(int x) { return x - 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn_a);
  @ requires \valid_function(fn_b);
  @ assigns \result \from fn_a, fn_b, x, flag;
*/
int apply_conditional(unary_fn fn_a, unary_fn fn_b, int x, int flag) {
  unary_fn chosen;
  if (flag) {
    chosen = fn_a;
  } else {
    chosen = fn_b;
  }
  /*@ calls inc, dec; */
  return chosen(x);
}

/* The fptr 'chosen' is a local assigned conditionally.
   RPP can't resolve it from formal parameter mapping. */
/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_conditional, &inc, &dec, x1, 1) ==
        \callpure(apply_conditional, &inc, &dec, x2, 1);
*/
