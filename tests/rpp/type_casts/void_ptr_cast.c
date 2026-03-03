/* run.config
   OPT: -rpp
*/

/*@ requires \valid((int *)p);
  @ assigns \result \from *((int *)p);
*/
int read_void(void *p) {
  return *((int *)p);
}

/*@ relational
      \forall int *p1, int *p2;
      p1 == p2 ==>
      \callpure(read_void, p1) == \callpure(read_void, p2);
*/
