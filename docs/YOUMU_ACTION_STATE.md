# Youmu action state `0x00530200` (exact)

`Youmu_dispatch_action_state_vslot28` (`0x00530200`) is **100% canonically exact**
under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` in unit `gpt-web-youmu-vslot28-full-root`
([YoumuActionState.cpp](../src/characters/YoumuActionState.cpp)).

- Callable code `[0x00530200, 0x0053953C)`: **37,692** bytes (zero alignment
  holes, 114 returns, 598 direct calls across 29 targets), SHA-256
  `19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
- Complete switch envelope `[0x00530200, 0x005399A0)`: **38,816** bytes (three
  sparse action tables with 33/44/22 destinations plus `action720` four-entry
  match-identifier table; 707 index bytes; 1,126 verified relocations), SHA-256
  `07283bd567ce8a199d6d14db90f27218521b465e4a7a2954c231ae9b259b16b3`.
- Owner audit: **98/98** `instruction_edge_identical_owners`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit gpt-web-youmu-vslot28-full-root youmu-vslot28 build/match-units/GptWeb_YoumuActionState.obj --json
```

## Key source shapes proven on this root

- Direct typed member updates on checked receiver/opponent layouts (removing
  cached opponent pointers in `525`/`526` and redundant float copies).
- Separate `if (advance()) { set_action(0); return; }` and
  `if (sequence_entry(1)) { set_action(0); return; }` exits in `302`/`603`,
  and natural sequence blocks without artificial shared `goto` labels in `603`.
- Distinct signed `byte_184`/`byte_47e` tests, unsigned direction snapshots in
  `600`/`730`, `signed char` spawn direction/control byte, and `unsigned char`
  effect direction.
- `action 720`'s flag-preserving `mov edx, 10; lea ecx, [edx+10]` between
  `cmp eax, 3` and `ja` (`0x00538C5D`), verified by
  [coff_switch_payload.py](../scripts/coff_switch_payload.py) and
  [test_coff_switch_payload.py](../tests/test_coff_switch_payload.py).

See [GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md#youmu-source-shape-findings)
for the detailed source-shape breakdown. Related Youmu roots:
[object initializer `0x00543670`](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md),
[fighter initializer `0x0053A1D0`](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md),
and [object update `0x0053CEA0`](YOUMU_OBJECT_UPDATE_2026_10_25.md).
