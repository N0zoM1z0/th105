# Complete original CRT sqrt owner and shared tail

68A39D/157 is now whole canonical and inventory-unique within actual original
libcmt:sqrt.obj. It is a shared physical runtime body, not an independent
public calling convention reconstructed from its first instruction.

The proof compares the entire186-byte original text owner at68A380:
__CIsqrt at source offset0, ordinary _sqrt at20, and shared start at29. The
157-byte shared body includes its real error path. Both public prefixes are
already separately excluded and receive no new credit. No copied game-code
implementation, register facade or private exported helper is introduced.

## Complete control-flow context

The actual common.obj helpers are fully compared:

- __load_CW23 at690DE5.
- __convertTOStoQNaN25 at690DFC.
- __fload_withFB67 at690E15.
- __checkTOS_withFB22 at690E58.
- __fast_exit13 at690E6E.
- __math_exit42 at690E7B.

Each original source boundary is fixed by its actual owning section, named
start and next original entry, and each helper has a complete closed CFG.
The whole owner plus these six regions contains111 instructions. Starting
from the two actual public entrypoints reaches every instruction, including
conditional transfers to the proved helper entries. The named external
startOneArgErrorHandling call retains independently established CRT ownership.
No generic conditional-exit, indirect-jump or unreachable-byte rule is relaxed.
No support body is counted as new game or function bytes.

## Whole data and real zero-fill

The complete sqrt operation-name data section8 bytes, original87disp data
section44 bytes and common readonly data section68 bytes all compare exactly.
The original extended indefinite value is compared as its actual raw bytes,
not converted or rounded. Source labels fix the real data roles, including
the separate common-object One constant rather than a same-named value in a
different object. Source .data/.rdata and native storage attributes agree.

The fastflag dependency is the actual four-byte subobject at offset0 in the
original fpinit.obj eight-byte .bss allocation; the next named field begins at4.
Native6FD3A4 is verified writable non-executable PE zero-fill. No raw bytes are
invented for BSS, no flag setter is forced into the program and no assumption
about future flag writes is used to simplify the body.

All four original members are extracted from the unchanged SHA-pinned SP1
archive. Their exact hashes and complete native/source receipts are in the
proof. The formal unit compares the complete157-byte shared tail, while the
origin gate requires the larger owner, public entries, helper bodies and data.
Only157 new runtime bytes are classified. Authored exact totals stay unchanged.

Twelve tests reject wrong source/extent/data roles, missing public roots,
mid-helper transfers, unproved external branches, overlaps, indirect/trap
instructions and incorrect return cleanup. All498 actual initialized-byte
mutation controls fail: every owner byte, every helper/exit byte and every byte
of all three data sections. The original generic CFG gate remains unchanged.
