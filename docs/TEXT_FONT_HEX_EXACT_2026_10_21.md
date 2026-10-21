# Native markup hex decoder: complete45/45 exact

`TextFont_decode_markup_hex @ 0x004128F0` is canonical **45/45 bytes,
all20 instructions**, under ordinary VC8 COFF. A real file-local typed C++
function in the actual markup TU naturally receives/returns AL, with no stack
arguments. All six parent calls remain. This adds one authored exact function
/45 bytes, without granting parent, runtime-helper or EH credit.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Preflights verify target/status/tracking; IDA rejects its wrong open
executable. Raw pinned bytes and native compiler/caller products provide the
accepted evidence.

## Complete boundary, source and ABI

Full target/source SHA256:
`79ad8cdb4a59f97d54112530ccbfe83b2a5ebf0ea59b5bf2190a31adddad520e`.
All45 bytes are reachable through four RET paths, ending at41291C before
separate INT3 padding. The native symbol owns exactly45 bytes through its RET;
there are no relocations, external dependencies, stack homes, data operands,
EH metadata, cropped extents or comparison waivers in this leaf.

Observed unsigned-byte ranges0..9/a..f/A..F map to0..15; all other inputs return
zero in AL. The source expresses those three ranges with unsigned-char
subtraction checks, followed by the real zero fallback. It has an ordinary
file-local cdecl declaration and definition after its genuine caller. VC8
privately chooses AL. No inline assembly, copied bytes, register facade,
noinline annotation, inert local or padding is introduced.

The tracked main-instruction census finds six E8 sites in reviewed game markup
411FA0:41251A/41253B/41255C/41257D/41259F/4125C0. Each loads the color character
into AL; the native parent retains six equivalent compiler-generated calls.
This game color policy establishes the helper's authored role, independently
of adjacency to STL/runtime methods. The retained external decoder was only a
source hypothesis; no old mapping or exact claim is inherited. Original source
spelling/TU and arbitrary indirect/remote caller completeness remain unknown.

Only AL is the byte result contract. Some paths subtract through EAX while the
invalid path clears AL alone; upper EAX must not be presented as a32-bit return.

## Leaf execution and changed parent

Actual complete target/source instructions pass **1,024/1,024** leaf cases:
all256 byte inputs across four upper-EAX patterns. AL matches the independent
range specification; full volatile register/flag behavior agrees between the
byte-identical programs, with normal ESP and saved-register restoration.

The real visible body removes the ordinary external declaration's argument
push/cleanup at six sites. Parent shrinks1682/459->1652/447, full canonical
`c898f9075d1af02bcb8136896df4d8dc51ce47f1ba9ef468f7983bf03ad60710`.
It still differs at+16, with788-byte source versus796-byte target local frame
and unresolved private EDX+ECX/RET8 versus ordinary member context. A smaller
parent is diagnostic, not an exact improvement claim.

All **8,640** parent cases pass again. This time both parent runs execute the
real byte-identical hex instructions; that leaf is no longer an abstract
observer. Remaining CRT/STL/font/color boundaries still use explicit observers,
with the same normal-path/first-invalid-boundary scope and no actual GDI/EH
unwind, allocation-failure, arbitrary-alias or protected-page claim. The earlier
ruby negative-control evidence remains phase-scoped; it is not repeatedly run
for unchanged ruby policy. See [the parent source checkpoint](TEXT_FONT_MARKUP_SOURCE_2026_10_21.md).

The previous five complete runtime bodies retain their hashes. Adding this
leaf does not qualify the parent's handler, FuncInfo or funclets; their exact
ownership/offset checks and the remaining provider definitions are still open.

## Acceptance and reproduction

The existing gpt-web-text-font-render unit now has seven configured functions.
Its full command intentionally exits with comparison_failed because six
candidates remain nonexact; the independent4128F0 comparison is exact45/45.
Only4128F0 joins matches.csv and the accepted comparison subset for this unit.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
```

After final source/ledger edits, that whole focused unit is cold-rebuilt:
helper45 remains exact and all nonexact results are explicit. No predecessor
accepted unit has a source dependency or changed definition. Shared headers,
profiles, object partition and relocation ledgers remain unchanged. No
unrelated or aggregate cold replay is claimed; progress is the updated ledger
snapshot with provisional authored denominator.

Full target/caller facts, native source/COFF/binary,1024 leaf/8640 parent receipts
and final canonical reports are under `build/font-hex-20261021/`; private recipes
are under `.analysis/font-hex-20261021/`. Selected evidence stays available.

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: real color/reset/setter/blend closure and genuine parent TU/link/EH
recovery. The larger Reimu496540 root remains nonexact at49655F/+31.
