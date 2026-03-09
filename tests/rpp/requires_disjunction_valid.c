/* run.config
   OPT: -rpp
*/
/* What this tests: Por with \valid_read in requires — the null-pointer pattern */

/*@ requires \valid_read(p) || p == \null;
  @ assigns \result \from *p;
*/
int safe_read(int *p) {
  if (p == (int *)0) return -1;
  return *p;
}

/*@ requires \valid_read(p) || p == \null;
  @ assigns \result \from *p;
*/
int safe_read2(int *p) {
  if (p == (int *)0) return -1;
  return *p;
}

/*@ relational
      \forall int *p;
        \callpure(safe_read, p) == \callpure(safe_read2, p);
*/
