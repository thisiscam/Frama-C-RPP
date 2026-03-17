/* run.config
   OPT: -rpp
*/

/* Positive test: enum -> int parameter should be accepted.
   In C, every enum value is representable as int (C11 6.4.4.3).
   Passing an enum where int is expected is always safe. */

typedef enum { RED = 0, GREEN = 1, BLUE = 2 } Color;

/*@ assigns \result \from x;
*/
int color_rank(int x) { return x; }

/*@ relational
      \forall Color a, Color b;
      a == b ==>
      \callpure(color_rank, a) == \callpure(color_rank, b);
*/
