# Youmu typed virtual calls, 2026-10-02

## Retained result

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 target bytes. Fourteen raw function-pointer calls now use existing
virtual member declarations: three self sequence selections in action214,
nine peer action changes in actions525/526, and two self frame selections in
actions600/603. Three unused cached-callee locals are removed. The shared
header, layout, helpers, compiler flags, relocation maps and object partition
are unchanged.

Fresh configured comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `2C`. Candidate metadata starts at `+0x9304`, versus target
`+0x933C`; its body is 56 bytes shorter. All97 physical switch destinations
and33 low entries remain distinct. Strict instruction/edge diagnostics reach
**27/98**, gaining low215 without losing any preceding26 identical owners.
This is diagnostic progress, with **zero new canonical exact credit**.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`05640450098076ee043c7c94d5fc46d9bd5a130ec229902293dd42474d0fc09c`.
Canonical compared candidate-window SHA-256:
`d222ca2b2461fb80bda278f16fc4924d1407500838b91004bbed6e9d36967e25`.
The compared window includes candidate metadata and is not a body hash.

## Raw target evidence and source inference

**Observed:** original Japanese v1.06a PE SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
entry point `0x0068B9D2`. The attached wrong-target IDA preflight still fails;
its output is not used. These observations use the attested PE directly.
No new Ghidra process or database observation is involved.

The fifteen Fighter primary-table bases are reconstructed from
`config/roster-fighter-vtable-origin-anchors.toml`. Fresh raw reads confirm
their RTTI locator offset is zero and every table shares these three slots:

| Slot | Youmu pointer DWORD | Callee | Existing accepted call view |
| --- | --- | --- | --- |
| `+8` | `0x006C514C` | `0x0045BFE0` | `int set_action_and_finalize(short)` |
| `+0x0C` | `0x006C5150` | `0x0045C390` | `int select_sequence(int)` |
| `+0x1C` | `0x006C5160` | `0x0045C180` | `int set_sequence_frame(short)` |

The action wrapper forwards a four-byte stack argument slot to the base
setter, which consumes its low word, then calls virtual `+0x3C` and returns
with `RET4`. The frame method reads the low argument word, writes the frame
word at `+0x140`, calls `0x0045C110` and returns with `RET4`. The accepted
callee source and exact units remain unchanged. The selector's existing
`int` view is reused; this checkpoint does not establish a unique original
selector parameter width or declaration. See the
[preceding ABI evidence](YOUMU_VIRTUAL_ABI_2026_10_02.md).

Action214 target calls at `531E42`, `531EE6` and `531F35` select6/5/5 after
negating the velocity field. Vptr and slot loads interleave with that field
store. **Inferred source:** ordinary inherited `select_sequence` expressions
replace the cached callees, preserving facing conditions, field stores and
return/join paths. The preceding callbacks already used ECX and a four-byte
argument slot; this change is not evidence of a former machine calling-
convention error. There is no intervening call or write to the primary vptr
between the old callee snapshot and invocation. Original source spelling and
optimized load placement remain inferred.

The peer calls load ECX from self`+0x170`, then read that object's primary
vptr and slot8, without an adjustment. Examples are `5353A6`/`53543B` for
actions100/102 and `5355DF` for action53. The complete nine peer sites are
`5353A6`, `53543B`, `535517`, `5355C0`, `5355DF`, `5357B9`, `53584E`,
`5359D6` and `5359F3`. **Inferred source:** those calls use the shared
`AnimationSequenceObjectView` prefix and its action member; existing peer
pointer reloads and the two real cached receiver lifetimes are preserved.
The exact original peer class declaration is not recovered.

Frame calls `536968` and `5372E5` supply ECX=self and push9 through slot1C.
They now use `set_sequence_frame(9)`. These changes are byte-neutral relative
to the corresponding typed-selector candidate. Narrow action/frame constants
fit the accepted word arguments; ignored return values do not require a
void-return function-pointer declaration.

## Diagnostics, controls and unresolved lifetimes

| Serial VC8 probe | Observation | Disposition |
| --- | --- | --- |
| Three action214 typed selectors | 27/98; metadata `+0x9314`; gain low215, no losses. | Retained. |
| Add two typed frame calls | Same canonical window as selector-only. | Retained accepted call view. |
| Add nine typed peer action calls | 27/98; metadata `+0x9304`; no losses. | Retained. |
| Both frame and peer changes | Same window as typed-peer probe. | Retained through configured rebuild. |
| Three action214 float-zero variants | Byte-neutral to preceding checkpoint. | Not retained; no original zero type established. |
| Explicit nested first-facing branch | 25/98; metadata `+0x92B0`; loses low11. | Not retained. |
| Effect125 coordinates inside call arguments, alone | 26/98; metadata `+0x92A4`; local trailing-prefix/sine-Y/cosine-X order improves. | Private source hypothesis. |
| Effect125 argument schedule combined with typed calls | 26/98; metadata `+0x92F8`; gains low215 but loses low11. | Not retained; original expression/order remains open. |

**Observed zero lifetime:** target loads zero at `531C6C`, compares velocity
against that live value repeatedly, discards it before conditional virtual
calls and reloads zero afterward. It does not cache velocity across those
calls. The candidate still has three extra velocity FLDs in action214.
Changing the zero carrier alone does not recover the target lifetime.

The effect125 probe locally reproduces target preparation of trailing
arguments before sine at `531D44`, Y rounding/outgoing store at
`531D5B/531D63`, cosine at `531D70`, and X rounding/outgoing store at
`531D94/531D9C`, before effect call `531DA1`. Its Y association remains
`(sine*100+selfY)+100`. A closer local schedule is not whole-root equivalence;
the combination's register/layout regression remains unresolved.

Fresh explicit-object packets still cover all138 target/candidate masked
floating guards, with zero owner-count differences or unordered-only leads
under ordinal hypotheses. All49 physical spawn payloads resolve without
conflicting modeled ESP merges; the same six normalized payload-address
owners differ. Arithmetic counts stay349/348 with three multiset leads in
601/696/710. Load/store multiset leads decrease14->13, removing low220.
These scans do not prove full operand, precision or exception equivalence.
Virtual physical-site totals are107/106 at slot8,31/31 at slotC,12/13 at
slot14 and2/2 at slot1C. Static site counts do not prove absent runtime calls.

The TH08 reference and its actual FSINCOS/FRNDINT examples are recorded in
[the angle audit](YOUMU_ANGLE_RANGE_2026_10_02.md) and
[the float-carrier audit](YOUMU_FLOAT_CARRIERS_2026_10_02.md). Neither
instruction occurs in this callable. The remaining x87 lifetime and sharing
differences do not establish an assembly requirement, and do not describe
the out-of-root trigonometric callees. No assembly is added here.

## Reproduction and remaining work

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh configured reports are
`build/youmu-typed-virtual-final-20261002.json` and
`build/youmu-typed-virtual-final-owners-20261002.json`. Explicit-object guard,
stack, arithmetic, load/store and call packets use the same prefix and date.
Private controls are under `.analysis/youmu-velocity-lifetimes-20261002/`
and `build/youmu-velocity-lifetimes-20261002/`; the fresh fifteen-table raw
readback is `primary-sequence-vtables.json` there.

The remaining work is target-backed recovery of zero/value lifetimes,
argument schedules and physical shared tails, followed by complete canonical
replay. Original local types, TU partition and compiler context remain open.
Whole-root exactness is required; no aggregate cold-replay claim is added.
