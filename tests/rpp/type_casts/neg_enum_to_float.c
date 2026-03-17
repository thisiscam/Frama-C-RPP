/* run.config
   OPT: -rpp
*/

/* Negative test: enum -> float parameter should be rejected.
   Enum values are representable as int (32 bits), but float only has
   24 bits of significand (IEEE 754 single precision). Not all enum
   values representable as int can be represented exactly as float. */

typedef enum { RED = 0, GREEN = 1, BLUE = 2 } Color;

/*@ assigns \result \from x;
*/
float color_to_float(float x) { return x; }

/*@ relational
      \forall Color a, Color b;
      a == b ==>
      \callpure(color_to_float, a) == \callpure(color_to_float, b);
*/
