# Action initialization reads the actual sequence deque

The common Fighter initializer and Patchouli's initializer now index the real
`std::deque<FighterSequenceSlot>` at Fighter `+0x55C`. Their old declaration-only
`at()` facades returned a short-prefix record but concealed a call to the native
subscript provider. The source now names the actual operation and reads the
shared record's signed `record_id_00`.

The existing preparation and insertion evidence establishes the 0x98-byte
record: two WORD fields followed by the real CSprite at +4. See
[the sequence owner](SEQUENCE_DEQUE_PROVIDER_2026_11_09.md). No shared record,
container layout, compiler option or unrelated reader is changed.

## Original call sites

The pinned Japanese 1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- Common initialization forms the receiver at `0x47846A`, calls `0x4399C0` at
  `0x478470`, reads the returned WORD and stores it in Fighter `+0x738`.
- Patchouli forms the same receiver at `0x51DDD3`, calls `0x4399C0` at
  `0x51DDE7`, then reads and publishes the same WORD field.

Each real caller TU emits the complete 94-byte `operator[]` specialization.
All three invalid-parameter calls resolve to `0x68A143`, and both emissions
match the native body through its return. Its canonical SHA-256 is
`5e6d9bae7c00a857a51b7ca00c03b37c95e1986a9e389d56e35924b205f7491b`.
This is the subscript contract, not the separate range-error behavior of `at()`.

## Complete affected comparison

The source/include closure contains exactly two configured units. Fresh
before/after builds preserve all existing 40 code/data sections, including
complete root sections, switch data and relocation roles after resolving the
actual provider symbol. Each TU adds ordinary STL support and the standard
`libcpmt` linker directive.

Patchouli remains exact across its 3,132-byte callable and complete 3,868-byte
payload. All 732 main instructions, 41 returns, three switch destination tables
and 447 remap bytes remain covered by the existing full-payload auditor.

The common initializer remains nonexact: candidate payload 5,305 bytes versus
5,521 native, with the same first difference at +20 and the same canonical
candidate hash `2b5e64188dc23b84678c864f0be04e49f92a843e54f95d77b398651ce43945cd`.
Both before/after full-payload reports are identical. This correction adds no
authored exact credit and makes no new Factory acceptance claim.

Evidence is retained in `build/frontier-action-entry-sequence-owner-20261109/`,
including native call contexts, full before/after comparisons and
`verification.json`. The scoped driver is
`.analysis/frontier-action-entry-sequence-owner-20261109/verify.py`.
All 18 pending input-migration files and their source SHA pins are preserved.
