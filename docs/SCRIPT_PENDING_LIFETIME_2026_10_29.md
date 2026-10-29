# CScript pending-command lifetime

CScript_clear_pending_commands405770 is canonical exact147/147:
SHA256ae5c1a883c9e61f6895e030461058811918188020d8828a97e3fdfd8239c5967.
This adds147 authored bytes. The function is an ordinary C++ member whose
private ESI receiver is chosen by VC8 LTCG, not declared in source.

## Independent source boundary

Hash-attested raw clear_commands4056C0 calls405770 at4056D1 with the whole
CScript receiver. A second independently decoded caller, script loading405810,
calls it at405884 after successful file loading. Thus the queue cleanup has
its own reusable game-owned boundary; it is not merely an inline loop inside
clear_commands. Load405810 remains unselected and supplies call evidence only.

The full147-byte helper closes through RET at405802. It tests pending_14,
gets the checked deque back element, calls that CCommandBase's scalar deleting
destructor, and only then pops the slot. The actual deque and cursor types
established in SCRIPT_COMMAND_CURSOR_2026_10_29.md are retained. Its template
access checks do not make this owner-level deletion policy compiler-library
code. The original method name is unknown; clear_pending_commands is descriptive.
The old origin rule grouped405770 with the real map-iterator helper4061F0,
asserting neither had an independent source boundary. The separate load call
and natural member replay contradict that claim for405770. Only that address
is removed from the rule;4061F0 retains its separate compiler-origin review.

ScriptLifecycle.cpp now defines this member separately and calls it from
clear_commands. There are no noinline/forceinline pragmas, dummy callers,
forced registers or executable aliases. The genuine lifecycle CIL naturally
retains exactly the shipped147-byte body, including all three checked-container
runtime calls. Its single source symbol is unexported and uniquely CIL-owned.

## Canonical witness and remaining difference

The existing private_from contract binds source and target caller CFGs and
requires the unique actual direct call. Both whole caller bodies close. The
native site is4056D1; the current source site is100012FA. The ordinary public
clear_commands export supplies the caller witness without exporting or changing
the helper's private ABI. The normal canonical replay resolves every call and
compares all147 bytes, rather than accepting a diagnostic prefix.

The complete outer clear_commands body is now182/native170, first+6. Native
retains the checked map iterator and its separate private increment helper;
the current CIL expands/simplifies that iteration. The outer method remains
nonexact and gets no credit. It is moved from the standalone comparison unit
to the real linked lifecycle unit so the private witness is reproducible.

Existing CScript destructor405660 stays95/95 exact, including its full handler,
FuncInfo, two cleanup funclets, unwind map and static-runtime initialization
witnesses. The original constructor65 and character parser505 also stay exact.

## Focused validation

    scripts/repo-python scripts/build.py --unit exact-first-script-lifecycle-linked --compare --json

Receipt directory: build/frontier-script-pending-owner-20261029/.
All79 previously accepted functions in20 actual header-dependent units replay
exact, plus the new147-byte root. The full timeline-loader1676-byte payload
also replays separately. Nonaccepted Scenario command update retains its
unresolved local basic_string constructor boundary; no accepted result is
blocked. Other pre-existing constructor/render mismatches remain mismatches.
This is an affected-unit replay, not a full corpus cold rebuild.
