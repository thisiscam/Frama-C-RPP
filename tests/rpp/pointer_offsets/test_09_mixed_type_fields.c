/* run.config
   OPT: -rpp
*/
/* What this tests: Category A — struct with mixed-type fields (int, pointer, char) accessed */

typedef struct { int id; char flag; int *ref; } Entry;

/*@ requires \valid(e) && \valid(e->ref);
  @ assigns \result \from e->id, e->flag;
*/
int entry_key(Entry *e) {
  return e->id + (int)e->flag;
}

/*@ relational
      \forall Entry *e1, *e2;
      \callset(\call(entry_key, e1, id1), \call(entry_key, e2, id2)) ==>
      \at(e1->id, Pre_id1) == \at(e2->id, Pre_id2) ==>
      \at(e1->flag, Pre_id1) == \at(e2->flag, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
