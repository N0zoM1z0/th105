# Three action-state readers use the real sequence deque

Tenshi, Yukari and Komachi now read `record_id_00` from the shared
`std::deque<FighterSequenceSlot>` at Fighter +0x55C. The removed declaration-only
`at()` facades returned a short pointer but bound it to the native subscript.
The real record is 0x98 bytes and contains a CSprite, not just the returned WORD;
its insertion and ownership evidence is in `SEQUENCE_DEQUE_PROVIDER_2026_11_09.md`.

All ten native read sites are checked in the pinned Japanese 1.06a executable:

- Tenshi: `63D516`, `63D525`, `63D588`, `63D59A`, `63DFD5`, `63DFE7`, `63E0D4`.
- Yukari: `57CCE5`, `57CCF3`.
- Komachi: `5E2133`.

Each call uses the +0x55C receiver directly or retains it in EDI, then reads the
returned WORD. The signed range checks and Komachi's sign extension remain
unchanged. Both reads of each short-circuit condition are retained.

All three actual caller TUs emit the complete native `operator[]` at `4399C0`:
94 bytes, three invalid-parameter calls, and canonical SHA-256
`5e6d9bae7c00a857a51b7ca00c03b37c95e1986a9e389d56e35924b205f7491b`.
This restores the source/provider contract without a new wrapper or ABI alias.

The full three-unit include closure is rebuilt. Every before/after full-payload
report is identical, including all switch data and resolved relocations:

- Tenshi: 49,184 candidate / 48,968 native bytes; first difference +8.
- Yukari: 57,840 / 58,248; first difference +18.
- Komachi: 65,304 / 65,176; first difference +8.

All 542 existing non-debug sections retain their bytes and relocation roles.
Compiler-local label names change in Tenshi, but their section offsets and all
resolved destinations are identical. Each TU adds 60 ordinary STL sections.
The existing 18-byte float-sine helper stays exact; its complete original-header,
caller, intrinsic, and inventory-uniqueness proof passes with the changed Tenshi
header pin. No input-migration source pin is changed.

The three authored roots remain unselected and nonexact. No new authored exact
credit or Factory acceptance is claimed. All 18 pending input files are preserved.
