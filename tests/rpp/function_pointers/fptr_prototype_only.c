/* run.config
   OPT: -rpp
*/

typedef int (*mapper_fn)(int);

/*@ assigns \result \from x; */
int double_it(int x);

/*@ assigns \result \from x; */
int halve_it(int x);

/*@ requires \valid_function(fn);
  @ assigns \result \from x, fn;
*/
int map_val(mapper_fn fn, int x);

/*@ relational
      \forall int x1, x2;
      \callset(\call(map_val, &double_it, x1, id1),
               \call(map_val, &double_it, x2, id2)) ==>
      x1 == x2 ==> \callresult(id1) == \callresult(id2);
*/
