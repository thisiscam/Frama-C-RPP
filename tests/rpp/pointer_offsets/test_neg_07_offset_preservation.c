/* run.config
   OPT: -rpp
*/
/* NEGATIVE TEST (offset preservation challenge):
   The function get_a returns p->a, but the property only constrains p->b.
   If RPP's implementation had a bug where it dropped field offsets
   (replacing p->b with *p in the generated code), the WP assertion
   might accidentally become provable since *p at the same struct
   address encompasses all fields.
   With correct offset preservation, the generated check must reference
   the specific field (p->b), making the property unprovable. */

typedef struct { int a; int b; } Pair;

/*@ requires \valid(p);
  @ assigns \result \from p->a;
*/
int get_a(Pair *p) {
  return p->a;
}

/*@ relational
      \forall Pair *p1, *p2;
      \callset(\call(get_a, p1, id1), \call(get_a, p2, id2)) ==>
      \at(p1->b, Pre_id1) == \at(p2->b, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
