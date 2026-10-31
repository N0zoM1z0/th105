# Audio scheduler finalizer: iterator lifetime correction

The complete241-byte419000 target keeps the original listener-list end node in
EDI at419039 across the loop. It separately checks the current node against the
live sentinel before each dereference and increment. The retained source called
end() in each loop condition, allowing its first dereference guard to disappear.
It now uses the real cached end iterator, as independently observed in the raw
PE, while preserving current native checked-iterator behavior and call order.
This is a source/lifetime correction, not a byte-count improvement.

The target remains the pinned original Japanese1.06a executable. The existing
startup419000 ownership evidence and candidate boundary are unchanged. Fresh
raw decoding and the boundary audit cover the entire241-byte body. It includes
the native short loop-alignment gaps; no gap is discarded for acceptance.

The original selected ordinary build was259/native241. Corrected ordinary source
is273/native241, nonexact at entry. Real CIL with actual CriticalSectionWrapper
and BattleThreadHandle definitions emits351 bytes and inlines the second wait;
using the real thread implementation as ordinary COFF plus the cached end
iterator emits304. The latter still inlines list destruction, while native
408A00 uses a private ESI boundary. No fabricated prototype, noinline barrier,
manual list guards, stack padding or register forcing was added.

The CIL diagnostic stops on unaccounted unreachable bytes (the earlier variant
also reaches an unsupported global vptr publication). Neither is an accepted
receipt or a reason to weaken the comparator. Both are already size-nonexact.
The public ordinary comparator reports the complete273-byte mismatch normally.

Source: src/audio/AudioSchedulerFinalizer.cpp. Only its existing unit includes
this file; no accepted root is affected. Public reproduction:

    scripts/repo-python scripts/build.py --unit gpt-web-audio-scheduler-finalizer --compare --json

Receipts: build/frontier-audio-finalizer-cil-20261031/ordinary.json,
boundary.json and ci.log. Private real-provider recipes are retained in the
corresponding .analysis directory. Exact totals remain1545 /438021 bytes.
