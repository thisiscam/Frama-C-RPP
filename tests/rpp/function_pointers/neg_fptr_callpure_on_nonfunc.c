/* run.config
   OPT: -rpp
*/

/* Negative test: \callpure used on a global variable instead of a function.
   \callpure expects a function name as its first argument. */

int global_x = 42;

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(global_x, x1) == \callpure(global_x, x2);
*/
