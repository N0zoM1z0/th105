# Replay filename generation, 0x0042A560

## Exact scope

Original Japanese1.06a target SHA256 remains
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The complete1322-byte function has351 decoded instructions/348 reached,
RET12 at42AA87, and six separating INT3 bytes. Three unreachable alignment
instructions at42A7D8/42A7DF/42A87D remain part of the full comparison.
No remote chunks, inline tables or indirect jumps occur. Its SHA256 is
 a22f59075af48cacc3be96b301b2fa3a5a3ec233fe55875a8595aa642e9c3c28.

Replay-save callers43BB5B and44E3FB pass a writable path plus two player-name
strings. Raw ECX receiver accesses are mode byte+EC and slot-store address+F4.
The target explicitly returns zero in EAX; callers ignore it. Both raw caller
edges and attested Factory IDA xrefs are checked. The supported descriptive
name and thiscall prototype were written to IDA and read back, without changing
any target bytes. Original nominal class identity and full layout stay unknown.

## Source and preserved behavior

`src/battle/ReplayFilename.cpp` uses real VC8 std::string objects, native time/tm
objects, one260-byte formatting buffer and a genuine virtual12-byte file-reader
lifetime. The vtable binding names the independently established CFileReader
identity; no hand-written vptr store or fake object padding is introduced.

- Directory/name/suffix start as `Replay`, empty string and `.rep`.
- Config presence is checked through the established configex.ini receiver.
  Story/versus choose different filename keys, and the directory key is expanded
  independently. Empty directory restores Replay; a nonempty directory receives
  the Replay/ prefix and an unchecked CreateDirectoryA call.
- Missing or empty configured names use time64/localtime64_s and the native
  year-mod100/month+1 formatting. Character bytes are sign-extended. The versus
  path preserves two independent slot lookups, not a cached single lookup.
- Concatenation remains directory + slash + name, even when the default name
  itself already begins with replay/. This possibly surprising native path is
  not normalized or repaired.
- Each collision probe uses CreateFileA access1/share1/open-existing/flags80,
  maps INVALID_HANDLE_VALUE to null, and treats failure as available. Existing
  files advance suffixes `_0.rep`, `_1.rep`, etc.; handles close through RAII.
  No new filesystem safety checks or error handling are inserted into game code.

All imported calls are bound from the canonical PE IAT, including register-held
wsprintfA/CreateFileA calls. All55 COFF relocations replay. New string bindings
check the complete literal including NUL; EH handler6B7C2D is separately pinned.
The original checkpoint left pattern expansion and slot selection declaration-only.
Pattern expansion is now independently1323/1323 in [its own review](REPLAY_PATTERN_2026_10_27.md);
slot selection receives no new implementation/ownership credit here. The config/file provider shapes are bounded
existing evidence, not claims about original source spelling.

## Complete first-source comparison

First full source compiled1319 bytes with434 unequal positions. Observed
story-before-versus branch order reduced that to429. Keeping the slot receiver
conversion inside its actual branches, rather than hoisting one pointer across
them, naturally recovered **1322/1322 exact**, including the whole frame,
register allocation, strings, imports and cleanup. No flags or ABI changed.
The config buffer declaration was then reconciled with its existing260-byte
shape; the formal new-unit build still matches completely.

```
scripts/repo-python scripts/build.py --unit exact-first-replay-filename --compare --json
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ci.py
```

Receipts live in `build/frontier-42a560-20261027/`: full target decode/facts,
first/branch/receiver source trials and previews, formal-first.json,
formal-second.json, origin/progress refresh and local-ci.log. Final CI is pending
at writing; its durable exit file is authoritative. Only this new unit is built;
prior unchanged accepted receipts support incremental totals. No new runtime
matrix, real filesystem I/O test, or full cold-corpus rebuild is claimed.
