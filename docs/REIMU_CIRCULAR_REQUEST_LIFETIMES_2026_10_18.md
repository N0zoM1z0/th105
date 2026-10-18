# Reimu: circular request lifetimes and physical arm order

This checkpoint concerns the81550-byte Reimu root478FA0 in the hash-attested
Japanese 1.06a executable. Target and callable hashes remain those recorded
in [the preceding entry checkpoint](REIMU_PRELUDE_LIFETIMES_2026_10_18.md).
IDA preflight again rejects the different attached target; observations below
come from canonical PE instructions. No root source-present or exact credit
is assigned, and no aggregate cold replay is claimed.

## Positive target evidence

The retained source groups obscure physical action order. Expanded generation
now orders distinct owners by their observed target addresses within each
reviewed region. This corrects the placement of214/215 relative to220..222,
402 relative to404,414 relative to416, and740 relative to760. It does not
infer original TU ownership or prevent subsequent compiler sharing.

More significantly, action669's circular object869 requests at48AA9F and
48AB8C prepare count3, the payload pointer, arg5=1 and unsigned direction
**before** their sine calls48AA3A/48AB27. Cosine calls48AA6B/48AB58 follow.
The signed facing used in X is read after cosine. The float payload is shared
between the three-iteration and four-iteration loops, as previously proved.

The former named-coordinate locals prepared all four trailing arguments
after the lookups. Source now expresses the rounded X/Y calculations inside
the spawn call. Both call sites recover the target's argument lifetimes;
buffer identity and loop source remain unchanged. No ABI, layout, compiler
flag, literal binding, machine-byte implementation or artificial helper is
introduced.

The CFG/ESP audit now checks both known circular request contracts: object822
with count4 for550/551, and object869 with count3 for669. It checks actual ID,
count, arg5, sine/cosine order, all reaching argument definitions and dominance
of each tail push over sine. The669 arm must still have four physical request
sites; only its first two use the circular contract. Existing550/551 two-site
guards remain intact. The retained old-coordinate control fails all four
pre-sine observations at both669 sites, while its buffer partitions agree.
New source passes both checks. Analyzer fixtures cover late pushes, wrong
count/ID, reversed lookup order and an unreviewed contract.

## Fresh results

| Candidate | Code prefix | Complete ordinary payload |
| --- | ---: | ---: |
| Previous checkpoint |81668|83040|
| Owner order only |81660|83032|
| Owner order plus669 lifetimes |81400|82772|

The selected code and metadata now fit their reviewed target windows, with
150/152 bytes to spare. This permits focused execution of the expanded
candidate itself. Frame570h remains. Complete decoding gives20260 instructions
(target20256);20253 are CFG-reachable (target20243). These are diagnostics,
not byte equality or partial credit. The target300/320 prefix sharing is still
unrecovered. First strict difference remains+17/478FB1: the candidate now
starts the immediate WORD7A0 store there, before its delayed PUSH EDI.
The signed main selector now starts at the target's4791D4 address. Its300
equality edge and the source320 table entry both reach47CC3A, confirming that
these complete source bodies still merge rather than reproducing the target's
partial prefix/tail sharing.

- Expanded ordinary **0/1528**:1010 integration inputs,510 default inputs,
  eight740 inputs stopped before indeterminate reads. Endpoints are1230 RET,
  82 object requests,30 effect requests,177 common-root entries, one action
  setter and eight guarded pending endpoints.
- Expanded ordinary669 **0/1086**:704 RET,378 object requests and four effect
  requests. Real helpers execute; world requests stop at actual entry. These
  tests do not execute returning world callbacks or the full historical matrix.
- All11 source switches, nine buffer partitions and the selected request
  preparations pass the full CFG/ESP audit.
- Genuine linked/ordinary replay checks2464 fields:1176 calls,1104 numeric
  literals,14 local metadata addresses,163 code pointers and seven game-data
  addresses. The exact PE HIGHLOW inventory has1281 entries. Every one of
  the82772 canonical payload bytes agrees; SHA256 is
  `ab0a6c4ad164579c98f44af8031e84e5247dbf186cf20e6ae2554fdd1af53bca`.

The first link audit correctly rejected unequal MAP envelope lengths. Its
extra12 bytes are allINT3 between the82772-byte ordinary payload and the next
16-byte-aligned MAP owner. The audit now separately proves this complete
alignment gap: exact length below16, fixed aligned start, allINT3, and no
relocation reaching or crossing it. The existing replay still requires equal
payload lengths, exact pointer roles, field inventories and all non-field
bytes. No opcode difference is masked. Tests reject changed gap contents,
truncation, wrong lengths and relocations in/crossing the gap. The linked DLL
is not executed and is not target-exact.

Current fragment CRLF SHA256 is
`6fbe314e3e8535d9b4a17923efd00ffd49ef3b1e0a58563d946bd7dbaf2b7cb7`.
Ordinary object SHA256 is
`ff0c0564928f2bcb02eb1b086937fb95e2bf38cc306c94f1495617d908e56f17`;
linked image SHA256 is
`308a60c50943292193bf1884068dcf7088109e340f17c4d93461af775a3f56de`.
An unchanged-input checked rebuild reused45 objects with zero compilations.

```bash
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --require-contracts
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 669 --native --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort defaults --cohort unresolved740
python3 scripts/ci.py
git diff --check
```

Next compare the remaining physical sharing graphs. Static primary-arm
reachability shows source310 joining the215/797 advance site, source522/523
sharing another advance, and source209/221 using separate sites where the
target shares one. Along with300/320, these explain the net two-site advance
deficit; they are not missing per-input calls or a behavioral proof. Direct
300 and560 are outside this primary-table owner census. Original source
visibility/profile, callable ownership and returning-world contexts remain
open. Superseded compact/trial copies were cleaned; current expanded/link
witnesses and one negative669 source/object remain. Nine primary database
file hashes are unchanged.
