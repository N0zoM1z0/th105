---
name: th105-typed-re
description: Generate and interpret target-pinned TH10.5 v1.06a instruction and ABI fact packets with scripts/typed-re.py. Use for exact bytes, provisional boundaries, callers/callees, register/stack evidence, access widths, calling convention recovery, or source-shape diagnosis before comparison.
---

# TH105 typed reconstruction

Use this read-only evidence layer below the semantic decompiler. Follow
`$th105-re` preflight and single-session rules first.

## Generate a packet

```bash
python3 scripts/typed-re.py ADDRESS --json > build/typed-re-ADDRESS.json
```

Add `--decompile` when pseudocode is useful and `--max-bytes N` for a reviewed
large candidate. The command verifies the local executable and active IDA
target, then records exact target bytes, IDA's candidate, disassembly,
callers/callees, and optional decompiler output.

Read `exact_observations` before interpreting names or types. The candidate
extent remains provisional even when the packet contains every byte.

## Shape source

- Derive calling convention from call sites, stack cleanup, register homes,
  decorated symbols, and receiver use together.
- Preserve narrow signedness and access width when instructions distinguish
  them.
- Treat stack slots, register allocation, branch polarity, constructor timing,
  EH regions, and x87 flow as code-generation evidence only after semantics are
  established.
- A direct address can be a member of a larger global object. Establish writes,
  construction/destruction, and relocation ownership before naming an alias.
- Prefer one type/lifetime/ownership change that explains several instructions.
  Never add inert locals, padding, fake behavior, assembly, or ABI lies.
- Verify every source-shaping hypothesis through `$th105-matching`.

Add reusable VC8 guidance only after a canonical 1.06a unit reproduces it. Old
1.06 or TH08 examples are external hypotheses, not corpus facts for this skill.
