/* run.config
   OPT: -rpp
*/

/* Category E: struct A* to struct B* - incompatible, should be rejected */

struct foo { int x; };
struct bar { float y; };

/*@ requires \valid(p);
  @ assigns \result \from p->x;
*/
int get_foo(struct foo *p) {
  return p->x;
}

/*@ relational
      \forall struct bar *p1, struct bar *p2;
      \callpure(get_foo, p1) == \callpure(get_foo, p2);
*/
