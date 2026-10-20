# ReimuObject 822 packet and argument lifetimes

The selected 496540 source now publishes the sequence-4 packet and prepares
its actual direction/Y/X call arguments in the target-observed order. The new
624-case observer passes, while the predecessor fails all 576 active request
prefixes despite equal final outputs. All 16 first-packet stack positions in
905..908 now agree, as do the 99 physical World call memberships. The complete
root remains **nonexact at 49655F/+31**; no new exact function is recorded.

## Observed target and inferred source

Only Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking checks pass. IDA attestation rejects10350095...;
no IDA semantics, Ghidra process, database write or target patch is used.
The main39853-byte candidate, void inference/ECX/RET0 contract and complete
46138-byte target comparison ownership remain unchanged.

Raw target49A24F..49A330 observes this sequence:

1. Publish packet words0/1 as zero, then call original RNG100.
2. Publish word2 as5 when the unsigned result is strictly below50, otherwise6.
   Publish word3 as zero after that call.
3. Prepare count4, packet pointer and variant1 before the second RNG100.
4. Convert that second result to direction1 or255 with strict `>50` byte
   arithmetic, and push it before the first coordinate RNG200.
5. Prepare the real Y float argument before the second coordinate RNG200.
6. Reach the actual four-word unparented request at64CCB0, call49A32B.

The source therefore uses four real packet assignments, retains the double
coordinate origins, and places the direction and coordinate expressions in
the actual method arguments. `unsigned char(1 - 2 * (roll > 50))` preserves
the observed byte policy. This is a VC8 emission hypothesis, not unique source
spelling or a portable guarantee of C++ argument evaluation order. Headers,
flags, ABI declarations, bindings and helper bodies remain unchanged.

The original27-byte RNG uses unsigned division by `UINT_MAX / limit`, not
modulo. A private Python MT search only discovers seeds; every retained result
is calibrated by the original target seeding routine and all four real RNG
calls at this822 entry. Seeds0/14/43/50/76/79/137/5489/FFFFFFFF include actual
49/50/51 at both100-bound comparisons. No RNG return is fabricated.

## Scoped execution and controls

`scripts/audit-reimu-object-822-argument-lifetimes.py` observes actual packet
writes, original RNG entries/results, pending outgoing stack words and logical
x87 state. The target packet offset is-584 from root-entry SP; source agrees.
At the later RNG calls the observer checks the already prepared metadata,
direction, complete packet and eventual Y argument against the real request.
It stops at the opaque request entry. Timer-inactive controls execute real
returns and compare ordered writes and retirement x87 state.

The576 request prefixes cover nine seeds, two x87 control words, both facings,
four amplitudes and four coordinate pairs including NaN. The48 inactive cases
cover both control words/facings, four amplitudes and channels14/15/200.
Input SHA256:
`5882f06795b2ed383942b71c7304b0dea78c7566bed2050ea171f72b66436dcf`.

| Frozen source/control | Result over624 inputs |
| --- | --- |
| Selected source | Zero output/write/order/pending/RNG/logical-x87 differences |
| Predecessor78d85ab4 | Zero output/write differences;576 packet-order and pending-argument differences |
| Wrong packet `<=50` | 64 output and pending-argument differences |
| Wrong direction `>=50` | 64 output differences |

Both wrong-threshold controls are genuine private source builds; their
same-TU4963A0 still compares66/66. Separate call-argument-only and packet-store
controls isolate the source changes. A genuine visible4351C0 definition is
also whole-root byte-neutral; that callee independently compares62/62 and the
control remains unselected.

Necessary affected checks also pass on the private selected candidate:
817 coordinate640,817 turn320,821 owner exits6720, retirement sample3600 at
stride37, and12 scoped905/907/908 selector prefixes/conditional call graphs.
The world-sharing observer passes all99/99 memberships over42 action entries,
540 original903 prefixes,180 retirement prefixes and its conditional normal-
return graphs. Sixteen actual first-World observations now match all16 packet
slots, newly including905. No opaque World return is fabricated.

The formal object's entire45700-byte native export equals the tested private
candidate. The new624 observer additionally passes on frozen formal
`tested.obj`; other scoped receipts are connected by that complete byte bridge.
Old133192/26342 and other historical receipts retain their own source epochs.
These checks exclude arbitrary aliases/resources, physical x87 TOP/exception
flags, unmasked exceptions and returning-World execution.

## Full comparison and remaining code generation

| Selected artifact | SHA256 |
| --- | --- |
| CRLF CPP | `4166880c578b304a66e799b0a5ecb3d4476c6ee9e84910c05953f39758435496` |
| Unchanged header | `6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b` |
| Formal COFF | `1ea1edcf91f8465c9fac1e1e2428141b3de73ba81459e553be8044ae1a8981bf` |
| Whole45700-byte canonical source section | `7ffa1d0deb87cc39ec7b821f18483293326b4269e82c8ea5f9a76a0dfcbaa3f8` |

The source has44832 code+868 metadata bytes,10394 decoded instructions,
428 calls and63 RETs, retaining the438h frame. Target has46128 owned code
bytes,10670 instructions,433 calls and68 RETs. The target comparison still
requests46138 bytes; its source hash covers the available45700 bytes, not a
fictional46138-byte padded body. Same-TU4963A0 remains canonical66/66.

Separate817 versus860/861 advance sites and the missing906 final World/wave
sites are restored. Other animation/indirect-call partitions merge: source
shares4351C0 over800/811/821/825 and over815/822; target requires finer sites.
Indirect-call membership also differs for907 and810/812/852. Total call-
membership distance rises9 to11; RET-distance stays27. These are diagnostics,
so the restored World sharing does not imply a closer complete function.

The225-byte822 request window retains13 differing bytes after known direct-
CALL replay: packet-pointer register allocation and direction arithmetic
register/constant allocation. It is not an exact subfunction. The908 post-wave
continuation still emits FILD then memory FADD, versus target FLD-before-FILD/
FADDP; it remains unexecuted by prefix audits. Original source/TU/profile,
other return sharing and whole-root equality remain open. No standalone-
compiler or LTCG impossibility is established.

## Receipts and reproduction

Current products and frozen controls are in
`build/reimu-object-822-arguments-20261021/`; private recipes are under the
same-named `.analysis/` directory. `facts-summary.json` retains the complete
native bridge, call/RET census differences and the nonexact225-byte window.
Completed unselected control graphs are gzip-compressed with per-file SHA256
readback in `completed-controls-compression.json`; frozen source/COFF/native
inputs and comparison/execution receipts remain. Restore compressed graphs
before older private recipes.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected exit1:496540 nonexact+31;4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-822-argument-lifetimes.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-822-arguments.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-world-sharing.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-world-sharing.json
```

Only root evidence/notes and its existing unit notes change. Mapping,
source-present status, origin, byte ownership and matches are unchanged.
No cold aggregate replay or new aggregate percentage is claimed.
