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

Current result:257/native259, first+59 is the changed forward branch distance.
The remaining substantive difference is optional-resource pointer load/reuse
and its downstream register choices. No exact or source-selection credit.
Receipt: build/frontier-45dc90-20261028/typed-selection-size.json.
Target SHA:9c5d531d1681747f13fea73e643355017f3be8cabcf65fbca0e41a6bfa91e23d.

The existing front-ready118-byte accepted peer remains exact in the fresh
original GS-off unit. Existing nonexact advance198 and consume346 retain
their +46/+204 residuals. Receipt:
build/frontier-45dc90-20261028/affected-peers-final.json.
Only this TU's two explicit profiles were built; no shared header changed.

The new EH relocation is independently read from the canonical prologue and
handler prefix at6BAD3B. It is an address witness, not acceptance of the
remaining body or its generated auxiliaries. Original nominal sprite type/TU
visibility and optional-resource scheduling remain unresolved.
