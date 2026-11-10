# Spell sequence preparation 0x0045DC90

The complete canonical259-byte body now has an independently checked typed
sprite-record candidate in SpellRuntime.cpp. Fresh typed sprite evidence from
the implicit copy constructor and rotation record motivated this revision.
The old opaque-buffer /GS blocker is resolved without disabling /GS: the real
0x98 local record contains two16-bit cells and a polymorphic0x94 sprite with
a typed0x80 base and five float extension fields. Normal destruction is empty;
ordinary generated EH retains the cleanup lifetime. No manual vtable stores
or copied assembly remain in this body.

Further corrected raw-target facts:
- The first bound compares the low signed byte of the deque's unsigned size.
- Fighter534 is selection_ids_34.live_count_10 inside SpellDataOwner at4F0,
  not an independent pointer. The current local view uses the real short deque.
- Record id is published directly to the local before the lookup call.
- The value1E is written before selector1 can override it with1.
- Optional texture setup uses current globals6FA6C4/6FA6C0 and helper406A60,
  not historical addresses or pointers to those globals.
- Final state55A reloads the post-enqueue live count; it does not reuse the
  pre-enqueue count.

Natural typed-record source initially emitted256 bytes with first mismatch+44.
A persistent deque reference produced257 with an extra EBP lifetime and was
rejected. Independent member size reads recover the native entry register
ownership and full-width initial count read. Selection size()==0 reproduces
its native MOV/test; empty() was byte-neutral against the old memory compare.

Current result:257/native259, first+59 is the changed forward branch distance. The
remaining substantive difference is optional-resource pointer load/reuse and its
downstream register choices. No exact or source-selection credit. Target
SHA:9c5d531d1681747f13fea73e643355017f3be8cabcf65fbca0e41a6bfa91e23d.

The existing front-ready118-byte accepted peer remains exact in the fresh original
GS-off unit. Existing nonexact advance198 and consume346 retain their +46/+204
residuals. Only this TU's two explicit profiles were built; no shared header
changed.

The new EH relocation is independently read from the canonical prologue and
handler prefix at6BAD3B. It is an address witness, not acceptance of the
remaining body or its generated auxiliaries. Original nominal sprite type/TU
visibility and optional-resource scheduling remain unresolved.

## 2026-10-31 implicit-copy layout control

After the rotation/copy checkpoint, a bounded local control gave texture04 to an
actual four-byte color-interface-derived sprite base, as independently proved by the
whole116-byte implicit copy. Fresh baseline and this control emit the same257-byte
preparation body and canonical compared hash
637bbd266bc8cbf15594bb7c0b13653ccbe5e68773722d282f8fba991d02234c. The native259-byte
body still compares optional resource in memory and reloads it for the texture call,
while both source variants load once into EAX and test that value. Base ownership
does not explain this scheduling difference. The source control is restored out; no
repeat of this base-only trial is needed. No ledger, match or count changes.

## 2026-11-03 source registration

Fresh target-backed comparison still emits257/native259, with no whole-function or
EH exactness claim. The complete 482-byte practice-control caller at `0x428070`
remains canonical exact and calls this entry at both `0x428238` and `0x428246`. The
native body hash and these two edges now anchor authored/source-present
registration. This adds no canonical exact bytes.

## November 8: shared record and complete cleanup proof

Preparation now constructs the existing `FighterSequenceSlot` directly and
passes it to `FighterSequenceController::enqueue_record` without a cast from
a duplicate local record type. Both size reads likewise use
`deque<FighterSequenceSlot>`, consistent with the existing render, update and
window consumers. The shared record is the same 0x98 layout: signed short ID,
unsigned short value, then the actual `CSprite` at +4. Native call `0x45DD6A`
enters the exact 114-byte enqueue implementation, which copy-constructs that
record into its queue storage.

Both affected compilation profiles preserve every byte and relocation role
in all 106 non-debug COFF sections after accounting for the corrected record
symbol. Their four complete comparison results are unchanged. The 118-byte
readiness method and independently rebuilt 114-byte enqueue remain exact.
Preparation still emits 257/native259 with its prior canonical source hash;
no new authored match is recorded.

The previously unproved exception regions now have complete local equality:
44 bytes of unwind/handler code at `0x6BAD30`, 44 bytes of unwind-map/FuncInfo
at `0x6E082C`, and the eight-byte record destructor at `0x45CF50`. The sole
unwind state destroys the record at frame -0xA4. The destructor writes the
`IColor` vptr to the sprite subobject at record +4, with no allocation release.
All code and metadata relocations are accounted for, and both complete main
CFGs and the auxiliary callable boundaries close. This narrows the remaining
work to the already-recorded main-body texture-load scheduling difference.

## November 9: actual deque insertion provider

The 114-byte callee at `0x45DBA0` is now independently identified as the real
`deque<FighterSequenceSlot>::push_back`, rather than an authored enqueue
method. Preparation calls that standard member directly. Both compiler
profiles preserve all four authored bodies and owned EH sections; the full
44/44/8 cleanup regions remain exact. The main preparation candidate retains
its prior 257-byte hash and is still nonexact. The incorrectly credited callee
is moved to compiler-generated ownership. See
`SEQUENCE_DEQUE_PROVIDER_2026_11_09.md`.
