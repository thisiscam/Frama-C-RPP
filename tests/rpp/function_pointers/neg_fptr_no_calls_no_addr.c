/* run.config
   OPT: -rpp
*/

/* Negative test: indirect call through function pointer with NO calls annotation
   AND the relational property passes a variable (not &func_name) as the fptr arg.
   RPP cannot resolve the indirect call target. */

/*@ assigns \result \from x; */
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply(unary_fn fn, int x) {
  return fn(x);
}

/* Here fn1 and fn2 are logical \forall variables, not concrete &func addresses.
   RPP has no way to figure out what function they point to. */
/*@ relational
      \forall unary_fn fn1, unary_fn fn2, int x1, int x2;
      fn1 == fn2 ==> x1 == x2 ==>
      \callpure(apply, fn1, x1) == \callpure(apply, fn2, x2);
*/
