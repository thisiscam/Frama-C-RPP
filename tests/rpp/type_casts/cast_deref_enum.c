/* run.config
   OPT: -rpp
*/

/* Positive test: explicit cast wrapping a pointer dereference in callpure args.
   (int)(*p) where p is a Color* pointer — TCast wrapping TLval(TMem(...)).
   The typer must look through the cast, reconstruct *p as a C expression,
   and assign it to aux_cast_local, rather than crashing in Logic_to_c. */

typedef enum { RED = 0, GREEN = 1, BLUE = 2 } Color;

/*@ assigns \result \from x;
*/
int color_val(int x) { return x; }

/*@ relational
      \forall Color* p, Color* q;
      p == q ==>
      \callpure(color_val, (int)(*p)) == \callpure(color_val, (int)(*q));
*/
