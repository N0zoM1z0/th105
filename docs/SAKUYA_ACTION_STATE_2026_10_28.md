# Sakuya Fighter action-state boundary, 2026-10-28

This is target/boundary evidence for4CADB0, not implementation or exact credit.
Complete source reconstruction remains in progress.

The canonical Japanese1.06a target SHA256 is
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The provisional41511-byte entry span is not the full callable. Existing ownership
records independently hash ten remote chunks through4DD2D2 exclusive. All prior
chunk hashes still agree. The complete contiguous callable extent is75042 bytes,
SHA256 a7d5eb49423691b16358efbb5cb857867932c230a86798f84da233fe4207eb51.
Full callable plus metadata [4CADB0,4DD7E0) is76336 bytes, SHA256
6ca4fc284871b25c320bfd93749f548b34b0b55122661caf137ab3efe6db138f.

Raw linear decoding closes19016 instructions. Fourteen jump tables have31/38/38
primary dimensions and eleven4-entry secondary dimensions. Remaps cover227/226/
230 labels starting0/301/541. Direct300/540/795/797/798 augment108 sparse action
labels. The CFG reaches18993 instructions/74937 bytes, with159 RET0s and190
virtual call sites. The native frame is4D8 and aligned to8. The formal comparison
must use the full owned extent, not only the provisional entry span.

## Alignment correction

Earlier ownership excluded seven-byte LEAs at4D2839,4D2C79 and4D2E19 but still
counted the preceding short jumps at4D2C77 and4D2E17. Both are unreachable
alignment instructions. Their immediate predecessors unconditionally branch to
4D2C8C and4D2E2A. Complete traversal of all14 tables and direct edges reaches
neither short jump; they skip their following LEA to the16-byte boundaries
4D2C80/4D2E20. The two exclusion spans now include the short jumps and are hashed
as nine bytes each. Main excluded bytes are25, not21; owned bytes are74937,
not74941. All remote chunks and remote_exact=false remain unchanged.

This is correction of four compiler-alignment bytes in the denominator, not
new restoration progress. Full-payload byte comparison still includes every
alignment byte; no masking or altered acceptance boundary is introduced.

## Analysis route

Local IDA preflight still lacks its pinned MCP runtime; that session is unused.
The existing Factory-native IDA decompiler failure was not retried. A separate
Ghidra session through Factory repository Bash re-attested imported executable
identity, entry68B9D2, x86/Windows specification and every mapped .text byte before
bounded analysis. Known ordinary helper ABIs, including exact45E0E0, were read
back in the isolated project. Full navigation export completed377265 bytes and
the project saved, verified after a client timeout before any repeat operation.

Decompiler removed-block/spacebase warnings remain hypotheses to review against
raw instructions. No target bytes or IDA metadata changed. The initial Iku
project is untouched. Receipts and raw disassembly are in
build/frontier-4cadb0-20261028/{target-facts.json,target-facts.log,target.asm,ghidra.log};
private preparation is .analysis/frontier-4cadb0-20261028/.
