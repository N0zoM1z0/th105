# CPU sequence reads use the actual record deque

Marisa and Alice CPU policies now index the shared
`std::deque<FighterSequenceSlot>` at Fighter `+0x55C` and read its signed
`record_id_00`. The old declaration-only `at()` receivers returned a short
pointer but had no implementation; their bindings concealed the actual checked
subscript provider at `0x4399C0`.

The existing sequence preparation and push-back source establishes the 0x98-byte
record: signed WORD ID, WORD metadata, then the actual CSprite at +4. See
`SEQUENCE_DEQUE_PROVIDER_2026_11_09.md`. This is not a deque of two-byte shorts.
The native CPU bodies supply the same receiver and read the first WORD at all
27 Marisa and 20 Alice call sites. Representative sites are `0x4B4625` and
`0x4F5272`; each follows `lea ecx,[esi+55C]` and then reads the returned WORD.

Both real caller units now emit the complete 94-byte standard subscript.
Replaying all three invalid-parameter calls gives the canonical SHA-256
`5e6d9bae7c00a857a51b7ca00c03b37c95e1986a9e389d56e35924b205f7491b`.
The complete callable closes through its native return with no EH or data tail.

The entire existing caller sections, switch payloads and relocation roles are
unchanged apart from resolving the old facade calls to the real provider:

- Marisa remains 16,867 bytes versus native 16,907, first mismatch +302.
- Alice remains 16,869 bytes versus native 17,009, first mismatch +53.

Both existing full-payload auditors reproduce their previous canonical hashes. This
repairs the source/provider contract without changing the known CPU residuals or
awarding new authored exact credit. No shared header, compiler setting, source SHA
pin or pending input migration file is changed.
