# RPP: Complex Pointer Offset Support

## Task

Extend RPP to handle `TMem` with nontrivial offsets in relational properties:
struct field access (`p->field`), array indexing (`(*p)[i]`), nested combinations.

Currently RPP only handles `*p` (simple deref with `TNoOffset`) and `*(p + range)`.
All other `TMem(_,_)` patterns abort with "Unsupported term in separate generation."

## Setup: use a git worktree

Do ALL work in an isolated git worktree so the main checkout stays clean.

```bash
# From the repo root (the directory containing .git):
git worktree add ../rpp-pointer-offsets -b rpp/pointer-offsets

# Then cd into the RPP directory inside the worktree:
cd ../rpp-pointer-offsets/CybersecurityBenchmarks/framac-example/Frama-C-RPP
```

All subsequent commands (make, frama-c, test runs) should be executed inside this
worktree path. When the task is complete, commit your changes on the
`rpp/pointer-offsets` branch inside the worktree. Do NOT modify files in the
original checkout.

To clean up after merging:
```bash
git worktree remove ../rpp-pointer-offsets
git branch -d rpp/pointer-offsets
```

## What to do on each iteration

1. Read this file and `tests/rpp/pointer_offsets/` to understand current state.
2. Try to compile RPP: `make` in the RPP directory (requires Frama-C dev headers).
3. Run the test suite: `frama-c -rpp tests/rpp/pointer_offsets/<test>.c` for each test.
4. Compare output against the corresponding oracle in `tests/rpp/pointer_offsets/oracle/`.
5. If a test fails (RPP aborts or produces wrong output), fix the relevant visitor in the OCaml source.
6. Re-run all tests after each fix. Do not break existing tests in `tests/rpp/`.
7. Commit working changes frequently inside the worktree.
8. Update this file's progress section.

When all tests below pass and no existing test regresses, output `<promise>DONE_POINTER_OFFSETS</promise>`.

## Tests (write these FIRST, before any OCaml changes)

All tests go in `tests/rpp/pointer_offsets/`. Each test file has the standard header:

```c
/* run.config
   OPT: -rpp
*/
```

### Seed tests (provided below)

The 6 tests below are starting points. You MUST also write additional tests yourself
(see "Additional tests you must write" after the seed tests). The final suite should
contain **at least 20 test files** (aim for 25-30) covering every category listed.

### Test 1: `struct_field.c` — struct field access via pointer

```c
/* run.config
   OPT: -rpp
*/

typedef struct { int x; int y; } Point;

/*@ requires \valid(p);
  @ assigns \result \from p->x, p->y;
*/
int sum_point(Point *p) {
  return p->x + p->y;
}

/*@ relational
      \forall Point *p1, *p2;
      \callset(\call(sum_point, p1, id1), \call(sum_point, p2, id2)) ==>
      \at(p1->x, Pre_id1) == \at(p2->x, Pre_id2) ==>
      \at(p1->y, Pre_id1) == \at(p2->y, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
```

**What this tests:** `TMem` with `TField` offset in `\at(p->field, Pre_id)` terms
and in `assigns \from` clauses.

### Test 2: `array_index.c` — array indexing through pointer

```c
/* run.config
   OPT: -rpp
*/

/*@ requires n > 0 && \valid(a+(0..n-1));
  @ assigns \result \from a[0..n-1], n;
*/
int first_elem(int *a, int n) {
  return a[0];
}

/*@ relational
      \forall int *a1, *a2, int n;
      \callset(\call(first_elem, a1, n, id1), \call(first_elem, a2, n, id2)) ==>
      \at(a1[0], Pre_id1) == \at(a2[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
```

**What this tests:** `TMem` with `TIndex` offset in relational predicates.

### Test 3: `nested_struct_ptr.c` — nested struct with pointer field

```c
/* run.config
   OPT: -rpp
*/

typedef struct { int val; } Inner;
typedef struct { Inner *inner; int tag; } Outer;

/*@ requires \valid(o) && \valid(o->inner);
  @ assigns \result \from o->inner->val, o->tag;
*/
int read_nested(Outer *o) {
  return o->inner->val + o->tag;
}

/*@ relational
      \forall Outer *o1, *o2;
      \callset(\call(read_nested, o1, id1), \call(read_nested, o2, id2)) ==>
      \at(o1->tag, Pre_id1) == \at(o2->tag, Pre_id2) ==>
      \at(o1->inner->val, Pre_id1) == \at(o2->inner->val, Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
```

