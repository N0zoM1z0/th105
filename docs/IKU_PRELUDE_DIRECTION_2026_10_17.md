# Iku object998 prelude direction ownership, 2026-10-17

Target is original Japanese1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete620920 root remains59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Evidence comes from the hash-attested PE and direct read-only Ghidra.
The mandatory IDA preflight rejected its wrong image; that session was unused.

## Observed contract and selected source

Before the main dispatch, actions150..153,154..157 and158 prepare object998
at calls620A0C/620A70/620ACC. Each independent branch reads byte104 once,
zero-extends it to the outgoing **DWORD direction**, and sign-extends its low
byte for the X offset. Multipliers are71/58/43; double Y additions are137/87/136.
Both coordinates retain their observed float round trips. Action and position
are re-read after each possible opaque spawn; the branches cannot be collapsed
on an assumption that the callback preserves actor fields.

The selected C++ captures a fresh `const int direction = byte_at(0x104)`
inside each branch, passes that raw value, and uses its signed-char conversion
only in the X calculation. The first preparation now emits MOVZX EAX followed
by MOVSX ECX,AL, and its CALL reaches620A0C, the target address. That address
agreement is incidental evidence, not a function or byte acceptance result.
No public type/layout, virtual ABI, profile or relocation mapping changed.

The target loads EDI=1 at620984, before the outer action149/159 guard.
The candidate still loads EBX=1 later. A private control naming the shared
variant1 before that guard, and using it for the flag and all three calls,
produces the **same entire canonical section** as the selected capture.
It is unselected; merely naming the literal does not recover its lifetime.
No volatile/register/assembly/padding or fabricated ABI is used.

## Native evidence and its boundary

The new `--prelude-spawns` whole-entry fixture passes **0/7086 mismatches**:

| Cases | Scope |
| ---: | --- |
| 5760 | All nine active action IDs, raw directions00/01/7F/80/FF, eight raw X and eight raw Y values, x87 PC53/64 |
| 336 | Signed action-range boundaries, flag751=0/1/255, directions-1/+1, block186=0/1, PC53/64 |
| 990 | Compact110-action routed-entry grid, sequences0/1/2 and frames0/7/12 |

Geometry includes signed zeros, subnormals, maximal finite X, Inf Y and
quiet/signaling NaNs. Exceptions stay masked. Geometry cases must reach the
actual465190 entry for object998, and their direction/variant/payload/count
words must equal `[facing & 255, 1, 0, 0]`. There are5832 object998 entries,
648 per active action, including72 guard cases. The other routed cases add
eight later object entries. Every target/source outcome and recorded actor,
call arguments, payload and global/RNG state agrees at its stop boundary.

The compact grid covers entry routing, not every action body: for example,
above-surface ground inputs can reach their real action9 callback early.
The fixture stops at the first selected final backend. Opaque spawn
continuation, callback mutations that change a later prelude branch, unmasked
FP exceptions and full-game equivalence remain unproved. Helpers run their
actual instructions; no return injection or executable/vtable patch is used.

The negative control changes only the three outgoing direction arguments
to signed-char extension. It detects **2304/5760 mismatches**,256 per action,
exactly the two negative byte values. One example changes outgoing128 to
4294967168 while preserving the coordinate words. The control intentionally
exits1. It is neither a selected source change nor a target patch.

| Profile | Input SHA-256 | Target-output SHA-256 |
| --- | --- | --- |
| Positive | c35ca64d9c48821aeeb7724e8cdc5aa06f9a7c9293090028f3686b37e6b2a0ff | 1450aaefcd7d1c57b3c49e5445a7017e9977ced92d7727c7e9e04304661e713b |
| Wrong direction | 0c37b7f70494d7ed1b2ac3d15236d9b44f5b3e26d0aa63d21f4520a9c0f04d0e | 198314ddbca69592abd2378aa29ca046a193ed7d90a948fab91f762c04f5231e |

## Whole-root result

Selected source CRLF SHA-256:
`a406a5e5c5853ba2c5b9d4b27cdea43458da731589fc4d87aa191b0e3a8c8bca`.
The native-tested and configured objects replay to identical **59462-byte**
canonical sections, SHA-256
`a96a9185a2c717315108dc8b8e8cc7064ebbd99144b0b8942c63989e60ab75a4`.
This is16 bytes smaller than prior source d6a5f127/section018be2dc.
The strict59038-byte comparator still fails first at **+0x64 /620984**.
No exact or partial authored credit is added.

Fresh complete CFG audit finds14990 reachable instructions,58302 instruction
bytes in a58305-byte callable span, three internal alignment bytes, metadata
at58308 and1157 following alignment/metadata bytes. There are128 RETs,
862 ordinary/177 register CALLs,33/42/35 switch tables, no local CALLs and no
external tails. Register-call count now equals target177, but incoming-action
groups still differ. Compiler regrouping affects the suffix as well as the
prelude; this is **not** a claim that all other bytes remain identical.

Internal owner diagnostics rise7 to8/109:2/4/5/10/204/215/303/696.
Frame400hex and84 natural payload homes remain, with84 singleton/bijective
conditional action/physical-ordinal constraints,57 identity and no reported
constraint issues;182 spawn calls/190 action-site records. Candidate
pre-epilogue14734 PCs/16896 states compare with target14870/16959.
These are conditional static correlations, not payload-value or feasible-path
proofs. All six73-byte atan2 preparations still equal target at their new
candidate starts628D45/628F54/629168/6293E1/62D825/62D9AC.

The17-action common height/clear incoming set remains intact at candidate
62ECAE/62ECBB. The310/409 advancement call remains shared at6245CD versus
separate target624612/625893; its previous0/1992 callback profile belongs to
the d6a5f127 source checkpoint and was not routinely replayed here. Target/
candidate advancement107/106, height19/18, clear30/28 and facing9/10 remain.
Initial constant1 placement, joint outgoing/exit sharing, original C++/TU/
inheritance/optimizer and full post-backend behavior remain open.

## Independent analysis and reproduction

One read-only Ghidra clone, limited to768MiB/two CPUs, re-attests imported/file
identity, entry, mapped .text, language/compiler and the complete root. It
reads back the initial MOV EDI,1, each MOVZX/MOVSX/PUSH and all three calls.
The guard span620979..6209C0 has SHA-256
5c687e36b64a9a80e9a711aa2b1e93d3f9d26b0cddf4868dad12a051562195b8.
The81-byte preparations6209C0/620A24/620A80 have SHA-256 respectively:

- 49f682adaed64c9dfbe249b46691d6800537d0a6dbef7f75a684b831c1ade9cc
- 8b3c7f6b0e4c9311cfb51a2162d26802cbb8f7ed88e4854bea620eea673096b1
- bb85885286556f3e3fe984b86a1e92da64fd4eed5035b07ba8feea8e11fe81f3

All nine primary project files remain unchanged; the disposable clone is
removed. Reports live under `build/iku-one-lifetime/`; private control patches
live under `.analysis/iku-one-lifetime-20261017/`. Superseded source/object
controls and caches can be deleted and rebuilt; retain current proof objects
and the small genuine-provider cache. No accepted-unit matrix was replayed.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --prelude-spawns --output build/iku-one-lifetime/IkuPreludeDirectionsNative.obj
python3 scripts/probe-iku-upper-actions.py --prelude-spawns --control prelude-direction --output build/iku-one-lifetime/WrongPreludeDirectionNative.obj
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/iku-one-lifetime/IkuPreludeDirectionsNative.obj
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
```
