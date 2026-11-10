# Battle information-record runtime origin, JP 1.06a

The original `0x46FF30` body is 2,005 bytes, SHA-256 `99d79a657a003cfd2dd32b1e3110eb0952676908631e6567a2087518bab97943`. The current-target boundary audit decodes all 2,005 bytes and finds two returns, no unreached bytes and no outgoing or indirect jumps. Prior target analysis describes the fighter gauges, sprite visibility and effect-lifetime policy in `KNOWLEDGE_BASE.md`.

The freshly rebuilt normal InfoManager update `0x46E5A0` (168 bytes) and Story
update `0x471C90` (99 bytes) both compare canonical exact and call this body at
`0x46E5C3` and `0x471C9C`. The body hash and both caller edges are pinned by the
origin rule.

Earlier private source controls are nonexact and are not selected as current source; the native deque/lifetime context remains unresolved. This checkpoint classifies game ownership only and adds no source-present or canonical exact credit.
