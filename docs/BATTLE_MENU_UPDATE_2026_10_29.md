# Battle pause-menu update, JP1.06a

4407E0 is now complete source-selected and positively authored. It remains
nonexact:892 source-owned bytes versus880 native-owned bytes, first difference
+48 at440810. There is no797-byte exact credit or prefix credit.

Native callable797 SHA256:
97d91340e08278600b314445f693a0f0007562d35631d5f9213dcd0cb7590532.
Native complete owned880 SHA256:
c65e52fb5e8f2d638dfbb00c32e5e53901f2d5fca83ed08bf9f49cbaa5237bf1.
Complete source892 SHA256:
b371c1cff89907db96946f12ce1225b63832033f327c77e7719a3e9afee9129c.

## Ownership, boundary and behavior

CMenuBattle vtable6C1A5C owns slot08 at4407E0; exact render440780 and deleting
destructor440F00 occupy the same RTTI-verified table. Raw CFG reaches all797
callable bytes through267 instructions and twelve RET0 exits.

The owned suffix contains alignment, a four-entry state dispatch table,
42-byte state remap and five-entry action table. State0 selects the main
menu;30/40 handle a replay-save question;31/41 handle the saved confirmation.
Other values retain the menu. The complete suffix is replayed separately from
the callable ledger; it is not silently cropped from the source comparison.

A pending owner transition at+84 returns true immediately. Main navigation
uses the vertical cursor and common input events39/40/41. Entry0 closes the
menu. Entries1/2 create the real330-byte CProfileKeyConfig for player0/1,
preserving allocation-failure and C++ cleanup paths. Entries3/4 request owner
transition1/2, with the actual session-option and config+71 replay-save policy.

Prompt result2 cancels and clears state. Result3 advances to31/41, saves the
replay and shows the saved message. Result4 applies the requested transition
and falls through the same state-clear path as result2. Confirmation completion
sets transition1 for31 and2 otherwise. No new defensive checks are introduced.

The exact CP932 select/title replay prompts and saved message are separately
fingerprinted. The existing InputManager layout places hold at+38. Native
40DCC0 is checked vector subscript, without an at-range exception path; its
declaration-only receiver retains that boundary. Shared source headers and
existing accepted consumers remain unchanged.

## Evidence and residual

The two real new expressions have separate cleanup states. Native full27-byte
handler6BB9C6 points to FuncInfo6E1520, two-state unwind map6E1510 and two
operator-delete cleanup actions. The source uses real new expressions and the
actual CProfileKeyConfig declaration, not a synthetic allocation or vtable.

Initial explicit-return source was924 owned bytes. A common-return switch
control was900 and unselected. The selected source retains the native result4
to result2 state-reset join and is892. Remaining differences concern shared
return blocks, the early owner guard and allocation of the constant1 across
state branches. No goto-only tail shaping, dummy liveness or register forcing
is used. Twelve extra bytes is not twelve differing positions: the full replay
has787 unequal positions including length.

Formal callable receipt and independent complete-relocation replay:
build/frontier-battle-menu-update-20261029/formal-build.json and compare.json.
Native CFG/tables/EH are recorded in native-facts.json in that directory.

Focused command:
scripts/repo-python scripts/build.py --unit exact-first-battle-menu-update --compare --json

Default CI and diff checks cover final source/tracking/progress. No cold corpus
build is required for this isolated source unit.
