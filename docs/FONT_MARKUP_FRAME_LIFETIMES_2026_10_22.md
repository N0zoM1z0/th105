# Markup length, temporary lifetime and independent owner placements

Scope: `TextFont_parse_text_markup @ 0x00411FA0`, original Japanese TH10.5
v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
No control in this checkpoint is selected into reconstruction source and no
exact credit is added. Work began October 21 and continued October 22.

## Fresh observations

The hash-attested raw target's entire 1744-byte main body decodes into 463
reachable instructions. Every main branch stays inside instruction boundaries;
the single RET8 at `41266D` ends exclusively at `412670`. The complete body
SHA256 is `6343d2d6639459aaeadb9de2acd74ecbb0be02f8a908e4b84af385f1daeccebb`.
This closes normal main control flow, not remote EH metadata or unwinding.
IDA preflight still rejects the wrong open executable, so no IDA semantics or
metadata writes are used. Target, status and tracking checks pass.

The selected source remains 1728 bytes /455 reachable instructions, canonical
`a3c2e09c65e0af2c63da0a20950896721a938a3299bc3cf12b4ed600f99296ff`.
It first differs at `411FB0 / +16`: target reserves 796 bytes, source 788.
The current EDX font/ECX height-output/two-stack-word entry and RET8 remain.

Fresh actual-instruction traces use `br>`, `/ruby>` and `color=012aEF>` with
explicit CRT/STL/font/color provider observers. The frame origin is calculated
from each emitted prologue, including its saved-register and cookie pushes.
It is not inferred from a vacant local or assigned from the old report.

| Role / position relative to the fixed frame | Target | Selected source |
| --- | --- | --- |
| Token allocation base home | +18 | +14 |
| Deque object address at grow-map call | +1C | +18 |
| Tokenizer context address | +30 | +38 |
| Original payload length across allocation | +3C | EBP |
| Allocation/consumption count across allocation | EBP | +34 |
| Temporary native string address | +44 | +40 |
| Ruby config constructor receiver | +64 | +60 |
| Ruby font constructor receiver | +18C | +188 |
| Delimiter array address | +324 | +31C |

Offsets are hexadecimal. At `strncpy_s`, target has 16 pending argument bytes,
while source has 20 because its allocation argument is still pending. Both
pass the same four actual copy arguments. Before the next loop `strtok_s`,
target already performs the temporary string's conditional heap release.
These are observed lifetimes and coordinates, not original variable names.

## Independent constraint on the owner extent

Fresh raw straight-line prologues through their first `411430` constructor call
were inspected at `431440`, `43A590` and `44DCB0`. In every case the constructor
receiver is a stack address exactly **0x194 bytes below an adjacent live GS
cookie**. The packet retains exact prologue encodings, caller-body hashes,
constructor sites and entry-relative coordinates.

This observation does not prove the original C++ `sizeof`. It does require an
explanation before increasing the shared owner extent: a larger automatic
object would extend into the independently observed cookie positions under
the ordinary nonoverlapping-object interpretation. The markup frame gap alone
therefore supplies insufficient evidence for a larger font or padding field.
The selected 0x194 owner and 0x128 config stay unchanged.

## Four bounded source controls

All controls compile serially with the same pinned O2/Ob1/GS profile and actual
render caller. Each complete function is compared; no comparison window is
cropped and no register facade or stack filler is introduced.

| Control | Complete markup bytes / instructions | Canonical SHA256 prefix |
| --- | --- | --- |
| Native size_t payload length | 1728 /455 | a3c2e09c65e0af2c |
| Separate used payload and consumed counts | 1728 /455 | a3c2e09c65e0af2c |
| Consumed count as the primary length | 1728 /457 | 93ae6d6a069f5e7b |
| Used named token string, scoped before next strtok | 1728 /455 | 633a895077bd5ba5 |

The first two controls are byte-identical to the selected source. The consumed
count control recomputes payload length and still delays allocation-argument
cleanup; the scoped string changes scheduling without recovering the target
frame. None solves the target lifetime/reservation differences. These are
source-epoch observations, not universal impossibility or LTCG conclusions.

The target plus baseline, consumed-count and scoped-string bodies execute on
the three inputs: **12 parent executions /9 source-to-target comparisons** all
agree under the observers. This small diagnostic checks those concrete traces;
it is not a new broad semantic, real library, EH, GDI or allocation-failure
qualification. No previous 2400/8640-case receipt is presented as a fresh run.

## Reproduction and handoff

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
```

`build/font-markup-length-20261021/formal.json` reproduces all 12 previous
complete font hashes and sizes, including accepted setter45/hex45/blend289.
The checked-character33 remains byte-equal and uncredited in origin review;
eight candidates remain nonexact. Only the relevant font unit is rebuilt;
there is no new aggregate cold-replay claim or selected source/header/profile/
partition/relocation change in this checkpoint.

Raw main-CFG packets, canonical bodies, stack traces and independent placement
evidence are in `build/font-markup-length-20261021/`. Private reproducible
controls, capture and tracing scripts are in
`.analysis/font-markup-length-20261021/`. Unselected object outputs may be
archived only after SHA256 readback; keep recipes and selected inputs.

Remaining questions are the additional fixed-frame homes, outgoing argument
cleanup, destructor-state scheduling and actual original compiler/TU context.
Do not infer extra owner fields from these gaps. Glyph +89 and the larger
ReimuObject root `496540 / +31` remain open; resume that large root from its
selected source and a fresh focused comparison rather than treating font
control results as evidence about it.
