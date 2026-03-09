/* run.config
   OPT: -rpp
*/
/* What this tests: array range in assigns \from with \call relational property */

#define N 10

static int dst[N];
static int src[N];
static int count;

/*@ requires 0 <= len <= N;
  @ assigns dst[0 .. N-1] \from src[0 .. N-1], len;
  @ assigns count \from len;
  @ assigns \result \from len;
  @ ensures \result == 0;
  @ ensures count == len;
*/
int copy_a(int len) {
  int i;
  /*@ loop invariant 0 <= i <= len;
    @ loop assigns i, dst[0 .. N-1];
    @ loop variant len - i;
  */
  for (i = 0; i < len; i++)
    dst[i] = src[i];
  count = len;
  return 0;
}

/*@ requires 0 <= len <= N;
  @ assigns dst[0 .. N-1] \from src[0 .. N-1], len;
  @ assigns count \from len;
  @ assigns \result \from len;
  @ ensures \result == 0;
  @ ensures count == len;
*/
int copy_b(int len) {
  int i;
  /*@ loop invariant 0 <= i <= len;
    @ loop assigns i, dst[0 .. N-1];
    @ loop variant len - i;
  */
  for (i = 0; i < len; i++)
    dst[i] = src[i];
  count = len;
  return 0;
}

/*@ relational
      \forall int len;
        \rela(
          \callset(\call(copy_a, len, id1),
                   \call(copy_b, len, id2)),
          \callresult(id1) == \callresult(id2)
          && \at(count, Post_id1) == \at(count, Post_id2));
*/
