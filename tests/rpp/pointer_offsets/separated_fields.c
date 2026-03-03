/* run.config
   OPT: -rpp
*/

typedef struct { int *data; int len; } Buf;

/*@ requires \valid(b) && b->len > 0 && \valid(b->data+(0..b->len-1));
  @ assigns \result \from b->data[0..b->len-1], b->len;
*/
int buf_first(Buf *b) {
  return b->data[0];
}

/*@ relational
      \forall Buf *b1, *b2;
      \callset(\call(buf_first, b1, id1), \call(buf_first, b2, id2)) ==>
      \at(b1->len, Pre_id1) == \at(b2->len, Pre_id2) ==>
      \at(b1->data[0], Pre_id1) == \at(b2->data[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
