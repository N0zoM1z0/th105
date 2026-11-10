# Original input-record allocation and overflow boundary

Native43B3B0 is the complete86-byte std::_Allocate family body emitted from
the existing actual SceneBootstrapInputEx input-record/vector source. Its
observed type is68 bytes (104 decimal), not a synthetic array introduced to
manufacture a multiplication constant. The same actual global table and
polymorphic record lifetime already prove vector cleanup43C280/73.

No source, header, flags, ABI declaration or public unit is changed here.
Fresh compilation of vc8-result-input-table-lifetime supplies the original
helper naturally; the73-byte cleanup still compares exactly.

## Whole bytes and compiler tail

All86 candidate bytes canonically agree:
941f3e0a3cd572df7ea47cdb8c4d4f8555a116d2312d3aca15a413134d8f1460.
The original COFF section has one additional INT3 byte. All87 source bytes,
including that byte, exactly match the corresponding87-byte native window:
1c7d9b7a4ac68b4e9f536a369d453c5c7da771845274643f74eecf65de439f62.

Native has ten consecutive INT3 bytes after the86-byte candidate, ending
before the next independent entry. The extra compiler byte is explicitly
verified, not hidden in a masked prefix. It receives no code/candidate credit.
The existing origin gate retains0.70/24 thresholds and declares exactly the
established one-CC tail allowance. Its66 nonrelocation bytes and complete
candidate are inventory-unique.

All26 instructions of the86-byte callable are reachable through the normal
allocation return or the terminal throw call. The normal path multiplies the
requested count by68. Overflow constructs the actual bad_alloc and reaches
CxxThrowException68A153. The complete74-byte CRT throw and32-byte initializer
retain their reviewed hashes; the initializer is noncontinuable and the actual
PE IAT identifies kernel32!RaiseException. This closes the throw endpoint
without weakening the ordinary RET-only decoder or treating an arbitrary CALL
as a return.

## Complete typed allocation-failure metadata

The actual source COFF ThrowInfo16, two-entry CatchableTypeArray12, both
CatchableType records28 and both complete TypeDescriptors canonically reproduce
native metadata. They prove bad_alloc/exception, size12, zero adjustments and
pdisp=-1, with the actual copy/dtor callback identities. The source bad_alloc
primary COL/type name agrees with native vtable6C05A0; ThrowInfo is6E3C18.
The original bad_alloc normal destructor401630/11 and copy402680/25 also compare
fully from this actual input-source object. They were already excluded.

Every ordinary function field is resolved: E8 fields18/59/82 bind original
operator new, exception construction and C++ throw; data fields64/77 bind the
proved ThrowInfo and actual bad_alloc vptr. No instruction or data byte is
masked in the independent canonical replay.

## Accounting and replay

Only43B3B0 moves review to compiler-generated exclusion. Excluded2007/review365;
authored exact1431/443916 bytes, source1635/authored1655/mapped1820 and777 units
remain unchanged. The larger scene bootstrap is still nonexact; neither the
record payload nor its whole construction is inferred exact from allocation.

- scripts/repo-python scripts/build.py --unit vc8-result-input-table-lifetime --compare --json
- Narrow vc8-generated-input-record-allocation-106a origin replay.
- scripts/repo-python scripts/ci.py and git diff --check pass.

This is pinned Japanese1.06a raw-PE and original VC8 source evidence, not a new IDA
interpretation, runtime exception test or generated executable run.
