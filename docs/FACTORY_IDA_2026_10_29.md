# Factory-native IDA workflow

The registered th105-ida provider now exposes46 allowlisted operations through
Factory-owned stdio. A fresh read-only preflight succeeded on2026-10-29 at
21:12..21:14 UTC. No database metadata or target byte was changed.

The metadata hash is canonical JP1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e,
MD52ae711a6c92c4addbdbf526bc61d8e59, file size3129344, base400000. The
independently retrieved entry point is68B9D2. Factory labels this initial check
metadata-only; it must not be reported as full mapped-byte verification.

The same five16-byte samples as scripts/check-ida-mcp.py were read from the
database and compared with the pinned raw PE:401000,68B9D2,420000,570000,
and6B0000. All agree. This is sampled mapped-byte attestation, not a whole-image
database byte scan. The inventory probe returns401000 with provisional size52;
its17 disassembly lines and nonempty decompilation work, as do callers/callees.
The byte-read fallback followed failed global-value queries for the code probe.

Private responses and comparison:
- build/factory-ida-preflight-20261029/operations.json
- build/factory-ida-preflight-20261029/samples.json
- build/factory-ida-preflight-20261029/comparison.json
- build/factory-ida-preflight-20261029/semantic.json

The legacy repository bridge still fails before connecting because its Python
runtime lacks mcp1.26.0. The Factory-native provider is a separate session;
it does not depend on that runtime. Do not repeatedly reinstall or poll the
legacy bridge when the native provider has independently passed preflight.

For the next bounded scope, re-attest metadata/entry/sample bytes and retain
fresh results. Use the discovered schemas, not assumed tool arguments. Factory
readbacks remain provisional analysis and add zero exactness credit. Check the
operation's truncation/retained-artifact metadata; do not treat a preview as a
complete decompilation. Raw control flow, calling convention and canonical
compiler comparison still decide source acceptance.

Metadata edits are allowed only within the reconstruction task and must be
mirrored into repository evidence and read back. Target-byte patches remain
forbidden. Do not invoke a bridge shell through semantic operations or infer
that the new provider authorizes additional system/credential changes.
