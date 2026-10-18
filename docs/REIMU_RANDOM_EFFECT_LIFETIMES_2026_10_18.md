# Reimu: random effect argument lifetimes

This checkpoint concerns Reimu's81550-byte root478FA0 in the original
Japanese1.06a executable, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable SHA256 remains
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA preflight rejects the different attached target. Facts below come from
canonical PE instructions; no new analysis database was launched or modified.
Root source selection, ledgers and exact credit remain unchanged.

## Target observations and selected source

Action221 starts47C0F7. Its effect123 preparation loads actor X at47C1A0,
reads unsigned facing at47C1A6, adds the double50 constant, pushes arg5=1
and direction at47C1B3/47C1B4, and stores the X base to an m64 home at47C1B5.
The first real MT call47C1B9 supplies unsigned modulo200 for rounded Y;
the second47C1EB supplies unsigned modulo100 subtracted from saved X base.
The effect wrapper call is47C21F. The following jump47C224 joins209's tail
at47B4F2; both actions reach the same advance call47B51B.

The retained source already had the necessary double X-base snapshot and
unsigned direction. Named float coordinate locals delayed the trailing
arguments until after both draws. Expressing the rounded calculations inside
the effect call recovers the observed argument lifetimes for208/211/220/221/222.
With the pinned VC8 compiler, Y draws first, then X. This is compiler/target
evidence, not a general C++ argument-evaluation guarantee or proof of original
source spelling. Layout, ABI, flags, bindings and helper bodies are unchanged.

## Focused native evidence

The new400-input cohort crosses five actions, five raw facings(-128,-1,0,1,127),
two MT seeds, both x87 PC53/64 settings and four X values(-0,640,2**20,2**25).
At2**25, the double X-base snapshot retains bits a float local would lose.
Target checks require exactly two actual MT calls and effect123 at435240.

The void-root harness also reads pending caller arguments at each MT entry:
direction/arg5 before draw1, rounded Y/direction/arg5 before draw2. It records
eight/twelve bytes above the return address, without writing machine state,
substituting helper results or stopping either MT call. Seeding calls outside
the root are excluded by the actual return address. Execution stops at the
first real world request; its returning continuation remains unproved.

| Actual compiled candidate | Inputs | Mismatches |
| --- | ---: | ---: |
| Selected expanded ordinary root |400|0|
| Old named-coordinate source, expanded |400|400|
| Wrong float X-base, staged late-low method |400|50|

The old-source control reproduces the preceding checkpoint's complete
canonical payload SHA256 `ab0a6c4ad164579c98f44af8031e84e5247dbf186cf20e6ae2554fdd1af53bca`.
Its final world arguments can agree while pending arguments differ; this
control calibrates the lifetime observation, not a claimed world-value bug.
The float control instead detects premature rounding in actual request X.
The selected staged method additionally passes0/400 and the old random0/36.

Fresh expanded integration/default/guarded740 execution passes0/1528:
1230 RET,82 object requests,30 effect requests,177 common-root entries,
one action setter and eight guarded pending endpoints. Thus1928 focused
expanded inputs pass; no full historical matrix or aggregate cold replay ran.

## Full candidate diagnostics and reproducibility

Code prefix81304 and ordinary payload82676 are96 bytes smaller than the
preceding checkpoint; frame570h and20253 reachable instructions remain.
All11 switches, nine buffer partitions and550/551/669 request preparations
pass. Genuine linked/ordinary replay agrees over all82676 payload bytes,
SHA256 `f9166f6a3ea904d0bcdb5a761bc0d22e2ccada0383f10c60282a27ac5e42ef73`.
It qualifies2463 fields(1175 calls,1104 numeric literals,14 metadata pointers,
163 code pointers,seven global addresses),1281 PE HIGHLOW entries and the
separate12-byte next-owner INT3 gap. Equality here is between candidate
forms. First strict target mismatch remains+17/478FB1.

Current ordinary object SHA256:
`2db6449a4c8f96d427765934f87309afc4cf80f60ceae5c45fc6448014859e77`.
Linked image SHA256:
`623740ceb34b6302cbadcab7c66bed2a330e9b45ff08eae131a3adab3632cd96`.
Fragment CRLF SHA256:
`f0c4fd4f47f14af4bf7ff3430d84c4c8ad4baf104f69bb4510085137988a089e`.
Native400-input SHA256:
`bf361d468c8d66edf136c733e164f896f4064018c174a107eea66798511cf069`.
Receipts are under `build/reimu-ltcg/` and `build/reimu-shared-finish/`.

Run heavy commands serially with `nice -n 10 taskset -c 0`:

```bash
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort random_lifetimes
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort defaults --cohort unresolved740
python3 scripts/ci.py
git diff --check
```

209/221 now share source47B5DD. Remaining physical sharing differs for300/320,
310 joining215/797(source47BFE5 versus target47D94A/47BFB2), and522/523
(source4858B0 versus target48599F/485D75). Source has118 advance sites versus
121 target; this is static ownership, not per-input multiplicity. Target214
also repeats its6C8/736/482 resource gate at47BD28..47BD60 without an intervening
call/write. Original visibility/source context is unknown; invented volatile
reads or duplicate inert conditions would not establish it. Returning world
contexts, original compiler context and whole-root exactness remain open.
