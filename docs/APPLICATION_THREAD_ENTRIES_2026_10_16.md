# Application thread entries: canonical 28 + 28 + 48

## Observed target and ownership

Only original Japanese TH10.5 v1.06a was used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The control/graphics entries each close eight instructions / 28 bytes, including
RET4, with no gaps or outgoing branch exits. Four INT3 bytes follow each.
Scene creation closes14 instructions / 48 bytes through RET4, immediately
before the separate scene-disposal callback `408870`. Its independent callback
address and complete return closure establish the boundary without padding.

| Entry | Owner callback PUSH | Work CALL | Body SHA-256 |
| --- | --- | --- | --- |
| `Application_control_thread_entry @ 408800` | `407F60` | `40880C -> 4081E0` | `1a31e944550c2208b38d29875ad31aaaceca818df1049f71e8babe29d9d71677` |
| `Application_graphics_thread_entry @ 408820` | `407E5E` | `40882C -> 4084F0` | `267f443c245b625ee960affffbeac78bfece65a50958217418e4db399bf3eff7` |
| `Application_scene_creation_thread_entry @ 408840` | `4083A8` | `40885E -> manager slot+10` | `9066a3e20b7527f146f8fcae576c05cf685b0076138c2e23fe306259583f97c1` |

Source-present bootstrap `407DA0` passes the first two entries to the PE-named
CreateThread import; source-present control worker `4081E0` passes the third.
Their handle/id pairs occupy application+50/+58/+64. That application-owned
lifetime establishes authored ownership independently of the compiler match.
The workers establish application context from singleton `702820`; neither
callback supplies a register receiver or explicit worker argument. The worker
declarations express the observed caller view, without claiming their bodies.

All callbacks call CoInitialize(0), perform their work only for a
nonnegative HRESULT, and call CoUninitialize on that successful path. All
return EAX=0, including failed COM initialization, and pop one unused pointer
argument. There are no local objects, GS buffers, SEH frames or EH cleanup paths.
Original function/type names and source partition remain unknown.

Scene creation loads the manager from singleton+74, calls its fifth virtual
slot with requested state+B0, and publishes the returned scene pointer at+80.
This corresponds to the independently reviewed WinMain/manager five-slot
contract. A null return is still published, and COM initialization failure
leaves the pending pointer untouched. The source view accesses only these
three fields; it does not allocate an application or claim its complete size.

## Source and canonical result

`src/platform/ApplicationThreadEntries.cpp` contains the three ordinary
`unsigned long __stdcall(void *)` callbacks. Each first source probe already
reproduced its complete extent; the current pinned-VC8 object confirms
**28/28 + 28/28 + 48/48 canonical exact** with identical complete COFF tails.
The earlier entries each replay two IAT DIR32 fields and one worker REL32 field.
Scene creation replays five DIR32 fields: two imports and three singleton
accesses. A dedicated new mapping allows only+74/+80/+B0; existing import,
singleton and callback-pointer mappings remain unchanged. No shared
header, ABI facade, forced register, synthetic stack local or manual byte is
introduced. Similar BGM thread source is corroboration only; raw application
bytes and call sites establish these results independently.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00408800 0x00408820 0x00408840 --json
python3 scripts/build.py --unit cross-v106a-application-thread-entries --compare --json
```

The current object report is `build/application-thread-entries-with-scene-formal.json`;
the new raw boundary report is `build/application-scene-creation-thread-boundary.json`.
Scene-creation name, source selection and exact row advance together. Only its
origin baseline row changes after checking unchanged rules for overlap and
attesting the PE. Both earlier accepted entries are freshly replayed from the
changed object; unrelated fingerprint records and units are preserved without
a full replay. Worker source-present/nonexact state is independently documented
in [the control note](APPLICATION_CONTROL_WORKER_2026_10_16.md) and
[the graphics note](APPLICATION_GRAPHICS_WORKER_2026_10_16.md).

Sequential direct Ghidra sessions attest executable/program SHA, image base,
entry/external entry marker, x86 Windows identity and every mapped .text byte
before saving names, 28-byte extents, stdcall, four-byte return/argument and
purge4. Same-session and fresh read-only checks verify the metadata, parameter
storage and full body hashes. Private scripts are under
`.analysis/application-thread-entries-20261016/ghidra-scripts/`; logs stay under
`build/application-thread-entries-ghidra-*.log`. Each process uses768MiB and two
active processors. The mismatched IDA session is excluded from analysis.
Scene creation has the same independently attested save/fresh-readback gate
for its48-byte body and standard callback signature; its scripts/logs use
`.analysis/application-scene-creation-thread-20261016/ghidra-scripts/` and
`build/application-scene-creation-thread-ghidra-*.log`.
