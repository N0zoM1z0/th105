# Connect main-state policy: complete827-byte canonical match

444830 is canonical exact827/827. The independent full-section comparison also
matches the one alignment NOP and all seven switch destinations:856/856.
The exact195-byte CMenuConnect update444B90 tail-jumps here at444C1F. No caller,
shared header or already accepted source is changed by this checkpoint.

Callable SHA-256:
30e871325bb176b50768b56e67979ba4fcb451d31c736fbbcf549d4dc00dc86c.
Full856-byte SHA-256:
5b9d706f7093d328f80d974cf1e872cc9389650cfb1689189bfe428e724dd95c.

## Full behavior and boundary

Raw decoding covers all196 instructions, a single RET at444910, all direct
branch destinations and the indirect seven-way switch at4448B0. The switch
owns444B6C..444B87, preceded by the native NOP444B6B. Branches never leave the
callable except ordinary helper calls. The entire far cancel tail through
444B6A is included, not cropped at the first return.

Cursor navigation emits event39. Confirm emits40, clears substate9 and handles
all seven selections:
- Host copies config+38 into port428, publishes outer state1 and resets editor.
- Direct join copies four WORDs from config+3C..42, then port44, publishes state2
  and begins endpoint editing.
- Address-file/history loading succeeds into outer state3/4 after the original
  selection prompt. Failed loading leaves the current mode unchanged.
- Clipboard reads the original1024-byte buffer, constructs the real checked
  string, compiles the original IPv4/port regular expression and searches it.
  On success it publishes state5, constructs the whole-match confirmation text,
  parses a separate whole-match temporary, and presents the original prompt.
- Selection5 enters state6; selection6 returns false immediately.

Cancel and the shared initial-key predicate emit41 and return false. Other
paths preserve the native final key check and return true. No stricter IPv4
validation, new guard or resource behavior has been invented.

## Typed library boundaries and lifetimes

The caller uses actual VC8 std::string, const_iterator, allocator and vector
layouts. The external8-byte regex owner and56-byte match-results object are
ordinary declared constructor/destructor boundaries, not implementations of
Boost internals. Their source names are local descriptive names, not a claim
about original release, symbol spelling or an independently reconstructed regex
engine. Target constructor443780 establishes the16-byte vector, two-word
iterator,20-byte submatch, two-word shared owner and final initialized dword;
destructor442F40 separately proves vector teardown and the shared owner at2C.
The regex constructor442710 initializes both owner words and invokes compilation;
its destructor442440 releases the shared control block. Whole-match string
return442C00 uses ordinary thiscall plus hidden return storage and an integer0.
These library roots get no authored or exact credit from this caller.

All seven real cleanup states match: string text, regex, match results, message,
matched text, concatenation result and the independent parse argument temporary.
Formal-object replay matches77 bytes of cleanup actions at6B9640, the46-byte
shared double-cookie handler at6B968D, FuncInfo36 at6DF4C0 and unwind map56 at
6DF4E4. Only actual zero-addend DIR32/REL32 fields are replayed. Total215 extra
EH bytes are independently verified but are not added to authored totals.

## Two target-backed corrections

The initial full section was852/native856. Native444936 is signedJL, so the
four-WORD loop uses a signed index. This is the actual fixed-count array loop,
not four reordered assignments or register constraints.

Native4449AC also prepares the already established path/text service702918 as
ECX before clipboard40D160. The prior standalone compatibility function is
stdcall because its body never reads this; that does not describe this caller.
The new caller uses an ordinary member declaration on the same known global.
A separate build of the actual existing clipboard implementation, with only
its normal member signature adapted, reproduces all97 native bytes and its
Win32 IAT calls. No private register ABI, fake return, forced barrier or hidden
body is manufactured. The existing97-byte acceptance is not counted again.
After these two observed corrections every827 callable and29 trailing bytes
match, with the same4D4-byte frame and all genuine string/regex lifetimes.

## Reproduction and accounting

    scripts/repo-python scripts/build.py --unit exact-first-connect-main-state --compare --json

Source:src/ui/MenuConnectMainState.cpp.
Formal receipt and independent full856/EH215/provider97/boundary evidence:
build/frontier-connect-main-state-20261031 and its .analysis counterpart.
Fresh Factory-native metadata, entry, five16-byte mapped/raw samples and
function/disassembly/decompiler/xref/callee probes are retained there.

Incremental authored gain is one function /827 bytes:1553 /441679. Source1749,
authored1769, excluded1421, review837, mapped1776 and units741. The three literal
bindings and handler identity are additive. Existing exact receipts remain
valid. Only the new canonical origin baseline is updated; no unchanged origin
rules are cold-replayed. Tracking/progress and CI gate the local commit; no push.
