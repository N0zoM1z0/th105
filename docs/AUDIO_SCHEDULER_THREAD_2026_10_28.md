# Audio scheduler thread 00419100

The canonical Japanese1.06a raw PE establishes the entire 591-byte stdcall
callable [419100,41934F), SHA256
`eec67e8897b41ffe61272030da24a17a0897d62a4e72d2bf827de6dcea376409`.
All decoded instructions are reachable. Its sole RET4 is41934C; the following
INT3 is outside the function. No switch data or remote chunks are present.
Existing independent ownership evidence records418F00 passing this entry to
CreateThread. No IDA session or external source was needed for this recovery.

The source uses the established AudioSchedulerState at703864, without changing
its layout or any accepted consumer. It creates one auto-reset event, snapshots
the maximum correction1000 minus60 intervals, and maintains a timeGetTime epoch,
integer accumulated count, single-precision correction/prior drift/fraction and
an adjustment flag. Each elapsed second recomputes the clamped correction unless
the previous wait was externally adjusted. Fractional correction adds at most
one millisecond per iteration. A nonzero wait adjustment is consumed and cleared.
The existing checked list of listener events is traversed while the existing
critical section is held. Thread shutdown closes the temporary event and returns0.
No missing-event fallback, additional locking or invented error handling is added.

Raw x87 stores establish float rounding at the drift comparison, selected drift,
correction and fractional accumulator. Ordinary nested comparison macros preserve
repeated expressions and the target's comparison polarity, including unordered
selection. The selected existing strict-FP profile disables exception-sensitive
scheduling locally, as independently used in the repository's angle/audio code.
This is a reconstruction hypothesis, not proof of the original compiler switches.

Full first default source produced489 bytes; unsuffixed-double arithmetic produced
473 and a rounded-double variant522. Strict default arithmetic produced553;
exception scheduling disabled produced555. Explicit single-precision drift
conversion and native clamp polarity produce the selected576 bytes. A standard
for_each trial removed native checked-iterator diagnostics and was not selected.
These are bounded whole-function controls, not credited fragments. Native frame
alignment, checked-iterator retention and scalar allocation remain unrecovered.

Selected unit: exact-first-audio-scheduler-thread.
Selected complete candidate SHA256:
`e2e19578441e5e424183b78eb0f38bea753271f63c8f78db2f4f0afcd1927e52`.
First mismatch is the prologue at+0; candidate576 versus native591 is **nonexact**.
Mapping existed already; source presence advances, matches.csv does not change.
Focused receipt: build/frontier-419100-20261028/formal-build.json.
Raw complete-boundary receipt: build/frontier-419100-20261028/boundary.json.
No shared header, alias or compiler profile changed; no corpus rebuild is needed.
