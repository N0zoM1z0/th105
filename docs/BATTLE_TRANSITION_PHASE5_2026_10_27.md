# Battle phase-5 transition, 0x004724E0

Complete source accepts **991/991 bytes** under pinned VC8 SP1 O2/GS.
Source src/battle/BattleTransitionPhase5.cpp, unit exact-first-battle-transition-phase5.
The complete generated GS/EH code68 bytes and exception metadata52 bytes also
replay exactly as supporting ownership evidence, with no additional code credit.

## Target, ABI and exception ownership

Only original Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e applies.
The complete body decodes286 instructions and reaches285; the one unreachable
LEA alignment instruction at47252A remains included in the exact comparison.
There is one RET0 epilogue and no unresolved jump or remote authored chunk.
Body SHA256:
3d8bd5b732ab0a830cf6d38c0726dffe61f2c70d8be251ba8f625ff4df4d4f7d.

The independently accepted CBattleManager transition4728C0 calls this method
at4729FC for phase5, ignores incidental EAX, then clears the owner frame counter.
ECX=this, no explicit arguments, void thiscall. Owner player array begins0C;
scenario receiver begins8C. Local views are pointer-only and not instantiated.

Native prologue reserves16C and uses both GS/EH cookies. It pushes handler6BBA06.
Two11-byte unwind funclets6BB9F0/6BB9FB destroy the respective temporary strings
through401E00; the46-byte handler checks cookies689D25 and dispatches to
CxxFrameHandler3 at6899E7 with FuncInfo6E1554. The two-state unwind table begins
6E1544; both entries transition to state-1. Replaying every relocation yields:
- Complete68-byte generated code SHA:
  b2adc90138192074d09f286a4240b75b2704b80fe83c03ff3188639c60e94eee.
- Complete52-byte metadata SHA:
  985800b8091be7db67c91dcbe5da73256f2d9732f40cf2cbb303ddccc6b0a520.

The canonical main comparator intentionally rejects .text$x as an ordinary
authored .text function; the separate auxiliary receipt strictly replays the
six code and three metadata relocations without weakening that validator.
Auxiliary code receives no new authored match/origin claim.

Factory-native IDA metadata/hash, entry68B9D2, mapped bytes and inventory were
reattested before use. Name/void prototype was updated/read back; no target bytes
changed. Direct IDA launcher remains missing mcp/uv, not attached to a wrong file.

## Actual control flow retained

The function searches the two Fighter terminal_finalize bytes with a real
advancing pointer and an independent index. On the first terminal fighter:
- The other fighter supplies the winner character key and signed player index.
  The flagged fighter supplies the loser key and index.
- Format data/scenario/%s/win.txt into the32-byte path buffer, configure scenario
  slot0 with combined-menu input, then call the accepted story-page loader.
- Install win and lose character records with ordinary by-value std::string
  arguments, signed player-byte promotion, X160/Y0 and color160/160/255.

Native code does not initialize the loser key if neither terminal flag is set.
The source does not synthesize a fallback or claim that malformed phase entry is
safe. A valid phase entry is expected to have a terminal fighter; proof that all
external callers enforce it remains outside this bounded reconstruction.

Four64-byte format rows are %sR%%d, %sU%%d, %s%%d and common%%d. Weights1/6/3/10
share a budget initially10. For a positive budget, signed RNG comparison may
skip a row and subtract its weight; an attempted row does not reduce the budget.
Label probes start at0 and stop on the first failed dispatch, bounded at128.
A failure after at least one success selects a random prior index, dispatches
that label and returns. Failure at0 or128 successful probes proceeds to the next
row. All probes are real scenario calls, not replaced by read-only dictionary
lookups. No actual scenario execution or RNG sampling is claimed here.

Local install_character uses the observed int stack argument for the signed
player-byte promotion. The declaration-only facade preserves the complete
by-value frame and call-site MOVSX; it does not claim the callee's original
nominal source parameter names/types. No shared helper/header is changed.

## Complete-source trials

First complete source978 bytes used indexed player search. The real pointer
cursor recovers991-byte size but a cached player-array base distorts later
owner rereads and frame allocation. Using a bounded owner-array view, retaining
fresh indexed reads, and correcting the signed RNG comparison gives994 bytes.
The native searched-index declaration precedes the pointer cursor.

Moving successful label selection into the actual failed-probe branch removes
an invented redundant post-loop count<128 check. This expresses the real nested
exit directly, without artificial goto or flag variables. Combined with the
real cursor initialization order, all991 bytes and GS/EH structure match.

Seven new string literals are pinned to their actual native argument addresses
and emitted COFF bytes; the complete46-byte EH handler is an address binding.
No existing relocation, compiler flag, shared header or accepted unit changes.
The source calls real std::string constructors/destructors, not manual SSO/EH
emulation. No inert locals, fake returns, assembly, copied bytes or padding.

## Reproduce and receipts

- scripts/repo-python scripts/build.py --unit exact-first-battle-transition-phase5 --compare --json
- scripts/repo-python scripts/validate-tracking.py --require-target
- scripts/repo-python scripts/check-match-literals.py --require-target
- scripts/repo-python scripts/ci.py

Private complete controls and strict auxiliary replay:
build/frontier-4724e0-20261027/ and .analysis/frontier-4724e0-20261027/.
The retained audit_auxiliary.py replays68 code plus52 metadata bytes against
the pinned target; target-facts.json records all extents/hashes.

Only this new unit is built; prior exact receipts are retained and totals remain
incremental. Final local CI is pending at writing; its terminal exit/log is the
commit gate. No broad cold build or extra runtime-test framework is introduced.

## Nearby negative context retained

Fresh466F40 isolated source remains1064 versus1074; a genuine same-TU probe with
new exact weather660B30 leaves that caller byte-identical while retaining the
weather full12348 exact. Private artifact scope frontier-466f40-20261027 records
the result; no old caller-lifetime stop is silently promoted.

The46FF30 native deque-begin control emits2006 versus2005 with a larger frame
and an out-of-line iterator dereference, unlike native inline checks. No source
selection or exact credit; earlier front/index negatives remain. Neither lane
is retried as a spelling grid without fresh independent evidence.
