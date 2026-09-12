# Aya action-entry evidence, 2026-09-12

This note supersedes the old near-size and scheduler-only diagnosis for
`AyaObject_initialize_action_entry @ 0x0061F0B0`. It is **not an exact claim**.

## Target observations

- Original Japanese 1.06a SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- Fresh IDA preflight and typed packets cover the 4,531-byte callable through
  RET `0x00620262`, and its angle dependency `0x00406540`.
- Action 855 writes byte `[esi+0x184]=10` at `0x0061FC81`, not
  `[esi+0x17C]`. This was a real retained-source member error.
- Action 821 uses unsigned JA for the random-result threshold. The prior
  signed comparison happened to have the same span, but was not the same test.
- Actions 812/817/822 use subtractive sequence dispatch. Ordinary nested
  switches reproduce those branches; the prior if chains did not.
- Action 853 sets its phase byte after the random call. Action 901 sets it
  after its heading/state assignments. Their previous stores were too early.
- Action 856 first admits sequences 1/2/3, then distinguishes sequence 1
  from the random-scale alternative. The target stores the negated angle
  directly from ST0 to the heading at `0x0061FD43`.
- The angle callee's last two instructions before RET are an m32 store/reload
  at `0x00406576/0x0040657A`. This establishes the returned value's rounding,
  **not a unique source-level float-versus-double return declaration**.

## Fresh experiments and retained result

The starting source had 30/32 exact-sized physical mapper rows but only
12/33 instruction-and-edge-identical audit owners (the audit includes an
additional owner row). Equal size was hiding substantive differences.

Retained source corrections restore the member, unsigned test, nested
switches, phase ordering, and structured sequence-1/2/3 graph above.
The double-return declaration is deliberately unchanged. Fresh canonical
comparison still fails first at +0x7F (target 0x28, candidate 0x30);
the section tail is 4,867 bytes and candidate metadata starts at +0x11BC.
The audit has 13/33 identical owners. Action 856 is 414/406 bytes and
108/106 instructions. Its larger span reflects restoring the target branch
graph while retaining the unresolved float-conversion discrepancy; the old
404-byte span combined opposing errors.

An isolated **float-return hypothesis** is a useful new lead:

1. Change only this TU's `atan2_degrees` declaration from double to float.
2. In this unit only, change its REL32 spelling from
   `?atan2_degrees@th105@@YANMM@Z` to `?atan2_degrees@th105@@YAMMM@Z`,
   keeping the target address `0x00406540`.
3. Rebuild and audit with the commands below.

With the structured graph, this produces 406/406 bytes and 106/106
instructions in action 856. All differences in that owner are then limited
to the heading-load register and the virtual-call setup instruction order;
the float store, clamp branches and shared tail agree. Adding a named
requested-sequence local or calling through the existing animation base
view is byte-neutral. These variants were reverted.

This is **not permission to change a return type just to pass comparison**.
The current shared definition and other declarations still say double;
the m32 return value alone is consistent with either declaration. A future
ABI work unit must audit independent callers and recover a coherent callee
implementation before changing shared contracts or accepted units.
The existing angle implementation also contains volatile accesses and a
self-assignment, so its historical exact result cannot establish the
original source type or justify reproducing those constructs elsewhere.

Fresh exported single-TU /GL links were tested with both /O2 /Ot and
/O2 /Os, using the float-return hypothesis. The speed variant realigns ESP
and uses an EBP frame; the size variant also keeps an EBP frame and changes
dispatch. Neither matches the target prologue. These unresolved diagnostic
DLLs were not executed and are not canonical comparison artifacts. They
do not exclude other original TU/caller contexts.

## Reproduction

Run target and IDA preflight before semantic work:

```sh
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/typed-re.py 0x0061F0B0 --decompile --max-bytes 6000 --json
python3 scripts/typed-re.py 0x00406540 --max-bytes 100 --json
python3 scripts/build.py --unit gpt-web-aya-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-action-entry build/match-units/GptWeb_AyaObjectActionEntry.obj --unit gpt-web-aya-object-action-entry --json
```

A compare exit status of 1 is expected for these nonexact candidates; verify
that compilation actually succeeded before consuming the object. Rebuild
again after reverting a hypothesis. Do not compare a stale variant object.

Local ignored evidence is under `build/aya-entry-*`, with the callee packet
at `build/aya-angle-return-typed.json`. Float-hypothesis reports use
`float-return-hypothesis` and `phase-order-hypothesis` in their filenames.
The retained source uses `retained-formal.json` and `retained-audit.json`.
The diagnostic link commands are in `build/probe-aya-entry-ltcg.sh`.
Reports are regenerable and deliberately not committed.
