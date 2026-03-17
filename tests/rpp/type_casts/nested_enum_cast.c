/* run.config
   OPT: -rpp
*/

/* Positive test: nested explicit casts in callpure args.
   (int)((long)a) where a is an enum variable — two TCast nodes stacked.
   The typer must strip both cast wrappers to find the base variable and
   generate aux_cast_local = (int)a, rather than crashing in Logic_to_c. */

typedef enum { RED = 0, GREEN = 1, BLUE = 2 } Color;

/*@ assigns \result \from x;
*/
int color_val(int x) { return x; }

/*@ relational
      \forall Color a, Color b;
      a == b ==>
      \callpure(color_val, (int)((long)a)) == \callpure(color_val, (int)((long)b));
*/
