# Complete binary design loader source; exactness still open

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`src/ui/DesignBaseLoad.cpp` now provides the full CDesignBase binary parser
and its source-visible gauge initializer. Two functions become source-present;
**no exact function or byte is added**.

```bash
python3 scripts/build.py --unit gpt-web-design-base-load --compare --json
# Expected exit1: parent EH relocation blocked; gauge initializer nonexact+5.
```

## Observed format and ownership

The complete loader `40B000..40BA69` remains2666 bytes/860 instructions, SHA256
`756f150004243d88a9dd987bcf9aec662b7a4c7caf808a789a72749adf2b16e2`.
Fresh CFG traversal resolves all seven table entries at40BA6C and reaches all
860 instructions, including the two nonreturning vector-range failure sites.
Thirty static virtual read sites recover this stream:

| Part | Fields |
| --- | --- |
| Header | ignored four-byte signature; unsigned texture count |
| Each texture | unsigned filename byte count; counted filename bytes; signed x/y/width/height words |
| Object header | unsigned object count; then unsigned ID and signed one-byte tag per object |
| Tag0: sprite | texture index; signed x/y; flags word |
| Tag1: base object | signed x/y |
| Tags2..5: gauge | texture index; signed x/y; flags word; mode is tag minus2 |
| Tag6: number | texture index; signed x/y; six signed words: glyph width, glyph height, columns, spacing, integer digits, fractional digits |

The loader ignores open/read results and the signature value. Source preserves
those calls and their data destinations. Split-path processing writes the
directory and extension outputs; the latter buffer is reused for counted
texture filenames. Each name buffer is cleared to260 bytes, then composed with
the directory using the target-owned `%s%s` format. There are three real260-byte
buffers, without artificial stack padding.

The temporary native rectangle vector is filled from a zero rectangle; the
owner's native handle vector at+4 uses `assign(count,0)`. Texture handles and
rectangle fields use checked `at` access while loading. Factory selection uses
checked subscripts. Number objects retain the otherwise-unused rectangle
subscript's validation, then use their separately supplied dimensions. The
explicit discarded-value expression preserves a real observed check rather
than allocating an unused local.

The four allocation sizes are AC/18/BC/E4. Raw RTTI names the owners
CDesignSprite, CDesignObjectBase, CDesignGage and CDesignNumber. Their sprite,
gauge and number members begin at+18. Member RTTI independently confirms
CTile -> CSpriteBase -> IColor, CSprite -> CSpriteBase -> IColor,
CGage -> CSprite -> CSpriteBase -> IColor, and CNumber -> IColor.
The source uses genuine polymorphic construction and guarded physical layouts;
there are no manual vptr stores or copied instruction bytes.

Positions convert signed integers to float fields+0C/+10. Sprite/gauge flag
bit0 sets scale X to-1 and Y to1. Nonzero IDs are inserted without replacing
an existing map key, then the new object is disabled. All recognized objects
are appended to the owning list; unknown tags consume no extra payload.
Existing list/map state is preserved, and the final member iterator becomes
list begin. RAII owns the file and temporary rectangle vector. Objects remain
raw pointers before publication, matching the observed construction model.

## Source boundaries and remaining compiler differences

The selected source has a2532-byte callable plus28 adjacent switch-table
bytes. These are **unrelocated structure facts**, not a2532-byte canonical
match. The target has an aligned EBP frame; the ordinary source omits it.
Strict comparison first blocks on the unqualified function-local symbol
`__ehhandler$?load@CDesignBase@th105@@UAEXPBD@Z`.

The target's46-byte handler6BE6A6, FuncInfo6E4E68 and two unwind entries are
independently pinned. Source FuncInfo also has two states, but this does not
establish equal frame offsets, funclets or metadata. No address binding is
introduced to bypass that missing proof. The native Construct_n/Assign_n,
map insertion/list growth and factory-construction boundaries also need honest
TU/ABI recovery before a whole-parent canonical comparison can pass.

