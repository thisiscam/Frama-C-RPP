/* run.config
   OPT: -rpp
*/
/* What this tests: Category C — struct containing struct by value: p->inner.field */

typedef struct { int x; int y; } Pos;
typedef struct { Pos pos; int id; } Entity;

/*@ requires \valid(e);
  @ assigns \result \from e->pos.x, e->pos.y, e->id;
*/
int entity_hash(Entity *e) {
  return e->pos.x + e->pos.y + e->id;
}

/*@ relational
      \forall Entity *e1, *e2;
      \callset(\call(entity_hash, e1, id1), \call(entity_hash, e2, id2)) ==>
      \at(e1->pos.x, Pre_id1) == \at(e2->pos.x, Pre_id2) ==>
      \at(e1->pos.y, Pre_id1) == \at(e2->pos.y, Pre_id2) ==>
      \at(e1->id, Pre_id1) == \at(e2->id, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
