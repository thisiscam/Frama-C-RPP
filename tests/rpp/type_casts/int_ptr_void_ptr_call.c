/* run.config
   OPT: -rpp
*/

/* Category B: int* to void* in a multi-arg \callpure. */

/*@ assigns \result \from x;
*/
int select_value(void *ignored, int x) {
  return x;
}

/*@ relational
      \forall int *p1, int *p2, int a, int b;
      a == b ==>
      \callpure(select_value, p1, a) == \callpure(select_value, p2, b);
*/
