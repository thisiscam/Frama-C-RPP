/* run.config
   OPT: -rpp
*/

/* Category E interaction: function pointer call inside a function that
   also does pointer arithmetic (p + offset).
   Tests interaction between RPP's pointer offset handling and fptr resolution.
   The function reads from an array via pointer offset AND calls through fptr.

   NOTE: \callset must be first in the predicate (RPP parser requirement).
   The data pointer arr is shared between traces, triggering the
   memory sharing error. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ requires \valid(arr + (0 .. n-1));
  @ requires n > 0;
  @ assigns \result \from fn, arr[0 .. n-1], n;
*/
int apply_to_first(unary_fn fn, int *arr, int n) {
  int val;
  val = *(arr + 0);
  /*@ calls inc; */
  return fn(val);
}

/* arr is shared between traces → memory sharing error.
   This tests the interaction of pointer parameters with fptr resolution. */
/*@ relational
      \forall int *arr, int n1;
      \callset(\call(apply_to_first, &inc, arr, n1, id1),
               \call(apply_to_first, &inc, arr, n1, id2)) ==>
      n1 > 0 ==>
      \callresult(id1) == \callresult(id2);
*/
