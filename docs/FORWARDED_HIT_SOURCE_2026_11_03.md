# Forwarded hit quantity source, 2026-11-03

The complete native hit-quantity routine at `0x46C5B0` is 301 bytes, SHA-256 `6744639bcb6d16e6df7e569fc02d712bf942c90a6f3a8590d427b72339bbc35a`, with 82 decoded instructions and `RET 0x18`. The exact AttackObject forwarding method calls it at `0x45C082`; both functions in that caller unit freshly replayed.

The retained source covers conditional scratch reset, dynamic quantity scaling, counter and owner updates, possible health recovery, damage and terminal handling. The former manually indexed vtable call is replaced by the existing `CBattleManager` typed virtual interface. Both actual BattleManager vtables identify slot `+0x2C` as `0x472490`, the independently reviewed depletion callback. This is the same target-backed interface used by the existing general-hit resolver; no manual vptr access or custom calling convention remains in this function.

The public `exact-first-forwarded-hit-quantity` probe emits 299 bytes against native 301, with first difference at the entry. It is source-present and nonexact; a two-byte length difference is not a claim that only two bytes differ. All seven actual relocation fields are replayed, and no exact or partial bytes are awarded. Receipts are `build/frontier-forwarded-source-20261103/source.json` and `caller.json`; the prior private typed-interface control is under `build/frontier-forwarded-virtual-20261029/`.

## Recovery recipient correction, 2026-11-06

The original recovery path loads the attack candidate's owner from `+0x16c` into EDI at `0x46C670`. It reads that owner's health and maximum at `0x46C685` and `0x46C695`, then writes the capped result to that owner at `0x46C6A2`. The prior source instead read and wrote the separately supplied fighter, which is used for the subsequent damage path. The source now restores the observed recovery recipient and retains the owner across the conversion. The recovery condition remains unchanged.

Moving initialization of the applied quantity to after the preliminary scratch-reset path follows the native instruction order. The focused unit now emits 297 bytes against the 301-byte native body, with the first relocated comparison mismatch at +191, rather than a mismatch at entry. The local cap comparison uses the native `cmp` and `jl` direction, but the conversion/register scheduling and virtual-call scheduling still differ. This is not an exact match and receives no exact-byte credit.
