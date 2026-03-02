/* run.config
   OPT: -rpp
*/
/* What this tests: Category E — pure function result depending on field of a by-value struct */

typedef struct { int len; int cap; } Header;

/*@ assigns \result \from h.len, h.cap; */
int remaining(Header h) {
  return h.cap - h.len;
}

/*@ relational
      \forall Header h1, h2;
      h1.len == h2.len ==> h1.cap == h2.cap ==>
      \callpure(remaining, h1) == \callpure(remaining, h2);
*/
