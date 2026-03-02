/* run.config
   OPT: -rpp
*/

/* Semantic negative: function pointer parameter is reassigned before use.
   RPP resolves the indirect call based on the ORIGINAL formal mapping (&inc),
   but the body reassigns fn to &dec. The generated wrapper uses inc_aux_1
   (inc's contract) instead of dec, making the proof use the wrong contract.

   The property happens to be trivially true (equal inputs => equal outputs
   regardless of which function is called), but the generated proof system
   is semantically incorrect: it reasons through inc's contract when dec
   is actually called at runtime.

   KNOWN LIMITATION: RPP does not track parameter reassignment. */

/*@ assigns \result \from x;
  @ ensures \result == x + 1;
*/
int inc(int x) { return x + 1; }

/*@ assigns \result \from x;
  @ ensures \result == x - 1;
*/
int dec(int x) { return x - 1; }

typedef int (*unary_fn)(int);

/*@ requires \valid_function(fn);
  @ assigns \result \from fn, x;
*/
int apply_reassigned(unary_fn fn, int x) {
  fn = &dec;           /* reassign the parameter! */
  /*@ calls inc, dec; */
  return fn(x);        /* calls dec, not inc */
}

/*@ relational
      \forall int x1, int x2;
      x1 == x2 ==>
      \callpure(apply_reassigned, &inc, x1) ==
        \callpure(apply_reassigned, &inc, x2);
*/
