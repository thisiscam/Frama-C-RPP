/* run.config
   OPT: -rpp
*/

int state;

/*@ assigns state \from state;
  @ ensures state == \old(state) + 1;
*/
void inc_state(void) { state = state + 1; }

/*@ assigns state \from state;
  @ ensures state == \old(state) + 2;
*/
void double_inc_state(void) { state = state + 2; }

typedef void (*step_fn)(void);

/*@ requires \valid_function(step);
  @ assigns state \from state, step;
*/
void do_step(step_fn step) {
  /*@ calls inc_state, double_inc_state; */
  step();
}

/*@ relational
      \callset(\call(do_step, &inc_state, id1),
               \call(do_step, &inc_state, id2)) ==>
      \at(state, Pre_id1) == \at(state, Pre_id2) ==>
      \at(state, Post_id1) == \at(state, Post_id2);
*/