**What this tests:** chained `TMem(TMem(...), TField(...))` — nested pointer deref + field.

### Test 4: `assigns_field.c` — side-effect on struct field

```c
/* run.config
   OPT: -rpp
*/

typedef struct { int count; int total; } Accum;

/*@ requires \valid(acc);
  @ assigns acc->count \from acc->count;
  @ assigns acc->total \from acc->total, v;
*/
void accumulate(Accum *acc, int v) {
  acc->count += 1;
  acc->total += v;
}

/*@ relational
      \forall Accum *a1, *a2, int v;
      \callset(\call(accumulate, a1, v, id1), \call(accumulate, a2, v, id2)) ==>
      \at(a1->count, Pre_id1) == \at(a2->count, Pre_id2) ==>
      \at(a1->total, Pre_id1) == \at(a2->total, Pre_id2) ==>
      \at(a1->count, Post_id1) == \at(a2->count, Post_id2);
*/
```

**What this tests:** struct field offsets in `assigns` clauses + `\at(..., Post_id)`.

### Test 5: `pure_struct_field.c` — pure function with struct field arg

```c
/* run.config
   OPT: -rpp
*/

typedef struct { int lo; int hi; } Range;

/*@ assigns \result \from r.lo, r.hi; */
int range_width(Range r) {
  return r.hi - r.lo;
}

/*@ relational
      \forall Range r1, r2;
      r1.lo == r2.lo ==> r1.hi == r2.hi ==>
      \callpure(range_width, r1) == \callpure(range_width, r2);
*/
```

**What this tests:** struct-typed value parameter with `.field` access in `\callpure` context.

### Test 6: `separated_fields.c` — separation on struct pointer fields

```c
/* run.config
   OPT: -rpp
*/

typedef struct { int *data; int len; } Buf;

/*@ requires \valid(b) && b->len > 0 && \valid(b->data+(0..b->len-1));
  @ assigns \result \from b->data[0..b->len-1], b->len;
*/
int buf_first(Buf *b) {
  return b->data[0];
}

/*@ relational
      \forall Buf *b1, *b2;
      \callset(\call(buf_first, b1, id1), \call(buf_first, b2, id2)) ==>
      \at(b1->len, Pre_id1) == \at(b2->len, Pre_id2) ==>
      \at(b1->data[0], Pre_id1) == \at(b2->data[0], Pre_id2) ==>
      \callresult(id1) == \callresult(id2);
*/
```

**What this tests:** pointer-to-struct with pointer field + array access through that field.

### Additional tests you must write

After creating the 6 seed tests above, **design and write at least 14-24 more test files**
(for a total of 20-30) covering the categories below. Use the seed tests as style references.
Each test should be a self-contained `.c` file in `tests/rpp/pointer_offsets/` with a clear
name reflecting what it exercises.

Study the existing tests in `tests/rpp/` to understand RPP's annotation syntax and
what patterns already work. Then look at the OCaml AST types (`TField`, `TIndex`,
`TNoOffset` and their nesting) to reason about which combinations need coverage.
Every test should target a *distinct* pattern — do not write near-duplicates.

#### Category A: Struct field variations (write 3-4 tests)

- Multiple fields read in a single relational predicate (e.g. 3+ fields)
- Write to one struct field, read another (`assigns p->x; \at(p->y, ...)`)
- Struct with mixed-type fields (int, pointer, char) accessed in the same property
- First vs. last field of a large struct (offset zero vs. non-zero)

#### Category B: Array index variations (write 3-4 tests)

- Constant index other than 0 (e.g. `a[3]`, `a[n-1]`)
- Variable index in relational predicate (`\at(a[i], Pre_id)`)
- Negative-offset-style access via pointer arithmetic (`*(a + i)` vs `a[i]`)
- 2D array or pointer-to-pointer indexing (`a[i][j]` / `(*a)[i]`)

#### Category C: Nested / chained offsets (write 3-4 tests)

- Three levels of nesting: `p->a->b->val`
- Struct containing array field: `p->arr[i]`
- Array of structs: `arr[i].field` through a pointer
- Struct containing struct (by value, not pointer): `p->inner.field`

