# Shared Object action 980 compiler scheduling, 2026-10-02

## Bounded result

`CharacterObject_continue_action_980 @ 0x00596370` remains **nonexact** against the original Japanese 1.06a executable (SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`). The 323-byte target callable SHA-256 is `1ae566c8e8a9230cc7ce1ff75a2b472ef0b4886b1f63786506b2735dadecd7bc`. A fresh configured VC8 `/O2` build first differs at `+0x21` (`596391`), in the virtual sequence call's instruction schedule:

```text
target:    mov ecx,esi ; push eax ; mov eax,[edi+0x0c] ; call eax
candidate: push eax    ; mov eax,[edi+0x0c] ; mov ecx,esi ; call eax
```

The target and candidate remain 323 bytes; the prior 81/82 normalized-instruction diagnosis is consistent with this fresh first mismatch, but is not a canonical acceptance claim. The configured source SHA-256 is `2c41428d5e2380bf2a463b4cea9ed6edda1dc798e7e549eaf17028d1aed81f9b`; object SHA-256 is `765e9ec9318df09e95e060c637a715d338dafd5f380e27a4d9afda6959bcbea4`; comparison-window SHA-256 is `630689cd4a1b0878f271db397c357b06f05c9742010c1a9830a5a2936c3a8d32`.

**Private compiler controls:** VC8 explicitly reports warning `D9002`, ignoring `/G7`; its canonical comparison window is identical to the configured build. A single-TU `/O2 /Ot /GL` diagnostic DLL also has a 323-byte `.text` body and the same candidate call order at offset `+0x21`. Its link used `/FORCE:UNRESOLVED` and reported missing externals, so the DLL is not runnable or a canonical comparison object. This limited probe does not exclude the original TU/LTCG context or other supported compiler options. No compiler profile, source, or relocation contract was changed.

The private checker `.analysis/object980-g7-20261002/prove-scheduler-controls.py` verifies target PE and configured source/object identities, replays the COFF relocation bindings, checks the exact eight-byte scheduling windows, and checks both private controls. It writes `build/object980-scheduler-controls-proof-20261002.json`; the configured report is `build/object980-g7-baseline-20261002.json`. The attached IDA session still fails target identity, so only hash-attested PE bytes were used. No Ghidra import or aggregate cold replay is claimed.

The [AyaObject action-entry control](AYA_ENTRY_VSLOT0C_SCHEDULING_2026_10_02.md) independently found 11 virtual sequence sites with the same `ECX`/argument ordering issue. An existing exact `BattleInputGate_collect_battle_control_bits` source emits both orderings at two nearby member calls, so the order is context-dependent; neither a global CPU flag nor a register-forcing source edit is justified by these observations. The remaining path is independent original source/TU/compiler-context evidence. No exact-ledger credit was added.
