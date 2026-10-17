# Iku MT visibility: retained calls and x87 state

The complete `Iku_dispatch_action_state_vslot28 @ 0x00620920` remains
nonexact. This bounded follow-up explains a concrete difference between the
ordinary-provider and MT-visible LTCG candidates. Exposing the MT translation
unit lets the generated root retain an x87 value across 16 MT calls. Marking
both MT functions `noinline` leaves the entire generated root byte-identical.
This supports interprocedural preservation information as a lead; it does
not identify the original compiler flags or a particular optimizer pass.

## Pinned inputs

- Original Japanese 1.06a executable SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- Target root `[620920,62EFBE)`: 59,038 bytes / 15,132 instructions;
  SHA-256 `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
- Unchanged selected `src/characters/IkuActionState.cpp`, CRLF SHA-256:
  `69c43bf58dcfbeee08866a93b007fa266718a37c7850b79609056b3920fa864b`.
- Target preflight passed. Wrong-image IDA remained rejected; this follow-up
  used raw PE instructions and genuine linked candidates, without a database
  or target-byte change.

The ordinary/MT-visible images are the same-game-source checkpoints from
[the provider-visibility investigation](IKU_PROVIDER_VISIBILITY_2026_10_17.md).
Their receipts pin probe version
`c477031d6eda7e20dad87281fedadce69c01c58fe4f272c5a8e81182fbcb380a`.
The new noinline image was generated with the public opt-in control, using
45/45 cached compile inputs. The prior genuine full-link canonical replay
remains scoped to its recorded tool version; it was not needlessly repeated.

## Static observations

An independent normal-return CFG inspection used each exported entry, the
next MAP symbol only as an upper bound, actual HIGHLOW relocations and
contiguous switch-destination runs. It did not require a hardcoded 33-entry
low table. All discovered transfers close without external tail transfers.

| Image | Root symbol envelope | Reachable instructions / bytes | Switch entries | Direct MT calls | x87 depth before MT calls |
| --- | ---: | ---: | --- | ---: | --- |
| Target | 59,038 | 15,132 / 59,038 | 33 / 42 / 35 | 19 | 19 at depth 0 |
| Ordinary providers | 59,504 | 15,002 / 58,344 | 33 / 42 / 35 | 19 | 19 at depth 0 |
| MT provider visible | 59,488 | 14,742 / 58,258 | 32 / 42 / 35 | 19 | 16 at depth 1; 3 at depth 0 |
| MT visible, seed/next noinline | 59,488 | 14,742 / 58,258 | 32 / 42 / 35 | 19 | 16 at depth 1; 3 at depth 0 |

The candidate envelopes include following metadata and are not accepted
compiler/function boundaries. Ordinary/MT-visible direct ordinary-call
counts are 863/853. These static counts do not establish action feasibility,
value equivalence or an exact result. The MT-visible low switch exists with
32 entries: the older strict COFF-table recognizer's failure was not evidence
that the switch disappeared.

x87 propagation accounts for every floating instruction present in these
roots, the reviewed ST0-return callees and `ftol`'s ST0 consumption. Every
normal-return join is consistent and every RET has depth zero. This is a
scoped depth calculation, not a general proof of callee preservation or
floating-value/exception equivalence.

A concrete ordinary-provider site spills a QWORD before the genuine MT call:

```text
10001B06  FLD  DWORD PTR [ESI+EC]
10001B0C  MOV  BL,BYTE PTR [ESI+104]
10001B12  FADD QWORD PTR [10022CC0]
10001B18  FSTP QWORD PTR [ESP+18]
10001B1C  CALL mt19937_next_u32
```

With the MT provider visible, the corresponding value remains live in ST0:

```text
10001B15  FLD  DWORD PTR [ESI+EC]
10001B1B  MOV  BL,BYTE PTR [ESI+104]
10001B21  FADD QWORD PTR [10022CC0]
10001B27  CALL mt19937_next_u32
```

Both visible variants retain all 19 direct MT call sites and have first-byte
entry mismatches. Their complete 59,488-byte raw root envelopes are identical,
SHA-256 `e45690d2b46e5cdaae1d30740183c07e883e07ede75c15931ca2b1b63f6f8859`.
`noinline` therefore does not recover the ordinary/target spill or prologue.
The control changes only two declarations in a generated build copy of
`Mt19937.cpp`; selected game source and canonical compilation profiles stay
unchanged. No synthetic floating clobber or false ABI declaration is added.

## Genuine helper execution

`scripts/probe-iku-mt-preservation.py` runs actual target instructions and the
linked MT bodies in Unicorn 1.0.2. It pins each receipt, image and MAP hash,
requires unique MT symbol addresses and rejects another Iku source/target.
The target helpers are:

| Helper | Bytes | SHA-256 |
| --- | ---: | --- |
| Seed `406670` | 64 | `6b243ded53f47d320824fa2fa31056026b41685c3f269d8bdefc8d11a53a8bd0` |
| Next `4066B0` | 279 | `f90693c2a6c176316bba3d1b1a83f94916893866dd276dc5ae2dc4b19db7b9a4` |

Before every call a normal float80 value is live: mantissa
`C000000000000001`, exponent `3FFF`. Its low mantissa bit cannot survive a
binary64 round trip. Cases cover genuine seeds 0, 1 and 119, plus index 625
with zero state to exercise the real default-seed path; control words `027F`
and `037F`; and 626 consecutive draws, crossing the twist and refill edges.

For both visible/noinline contexts, **10,016 paired draws pass with zero
differences**. Checks include EAX, all 624 state words and the index, real
RET/ESP, EBX/ESI/EDI/EBP, float80 bits, control/status/tag state. Execution
must remain inside the pinned helper image's `.text`; writes are confined
to the MT state/index and stack. No callee result or return is injected.

Input SHA-256:
`827959a8e7c9107eb732b7c18fcce6d3a23006ad05524fd1ef985b2ad52c58b1`.
Target-output SHA-256:
`e6be64b7fedfa20c42a2ab816a63bb06d1ef3a2fd0040c462ff6de199d22accd`.
The different-seed control initializes the source from genuine target seed 1
while the target uses seed 0: **2/2 differences**, expected exit 1.

This verifies those real helper bodies with a live value. It does not run the
complete Iku root, DLL startup or post-backend paths, and does not infer the
original compiler's formal call-preservation contract. No exact credit is
added; the ordinary whole-root comparison remains nonexact at `+0x64`.

## Reproduction and next work

```bash
python3 scripts/probe-iku-action-ltcg.py --reuse --provider-visibility cross-v106a-mt19937-next
python3 scripts/probe-iku-action-ltcg.py --reuse --provider-visibility cross-v106a-mt19937-next --mt-noinline-control
python3 scripts/probe-iku-mt-preservation.py build/iku-action-ltcg/provider-visibility/235111e6218f11bf build/iku-action-ltcg/provider-visibility/235111e6218f11bf-noinline
python3 scripts/probe-iku-mt-preservation.py build/iku-action-ltcg/provider-visibility/235111e6218f11bf build/iku-action-ltcg/provider-visibility/235111e6218f11bf-noinline --control different-seed
```

The final command intentionally returns 1. These are diagnostic visibility
builds, not canonical full-root comparators. Local reports are
`build/iku-mt-boundary-public-{noinline,native,control}.json` and
`build/iku-mt-boundary-static-facts.json`; generated artifacts stay untracked.
The ordinary visibility context remains `e3b0c44298fc1c14`.

Retain ordinary MT opacity for the canonical source while investigating
the shared effect ST0 join, landing-tail ownership and action 730's extra
facing call. Repeating broad `/GL` or noinline toggles has no new evidentiary
value without a more specific source/context hypothesis. The original TU
partition, optimizer phase and full-root value/exception equivalence remain
open. Accepted units, shared ABI/layout and exact ledgers are unchanged.
