/* run.config
   OPT: -rpp
*/

/* Genuine negative: function pointer aliased through a local variable.
   The function stores the fptr parameter into a local and then calls
   through the local. After inlining substitution, the local variable
   is NOT in the fptr_targets map (only the original formal is).
   RPP cannot trace the alias chain fn -> local_fn -> call. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply_aliased(unary_fn fn, int x) {
  unary_fn local_fn = fn;  /* alias the parameter */
  /*@ calls inc; */
  return local_fn(x);      /* call through the alias */
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_aliased, &inc, x1) == \callpure(apply_aliased, &inc, x2);
*/
