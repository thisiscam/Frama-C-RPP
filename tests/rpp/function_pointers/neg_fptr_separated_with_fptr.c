/* run.config
   OPT: -rpp
*/

/* Category E interaction: \separated involving a function pointer and
   a regular data pointer.  RPP's separate_checker exempts TPtr(TFun _)
   from the sharing check but does NOT exempt data pointers that happen
   to be passed alongside function pointers.
   This test verifies that memory sharing is still caught for data
   pointers even when function pointers are present. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ requires \valid(p);
  @ assigns *p \from fn, *p;
*/
void apply_to_ptr(unary_fn fn, int *p) {
  /*@ calls inc; */
  *p = fn(*p);
}

/* Using the SAME pointer p in both traces triggers the sharing error.
   The function pointer &inc is safe to share (constant), but p is not. */
/*@ relational
      \forall int *p;
      \callset(\call(apply_to_ptr, &inc, p, id1),
               \call(apply_to_ptr, &inc, p, id2)) ==>
      \at(*p, Pre_id1) == \at(*p, Pre_id2) ==>
      \at(*p, Post_id1) == \at(*p, Post_id2);
*/
