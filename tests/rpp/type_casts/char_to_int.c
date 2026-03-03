/* run.config
   OPT: -rpp
*/

/*@ assigns \result \from c;
*/
int char_to_upper(int c) {
  if (c >= 'a' && c <= 'z') return c - 32;
  return c;
}

/*@ relational
      \forall char c;
      \callpure(char_to_upper, c) >= 0;
*/
