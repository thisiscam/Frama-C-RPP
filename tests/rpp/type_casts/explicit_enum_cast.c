/* run.config
   OPT: -rpp
*/

/* Positive test: explicit (int) cast of enum variable as callpure argument.
   An explicit ACSL cast (int)a where a is enum should be accepted and
   generate correct C code, just like the implicit enum->int promotion. */

typedef enum { RED = 0, GREEN = 1, BLUE = 2 } Color;

/*@ assigns \result \from x;
*/
int color_val(int x) { return x; }

/*@ relational
      \forall Color a, Color b;
      a == b ==>
      \callpure(color_val, (int)a) == \callpure(color_val, (int)b);
*/
