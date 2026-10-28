# PatchouliObject complete update, 2026-10-28

`PatchouliObject_update_action_state @ 00520890` now has a complete manual
source hypothesis for30 primary actions and the default. It is **not exact**.
The whole callable and metadata were compiled/replayed before local controls.
No isolated case, normalized instruction stream, or matching count earns credit.

## Canonical observations

Target Japanese TH10.5 v1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw primary vtable6C4E24, slot28 cell6C4E4C, COL6DA55C and TD6E8348 identify
PatchouliObject and520890. The audit independently verifies this chain.
The following initializer52D200 and its existing source/unit are unchanged.

Callable `[520890,52CE69)` is50649 bytes, SHA256
`bf3a47cba713db2ffc1d72d9e3803aaa7b5b39e49da0ea11f34aed09ca8ab7ce`.
All12050 instructions decode. The CFG reaches12041 instructions/50606 bytes;
43 internal padding bytes occupy nine explicitly audited ranges. There are
82 RET0s,24 indirect virtual calls and550 direct calls to28 distinct targets.
No outgoing tail escapes the callable. ESP is aligned to8 with frame0x3E0.

Full payload `[520890,52D1FC)` is51564 bytes, SHA256
`6f0593093c471bd996eaa1f871a72f1339e80e5d0291a81224ba9b53608ac0cf`.
Three bytes of LEA alignment precede the first table. Twenty-one tables have
31,4,11,7,10,6,4,14,7,4,8,10,4,6,12,6,6,4,11,4,4 DWORDs respectively.
The primary remap has199 bytes at52CEE8; phase855 has20 bytes at52D114.
One NOP follows the primary remap. Four INT3 bytes separate the initializer;
they are excluded. All table edges, remaps and padding are covered without masks.

## Source evidence and limitations

The direct repository IDA preflight lacks its pinned MCP runtime; that session
was not used. Factory-native th105-ida was independently re-attested at19:57 UTC
against target metadata, entry68B9D2, mapped bytes, function inventory and its
46 operations. Decompilation was navigation only. Raw PE instructions are the
comparison authority. No target or database metadata was modified.

The new class is a pointer-only call view, not an allocation/layout claim.
Motion calls use this+4 and wave calls owner348. Native4351A0 ignores ECX but
520A0D explicitly supplies this+4, so this caller uses a member-shaped view
with the same two integer arguments and RET8. Sine406480/cosine4064B0/ratio4064D0
have float(int) contracts, unlike the double(float) quantized helpers.
Absolute406330 is a dependency ABI only; its ownership remains independently
under review and receives no new credit. No accepted shared header is changed.

Raw checks correct omitted ST0 consumers, signed owner tiers/counters,
unsigned RNG conversions, float-rounded intermediate speeds, height snapshots,
callback-sensitive pointer reloads and sequential phase tests. Phase800 alpha
exhaustion explicitly clears113 before retirement. Related-object and owner
receivers remain distinct. The target's unexpected owner/target action test in
856 and the extra final packet spawn in855 are retained, not normalized away.

The initial complete candidate was51492 bytes with frame428. A corrected
800 alpha-clear path/control orientation produced51460. The native816 pairs
of radial bursts reuse one packet, and856/910 out-of-bounds difficulty bursts
reuse their existing packet. Expressing those actual packet lifetimes removes
six unnecessary arrays and restores the native3E0 frame without padding,
inert locals, volatile stores or artificial register constraints.

Some910/920 difficulty switches have no native fallback initialization for an
out-of-range match identifier. The source retains the ordinary uninitialized
locals on that path; no invented safe default or fake register value is supplied.
Their original source lifetimes and invalid-identifier behavior remain unresolved.

## Selected whole replay

Command:
`scripts/repo-python scripts/build.py --unit exact-first-patchouli-object-update --compare --json`

The independently audited complete candidate is51428 bytes, SHA256
`0a0e3ac54833017e5be2e277bbf8b9ba977b5efd929d8d59940aaeed3fc35274`.
It differs first at+37 /5208B5 and has46381 unmasked differing positions over
the complete payload. Frame3E0, all28 direct-call target counts,24 virtual calls,
all21 table dimensions and all219 remap bytes agree. Candidate87 RETs versus
native82 and differing packet stack homes, control-tail sharing, expression
lifetimes and instruction scheduling remain. These agreements are diagnostics,
not an exactness percentage or acceptance.

Isolated unit: `exact-first-patchouli-object-update`.
Audit: `scripts/audit-patchouli-object-update.py`.
Receipts: `build/frontier-520890-20261028/{formal-build,full-audit,target-audit}.json`.
Private source preparation and raw navigation: `.analysis/frontier-520890-20261028/`.
Only source/mapping ledgers advance; `matches.csv` is unchanged. Existing accepted
units keep their prior receipts because no shared binding/profile/source changed.
