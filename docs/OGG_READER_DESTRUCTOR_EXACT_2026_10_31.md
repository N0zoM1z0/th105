# Ogg reader-owner destruction: complete 15-byte exact replay

The independently bounded BgmOggDataSource destructor418A00 now matches all15
bytes. Native and canonical source SHA-256:
e6da22a17b7dd1d51029151d7c09de1f84e1153f347f5e98d3e697c0e19a602e.

The existing ordinary source models the reader-owning prefix through
BgmOggReaderBase and the composed decoder data. This is an observed ownership
adapter, not proof of original nominal class names. The reader pointer is
conditionally deleted through its real virtual destructor. The stream body
still owns codec close before member cleanup, so no close operation is moved
into this destructor. No C++ source body or ABI declaration changed in this step.

Genuine CIL naturally emits the private EAX entry and all15 native instructions.
No assembly, explicit register, fake convention or wrapper is added.

## Exact private parent and third cleanup

The existing stream destructor402880 remains fully exact220/220, including all
three cleanup actions, handler6BD8DE/27, FuncInfo6E3ED4/36 and unwind map6E3EBC/24.
Its third cleanup at6BD8D3 is11 bytes: load the actual parent receiver from the
stack, add the observed decoder-member offset30h, then tail-jump at6BD8D9 to
418A00. The complete source/native preparation and branch match.

The exact parent is itself private, reached through its independently verified
real release caller404270. Each child comparison freshly replays the parent's
entire body, existing private-entry witness and full EH packets. The nested
entry witness is preserved in the child receipt. Release itself remains
nonexact and receives no credit.

The cleanup contract now handles only the two observed bounded forms:
an8-byte stack receiver/address plus tail, or an11-byte stack receiver load,
same-register positive member offset and tail. Both sides must match every
preparation byte and reach the selected actual source/native destructor.
A parent may be exported or independently direct-call witnessed; deeper,
source-only or EH-role-only parent paths are rejected. The exact-parent rule
and normal whole-child comparator are unchanged. The complete EH graph is
not replaced by an indexed handler-only claim.

## Focused regression and accounting

Fresh replay preserves:
- the existing220-byte stream and139-byte DirectSound resource destructors;
- all13 previously accepted CSV/script/file-buffer roots, including the prior
  eight-byte cleanup-edge form;
- the independently accepted89-byte stream constructor.

Three additional regressions cover the11-byte member-offset form, a wrong
register despite equal byte hashes, and retention of the private parent's
independent entry proof. The11 cleanup-contract tests are target-independent.

The mixed constructor unit's other candidate still blocks its all-functions
comparison; only the requested accepted constructor is claimed freshly exact. No
cold all-unit corpus or game execution was performed.

Only this15-byte authored body is added. Compiler cleanup bytes and the reader's
virtual callees receive no duplicate credit. The source-only lifetime origin
rule now skips both exact destructors and still owns only release/lookup.
Totals become1,555 exact /441,708 bytes. Source1,752, ownership1,772,
exclusions1,640, review615, mapped1,779 and match units745 are unchanged.

Promotion also exposed a pre-existing duplicated BGM origin-rule identifier.
The constructor/allocator scope keeps its original ID; remaining member-lifetime
release/lookup evidence now has a distinct ID and the two census references
follow it. The allocator's already-exact constructor edges are represented as
selected-body calls to a matching target, rather than asking the source-only
selector to reselect that constructor. Both complete affected rules pass fresh
native validation. A new CI invariant rejects duplicate origin-rule IDs.
No unrelated census rules were rebuilt or relabeled.

Final default CI passes192 tests; generated progress and whitespace checks pass.
