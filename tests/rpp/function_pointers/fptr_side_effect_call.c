/* run.config
   OPT: -rpp
*/

int state;

/*@ assigns state \from state, x;
  @ ensures state == \old(state) + x;
*/
void add_to_state(int x) { state = state + x; }

/*@ assigns state \from state, x;
  @ ensures state == \old(state) * x;
*/
void mul_state(int x) { state = state * x; }

typedef void (*state_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns state \from state, x, fn;
*/
void update_state(state_fn fn, int x) {
  /*@ calls add_to_state, mul_state; */
  fn(x);
}

/*@ relational
      \forall int x1, x2;
      \callset(\call(update_state, &add_to_state, x1, id1),
               \call(update_state, &add_to_state, x2, id2)) ==>
      x1 == x2 ==>
      \at(state, Pre_id1) == \at(state, Pre_id2) ==>
      \at(state, Post_id1) == \at(state, Post_id2);
*/
