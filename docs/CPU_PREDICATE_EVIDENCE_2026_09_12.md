# Shared CPU predicate audit, 2026-09-12

## Scope and acceptance

Root `0x005F1F80`, 15,910-byte comparison extent, unit
`gpt-web-default-cpu-action-policy`, source `src/characters/CpuActionPolicies.cpp`.
The original Japanese 1.06a target SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh IDA metadata, mapped-byte and semantic preflight passed. The retained
source and older owner reports were treated as hypotheses.

**The whole function remains nonexact.** No match ledger or exact-byte
numerator changes. Current formal first mismatch is +0x12E, section tail
16,481 bytes, metadata begins at +0x3DF0. The diagnostic owner count is only
14/41, not partial acceptance. Canonicalized comparison-window SHA-256:
`8c84e3f3eff993a14715b929046cdae4f2e60633345b4625e512eb0fa5f06bdb`.

## Fresh target observations and retained source changes

- The three full-result random comparisons in action 200 use unsigned
  branches: `0x5F219A`, `0x5F220C`, `0x5F2288` are JAE/JNB. Its floating
  tests also distinguish ordered predicates from their negated relational
  alternatives. A positive A/B/C selection ladder reproduces this owner's
  instructions except two edges into a still-different shared x87 cleanup.
  Its 448-byte span alone is not an exact claim.
- The later direct random-result comparisons likewise use unsigned EAX
  branches, including the shared policy-expiry JA at `0x5F5D0F`. There are
  51 additional source comparisons in the geometry-selection and expiry
  paths. Their thresholds now have unsigned suffixes. Together with action
  200, 54 source comparisons express unsigned full-result consumption.
  The callee declaration, call order, call count and argument expressions
  are unchanged. This does not uniquely prove the callee's original C++
  return declaration. Its bounded result may make signed and unsigned
  predicates equivalent on reachable game states; that does not make their
  generated instructions interchangeable for exact matching.
- Narrowing into a stored word is a separate contract. At `0x5F3B60`,
  `0x5F3ECA`, and `0x5F41E3`, target loads +0x76E as a word and compares
  it with +0x482, followed by **JG**. These three source comparisons now
  use signed 16-bit operands. Do not propagate the full-EAX unsigned rule
  to these stored words.
- Action 300, 301 and 404 reset arms now put zero mode on the fallthrough
  path observed in the target. Their remaining range, tail and register
  differences are not solved by that observation.
- Action 404–406 now uses positive distance predicates and ordinary repeated
  expressions. Removed decompiler-style double temporaries introduced an
  extra x87 stack copy. Target still retains separate signed lower/upper
  tests where VC8 folds the current source to an unsigned range test.

These are instruction-backed source-contract corrections, not a claim of
unique original source or new observable gameplay fixes. Source-only tests
guard the signedness distinction; they do not replace canonical comparison.

## Rejected experiments

- Ordinary range ladders for action 300/301 fold to unsigned subtract/range
  tests. Explicit cascade labels change tail ownership. An ordinary inline
  range helper leaves a non-target call; forcing that genuine helper inline
  still folds the range. These range rewrites and the helper were reverted.
- Typed-member and later action-load variants make policy 9/10 target-sized
  but change register allocation, including neighboring policy owners.
  Both variants were reverted; size equality was not accepted.
- RTM 14.00.50727.42 on the temporary natural-range source differs slightly
  from SP1 but retains the folded range. Unlike the common-Fighter baseline,
  this CPU experiment is **not byte-identical across compiler revisions**.
  No default profile changes. See [RTM provenance](VC8_RTM_PROBE.md).
- `/fp:strict` introduces `_ftol2_sse_excpt`. The existing relocation contract
  correctly blocks that object; it was not aliased to a different helper.
- `/Og-` produces a non-target EBP frame with 0x268 bytes of local space.
- A fresh `/O2 /GL` single-TU `/LTCG` DLL link of the retained source starts
  with `push ebp; mov ebp,esp; and esp,-8; sub esp,0x10`, unlike the target.
  This exported, unresolved diagnostic does not exclude other LTCG profiles,
  source, caller visibility or whole-program contexts, and is never executed.

## Reproduction

Only this root is rebuilt in the inner loop, per the user's session-specific
authorization. All generated packets, reports, objects and linked images
remain under `build/`.

```bash
python3 scripts/check-ida-mcp.py
python3 scripts/typed-re.py 0x005F1F80 --max-bytes 15910 --json > build/cpu-typed.json
python3 scripts/build.py --unit gpt-web-default-cpu-action-policy --compare --json > build/cpu-formal.json
```

The last command currently exits nonzero because this root is nonexact.
Diagnostic owner audit:

```bash
python3 scripts/audit-giant-action-owners.py default-cpu-action-policy \
  build/match-units/GptWeb_DefaultCpuActionPolicy.obj \
  --unit gpt-web-default-cpu-action-policy --json > build/cpu-owners.json
```

To inspect the signed-word observations directly in the fresh IDA packet:

```bash
jq -r '.exact_observations.disassembly.lines as $a |
  range(0; $a|length) as $i |
  select($a[$i].instruction|test("mov [a-z]+, \\[esi\\+76Eh\\]")) |
  $a[$i:($i+3)] | map(.address+" "+.instruction) | join("\n")' build/cpu-typed.json
```

The retained-source single-TU LTCG discriminator can be repeated without
changing the accepted compiler profile:

```bash
_CL_=/GL bash scripts/compile-unit.sh src/characters/CpuActionPolicies.cpp build/cpu-ltcg.obj
WINEPREFIX="$PWD/.tools/wine-msvc8" WINEARCH=win32 WINEDEBUG=-all \
  wine .tools/msvc80-sp1/bin/link.exe /nologo /DLL /NOENTRY /LTCG /NODEFAULTLIB \
  /FORCE:UNRESOLVED /OPT:NOICF \
  '/EXPORT:?update_default_cpu_action_policy@CpuActionPolicyView@th105@@QAEXXZ' \
  "/OUT:Z:$PWD/build/cpu-ltcg.dll" "Z:$PWD/build/cpu-ltcg.obj"
objdump -d -Mintel -j .text build/cpu-ltcg.dll
```

Unresolved external diagnostics are expected; this image is not runnable or
eligible for acceptance. Do not mask those unresolved calls in a comparator.
