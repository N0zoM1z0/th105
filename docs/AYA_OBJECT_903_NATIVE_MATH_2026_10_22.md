# AyaObject903 actual math and alpha-read epochs

## Bounded result

Root61A290 remains nonexact. This audit executes sequences2/3 from the actual
root entry through RET using original target math and frame helpers. It adds
numerical evidence without selecting a source change or adding exact credit.
Target is exclusively original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The IDA session again fails identity and supplies no semantic evidence.

Observed mode table61F080 identifies sequence2 at61E744 and sequence3 at61E858.
Both check owner health, update phase6 fields, call435160 with the heading pair,
and move X/Y. Sequence2 adds the target double at6C4270 to field11C and
multiplies field120 by the target double at6C0EC8; sequence3 uses6C41D0/6C4298.
Both first round/store the scale product as float before the optional second
fade multiplication. Sequence2's fading interval is:

```text
61E827 FMULP ST(1)
61E829 MOV AL,[ESI+113]
61E82F FSTP [ESI+120]
61E835 CMP AL,20
```

Sequence3 performs its second FMUL at61E91B and jumps61E829. The current source
stores the second product before reading alpha. This reconfirms the older
[fade-tail observation](AYA_OBJECT_903_FADE_TAIL_CONTROLS_2026_10_02.md) against
fresh target bytes and the current complete object, rather than trusting it.

## Original native dependencies

The new `scripts/audit-aya-object-903-native.py` reuses the Aya animation fixture
with action903 and its real vtable. It executes original435160, cosine4063D0,
sine406360, fabs68BAAE, control-word helper696387 and conversion68A1A0, plus
original4351C0 below its virtual-dispatch threshold. No helper return is mocked.
Code mappings stay read-only and every executed math instruction is checked
against the hash-attested PE. Unknown code or writes reject the run.

The3600-entry lookup table is produced by executing original4065B0 at PC53,
including its cardinal overrides, via `iku_native_math.lookup_fixture`.
Its14400-byte SHA256 is
`c134fa85e7988574c2db386dc8e14de2113d6e465c18f4503bd265219c5ca898`.
The initializer is an observed dependency, not a newly accepted boundary or
ownership claim. No host-generated trigonometric values are substituted.

## Executed matrix

3168 cases cover sequences2/3, eight masked precision/rounding control words,
phase0/6, initial/fading states, alpha19/20/255, signed facing, counters179/180,
eight finite heading values, three finite magnitudes, and scale bit patterns
including adjacent floats, signed zero, subnormal, largest finite, infinities
and quiet/signalling NaNs. Ninety-six owner-health0/-1 cases retire before math.
The valid runs execute3072 oriented calls,6144 fabs/conversion calls,12288
control-word calls and2688 actual frame-helper calls.

The current selected source agrees in every case on complete actor memory,
parameter memory, ordered writes, helper calls, final x87 status/tag, stack
cleanup and saved registers. Alpha reads differ in1920 fading cases: all1920
have different write counts, status/tag and live x87 registers at the read;
1584 also expose a different stored scale value at that instant. These are
read-epoch observations, not1920 differing final gameplay outcomes.

The audit records only live physical x87 register slots according to the tag
word; empty-slot residue is excluded. It reports read epochs separately from
normal effects, so an effects pass is never a claim of instruction timing or
canonical equivalence. This is finite masked-environment evidence, not proof
for arbitrary animation resources, virtual callbacks, unmasked exceptions,
other903 sequences or the complete root.

## New source control, not selected

A real `double faded_scale` product, followed by an alpha snapshot and the
float store, tests whether preserving the double-valued computation changes
the earlier float-carrier result. It compiles as a complete20064-byte root,
SHA256 `a4d109ae2b86e67ba11de79757aa8a59970c723b4f21c70cf2b262f3b4141b35`.
It still reads alpha **before** the fading FMUL, as with the old float-carrier
controls. Both target and candidate903 remain1697 versus1726 bytes.

All3168 final-effect cases also pass for this control. Its read/write epoch
counts and stored scale snapshots agree, but1764 live x87 snapshots differ;
960 also differ in status/tag. Thus checking only actor memory or write count
would miss the premature read. This control is not selected, even though it
moves one observable aspect closer. The original ordering and shared fade-tail
placement remain open; no native/LTCG impossibility follows.

## Callback failure handling

The preliminary trial uncovered an actual harness failure: the installed
Unicorn/ctypes bridge prints and swallows exceptions raised inside callbacks.
Missing fabs/control-word entries therefore did not stop that preliminary run.
Its results were discarded; only a short invalid-run diagnostic is retained.

`native_callbacks.guarded_callback` now catches callback errors, records them
and calls `emu_stop`. The shared Aya fixture clears the error list before each
execution and raises from it immediately afterward, before accepting RET or
memory observations. An injected failure at the actual435160 entry verifies
that a real Unicorn callback stops and is rethrown; unit controls cover failed
and successful forwarding. Newly verified math ranges come from the actual
callee instructions, not from permitting arbitrary PE execution.

Affected replays after this fix all pass:

| Fixture | Cases | Selected differences |
| --- | ---: | ---: |
|901 transitions/scale|6540|0|
|902 phase/speed|4288|0|
|902 spawn-entry prefixes|3744|0|

These successful replays replace reliance on the old callback exception
behavior for this affected scope. They do not validate unrelated emulators.

## Reproduction and remaining work

Private double-control recipe/source and build reports reside under
`.analysis/aya-903-native-20261022/` and `build/aya-903-native-20261022/`.
The initial invalid trial is clearly marked and supplies no accepted result.
Selected and control execution reports are `selected.json`/`double.json`;
`fault-injection.json` records the actual rejected callback; regression receipts
are `901-regression.json`, `902-phase-regression.json`, `902-spawn-regression.json`.

```bash
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-903-native.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-901-transition.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-902-phase.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-902-spawn-prefix.py
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/ci.py
git diff --check
```

`configured-formal.json` is the fresh selected build/comparison: full20064,
first mismatch34/hex22, target0F/candidate59, compared-window SHA256
`e51da96720d42d51649f5df692080214f82b3d3fa3004e889c64b59b812c63ad`.
The selected source, shared ABI, compiler profile, unit manifest and exact
ledgers remain unchanged. The next source experiment needs another supported
lifetime or merge-context lead; repeating float/double product snapshots alone
has not recovered the target's mid-product alpha read.
