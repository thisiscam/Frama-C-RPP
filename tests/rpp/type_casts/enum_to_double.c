/* run.config
   OPT: -rpp
*/

/* Positive test: enum -> double parameter should be accepted.
   Enum values are representable as int (C11 6.7.2.2), and a 32-bit int
   fits exactly in double (53-bit significand). */

typedef enum { RED = 0, GREEN = 1, BLUE = 2 } Color;

/*@ assigns \result \from x;
*/
double color_to_double(double x) { return x; }

/*@ relational
      \forall Color a, Color b;
      a == b ==>
      \callpure(color_to_double, a) == \callpure(color_to_double, b);
*/
