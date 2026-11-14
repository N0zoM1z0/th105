# Origin corrections, 2026-11-14

## 0x40FDB0 is `std::deque<CsvRow>::_Tidy`, not authored

The function formerly tracked as authored `CsvReader_clear_rows` is VC8's own
`std::deque<std::deque<std::string>>::_Tidy`. It pops every row through the row
`_Tidy` at 0x40FF90, frees each block, frees the map and clears it. The CSV reader
source already emits that member out of line, and the emitted body compares
exact, 125/125:

    scripts/repo-python scripts/build.py --unit gpt-web-csv-reader-next-int --compare --json

The 125-byte `deque<PatGroup>::_Tidy` at 0x461AF0 has the same shape and was
already excluded. The new rule `vc8-generated-csv-rows-tidy-106a`
(`config/vc8-generated-csv-rows-tidy-origin-anchors.toml`) excludes 0x40FDB0 as
compiler-generated. The authored CSV reader rule now covers only `next_string`
and `advance_row`. The reader destructor at 0x42E980 tail-enters this `_Tidy`, as
`~deque` does.

A scan of every `std::` function emitted by the current unit objects found no
other authored nonexact function whose bytes match one.

## Line-ending state of source pins

`.gitattributes` checks out `*.cpp` and `*.hpp` with CRLF, but the working tree
had been LF throughout, with 959 files affected. Raw-hash origin pins had been
recorded from both states. The tree has been re-checked-out with CRLF, and every pin of a
file changed since `a075cb1b` was renewed after its proof rebuilt. Each pin's own
hashing convention was kept:

- implicit-lifetime, CSprite and input-cleanup pins hash the raw bytes;
- linked allocator pins and `normalized_sha256` pins hash the LF form.

After editing a `.cpp` or `.hpp` file, keep CRLF. Python text-mode writes produce
LF; re-check-out the file after committing, or write bytes.
