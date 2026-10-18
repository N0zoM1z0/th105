# Reimu root: entry argument lifetimes

This is a source-shape checkpoint for `478FA0`, not whole-root acceptance.
The canonical Japanese 1.06a executable and the81550-byte callable retain
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
and `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA preflight still rejects the attached database's different target hash;
all new target observations come from the attested PE.

## Target observations and selected hypothesis

The three entry spawns at479056,4790BD and47911C call465190. Their respective
direction loads at479009,47906E and4790CD are `MOVZX EAX,BYTE [ESI+104]`.
Each raw DWORD is pushed as the direction argument; `MOVSX` fromAL separately
feeds the signed coordinate multiplier57. The first signed result stays in
EAX, the second usesECX and the thirdEDX. Each Y expression adds the observed
double94/60/100 and rounds through an m32 temporary before argument delivery.
The signed X product is loaded withFILD, added to the actor's m32 X and
rounded again. Later action reads remain independent across possible calls.

`ReimuActionStatePreludeBody.hpp` now snapshots the raw unsigned direction
once per call and supplies the rounded coordinates as argument expressions.
The resulting root recovers all three MOVZX/raw-argument/signed-register
patterns. This is evidence for the selected lifetime hypothesis; equivalent
source spellings and original local names remain unknown. No field types,
ABI declarations, compiler flags, relocation bindings or ledgers changed.

The Iku620920 entry also resets WORD7A0/7A2 using16-bit accesses. That offers
no positive reason to change Reimu's field types. Reimu's target first sets
the available EBP to7 at47912D, whereas the candidate first pools zero there.
The original cause of this register-allocation difference remains unknown.

## Focused results

- Entry-only VC8 text changes530 to522 bytes. Native entry comparison is
  **0/10584**, including signed-direction endpoints, NaNs, infinities and
  PC53/PC64. Actor memory, first real callback arguments, return/dispatch
  endpoint, stack, preserved registers and x87 state are compared.
- The compact void witness is50816 bytes. The nine request-family matrices
  pass **0/6722**:5102 native returns,1604 real object-request entry stops and
  16 real effect-request entry stops. Helper results are never fabricated;
  returning-world behavior is outside this proof.
- The expanded ordinary and genuine linked roots both retain prefix81668,
  text83040 and frame570h. All11 switches and nine buffer partitions qualify.
  Independent replay checks all2465 relocation fields and1282 HIGHLOWs;
  **all83040 canonical candidate bytes agree** between the two build paths.
  Their new common SHA256 is
  `ef6cc2879b328bc86a22b274b1bce9b36acb5f3221818227069e7e073738b01b`.
- Strict comparison with the target still first differs at+17/478FB1.
  Code/metadata exceed their target envelopes by118/116 bytes. The oversized
  root and linked DLL are not executed. There is no new exact/source credit,
  aggregate cold replay or replay of the complete historical native matrix.

Current witnesses:

| Artifact | SHA256 |
| --- | --- |
| Prelude fragment, CRLF | `68b5237e719b58950cfc96e4e19be59c0c27a7460f18a62d310e3062381584f8` |
| Entry object | `5fc6bbc1749153fe47bfc6d90d4b7d59b3593bdc94f8f8ff35b49ea6bceca362` |
| Ordinary root object | `046b8cc0d4d02d287aaec1c8406ff7c9ae834921f312047c9f8089f854dbe2c7` |
| Compact object | `7085f25f85e714e6070143db042aa59156700ef6ed038768e75e79a5ca6609c5` |
| Linked image | `83c5ac15e506f7be591e4b3ecd62197c0a4cdaec12ea04a3bbc0bcea869bf1f9` |

```bash
scripts/compile-unit.sh src/characters/ReimuActionStatePrelude.cpp build/reimu-prelude-lifetimes/ReimuActionStatePrelude.obj
python3 scripts/audit-reimu-action-prelude.py build/reimu-prelude-lifetimes/ReimuActionStatePrelude.obj
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/probe-reimu-action-source-shape.py --void-root --compact --output-dir build/reimu-prelude-lifetimes/compact
python3 scripts/audit-reimu-root-stack.py build/reimu-prelude-lifetimes/compact/ReimuActionStateDispatch.obj --native-only
python3 scripts/ci.py
git diff --check
```

The real-link compiler cache conservatively hashes every source header:
editing this fragment invalidated45 objects, despite only three top-level
command groups in the receipt. Unchanged-input cache reuse remains available;
do not mistake the command-group count for the number of compilations.
73 superseded copied sources, objects and large dumps were removed, freeing
7161518 bytes. Current witnesses, small historical receipts and primary
analysis databases remain. Callable ownership, partial300/320 sharing,
original TU/visibility/profile and returning-world contexts remain open.
