# Texture-stage binding: complete source and call-order recovery

`TitleResourceManager_bind_texture @404DF0` is now source-present in
`src/assets/TextureStageBinding.cpp`, unit `gpt-web-texture-slot-binding`.
It remains **nonexact**: ordinary VC8 O2 emits102 bytes against the complete
107-byte target, first differing at entry. No matching row or partial exact
credit is added. This recovers a real direct dependency of CGage41B3F0;
neither caller nor binder receives exact credit from the other's progress.

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking checks pass. IDA still fails target attestation
with10350095... and supplies no semantic evidence. All observations use the
hash-attested PE; no executable or analysis database is modified.

## Observed callable, fields and behavior

The complete callable is `[404DF0,404E5B)`, SHA256
`c507bdb541478a700181ff1d1bfd3637cbc78261eed2de6390ec68fa1fb239fc`.
All45 decoded instructions are reachable through a closed local CFG, with
RET8 at404E22/404E58 and five following INT3 bytes. There are three CALLs:
indirect device calls404E13/404E4D and actual lookup417800 at404E37.
No remote tail, jump table or local EH region is owned by this callable.

ECX supplies the manager; two32-bit stack arguments supply handle and stage.
The body indexes the cache at receiver+64 with stage*4. The selected shared
view has eight cache cells in an84-byte prefix, with an explicit offset guard.
Original stage signedness and unique class/TU spelling remain unknown. The
retained TitleResourceManager name supplies an existing source call contract;
it is not fresh RTTI class-name proof. A void return view fits the caller ABI
and the cache-hit path, which assigns no defined result value.

The independently exact-backed D3D backend view places its device at
aggregate7036A0+20 =7036C0. The source uses `g_d3d_backend.device_020` and its existing
attested+32 relocation addend, rather than retaining an opaque standalone
global alias. The target dereferences that device's vptr and calls slot104,
the typed D3D9 SetTexture contract with device/stage/texture stack arguments
and callee stack cleanup. The manager receiver and device are distinct. Old
retained comments naming other device/manager addresses are not used as evidence.
Shutdown414C50 independently reads/releases/clears the three interface pointers
at7036BC/7036C0/7036C4. Original C++ global declaration grouping is not uniquely
proved; the selected aggregate is the existing target-backed source view.

The three policies are observed directly:

- Handle0 always calls SetTexture(stage,0), then stores cache0, even if that
  cache cell was already zero.
- An equal nonzero cached handle returns without lookup or device access.
- A changed nonzero handle captures the device vptr, calls the real lookup
  with the original receiver/token, reads the returned resource cell, reloads
  the global device pointer, dispatches SetTexture, then publishes the handle.

The API result is ignored before cache publication. Invalid stages or failed
lookups are not given new recovery behavior. The source retains the actual
virtual call and nests `*lookup_token(handle)` as its texture argument; it
does not hand-evaluate a vtable or fabricate a helper result.

## Compiler diagnosis and genuine context control

The ordinary typed C++ call already captures the device vptr before lookup
and reloads the device pointer afterward. The remaining discrepancy concerns
callee-save placement: the target saves EBX/EBP/ESI/EDI and a four-byte stack
slot at entry; the102-byte candidate saves EBX only on the nonzero branch and
EBP only on its cache-miss branch. Consequent parameter offsets and epilogues
differ. The purpose of the target's extra slot and its source/compiler context
remain unknown. No inert local, padding or register directive is added to
manufacture that frame.

Bounded controls are retained as diagnostics:

| Control | Result |
| --- | --- |
|Ordinary C++ call, C-style COM interface control|Both emit the same complete102-byte body. C interface spelling is not required by the observed read order.|
|Explicit zero/hit guard returns, GS on, strict FP, installed RTM, Z7, typed device global and backend member|Same whole102-byte body. The backend-member view is selected for its independently supported ownership.|
|Common cache-publication forms|95/96 bytes; unselected.|
|Single call with conditional texture argument|64 bytes; unselected.|
|Cache-cell reference / global-device reference|95/101 bytes; unselected.|
|Size pragma / global-optimization-off pragma|92/132 bytes and different frames; unselected.|
|Zi control|Compilation fails C1902, program-database manager mismatch. No successful Zi object/comparison or negative compiler-provenance conclusion.|

A genuine closed CIL context is also built with the actual native checked
vectors, token validation and scoped critical-section lock from
`ResourceHandleLookupRuntime.cpp`, plus the binder. Both real service entries
are exported with their observed normal ABI. Actual pinned compiler/runtime
libraries resolve all code; absolute bindings supply only attested game data
and IAT cells. No stub, executable-address absolute symbol, synthetic caller,
unresolved link or forced return is used. The resolved image is a comparison
artifact and is not executed as an application.

