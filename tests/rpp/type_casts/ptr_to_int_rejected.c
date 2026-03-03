/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from x;
*/
int identity(int x) { return x; }

/*@ relational
      \forall int *p;
      \callpure(identity, p) >= 0;
*/
