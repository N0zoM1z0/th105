# Complete GameConfig save source registration

Original Japanese 1.06a GameConfig save 427390 is now authored and source-present,
not exact. The complete target [427390,4276FD) is 877 bytes, with 334 decoded
instructions and RET0 at 4276FC. Its SHA256 is
ad633c071c15bf198ec6c453d794d3f513e30d8aa7ceae7d3d95d522e6ee0880.

## Ownership and ordinary source

Fresh canonical callers close_config_menu 43CDD0/48 and
shutdown_scene_resources 43D670/264 both pass in full. Their tail jumps at
43CDFB and 43D773 respectively reach 427390. The scoped origin rule checks the
complete body hash and these exact incoming edges, not a name or prefix.

src/config/GameConfigSave.cpp uses actual std::string[2], std::deque<std::string>
and the existing polymorphic CFileWriter. Compile-time layout checks establish
string size 1C, deque size 14, complete view size 74 and offsets 48/64.
The actual version getter 43AA40 returns 6A. The serializer writes version,
two profile paths capped at 260 bytes, timeouts and four ushort values, at most
ten recent strings capped at 1024 bytes, then the observed flags, mode, default
game type and volume fields. The writer retains actual CreateFileA/WriteFile/
CloseHandle behavior. No builds execute configuration file I/O.

The native prologue has a real security cookie and EH handler. The selected
vc8-sp1-probe-o2 unit therefore enables GS. The handler's first 16 bytes at
6B7A38 are 8b5424088d42d88b4ad433c8e8dc22fd. This is a relocation ownership
binding only, not a full remote EH-body equality claim. Existing writer vtable
6C0F4C and config.dat literal 6C0F5C bindings are reused.

## Full comparison and bounded residual

The complete ordinary source is 877 bytes, canonical SHA256
f66c8b19a454923fdea0740dd07b36dbd18bf1dbcc177912085ef0ff76194be9.
Only offsets 579 and 582 differ, first at 4275D3: the native checked-deque
bound loads [ESI+54], then adds [ESI+58]; the source swaps these operands.
This remains a failed whole-function comparison. There is no prefix credit.

A private const-method control, motivated by read-only serialization and the
genuine const deque overload, is byte-neutral and unselected. Earlier GS-disabled
real-string, manual-view and MenuString28 controls are not selected. No register
declaration, volatile forcing, padding, copied native code or fake lifetime is
used. The global GameConfig constructor's separate SSO/EH topology remains
unresolved; this read/write-format view does not claim that constructor.

Reproduction:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-game-config-save --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit cross-v106a-config-close --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-scene-resource-shutdown --compare --json

Receipts are under build/frontier-config-save-source-20261101:
formal.json, close.json, shutdown.json and first-canonical.json.
Source 1785, authored 1805, mapped 1812, excluded 1798, review 424, units 765.
Exact 1585 / 449721 authored bytes is unchanged; matches.csv is unchanged.
