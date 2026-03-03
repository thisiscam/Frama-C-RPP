/* run.config
   OPT: -rpp
*/
/* What this tests: Category F — struct field and array element used together */

typedef struct { int tag; int *data; } Tagged;

/*@ requires \valid(t) && \valid(t->data+(0..n-1)) && n > 0;
  @ assigns \result \from t->tag, t->data[0..n-1], n;
*/
int tagged_first(Tagged *t, int n) {
  return t->tag + t->data[0];
}

/*@ relational
      \forall Tagged *t1, *t2, int n;
      \callset(\call(tagged_first, t1, n, id1), \call(tagged_first, t2, n, id2)) ==>
      \at(t1->tag, Pre_id1) == \at(t2->tag, Pre_id2) ==>
      \at(t1->data[0], Pre_id1) == \at(t2->data[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
