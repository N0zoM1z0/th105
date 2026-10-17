# Iku steering argument lifetimes

Action730 in `Iku_dispatch_action_state_vslot28 @ 620920` now constructs its
two atan2 arguments in the target order and reuses the target scratch home.
Both73-byte preparation intervals agree byte for byte with the target.
They are internal root intervals, not independent functions or exact credit.
The complete59038-byte root remains nonexact at+64hex/620984.

The executable is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` is59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The candidate, authored origin, durable name and source selection were
checked before editing. Wrong-image IDA was rejected and supplied no semantic
evidence. Direct Ghidra independently attested the file/imported identity,
entry point, full mapped .text, language/compiler, root and bounded intervals.

## Observed target and selected source

Sequences7/8 call atan2 at62DB0B; sequences9/10 call it at62DC89. Both paths
read the peer pointer from170 and signed facing from104, subtract the actor's
X from the peer's X, multiply in x87 and round the X result to float. They
then reload that result into outgoing slot ESP+4 **before evaluating Y**.
The peer-Y subtraction is rounded to float and put into outgoing slot ESP.
The signed integer and both rounded coordinates reuse the same initial
ESP+10 scratch home at different times.

The preceding source calculated two float locals before the call. VC8 kept
X and Y simultaneously in separate homes and delayed the outgoing X store.
The selected source retains the explicit float X local, binds peer Y as a
const field reference, and evaluates the rounded Y difference in the actual
call expression. There is no new callable, external ABI, field-layout change
or manually placed stack storage. The reference describes existing float
storage; it does not invent an original C++ declaration.

| Target preparation | Selected preparation | Bytes | SHA-256 |
| --- | --- | ---: | --- |
| [62DAC2,62DB0B) | [62D835,62D87E) | 73 | d5af31aecb4de70f5b4e003ef86c28f67fffd5a4c43c3a14ac4819c49f0dd0c7 |
| [62DC40,62DC89) | [62D9BC,62DA05) | 73 | dd55731ce833ac416f3ea3dbf339ee782bfdad65b2c9a8d51a407c821a6f8a0a |

These spans contain no CALL displacement or masked field. Equality was
checked over all73 bytes in each span, including the actual ESP operands,
FILD/FMULP, float round trips and outgoing stores. The following calls still
resolve to the genuine406540 under ordinary canonical relocation replay.

Complete canonical section comparison against the priorc9a1c3e4 source finds
**only40 changed bytes**, all inside those two preparations. Every other
section byte, including the switches and following metadata, is identical.
The section remains59478 bytes,15000 reachable instructions/58318 instruction
bytes in58321 callable span,128 RETs and862 ordinary/178 register calls.
There are no local CALLs or external tails. Owner diagnostics remain7/109;
neither that count nor the two internal intervals constitutes exact credit.
Fresh payload correlation retains84 singleton/bijective constraints,57
identity,182 spawn calls/190 action-site records and frame400hex. Candidate
pre-epilogue PCs14744/states16900 are unchanged. These are conditional
action/physical-ordinal diagnostics, not payload-value or feasible-path proof.

- Selected CRLF source SHA-256:
  `c8140ff0c2ca77ebd7440f8f756f0224eee29d984fb290dc66b43324539635af`.
- Complete canonical section SHA-256:
  `7684266d089d10a0937dda3b9aa2ec770f5dbac76b1f636d530a5bb99377a6e8`.
- Previous complete canonical section SHA-256:
  `ec153b60cb6f2d40487e486a25c78d619efcd901ae01291d9c1c7b88f3a361f6`.

## Focused native verification

The expanded `--steering-clamps` profile passes **0/4960 mismatches** from
the real whole-root entry. Configured and native objects normalize to the
same complete59478-byte section. The3840 existing finite-geometry cases
continue through genuine atan/lookup/facing helpers and both-axis clamps,
ending in3312 RETs and528 actual sequence-backend entries per side.

The additional1120 cases stop at the genuine atan2 entry and compare its
two full float argument bit patterns, actor state and prior call trace.
Each sequence7/8/9/10 contributes280 entries: five signed byte facings,
both x87 PC53/PC64 control words and28 coordinate quadruples. The quadruples
cover every signed-zero combination, adjacent/cancelling finite inputs,
subnormals, maximum finite values, infinities and quiet/signaling NaN payloads.
The wider facing domain is diagnostic input, not a gameplay-feasibility claim.
The exceptional arguments do not execute the math backend or require an
invented result. Both roots retain empty x87 stacks and the input control word
at every observed stop;252 target-root instructions are visited overall.

The new `--control steering-facing` changes only730's X multiplier to use
the unsigned direction byte. On the same1120 argument cases it detects
**368 differences**, including signed-zero argument differences. This
calibrates the signed-facing/float argument contract separately from the
subsequent aim and clamp behavior. No dependency return is replaced.

| Profile | Input SHA-256 | Target-output SHA-256 |
| --- | --- | --- |
| Positive4960 | 55ce43b0a4164e125b5e8fd41b27605b6a3d53f27ff9aba55882362120158653 | ccd9c0d9cb9c5d4f3d0969929e53077f1df404a857431fddfd184c1b50f85290 |
| Wrong-facing1120 | 2058440db364c2a79436b59d482a8a857045678be1d77965e3ba4a7c0fe6e375 | 0d9a36e78a595c73079eb42c3ac47dda0caf4a64c833f7f0723e27ed79eafd79 |

Backend return/continuation, unmasked floating exceptions and full-root
behavior remain outside this evidence. Other native profiles retain their
earlier source hashes; they were not habitually replayed.

## Rejected controls and remaining work

| Source property | Canonical section | Observation |
| --- | ---: | --- |
| Both arguments expanded with existing value accessors | 59538 | VC8 materializes extra peer-coordinate return temporaries; unselected. |
| Both arguments read directly from peer fields | 59474 | One scratch home is recovered, but FIMUL replaces target FILD/FMULP; unselected. |
| Explicit X local, Y value accessor in the call | 59494 | Target X multiplication remains, but the accessor return adds a Y temporary; unselected. |
| Explicit X local, peer Y field reference | 59478 | Both complete73-byte preparations agree; selected. |

All tested shapes retain five physical730 facing sites versus four target
sites. In particular, the candidate still duplicates the face call after
the final Y lower-bound split. Target62DBE9's two paths pop the remaining
x87 bound and converge at62DC16/62DC18; the185-byte mode/clamp interval is
unchanged by this source correction. Original source/TU/compiler pass and
the cause of that duplication remain unknown. Initial constant1 lifetime,
the six-action effect's outgoing join and310/409 sharing also remain open.
No standalone/LTCG barrier is established.

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --steering-clamps --output build/iku-730-facing/IkuSteeringArgumentsNative.obj
python3 scripts/probe-iku-upper-actions.py --steering-clamps --control steering-facing
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/iku-730-facing/IkuSteeringArgumentsNative.obj
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/ci.py
git diff --check
```

Strict comparison and the deliberate control exit1. Reports remain under
`build/iku-730-facing/`; private control recipes are under
`.analysis/iku-730-arguments-20261017/`. One read-only768MiB/two-CPU Ghidra
clone was used, reached through a temporary build-path symlink because
headless rejects leading-dot project path components. All nine primary files
are hash-unchanged; the clone and alias were removed. Superseded private
objects/sources are disposable. No shared header/profile/layout/relocation,
exact ledger or accepted unit changed; no aggregate cold replay was needed.
