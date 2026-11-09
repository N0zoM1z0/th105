# Iku, Tenshi and Udonge shared runtime providers

The three object-update hypotheses now call the existing CharacterObjectRuntime
implementations for motion, frame advancement, six-state advancement and phase
advancement. Twelve undefined method aliases and three empty motion-view classes
are removed. The shared runtime header, layout and implementations are unchanged.

## Original receiver evidence

The pinned Japanese 1.06a executable establishes every affected receiver across
the complete control-flow graphs, including all switch destinations:

| Caller | Motion 435160 | Frame 4351C0 | Six-state 4963A0 | Phase 64CD00 |
| --- | ---: | ---: | ---: | ---: |
| Iku 632C30 | 36 | 16 | 28 | 18 |
| Tenshi 64CD50 | 35 | 6 | 16 | 5 |
| Udonge 5D46C0 | 45 | 15 | 26 | 5 |

All 116 motion calls receive owner+4. The other 135 calls receive owner. The
analysis invalidates EAX/ECX/EDX after calls and retains pointer offsets at a
control-flow join only when every incoming value agrees. Existing target audits
also verify complete callable and metadata hashes, padding and table ownership.

## Complete affected comparison

Fresh before/after builds preserve all 339 non-debug COFF sections, including
bytes, section attributes and relocation roles. Only the twelve external symbols
and one compiler-local label change names. Complete canonical payloads and their
inventories remain identical:

| Caller | Candidate payload | Original payload | Candidate SHA-256 |
| --- | ---: | ---: | --- |
| Iku | 34196 | 34524 | 4873dcf1de935d6c2cea91eb22ad2f762eb8ffdef2c075e5abfa52e2f809d01b |
| Tenshi | 42508 | 41984 | 8f1b65b905861ec444115943dd9d9138cbc4b9e489d99b7d52c9a6250aef146c |
| Udonge | 43921 | 43537 | a7ffda570bf380a94ceff70c099bd035ae8f5fd915e73edadae7b86ccf26c03c |

The actual include closure contains these three update units only. The three
provider units were rebuilt as well: motion57, frame62, six-state66 and phase73
remain exact. The co-emitted Reimu update remains unchanged and nonexact.
These changes resolve real provider identities, not the parent functions'
existing byte differences. No authored exact credit or source-origin pin changes.

Private recipes and receipts are in
`.analysis/frontier-roster-runtime-providers-20261109/` and
`build/frontier-roster-runtime-providers-20261109/`. Each caller has a full native
receiver report and complete before/after payload report; `sections.json` records
the unchanged section comparisons. The pending input migration is untouched.
