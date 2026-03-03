/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x;
*/
double square(double x) {
  return x * x;
}

/*@ relational
      \forall float a, float b;
      0.0f <= a && a < b ==>
      \callpure(square, a) < \callpure(square, b);
*/
