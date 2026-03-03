/* run.config
   OPT: -rpp
*/

int counter;

/*@ assigns counter \from counter;
  @ ensures counter == \old(counter) + 1;
*/
void tick(void) { counter = counter + 1; }

/*@ assigns counter \from counter;
  @ ensures counter == \old(counter) + 5;
*/
void tick5(void) { counter = counter + 5; }

typedef void (*action_fn)(void);

/*@ requires \valid_function(act);
  @ assigns counter \from counter, act;
*/
void perform(action_fn act) {
  /*@ calls tick, tick5; */
  act();
}

/*@ relational
      \callset(\call(perform, &tick, id1),
               \call(perform, &tick, id2)) ==>
      \at(counter, Pre_id1) == \at(counter, Pre_id2) ==>
      \at(counter, Post_id1) == \at(counter, Post_id2);
*/
