# Iku effect62 direction and outgoing arguments

This bounded investigation concerns the six-action effect continuation in
`Iku_dispatch_action_state_vslot28 @ 620920`. The selected reconstruction
source remains unchanged. The new native fixture separates the raw direction
argument from its signed use in the X offset and rules out two additional
source shapes in the current compiler context. Whole-root equality remains
unproved; there is no new exact or partial authored credit.

The target is original Japanese TH10.5 v1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` is59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The wrong-image IDA session was rejected; no IDA semantic observations were
used. A direct read-only Ghidra clone independently attested file/imported
identity, entry point, full mapped .text, language/compiler and root bytes.
It read back all six argument preparations and the shared call. Its nine
primary project files remained unchanged; the clone was deleted.

## Target observations

Actions416/417/565/566/567/568 still share call626C3B to435240 and the
vslot14 sequence transition. The merge at626C34 is a **partial outgoing
argument join**: trailing1, direction and Y are already on the stack; X
arrives in ST0 for `FSTP DWORD [ESP]`.

At626BF4, action416 reads byte104 once with `MOVZX EAX,BYTE [ESI+104]`.
It pushes that zero-extended DWORD at626C08, then uses `MOVSX EAX,AL` at
626C09 for the signed `*47` X offset. Action417 repeats this at626F83.
Consequently raw80/FF become outgoing128/255, while their offset meanings
are-128/-1. The callee's existing direction parameter remains a full int;
narrowing its ABI would discard the distinction established by the caller.

416/417 explicitly round both `Y+132` and `X-signed_direction*47` to float.
The X store/reload at626C2C/626C30 precedes the shared outgoing store; removing
that rounding is not justified by the ST0 join. The scratch integer, rounded
Y and rounded X reuse the same initial-stack home, ESP+10, at different
times. The raw-X actions565..568 round `Y+150` and load X directly, preserving
its signed zero without an arithmetic zero offset.

The six independently checked preparation spans are:

| Action | Target span | Bytes |
| --- | --- | ---: |
| 416, including shared call | [626BF4,626C49) | 85 |
| 417 | [626F83,626FC8) | 69 |
| 565 | [629DCE,629DFD) | 47 |
| 566 | [62A5A0,62A5CF) | 47 |
| 567 | [62AE01,62AE30) | 47 |
| 568 | [62B6A9,62B6D8) | 47 |

These are instruction/dataflow observations. Original variable declarations,
translation-unit structure and the optimizer pass responsible for sharing
are still unknown.

## Focused native evidence

`scripts/probe-iku-upper-actions.py --sequence-effects` now tests raw direction
boundaries00/01/7F/80/FF, represented as signed input bytes0/1/127/-128/-1.
These are diagnostic byte-domain inputs, not claims that every orientation
value occurs during normal play. The fixture retains both x87 control words,
signed-zero/subnormal X, finite Y, neighboring frame/timer gates, sequence
indices, enable bytes and resource gates. Each action must actually reach
the effect with all five zero-extended direction values.

The selected source passes **0/2664 mismatches** from the real whole-root
entry:1568 effect entries,672 action entries,24 object entries and400 RETs
per side, covering588 target-root instructions. Actual helpers execute; no
helper return is substituted. Direction histograms are recorded per action.
Effect entry counts are302/302/180/180/302/302. Negative-zero outgoing X
counts are10/10/30/30/50/50.

The new `--control effect-direction` deliberately sign-extends only the
outgoing direction. It detects **624/2664 differences**, distributed
120/120/72/72/120/120. An80 example passes128 in the target andFFFFFF80 in
the control, with the same effect id, X, Y and trailing argument. The fixture
therefore checks the DWORD argument rather than merely its low byte.

- Input SHA-256:
  `b2074bb2378efe8c8e5adc0c6a7f87a990e70d04ab5817c2b296e7a01bb1cc43`.
- Target-output SHA-256:
  `d506036a933bc41116ef64b1587b67bc30527fb4f1986a7b2ebada0a8001fc92`.
- Selected CRLF source SHA-256 remains
  `c9a1c3e4715f18e19991fd7d5b19239fda5b482b1b1beaa4d6c13c41b867bda6`.
- Configured and native objects reproduce the identical complete59478-byte
  canonical section, SHA-256
  `ec153b60cb6f2d40487e486a25c78d619efcd901ae01291d9c1c7b88f3a361f6`.

Effect execution, its return and the subsequent sequence callback remain
outside this native scope. Their continuation is static control-flow evidence.

## Rejected source controls

An early int carrier captures byte104 before the coordinate expressions,
reuses its signed low byte for416/417's offset and passes its raw value to
the existing shared call. It retains exactly the six-action incoming set
but still spills X. The section grows59478 ->59510, with15001 instructions,
128 RETs and54 effect sites. Canonical section SHA-256 is
`636a89b293deff1cdcb3d63c36b877fc829692a6e3b542b44bab8929fa19ae8d`.
It remains nonexact+64 and is unselected.

A second control puts each genuine effect/next-sequence/return directly in
its branch. Its arguments are `float(X-float(facing()*47))` and
`float(Y+132)` for416/417, or raw X and `float(Y+150)` for565..568, with
unchanged raw direction and trailing1. This restores one direction read in
416/417 and removes the extra raw-X spill. However, the compiler emits five
effect sites for the six actions: one shared by416/417 and four separate
raw-X sites. Whole-root effect sites grow54 ->58, register calls178 ->182,
RETs128 ->132 and the section grows to59782 bytes/15106 instructions.
Canonical section SHA-256 is
`1e7122868625cf9873ed349be414dec2feeb629fd3964fe940197baae208f164`.
Giving Y an explicit shared float local is whole-section byte-neutral.
Both controls are unselected; native equivalence is not claimed for them.

The direct-argument control also received a genuine `/GL` root / `/LTCG`
link with the existing ordinary game providers, SDK and CRT. The private
recipe changes only the root source path and retains its original include
directory. It reused43/44 compiler objects and rebuilt the root. All switches
close;901 HIGHLOWs and866 direct calls replay over59792 envelope bytes,
including ten explicit trailing alignment bytes. Effect sites remain58:
this tested link context does not restore the six-way partial argument join.
The strict59038-byte comparison still first differs at+64/620984. The image
was not executed. This is not evidence of a general standalone/LTCG barrier.

## Reproduction and remaining work

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --sequence-effects --output build/iku-effect-direction/IkuEffectDirectionsNative.obj
python3 scripts/probe-iku-upper-actions.py --sequence-effects --control effect-direction
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/iku-effect-direction/IkuEffectDirectionsNative.obj
python3 scripts/ci.py
git diff --check
```

The strict comparison and intentional negative control exit1. Reports are
under `build/iku-effect-direction/`; private source recipes are under
`.analysis/iku-effect-direction-20261017/`. Obsolete controls, linked images
and database clones are disposable; retain the small genuine-provider cache.
No public ABI, layout, shared header, accepted profile, relocation ledger or
exact ledger changed. No accepted-unit matrix or aggregate cold replay was
needed. The selected source's extra X home and earlier argument join remain
unresolved, alongside initial constant1 lifetime and other call-sharing gaps.
