# CScript owns commands and a checked iterator

The pending deque014 contains CCommandBase pointers, not command factories.
The three old runtime cells028/02C/030 are one12-byte VC8 checked deque iterator.
ScriptCommandRegistry.hpp and ScriptLifecycle.cpp now model those actual types.
No exact count changes: constructor65 and genuine-LTCG destructor95 remain exact.

## Independent native evidence

The command-line parser405930 looks up a factory, calls its virtual create
slot at405A61, then calls the returned command's parse slot at405A76. Its
fallback similarly creates at405A8C and parses at405A9A. Both paths append the
created command pointer to deque014 at405AA4. Factory objects remain separately
owned by the map000/default factory00C; they are not the deque values.

Load405810 initializes the cursor from the deque's begin position:028 is zero,
02C is the deque address and030 is its logical offset. Next-command405AC0
compares that iterator with deque.end(), dereferences it, then increments the
logical offset. The selected VC8 header's actual iterator is12 bytes and
reproduces the three constructor stores and checked access layout. Compile-time
checks now pin its size and offset028. The unnamed/uninitialized010 cell is
unchanged.

## Source and focused validation

The constructor initializes current_28() as a genuine iterator rather than
three void pointers. Cleanup deletes CCommandBase objects before popping their
slots, retaining the independently verified native order. The linked contract
uses the actual command-pointer deque destructor/tidy symbols; its full native
EH cleanup validation still passes.

The dependency graph identifies18 affected units with77 accepted functions.
All77 freshly replay exact. Existing nonexact results are preserved separately:
clear_commands296/170, Scenario constructor1528/1527 and render930/930 retain
their previous canonical candidate hashes. The Scenario interpreter remains
blocked at its unqualified local string-copy constructor, not accepted.

Receipts:build/frontier-script-command-cursor-20261029/affected.json,
regressions-0-9.json, regressions-9-18.json and each named unit's formal report.
The full destructor receipt retains its validated_cleanup_eh packet. No cold
corpus rebuild or unrelated origin-check claim is made. Default CI validates
the final header/source/manifest reconciliation.

## Next-command boundary remains open

A truthful private next_command implementation using the real iterator emits
104 bytes in COFF, but calls the iterator dereference through normal ECX rather
than target-private EAX. Genuine CIL instead inlines that dereference and emits
156 bytes; a genuine iterator-reference lifetime gives153, still nonexact.
No forced ABI or inlining barrier is introduced. Those controls stay private;
no new method, helper or authored credit is selected from them.