That context still emits the same102-byte canonical binder. Its source,
unit dictionary, DLL/map/bindings/CIL inputs, commands and provenance are in
`context.*`, `context-unit.json` and `context-comparison.json` in the build
scope. This is one genuine context control, not proof that every standalone
or LTCG arrangement is impossible. It does not accept the lookup's EH/private
vector-helper surface or change the selected lookup implementation.

## Native prefix audit and negative control

`scripts/audit-texture-binding-prefix.py` executes immutable target and
relocated source instructions for160 unique fixtures: stages0..7, four handle
words, distinct zero/equal/different cache words and null/valid device pointers.
The input matrix SHA256 is
`ab4e6a17b8488c5f795b611432f6fe876d5e71d45a9e0adbcc12ecbdbf485369`.
It compares ordered manager/device reads, modeled84-byte manager prefix,
writes and endpoint arguments. Actual RET8 completions check the stack and all
nonvolatile registers. Root code/CFG, PE identity and input pins are checked.

All160 selected prefixes agree:

| Endpoint | Cases | Scope |
| --- | ---: | --- |
|RET8|48|Actual cache-hit return; no device or lookup call.|
|Device-call instruction|16|Actual outgoing SetTexture pointer and three arguments; stop before COM execution.|
|Lookup417800 entry|40|Actual E8 and receiver/token; stop before helper execution.|
|Null-device read fault|56|Actual unmapped vptr read before dispatch/lookup.|

Code hooks enter30 of45 target and27 of40 source instructions. This includes
the device CALL boundary where execution stops and the faulting read; it is
not retired-instruction or complete-function dynamic coverage. No lookup or
device return value is substituted. Post-call cache stores are recovered
statically and are not executed by this audit. Runtime driver/lookup behavior,
exceptions, arbitrary aliases/stages and full-game fixture reachability remain
outside its scope. Null-device fixtures are native machine inputs, not a claim
of defined C++ null-object behavior.

A real C++ negative moves lookup to a preceding local before the device call.
It produces80/160 differences:40 null-device cache misses reach lookup where
the target faults first, and40 valid-device misses lack the target's prior
device/vptr reads. Its endpoint counts are48 RET,16 device calls,80 lookup
entries and16 faults. This calibrates the ordering check; it does not convert
the passing prefixes into canonical equality.

Final positive/negative receipts are `final-selected-native.json` and
`final-wrong-lookup-hoist-native.json`, with commands in
`aggregate-native-commands.json`. The audit intentionally reports
`build_provenance_verified=false`; formal source/object provenance and actual
negative-build source/hash receipts are separate.

## Pins, ledgers and reproduction

| Selected artifact | SHA256 |
| --- | --- |
|CRLF source|de230bdb76899b1d349f447dbe31db13effde27a11172e2e6b18abd73a18dcb7|
|Formal COFF|ac583e36f767e4c54b47d8c2e59042385c40139675efe455419ee1776e3982c7|
|Complete canonical102-byte source body|43346e2dac80c6d7df7ae0fb9b3dd23c17d399b90c0d11e5044611d4241bd105|

The candidate remains107 bytes and becomes mapped/source-present/implemented.
Its existing authored disposition is unchanged. Five affected origin witness
sets are replayed, including three callers' updated implemented-callee status;
all196 rule selections are unchanged. A stale origin-review phrase is corrected.
No full library-anchor or aggregate cold replay is claimed.

No shared header, compiler profile, relocation ledger or prior accepted source
changes. Only the new unit is rebuilt. Existing callers retain their actual
404DF0 binding; CGage41B3F0 and ReimuObject496540 remain nonexact.

```bash
# Expected exit1:102/107, first mismatch at entry.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-texture-slot-binding --compare --json
# Expected exit0:160 equal scoped prefixes.
taskset -c 0 nice -n 10 python3 scripts/audit-texture-binding-prefix.py \
  build/match-units/GptWeb_TextureSlotBinding.obj \
  --output build/texture-bind-20261021/reproduced-native.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Selected source/COFF, target packet, control reports and native receipts are
under `build/texture-bind-20261021/`. Private regeneration recipes are under
`.analysis/texture-bind-20261021/`. Generated compiler/linker artifacts are not
committed. Completed unselected controls are losslessly compressed in
`unselected-trials.tar.gz`, with per-file hashes and a verified round trip in
`unselected-trials-manifest.json`. Restore it before private recipes that read
an earlier control source. Selected source/COFF, final native receipts and the
genuine linked context remain uncompressed. Current ledgers and this source
epoch supersede the older97-byte
probe diagnosis; original frame and save-placement recovery remains open.