#### Category D: Assigns / side-effect with offsets (write 2-3 tests)

- `assigns p->field` where only some fields are modified, others preserved
- `assigns a[i]` — single array element as side-effect location
- Multiple `assigns` clauses with different field offsets on the same struct pointer
- Post-state comparison of both modified and unmodified fields

#### Category E: \callpure and value-type struct offsets (write 2-3 tests)

- Pure function taking two struct-typed value parameters, comparing fields across both
- Nested struct passed by value (`Range` containing another struct by value)
- Pure function result depending on array element via pointer field in a by-value struct

#### Category F: Separation / aliasing with offsets (write 2-3 tests)

- Two struct pointers with overlapping field separation (`\separated(p1->x, p2->x)`)
- Separation between a struct field and an array element (`\separated(p->data, q[0])`)
- Aliased pointers: same base pointer appearing in two call args with different field accesses

#### Category G: Edge cases and stress tests (write 2-3 tests)

- Empty struct or struct with single field (offset is always TNoOffset effectively)
- Union field access (if RPP should reject, test that it produces a clean error)
- Very deeply nested type (4+ levels) to test recursion depth
- Mix of `\at(..., Pre_id)` and `\at(..., Post_id)` for the same field in one property

### Naming convention

Name tests `test_07_<short_desc>.c`, `test_08_<short_desc>.c`, etc. (continuing from 07).
Keep each file focused on one pattern. Add a brief `/* What this tests: ... */` comment
at the top of each file (after the `run.config` block).

## Files to modify (OCaml source)

Based on code inspection, the following visitors need new match arms for `TMem(_, TField(...))`
and `TMem(_, TIndex(...))`:

1. **`rpp_generator.ml`** — `aux_visitor_6` (L404-416) and `aux_visitor_7` (L420-459):
   - Currently: `TMem(t, TNoOffset) -> OK`, `TMem(_, _) -> abort`
   - Need: handle `TField`, `TIndex` offsets by propagating them correctly.

2. **`rpp_predicate_visitor.ml`** — `supported_side_effect` (around L200-218):
   - Currently: `TMem(_, TNoOffset)` accepted, `TMem(_, _)` rejected for assigns/from.
   - Need: accept field/index offsets and track them through the side-effect map.

3. **`rpp_predicate_visitor.ml`** — separation checker (L522-538):
   - Currently: only checks simple `*p` pointers for sharing.
   - Need: extract base pointer from `p->field` or `p[i]` patterns for sharing check.

4. **`rpp_visitor.ml`** — term visitor for `\at` with `TMem` (around L354):
   - Currently: only handles `Tat(TMem(t), TNoOffset, FormalLabel(s))`.
   - Need: handle `TField`/`TIndex` offsets inside `\at`.

5. **`rpp_predicate_visitor_axiom.ml`** — axiom term generation (L344-348, L888-911):
   - Currently: constructs `TLval(TMem(t), TNoOffset)` only.
   - Need: propagate offset from source term.

## Existing tests that must NOT regress

All files in `tests/rpp/` (excluding `pointer_offsets/`) must continue to produce
the same oracle output. Run `make tests` or diff against existing oracles.

## Progress

- [x] 6 seed tests written to `tests/rpp/pointer_offsets/`
- [x] Additional tests written (24 more, for 30 total)
- [x] `rpp_generator.ml` updated — `aux_visitor_6` and `aux_visitor_7` accept any TMem offset
- [x] `rpp_predicate_visitor.ml` updated — `supported_side_effect`, `sort_pointer`, `check_pointer` accept TMem with arbitrary offsets; added `build_term_valme_at` for nested TMem in `\at` context
- [x] `rpp_visitor.ml` updated — `visit_term` matches `Tat(TLval(TMem(t),off),...)` with any offset; added `visit_term_valme_at` and `build_term_valme_at` virtual; `check_result_from_formals` uses recursive base variable extraction
- [x] `rpp_predicate_visitor_axiom.ml` updated — `build_term_at_mem` propagates offset; added `build_term_valme_at`
- [x] `rpp_visitor.mli` updated — new `build_term_valme_at` and `visit_term_valme_at` signatures; `build_term_at_mem` and `visit_term_at_mem` accept offset parameter
- [x] All 30 new tests pass
- [x] No existing test regressions (11 pre-existing failures unchanged)
