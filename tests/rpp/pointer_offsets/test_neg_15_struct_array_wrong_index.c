/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (semantic): Wrong index in struct array field.
   Function reads b->data[0] (first element), but the property
   constrains b->data[1] (second element).
   Tests that TIndex inside TField is preserved correctly in the
   generated wrapper — the specific index must appear, not be dropped. */

typedef struct { int *data; int len; } Buf;

/*@ requires \valid(b) && b->len >= 2 && \valid(b->data+(0..b->len-1));
  @ assigns \result \from b->data[0..b->len-1], b->len;
*/
int buf_first(Buf *b) {
  return b->data[0];
}

/*@ relational
      \forall Buf *b1, *b2;
      \callset(\call(buf_first, b1, id1), \call(buf_first, b2, id2)) ==>
      \at(b1->data[1], Pre_id1) == \at(b2->data[1], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
