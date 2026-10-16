# Application control and graphics thread entries: 28/28 each

## Observed target and ownership

Only original Japanese TH10.5 v1.06a was used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Each complete callable closes eight instructions / 28 bytes, including RET4,
with no gaps or outgoing branch exits. Four INT3 bytes follow each callable.

| Entry | Bootstrap callback PUSH | Worker CALL | Body SHA-256 |
| --- | --- | --- | --- |
| `Application_control_thread_entry @ 408800` | `407F60` | `40880C -> 4081E0` | `1a31e944550c2208b38d29875ad31aaaceca818df1049f71e8babe29d9d71677` |
| `Application_graphics_thread_entry @ 408820` | `407E5E` | `40882C -> 4084F0` | `267f443c245b625ee960affffbeac78bfece65a50958217418e4db399bf3eff7` |

Source-present bootstrap `407DA0` passes these actual entries to the PE-named
CreateThread import and stores their handle/id pairs. That application-owned
lifetime establishes authored ownership independently of the compiler match.
The workers establish application context from singleton `702820`; neither
callback supplies a register receiver or explicit worker argument. The worker
declarations express the observed caller view, without claiming their bodies.

Both callbacks call CoInitialize(0), invoke their respective worker only for a
nonnegative HRESULT, and call CoUninitialize on that successful path. Both
return EAX=0, including failed COM initialization, and pop one unused pointer
argument. There are no local objects, GS buffers, SEH frames or cleanup paths.
Original function/type names and source partition remain unknown.

## Source and canonical result

`src/platform/ApplicationThreadEntries.cpp` contains the two ordinary
`unsigned long __stdcall(void *)` callbacks. The first source probe already
reproduced both complete extents; the configured pinned-VC8 build confirms
**28/28 + 28/28 canonical exact** with identical complete COFF section tails.
Each function replays two IAT DIR32 fields and one worker REL32 field. All
existing import and callback-pointer mappings remain unchanged. No shared
header, ABI facade, forced register, synthetic stack local or manual byte is
introduced. Similar BGM thread source is corroboration only; raw application
bytes and call sites establish these results independently.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00408800 0x00408820 --json
python3 scripts/build.py --unit cross-v106a-application-thread-entries --compare --json
```

Fresh reports are `build/application-thread-entries-boundaries.json` and
`build/application-thread-entries-formal.json`. Names, source selections and
both exact rows advance together. Only the two matching origin baseline rows
change after checking the unchanged rules for overlap and attesting the PE;
unrelated fingerprint records and accepted units are preserved without a full
replay. Neither worker body gains source-present or exact credit.

Sequential direct Ghidra sessions attest executable/program SHA, image base,
entry/external entry marker, x86 Windows identity and every mapped .text byte
before saving names, 28-byte extents, stdcall, four-byte return/argument and
purge4. Same-session and fresh read-only checks verify the metadata, parameter
storage and full body hashes. Private scripts are under
`.analysis/application-thread-entries-20261016/ghidra-scripts/`; logs stay under
`build/application-thread-entries-ghidra-*.log`. Each process uses768MiB and two
active processors. The mismatched IDA session is excluded from analysis.
