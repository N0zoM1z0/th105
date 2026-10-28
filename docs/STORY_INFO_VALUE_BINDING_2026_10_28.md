# Story InfoManager value binding 0x00471A80

The complete351-byte native body471A80..471BDF exclusive is reconstructed as an
unselected352-byte candidate. First mismatch+16/471A90; no source-selection or
exact-byte credit is added. The canonical Japanese1.06a target remains pinned
by the repository SHA-256.

Native policy binds two integer gauges and two float-number adapters:
- Fighter signed16-bit health174 and secondary47C become record integers08/0C.
  In story mode, the normal record's float-ratio cell08 is an integer overlay.
- Primary span176 is captured and rounded before the first old-gauge release.
  The second span is freshly read after publishing the first new gauge.
- Each old adapter is scalar-deleted before scalar-new. The UI receiver is
  object+18; gauge pointers are at receiver+A0 and number pointers at+24.
- Both number adapters point to the existing story-progress float at record10.
  The target null-allocation branches are retained by ordinary VC8 new-expressions.

The source reuses the established TGageValue and CNumber::bind_value templates.
Existing shared headers and runtime layouts are unchanged. Only the already
affected BattleInfoGaugeRuntime.cpp unit was rebuilt: its accepted20/27-byte
value providers and648-byte normal binder remain exact.

The residual is initial health-address/store scheduling: native LEA EBX then
MOV[EBX],ECX, versus the candidate direct MOV[ESI+8],ECX and later LEA EBX.
That extra displacement byte shifts the rest of the emitted body. A private
union field view and explicit real health-value capture were byte-neutral;
neither speculative change was retained. No forced registers, volatile
accesses, padding, fake ABI or assembly are used.

    scripts/repo-python scripts/build.py --unit gpt-web-battle-info-gauge-runtime --compare --json

Receipt: build/frontier-471a80-20261028/formal-build.json. It reports three
existing exact functions and the new nonexact story binder separately.
