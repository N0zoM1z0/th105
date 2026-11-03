# Fighter outcome selector source, 2026-11-03

The existing fighter outcome-selector source is now tracked individually. Native `0x45E120` spans 620 bytes, SHA-256 `5a84fe2d72fc87b44efa204195345867c9c95be0a8a46c38b20709d907dc6feb`, with 185 decoded instructions and eight `RET 4` exits. Freshly exact battle outcome A and dispatcher call it at `0x46D4CB` and `0x46D849`.

The source selects reaction outcomes from the observed low-byte attack flags, current frame flags, fighter state, practice settings, random policy and relative position. Source and field names describe the recovered behavior, not known original spelling. Earlier bounded type and source-lifetime controls are summarized in `KNOWLEDGE_BASE.md`.

The separate public `exact-first-outcome-selector` unit compiles to 610 bytes against native 620, with first mismatch at offset 20 from a register-allocation choice. It remains nonexact; the ten-byte size difference is not a count of byte mismatches. No forced register, partial-byte or exact credit was added. The existing exact sibling/dispatcher unit remains separate and passes. Fresh receipts: `build/frontier-outcome-selector-20261103/source.json` and `caller.json`.
