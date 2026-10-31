# Wave-service handle load: complete source, nonexact

The authored service at 401AF0 has a complete 224-byte native body, SHA-256
4656d7b85447306152dcaac9d06591a317ba024485e32c0d6b1443540ec4ffa2.
All 85 decoded instructions are reachable; both returns clean eight stack
bytes, including the hidden value-result parameter. The freshly exact fighter
wave loader45F680/132 calls it at45F6D3. Hash-attested raw PE was used throughout;
no unverified IDA session supplied semantics.

## Ownership and complete policy

The existing wave-service layout establishes the second handle manager at64
and gain fields450/454. The service acquires a stable pointer cell and packed
token, creates the actual twelve-byte CDSBuffer, publishes it to that cell and
loads the requested path. On failure it conditionally deletes the buffer,
recycles the token and returns a zero value. It does not clear the freed cell
or add an allocation-success guard absent from the native function.

On success, effective gain is gain454 * gain450, rounded to float before the
existing minimum threshold/logarithmic conversion. The native DirectSound
buffer receives the resulting volume if its resource pointer exists. The
packed token is returned through the ordinary four-byte value result. The
existing BgmHandleResult represents that zero-initialized token value here;
its name does not imply that the service loads BGM or proves original spelling.

The real checked pointer deque, stable-slot vector, generation vector, free
list and critical-section member are represented in the manager. Acquisition
and release use normal C++ members, not EDI/EAX declarations. The native
acquisition and release bodies were read in full to establish fresh/recycled
generation handling, checked indexing and lock ownership. These providers are
not promoted or counted as exact.

## Actual source graph and strict comparison

WaveServiceLoad.cpp includes the existing BgmStreamRuntime.cpp and WaveDataRuntime
implementations, adding the corresponding complete wave-file load member and
ordinary dispatcher policy. Only a nonvirtual load_wave_file declaration is
added to BgmBufferRuntime in its existing source; its layout and other bodies
are unchanged. No duplicated runtime source snapshot is published. This graph
contains the actual reader, DirectSound resource, math and handle providers,
not a synthetic imported private-ABI shim.

The public exact-first-wave-service-load unit emits 221 bytes versus224 and
fails at the first byte. Native has an aligned EBP frame and EDI acquisition
receiver; the source has a simple stack slot and normal ECX acquisition call.
Both whole root bodies and all relocation identities are compared. Actual
CDSBuffer RTTI/vtable validation passes through the existing strict vtable
contract. No fake aligned local, register forcing, noinline barrier, assembly,
byte copy or comparator relaxation is introduced.

An early private diagnostic preserved the volume free function through a
low-level build call. Public manifest validation correctly rejected that
unsupported preservation contract. It was removed, with no verifier change;
the accepted public configuration has no preserved free-function export and
still naturally emits221. Only the public replay is the reproducible result.

The current linked acquisition454/native364 and release163/native167 remain
unaccepted. The emitted load member304 is not independently promoted in this
unit; its existing standalone canonical304 witness remains separate.

## Regression scope and receipts

Fresh selected BGM Ogg291 and SFL484 pass with their full existing contracts.
The mixed BGM runtime unit's aggregate comparison first hits an already
uncontracted nonexact callee; the two accepted roots are therefore compared
explicitly in the freshly built unchanged unit, without bypassing a gate.
BGM play351 and prepare159 plus all79 preparation EH bytes pass. The existing
fighter wave resource unit passes its132/333/199 roots. No corpus-wide rebuild.

Receipts under build/frontier-wave-service-load-20261031 include public.json,
ownership.json, native.txt, bgm-runtime-focused.json, bgm-service.json and
caller.json. The independent ownership rule checks the complete body hash and
fresh exact caller edge. Private experiments remain under .analysis.

This is source-present/authored ownership only. Exact stays1577/448878; source
becomes1775, authored1795, mapped1802, excluded1714, review518 and units760.
