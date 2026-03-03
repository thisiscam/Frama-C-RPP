/* run.config
   OPT: -rpp
*/

int global_val;

/*@ assigns global_val \from global_val;
  @ ensures global_val == \old(global_val) + 1;
*/
void inc_global(void) { global_val = global_val + 1; }

/*@ assigns global_val \from global_val;
  @ ensures global_val == \old(global_val) - 1;
*/
void dec_global(void) { global_val = global_val - 1; }

typedef void (*modifier_fn)(void);

/*@ requires \valid_function(fn);
  @ assigns global_val \from global_val, fn;
*/
void modify(modifier_fn fn) {
  /*@ calls inc_global, dec_global; */
  fn();
}

/*@ relational
      \callset(\call(modify, &inc_global, id1),
               \call(modify, &inc_global, id2)) ==>
      \at(global_val, Pre_id1) == \at(global_val, Pre_id2) ==>
      \at(global_val, Post_id1) == \at(global_val, Post_id2);
*/
