# Profile menu state-one source

`CProfileMenu::update_state_one` at `0x0044CA80` is owned by the exact profile
menu dispatcher tail edge at `0x0044D2E6`. Its original 446-byte callable and
four-entry switch table are independently pinned in
`ORIGIN_RECOVERY_2026_11_03.md`.

The ordinary structured source covers input-mode updates, empty-name handling,
filename construction, existing-name confirmation, creation and message
confirmation. It uses the existing string, menu and editor interfaces and the
real `commit_state_one` bool return. No synthetic control flow or manually
constructed exception machinery is used.

The fresh O2/GS object section is 520 bytes including its same-section switch
table, versus the original 446-byte callable. The first code mismatch is +17
at a callee-saved-register decision. This remains nonexact, receives no exact
function or byte credit, and does not establish source/native switch or remote
EH equivalence. The newly pinned handler address `0x006BA250` is verified by
the original body's push and the handler's first 16 bytes only; it is a
relocation identity, not a complete handler proof or additional coverage.

The exact 227-byte dispatcher and 696-byte sibling state-six body both replayed
exact; target-independent CI passed all 1,024 tests and progress checks.
