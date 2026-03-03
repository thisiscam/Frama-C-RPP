/* run.config
   OPT: -rpp
*/

/* Category B: struct pointer to void pointer */

struct point { int x; int y; };

/*@ requires \valid((struct point *)p);
  @ assigns \result \from ((struct point *)p)->x;
*/
int get_x(void *p) {
  return ((struct point *)p)->x;
}

/*@ relational
      \forall struct point *p1, struct point *p2;
      p1 == p2 ==>
      \callpure(get_x, p1) == \callpure(get_x, p2);
*/
