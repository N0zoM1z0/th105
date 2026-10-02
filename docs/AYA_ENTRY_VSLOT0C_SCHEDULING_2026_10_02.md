# AyaObject action-entry vslot +0x0C scheduling, 2026-10-02

## Bounded result

Freshly rebuilt `AyaObject_initialize_action_entry @ 0x0061F0B0` is still **nonexact** against the original Japanese 1.06a executable (SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`). Its target callable is 4,531 bytes, SHA-256 `31c7399e608cfc6eb2a663ca53a99e6d8eaf12df221cbe1d0440cbed4ba919bd`. The first canonical mismatch is at `+0xDF` (`61F18F`), in action 803. Both target and candidate action 803 have 60 bytes/18 instructions; the only local difference is the order of two instructions preparing its virtual sequence call:

```text
target:    mov ecx, esi ; push eax ; call edx
candidate: push eax    ; mov ecx, esi ; call edx
```

**Target/COFF observation:** the same five-byte order difference occurs at all 11 call sites using vtable slot `+0x0C` in this root: `61F18F`, `61F292`, `61F592`, `61F8D3`, `61F9EF`, `61FAEF`, `61FCBB`, `61FE76`, `61FEFD`, `61FFF1`, and `620225`. The hash-bound proof replays this unit's REL32/DIR32 bindings before comparing those candidate bytes with the target PE. All 11 target sites encode `8B CE 50 FF D2`; all 11 configured candidate sites encode `50 8B CE FF D2`. This repeated site class makes a per-action semantic rewrite an unsupported inference. The source-present shared action-980 primitive has a historically recorded instance of this same residual, but it is a separate function and no current exact claim follows from that record.

A private control removes case 803's heading-pointer local and reads the same real `heading_340[2]` directly. The entire canonical comparison window is byte-neutral. A separate `/O2 /Os` VC8 control changes the prologue at byte 0 and loses the configured action switch shape; it is not retained. These controls do not exclude other source spellings, compiler flags, original TU composition or LTCG context.

The configured source SHA-256 is `c9d1abb5e60a6f01529da98b4c955717febedd00672e470ee211633970f3004b`; object SHA-256 is `1bc34e3ca0bbc282b828c7f0b9d2b93a9c33ffac5ff620cc477eb21c95cfe4f3`; comparator-window SHA-256 is `a38cf5f048009bbad0328fc28e436774f91383844d365c8cc6669f6d20de2910`. Target traversal closes all 1,195 instructions/4,531 bytes through one 32-destination action switch, with zero unreached bytes or unresolved indirect exits. The configured candidate has 13/33 instruction-and-edge-identical owner rows, metadata at 4,532, and section tail 4,859. Neither metadata adjacency nor owner counts are exact-byte credit.

The private proof `.analysis/aya-entry-803-20261002/prove-scheduler-cohort.py` verifies the target hash, configured source/object hashes, relocation replay, 11 sites, direct-heading byte neutrality and `/Os` regression. Its output is `build/aya-entry-803-scheduler-cohort-proof-20261002.json`; configured comparison and audit use `build/aya-entry-new-baseline-20261002.json` and `build/aya-entry-new-baseline-audit-20261002.json`. The retained source, ABI, compiler profile, relocation contract and exact ledgers are unchanged.

The shared float-return `atan2_degrees @ 0x00406540` contract is already accepted in [the later angle evidence](ANGLE_ATAN2_EVIDENCE_2026_09_12.md); the original double-return paragraphs in [the earlier Aya note](AYA_ENTRY_EVIDENCE_2026_09_12.md) are historical. Further work needs independent original compiler/TU/LTCG evidence or a natural source expression that changes this entire repeated call class while preserving the proved switch and ABI. IDA preflight again failed target identity, so only hash-attested PE bytes were used. No Ghidra import or aggregate cold replay is claimed.
