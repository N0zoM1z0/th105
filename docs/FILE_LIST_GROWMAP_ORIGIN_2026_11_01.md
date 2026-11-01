# FileList tile-deque map growth

The actual selected FileListFinalize.cpp now exposes a complete canonical
compiler helper at439D70: std::deque<FileListRenderTile>::_Growmap,341 bytes.
Both complete body hashes are:
34552e1f32b437f333d899571905e8ebea659521d75f47c848d81c817823d455.

Native page finalization43A590 calls it at43A8D6 when its CTile deque's map
needs room. The actual source owns the typed A4-byte tile and uses ordinary
push_back; no template implementation or isolated code replica is authored.
The complete source-generated function has313 nonrelocation bytes and seven
code relocation fields. All seven are canonically resolved:

-Original length-error helper449940, already compiler-excluded.
-Pointer-array allocation439580, already compiler-excluded.
-Four distinct memmove_s calls to original CRT689EB0.
-One allocation release through6898EA.

The generated-origin rule explicitly requires allfour memmove_s occurrences,
not just one convenient field. Full candidate-inventory uniqueness passes
unchanged .70 coverage/24 nonrelocation-byte/zero-tail limits. The actual native
caller edge and complete target hash are also checked. No masked comparison is
substituted for the formal whole341-byte canonical comparison.

Discovery scanned only three newly built FileList/default-interface objects,
not the repository or old cold corpus; this was its only remaining review hit.
The parent remains the same1155/native1106 nonexact source. Its helper does not
confer any prefix or authored credit on that root. The CTile164 copy was already
proved/excluded and is not counted again.

Only439D70 moves review to compiler-excluded: excluded1970/review402. Authored
exact1431/443916, source1635/authored1655/mapped1820 and units772 are unchanged.

Reproduce the mixed parent/helper unit:

    scripts/repo-python scripts/build.py --unit exact-first-file-list-finalize --compare --json

The command reports the intentional parent mismatch and exact helper341.
Receipts: build/frontier-file-list-growmap-20261101/formal.json and canonical.json.
No source change, threshold relaxation, all-exact rebuild or push.
