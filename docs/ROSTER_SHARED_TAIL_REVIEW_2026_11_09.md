# Roster shared-tail follow-up, November 9, 2026

The Youmu 853 correction does not transfer to the reviewed Yukari, Yuyuko,
Patchouli or Remilia tails. No new source correction was justified in this pass.

The existing raw-PE inventories supplied each complete callable and owned
switch tables. The private checks verify their full payload hashes and follow
every CFG successor from each nondefault action. Register facts are retained
only when equal at a join; calls invalidate EAX, ECX and EDX. Unknown values
stay unknown. Every reported lifetime ADD also retains ESI as the object base.

| Object | Nondefault actions | Distinct ADD sites at +0x330 |
| --- | ---: | ---: |
| Yukari | 32 | 56 |
| Yuyuko | 28 | 49 |
| Patchouli | 30 | 59 |
| Remilia | 27 | 34 |

All 198 physical ADD sites add -1. Among sequence comparisons with a known
constant, the only sites shared by different primary actions are Yukari
`0x590CA0` (826 and 910, both 9) and Patchouli `0x529ED8` (856 and 910,
both 2). These agree with the current source. The check covers these ADDs
and known direct field comparisons, not every possible lifetime write or
whole-function behavioral equivalence. All four roots remain nonexact.

Two less obvious Yukari/Yuyuko paths also support retaining the current code:

- Yukari 820's sequence-4 edge reaches `0x58FCCB` with cached AX still equal
  to 4, then compares it with 5. Sequence 5 takes the default edge. Do not
  invent a reachable sequence-5 branch to simplify this native redundancy.
- Yuyuko 848 first checks the parent's +0x140 word at `0x5737FE`. Its call at
  `0x573822` retires immediately on a true animation result. Only a false
  result reaches the sequence-12 entry guard; the following signed sequence-at-most-9
  check is separate. The source preserves that short circuit.

Evidence is retained under
`.analysis/frontier-{yukari,yuyuko,patchouli,remilia}-shared-tails-20261109/check.py`
and the corresponding `build/frontier-*/guards.json` files. These checks use
only the SHA-attested Japanese 1.06a target, not decompiler output. The retained
Yukari/Yuyuko reports were verified after Factory access recovered, then rerun
with the explicit object-base assertion alongside the new Patchouli/Remilia
checks. No game source, source pins or exact ledgers changed.