For texture loading, source calls the actual normal-ECX public99-byte
`TitleResourceManager::load_texture @ 404C90`, whose four stack arguments and
RET16 were freshly verified from the target. The original loader inlines this
operation through405090/409080/405200. Recovering that source visibility is
still required. The new unit uses the public declaration only; it neither
includes nor copies the inherited naked-assembly implementation. No ordinary
external facade is invented for those private entries.

The old unsupported `int load` header declaration becomes a source-facing
`void load`. The four independently accepted43FCA0 caller sites ignore EAX;
the parent cleanup does not publish an intentional result. Original nominal
return spelling remains an inference, rather than a new ABI theorem. The
implementation contains no fabricated return value.

## Gauge initializer and bounded controls

`CGage_initialize_texture @ 41B280` is a complete360-byte/107-instruction
RET12 callable, SHA256
`e160e6a43225f641135b7b956e43102d8d1c34aa8a6e1962761abbc81a26d93a`.
The factory passes its CGage member in ESI, mode in EAX, and handle/width/height
on the stack. The normal public size query404E60 receives the **handle parameter
as its width-output destination**, plus one height-output local.

The genuine same-TU C++ helper preserves that alias, writes dimensions/mode,
handle/pivots, UV spans and quad coordinates, colors/Z/RHW, scale and angle.
Interleaving reused float lifetimes with their vertex stores recovers all65
x87 operation forms under strict FP with exceptions off. Stack scratch homes
and integer scheduling still differ; this is not native numerical, unmasked
exception, arbitrary alias or exact coverage. Source mode is in **ECX**, while
the target requires **EAX**. Both caller and callee are defined together; no
external declaration pretends that those private contracts already agree.

| Private control | Full helper size/result |
| --- | --- |
| double-valued ratios | 277, nonexact |
| float ratios, default FP/exceptions off | 317, nonexact |
| strict FP, four hoisted float locals | 356, nonexact |
| strict FP, immediate exceptions on | 362, nonexact |
| strict FP, interleaved reused floats | 360, nonexact+5; selected |
| texture publication inside query argument | 360, nonexact+5 |
| genuine file-local cdecl definition | 358, nonexact+5 |
| mode-last source parameter order | 360, nonexact+5 |
| genuine internal-class member definition | 368, ordinary thiscall/nonexact+0 |

Same size and instruction count confer no exact credit. These bounded results
leave original member/free-function spelling, private register lowering and
larger TU/LTCG visibility open; they do not prove an impossibility.

## Durable state and replay

The loader's existing authored rule retains its selection and gains current
source evidence. A new positive rule classifies only the360-byte gauge helper,
with its full target hash, reachable factory call and CGage vtable witness.
All197 predecessor selectors are unchanged; only these two bounded witness
sets were revalidated. `matches.csv` is unchanged.

The shared return declaration's full quoted-include closure has15 units,
including the new pending unit. All **50 predecessor accepted functions in
14 actual consumers** were rebuilt serially and remain exact. No unrelated
unit, cold aggregate replay or new aggregate percentage is claimed.

Selected source SHA256:
`0702b0758d231a105cf3dd7aa59d3e4f13bef26f79353bc370e985cca2efbec3`.
Formal COFF SHA256:
`a7389135f6063f4d6f64dad66f6d14cfb4efd2bb3087212dc1619c6f1f074a55`.
Facts, frozen controls, source/EH structure, comparison failures and all
affected replays are under `build/design-base-loader-source-20261021/`;
private recipes are in the same-named `.analysis/` directory. IDA rejects its
wrong-target session; no Ghidra session or database mutation is used. Builds
run serially on CPU0 at nice10.

Next work must qualify the EH/TU boundary and recover real private texture and
gauge helper visibility. CDesignBase cleanup40BB40 and Reimu496540 remain open.
