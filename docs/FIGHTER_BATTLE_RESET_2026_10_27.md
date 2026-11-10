# Fighter battle reset 0x00460200

The retained complete FighterInitialization.cpp body was corrected at this
checkpoint but remained unselected and nonexact. It has since been selected
and classified as authored; it still has no exact credit. The original
Japanese1.06a target is1247 bytes, ending atRET0 at4606DE. Three returns include
two independent virtual action700 tails. The native EBP value seen by IDA is a
conditionally saved local, not a usercall argument.

Fresh target metadata/entry/mapped bytes/inventory attestation and raw decoding
precede the scope. The direct IDA launcher still lacks mcp1.26.0. Decompiler output
was used only as a provisional guide.

## Corrected source and independent evidence

- Default state4B8 reads the already attested g_fighter_state_4b8_default6FA880,
  not the stale6E4E20 literal.
- Sequence mode432520 is the accepted SpellDataOwner::set_sequence_mode byte
  member. Its receiver is Fighter+4F0 on both branches. The old stdcall
  declaration omitted ECX and is removed.
- Sequence clear45FC80 is a no-argument member operating on the native20-byte
  deque header; its native body destroys sprite members and releases blocks.
  A declaration-only local member view replaces the historical fastcall name.
  This caller does not implement or confer credit on that helper.
- The native first-element access has three checked-iterator predicates.
  The real VC8 deque begin()[0] reproduces these checks without manually
  copying the STL guards. Bare *begin() omits one guard and is not selected.
- Native4605EE loads health once, stores maximum176 then current174. The chained
  assignment preserves that publication and removes the old repeated load.
- Signed record IDs below200 take the lookup branch; the other path writes-1.
  Both independently issue virtual action700 before returning, as shipped.

All other sparse stores and helper calls retain the observed order. The first
833 target bytes already matched after correcting the global, before the
sequence-mode/iterator work. No artificial locals, volatile accesses, fake
returns, assembly, target arrays or register coercion are used.

## Comparison and limits

Initial corrected-global isolation1231; real mode member1240; native *begin()
1209; full iterator subscript1251; actual one-read health publication and branch
ownership1247. Final source is1247/1247 with25 unequal byte positions, first
+853/460555, SHA-256
7b568c7c4fd87bcb204175e355f3e5e86c27add1df6a7d5a8003cf6c731ba31a.
This improves the historical29-difference note, but is not exact.

Remaining differences are CL/AL and other caller-saved register allocation,
the independent deque-address LEA placement, and virtual-call register choice.
Using an actual clear member rather than the ABI-equivalent one-argument
fastcall leaves these25 differences unchanged. Do not infer original nominal
type or LTCG impossibility, and do not continue spelling controls absent new
independent lifetime evidence.

Only this source's directly affected accepted fighter-input-phase unit is
freshly rebuilt and canonically compared. It remains exact. No whole corpus is
rebuilt. formal-public.json records the full root mismatch; affected-unit.json
records the accepted consumer. No gameplay execution is claimed.
The final local gate is local-ci.log in the same scope.

## 2026-11-03 source registration

The complete retained source is now selected by the reproducible
`exact-first-fighter-battle-reset` unit. A fresh pinned build gives the same
1247-byte canonical candidate and first mismatch at +853, with SHA-256
`7b568c7c4fd87bcb204175e355f3e5e86c27add1df6a7d5a8003cf6c731ba31a`.
It is still nonexact and earns no matching bytes.

The original whole-body hash and the native call at 4776D3 from the exact
346-byte Fighter extended reset establish authored ownership independently of
source similarity. The generic origin rule checks that body and edge. The
complete raw CFG closes 290 instructions and three returns; the function has
no unresolved indirect or external jumps. This does not establish the
original source spelling or untested runtime behavior. The target-specific
origin rule was validated directly; a full origin census did not finish within
the available factory command window and is not claimed here.
