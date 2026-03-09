/* run.config
   OPT: -rpp
*/
/* What this tests: global array in assigns \from with post-state comparison */

#define SIZE 8

static int buf[SIZE];
static int state;

/*@ requires 0 <= n <= SIZE;
  @ assigns buf[0 .. SIZE-1] \from val, n;
  @ assigns state \from n;
  @ assigns \result \from n;
  @ ensures state == n;
  @ ensures \result == 0;
*/
int fill_a(int val, int n) {
  int i;
  /*@ loop invariant 0 <= i <= n;
    @ loop assigns i, buf[0 .. SIZE-1];
    @ loop variant n - i;
  */
  for (i = 0; i < n; i++)
    buf[i] = val;
  state = n;
  return 0;
}

/*@ requires 0 <= n <= SIZE;
  @ assigns buf[0 .. SIZE-1] \from val, n;
  @ assigns state \from n;
  @ assigns \result \from n;
  @ ensures state == n;
  @ ensures \result == 0;
*/
int fill_b(int val, int n) {
  int i;
  /*@ loop invariant 0 <= i <= n;
    @ loop assigns i, buf[0 .. SIZE-1];
    @ loop variant n - i;
  */
  for (i = 0; i < n; i++)
    buf[i] = val;
  state = n;
  return 0;
}

/*@ relational
      \forall int val, int n;
        \rela(
          \callset(\call(fill_a, val, n, id1),
                   \call(fill_b, val, n, id2)),
          \callresult(id1) == \callresult(id2)
          && \at(state, Post_id1) == \at(state, Post_id2));
*/
