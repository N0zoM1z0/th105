# Audio scheduler initialization and global ownership

The 249-byte native entry at `0x418F00` initializes the audio scheduler at
`0x703864`. Its newly recovered source is retained as an unselected lifecycle
candidate. A natural whole-owner compile reproduces the 249-byte instruction
shape, but strict callback and lifecycle replay is not complete. The function
remains in origin review and receives no source-selection or exact credit.

## Original initialization order

The hash-attested Japanese 1.06a body constructs the critical section, initializes
the thread handle and allocates the checked listener-list sentinel first. Only
then does it set the tick interval to 16, wait adjustment to zero and running
flag to one. These are constructor-body assignments, not member initializers
that would run before the list allocation.

It calls `timeBeginPeriod(1)`, clears the listener list, waits for an existing
thread, and passes `0x419100` to `CreateThread` with a null parameter and the
thread-ID field at `0x703884`. It stores the returned handle and requests
priority 15 without introducing a failure guard. The source uses the real
`BattleThreadHandle::start` and `set_priority` implementations for this sequence.

The complete body closes at `0x418FF8`, followed by seven INT3 bytes. Its SHA-256
is `ec6950230ba030c3aedbd9a799a94eadbf2d911a89c06f8c9e7aad692670b25b`.
The 17-byte initializer at `0x6BE8A0` calls it and registers `0x6BEED0` with
atexit. The latter is a five-byte tail jump to `0x419000`; the initializer's
original C++ table slot is `0x6C0390`. Constructor FuncInfo `0x6E3E98` has two
cleanup states through handler `0x6BD8A3`. The destructor itself has no local EH
frame. These observations are independent of the old IDA boundary inventory.

## Source and bounded compilation

`AudioSchedulerInitialization.cpp` implements the constructor.
`AudioSchedulerLifecycle.cpp` supplies the real global definition and a destructor
using the already recovered shutdown policy. Member cleanup is automatic rather
than an additional manual destruction pass. It includes the actual thread and
critical-section providers; the scheduler entry remains the separately defined
stdcall function. The 60-byte, four-byte-aligned zero-initialized global layout
is verified in the emitted COFF. The source-facing class name is not a recovered
original nominal name.

The public source compiles normally with VC8: constructor 217 bytes and destructor
329 bytes, both receiver-relative. A private real-global LTCG context naturally
specializes the receiver, producing constructor 249 and destructor 371 bytes.
The native destructor is 241 bytes, so it remains clearly nonexact.

That private context also includes the actual scheduler loop. Its default-FP
523-byte result is not the native 591-byte callback, nor the separately selected
strict-FP 576-byte candidate. The existing strict linker comparator has no
supported code-pointer witness for this callback. Binding its code address as
data is rejected, and was not retained. The paired global checker also expects
cleanup EH on both lifecycle methods, whereas this destructor has none. No
validator relaxation or new pointer-binding exception is part of this checkpoint.
The 249-byte shape is useful evidence, not a canonical exact receipt.

## Existing consumers remain unchanged

The complete shared-header closure contains four configured units. Fresh replay
keeps listener creation `0x419350` exact at 169 bytes and BGM service initialization
`0x403460` exact at 133 bytes. Listener removal 198/193, waiting 129/184, the old
selected free finalizer 273/241 and the strict scheduler loop 576/591 retain their
previous nonexact code. All 57 non-debug COFF sections in the three ordinary units
are unchanged. The listener DLL's four sections are unchanged apart from its
export-directory timestamp.

Evidence and the preserved private compiler recipe are under
`build/frontier-audio-scheduler-lifetime-20261109/` and the corresponding
`.analysis/` directory. The public candidate is deliberately absent from match
units and exact ledgers. A next pass needs a supported, complete callback and
no-EH lifecycle proof, rather than another constructor spelling experiment.
