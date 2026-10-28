# Yukari action-state root 57B030

## Status and scope

Complete124-action source candidate, unselected and nonexact. Compilation,
semantic hypotheses and local diagnostics confer no implementation/exact credit.
The canonical target remains Japanese TH1051.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Factory native IDA was checked on October28: target hashes/file size,
entry68B9D2, initial function inventory401000/52, and16 mapped bytes at401000,
68B9D2,420000,570000,6B0000 all agree with the independently hashed PE.
The direct repository launcher still lacks mcp1.26.0. Decompiler output is a
hypothesis only; raw instruction evidence overrides its lost ST0 results and
misleading shared-tail calling-convention annotations.

Native callable57B030..588F02 is57042 bytes,14501 decoded/reachable instructions,
140 RETs,889 direct calls to32 targets, no unreached ranges. Four action tables
and five nested difficulty tables close every indirect exit. Low/mid/high/
special tables contain44/27/47/6 destinations; the default is588EF3. Complete
payload through5893B8 is58248 bytes, including the two bytes before the first
table, SHA2568c76f4df41ea9627a161193cf132671508311cd6e04717a4314a7cb2390682af.
Callable SHA2567caa43b9c69087875de1d8db150434733ad7b8a0fbd0d7bd245ee288f3db5db3.

## Source and replay

Source: src/characters/YukariActionState.cpp and .hpp. The receiver is a
pointer-only extension, not a recovered complete nominal Fighter layout.
All direct helpers remain declaration-only; none inherits root ownership.
Unit: exact-first-yukari-action-state.

```
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-yukari-action-state --compare --json
scripts/repo-python scripts/audit-yukari-action-state.py
scripts/repo-python scripts/compare-giant-action-switches.py yukari-vslot28 build/match-units/ExactFirst_YukariActionState.obj --json
```

Public replay emits57760 full bytes versus58248. First difference+8 is the
frame immediate4E8 versus native4E0. Candidate SHA256:
e44be96ebde4b16c2a0c178395efda0ba2178be0a24ba7d4575a327ded6537ca.
Full audit reports54746 unequal/missing positional bytes, not a semantic
percentage. Comparison exit1 is expected. Final receipts:
build/frontier-57b030-20261028/formal-first.json, formal-audit.json,
final-map.json and final-action-{calls,fp-ops}.json. Private first/zero-offset/
owner-order/random-argument/entry-gate trials remain in the same build scope;
source recovery fragments are in .analysis/frontier-57b030-20261028/.

New source/header and append-only unit/literal entries have no existing accepted
consumers. Unchanged exact receipts are retained; no whole-corpus cold build is
claimed or required. Final scripts/ci.py and git diff --check remain mandatory.

## Preserved target distinctions

- Prelude998 emits paired+10/-10 one-float packets, not the null packets used by
  other roster peers. Coordinates are(80,130),(60,80),(75,140), signed facing;
  7A2=100. Walk speed is4.5; normal jump12.5/.55; high jumps use.65 gravity.
- Native71..78,88,89,145 recovery actions preserve integer-truncate-then100
  velocity captures, AL boundary tests, layout/event/reset order and one-time999.
  197..199 use independent981 packet lifetimes;199 makes two checked deck calls
  at receiver+55C. 201/224 landing clears VY/gravity, not VX. 201's entry4/5
  checks share the native outer time gate.
- Yukari214 uses five/six release states, turn1/3, acceleration.3, no copied
  peer angle wrapping, and direction-sensitive release selection. Native trig
  results are consumed from ST0 despite missing return assignments in IDA.
- 400/401/404 fan800 has distinct low/high packets and timing;402/406 retain
  float induction and their different formulas. Counter/callback order is not
  replaced with a generalized peer pattern. 801 packets contain four floats.
- 522/523 preserve actual atan/sqrt calls and the native constants37825,65025,
  128500,190800. Do not recompute those constants from presumed geometric
  coordinates: native135/135 atan and37825 sqrt coexist. Their shared speed
  temporaries are float, demonstrated by583389 onward.
- 565/566 distinguish time-counter and frame-timer control. 566 can set frame
  timer75 and then take its same-frame launch. 721 uses10, not75;720 reads
  owner+168 Y for its difficulty burst, not peer+170 Y.
- 710 packet fields1/2 are initialized outside each loop; subsequent callback
  mutations are not overwritten per iteration. Difficulty740 default at588718
  reads an uninitialized stack local. The source leaves the local unset outside
  difficulties0..3; invalid-difficulty behavior is not recovered portable
  semantics and no made-up default was introduced. Further evidence is needed
  before selecting this source.
- 656 loads virtual slot+0C and argument5, then jumps into shared call57B867.
  Reading only instructions immediately before call57B869 falsely suggests
  set_action(10). The incoming register/argument context must be preserved.

## Diagnostics and remaining work

Zero-offset spawn coordinates now read X directly, eliminating unsupported FP+0
in520/521/525/526. Low cases follow raw physical-owner order. Random emission
arguments preserve target Y-before-X evaluation and captured bases while
avoiding unnecessary source temporaries. These are natural semantic/lifetime
changes, not padding or register forcing.

Current per-action direct-call and FP-operation counts agree. Physical virtual
site counts still differ in201(3/2),214(14/13),656(3/4); these count reachable
sites, not dynamic executions or nominal vtable meanings. They do not prove
semantic equality. Native44 low owners become43, merging210/222. The manifest
permits that candidate count only for diagnostics; target expectations remain44.

Payload dataflow resolves101 homes on each side, no unknown spawn pointers.
Native/candidate frames1248/1256 and epilogues140/144 differ. Packet ordering,
size-class positions and scratch lifetime are not yet exact. All49 crossed
consumers test AL; native9/candidate8 on-surface physical sites likewise test
AL. Candidate has3 unreachable compiler alignment bytes. General unordered FP
predicates, callback aliasing and original TU/lifetime context remain open.

Seventeen new literals have unique native operand witnesses and matching COFF
values; no arbitrary unresolved literal binding was allowed. No target patches,
assembly, forced registers, inert locals or fake returns were introduced.
Exact tracking remains1427 functions/413799 authored bytes.
