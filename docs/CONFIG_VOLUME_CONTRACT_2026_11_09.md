# Configuration volume setters do not return a status

The configuration volume helpers now use void contracts consistently with the
reconstructed audio setters. Previously, their local interfaces declared those
setters as returning int, and the SE helper returned the last handle operation's
incidental EAX value. The menu and bootstrap do not use that value. A shared
header now prevents these consumers from diverging again.

## Original call and result flow

The evidence is the raw Japanese 1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
A complete executable-section E8/E9 scan finds the following edges, each checked
at a decoded instruction boundary:

- BGM percentage helper `43B1C0` calls master-gain setter `403A30` at `43B1E1`.
  Its only direct caller is menu update at `441255`; `441260` overwrites EAX
  with the configuration pointer before using it.
- SE percentage helper `43B1F0` calls per-handle setter `401CE0` at `43B22E`.
  The remaining loop instructions only advance/compare ESI. Menu call `4412B3`
  likewise overwrites EAX at `4412BE` before any read.
- Bootstrap calls the BGM setter at `43F132`, then the SE helper at `43F13E`.
  It never interprets either result. Its caller at `41E104` immediately starts
  the next scene-load request at `41E10B`, again without using EAX.

No aligned pointer to these four entries occurs in the non-executable raw
sections. Whole native bodies and hashes are retained for the setters, wrappers,
menu, bootstrap and scene-manager initialization. Existing provider source is
already void: `WaveHandleGainView::set_handle_gain` and
`BgmLoadServiceView::set_master_gain`. The register's presence at RET does not
establish an integer status or the original source spelling.

## Preserved behavior and comparison

Scaling still promotes the actual float `0.01f` to double, multiplies by double
`0.75`, and rounds to float. SE still updates all 128 handles in
`6FCA98..6FCC98` using the observed signed address comparison. No operation,
guard, return-register instruction or loop ordering was added or removed.

All three affected units were rebuilt. The BGM and SE roots remain 39/39 and
80/80. Menu update remains 665/665; its full 688-byte owned section also matches,
including the three-byte alignment LEA and five-entry switch table. Bootstrap
keeps its previous complete 3,722-byte candidate and first difference at +863.
All 359 non-debug COFF sections have unchanged bytes and relocation roles,
allowing only the four explicit symbol-name changes from int to void.

The build/proof files are in `build/frontier-config-volume-contract-20261109/`
and `.analysis/frontier-config-volume-contract-20261109/`. Tracking and the
lightweight CI pass. Existing nonexact audio providers remain nonexact, and no
new authored exact credit is added.
