# YoumuObject action-entry nested switch closure

## Scope

The bounded root is `YoumuObject::initialize_action_entry @ 0x00543670`,
whose reviewed callable is `[0x00543670, 0x00544A97)` (5,159 bytes). All
target observations here come from raw bytes of the original Japanese 1.06a
executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The active IDA MCP image has a different hash; no IDA or Ghidra semantic fact
is claimed in this checkpoint.

## Observed target control flow

The existing owner audit knew the 29-destination action switch but reported
5,083/5,159 reachable bytes, one unresolved indirect exit at `0x0054464F`,
and an unreached range `[0x00544656, 0x005446A2)`. The source path is action
901, sequence 6. Raw target instructions at `0x00544638..0x0054464F` test
sequence 6, load the match identifier from `0x006FA894`, reject values above
3, and execute `jmp dword ptr [eax*4 + 0x00544BD4]`.

The four consecutive target DWORDs at `0x00544BD4` are, in index order:

| Index | Destination | State words written |
| --- | --- | --- |
| 0 | `0x00544692` | `+0x366 = 30`, `+0x368 = 4` |
| 1 | `0x0054467E` | `+0x366 = 25`, `+0x368 = 7` |
| 2 | `0x0054466A` | `+0x366 = 20`, `+0x368 = 10` |
| 3 | `0x00544656` | `+0x366 = 15`, `+0x368 = 12` |

All four bodies rejoin at `0x005446A2`, inside the reviewed callable. The
case-0 store uses `DI`; the enclosing action path loads `EDI = 4` at
`0x005445C6` before reaching this switch. The
table occupies `[0x00544BD4, 0x00544BE4)` after the callable and primary
switch metadata; it is structural compiler data, not another 16 authored
callable bytes.

`config/giant-action-switches.toml` now records this auxiliary table, exact
entry order, and dispatch address. `scripts/audit-giant-action-owners.py`
checks the actual target DWORDs, requires destinations inside the callable,
and requires the configured dispatch to be traversed. A fresh focused audit
reaches **5,159/5,159 bytes**, with no unreached range, unledgered direct
target, or unresolved indirect exit. It reports two validated switch jumps:
the 29-destination action table and this four-destination state table.
This closes raw target branch reachability; it does not prove original TU
ownership or exact candidate bytes.

## Action 820/850 source and comparison

Raw target action 820 writes `phase_index_184 = 1` at `0x00543C0F`, then
unconditionally jumps from `0x00543C16` to `0x00543DA7`. Action 850 starts at
`0x00543D95`, stores two 2.0f scales, then reaches that common tail. The tail
reads `heading_340`, stores its first float to `+0x12C`, converts its third
float, and calls the vtable `+0xC` slot. The ordinary virtual
`select_sequence(int)` call produces the same canonical candidate window as
the former hand-written vtable function pointer, so the source now uses the
virtual call directly. Removing the short-lived local heading pointer is also
byte-neutral.

The target owner spans are action 820 **12** and action 850 **57** bytes;
the candidate still has **26** and **37**. A separate, reverted ordinary-C++
probe writing the common tail independently in both action arms grew action
820 to 46 bytes and moved metadata from +5,156 to +5,176; it did not recover
the target ownership. The retained natural virtual-call source is byte-neutral
against the starting candidate.

Focused reproduction:

```bash
taskset -c 2 python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
```

The complete canonical comparison remains **nonexact** at `+0x80`
(`0x005436F0`); the 5,159-byte target and current candidate window hash
`b800b08d6f4fe213079dfccf0653a652d9095350ab76985b63237b0b1f1ca6da`
are unchanged. The current owner audit has 6/30 instruction-and-edge-identical
diagnostic owners. No partial or whole exact credit is added. The original
source/TU condition that places the shared 820/850 tail in action 850 remains
unknown.
