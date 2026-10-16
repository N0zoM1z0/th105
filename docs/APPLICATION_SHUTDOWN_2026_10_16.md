# Application shutdown: canonical 245-byte reconstruction

## Observed callable and application ownership

The only target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`407F80..408075` contains 245 reachable bytes / 82 instructions, with no
unreached range, overlapping decode or outgoing direct branch. Its final
instruction at `40806F` is `JMP DWORD PTR [6C02C0]`; the PE import descriptor
identifies this cell as OLE32 CoUninitialize. This resolves the boundary
auditor's sole indirect exit. The body has 11 subsequent INT3 bytes.

Body SHA-256:
`0fbc1e1bcb65e97ccfc6f55edfe31593408ee0fa910a4935fe6faf8e9247ba5d`.
The entry is normal ECX thiscall, without explicit parameters or stack purge.
WinMain calls it at `665A9A` with singleton receiver `702820`, after the main
loop or failed application initialization. That application call chain, its
owned subsystem teardown and RTTI callback owners establish authored policy;
this is not a generic compiler/library cleanup helper.

## Recovered behavior and physical view

The complete source preserves the target order:

1. Clear running byte +4C; join the +64 thread owner.
2. Signal event +90 with SetEvent, then join the +6C thread owner.
3. Signal event +60, then join +58 and +50 thread owners.
4. Enter CRITICAL_SECTION at +98; virtually delete and clear scene pointers
   +7C and +80; leave the same critical section.
5. Call primary manager +74 vslot+4, then conditionally delete/clear it.
6. If fade +78 exists, call its vslot+4, reread it, then conditionally
   delete/clear it. Both inner pointer checks and reloads are target behavior.
7. If startup option +23 is enabled, release the IME context with the main HWND.
8. Shut down DirectSound and DirectInput, unregister the RenderModeManager
   reset listener, shut down D3D, then tail-call CoUninitialize.

The imports at `6C0040` and `6C02C0` are independently identified from the PE
as **SetEvent** and **CoUninitialize**. The two event calls do not close those
handles. The four `414640` calls use the independently exact eight-byte
thread owner whose wait method closes its thread handle internally.

The callback vtables `6C74AC` and `6C74C4` have complete-object locators
`6DBD58` and `6DBDA4`, identifying `CSceneManager` and `CFade` through type
names at `6E912C` and `6E9148`. Their slots +4 point to `41E120` and `41F890`.
The two active scene deletes call virtual slot zero with scalar-delete flag1.
The callback storage releases instead use ordinary operator delete/free at
`6898EA`, without destructor dispatch. The source uses unconstructed local
prefix views for these distinct ownership paths. It does not emit or replace
those owners' vtables. The explicit Enter/Leave calls and absence of any EH
frame are preserved; no speculative RAII unwind behavior is introduced.

`ApplicationShutdownView` reaches the existing startup-options value at +8,
real eight-byte thread records and the critical-section wrapper at +94.
Offset assertions guard the accessed layout. Opaque prefix regions record
unreviewed fields; this is not a claim about the complete application size.
Original class/TU names and thread/event roles beyond observed sequencing
remain unknown. No register forcing, fake ABI, alignment or inert local is used.

## Canonical comparison and database state

The first complete probe exposed two concrete source issues: the event import
was initially guessed as CloseHandle, and fade teardown lacked the target's
post-callback null check. Correcting both from target instructions yields
**245/245 canonical exact**; a separate register-scheduling workaround is
unnecessary. All eleven direct-call relocations and seven absolute relocation
fields are resolved through the formal unit and existing attested mappings.
The only local DIR32 alias maps the IME context prefix to the already known
ProfileMenuController aggregate. Shared source, headers, flags and relocation
ledgers were not changed.

```bash
python3 scripts/build.py --unit cross-v106a-application-shutdown --compare --json
python3 scripts/audit-candidate-boundaries.py 0x00407F80 --json
```

Formal report: `build/application-shutdown-formal.json`, zero differences over
the complete callable and complete 245-byte COFF section tail. Exact source is
`src/platform/ApplicationShutdown.cpp`. Mapping, implementation and match rows
advance together; the canonical authored baseline regenerates the origin row.
Only focused validation is needed for this isolated addition.

Direct Ghidra sessions independently attested PE SHA, image base, entry and
external-entry marker, x86 Windows analysis identity and full mapped .text
before saving the 245-byte function, durable name, void thiscall contract and
zero purge. A fresh read-only session checked saved metadata, ECX storage and
whole-body SHA. Scripts stay private under
`.analysis/application-shutdown-20261016/ghidra-scripts/`; save/readback logs
stay under `build/application-shutdown-ghidra-*.log`. Ghidra used one process
at a time with 768 MiB heap and two active processors. The failed IDA target
preflight and factory adapter were not used for analysis.
