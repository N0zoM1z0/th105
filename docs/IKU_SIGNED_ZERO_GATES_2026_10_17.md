# Iku signed zero gates and constant1 consumers, 2026-10-17

Target is original Japanese1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Complete root620920..62EFBE remains59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The mandatory IDA preflight rejected its wrong image. Observations below use
the attested PE and direct read-only Ghidra; no IDA semantic data was used.

## Observed gates and selected source

Tracking the initial constant1 through the root led to three extra source
consumers. The equivalent integer expressions `< 1` and `<= 0` have different
VC8 lowering here. Selection follows the target's actual comparison operand:

| Action | Target observation | Selected source |
| --- | --- | --- |
| 200 |6214E1 TEST ECX,ECX;6214EA JG; then signed WORD730>1 or>45 | signed facing times DWORD6B4 `<= 0` |
| 223 |622F03 TEST EDX,EDX;622F0C JG; then signed WORD730>11 or>45 | same zero predicate |
| 214 |62272E/622749 CMP WORD[ESI+482],0; JG skips exit | signed WORD482 `<= 0` |

Both input products retain a sign-extended byte104 and actual32-bit IMUL.
200's WORD730>1 condition still needs1; it is not changed. The target's
572/573 sequence checks explicitly compare WORD13E against DI=1 at62B947/
62BAC4 and use JGE. Their `< 1` source expressions remain intact. No floating
comparison, shared type/layout, virtual ABI, profile or relocation was changed.

At the intermediate two-input-gate checkpoint, the entire59462-byte section
changes only six bytes: candidate6214EA/6214EB/6214F3 and622F4F/622F50/622F58.
CMP-register1 becomes TEST-register-self; JGE becomes JG. Every other byte,
including switch metadata, is identical to the preceding a406a5e5 source.
Intermediate source CRLF SHA-256 is
`d379d5a4527ae9650276c3bbea0a0d66f5c117ab59f8529b4b9409d372090a9a`;
its section SHA-256 is
`3c42bc969f2a9b13f0840fe6629751fc86a2dc1f34abef613df83c47b3f59979`.

The additional214 resource rewrite restores the zero comparison and reduces
the complete section by four bytes. It also changes sequence-call sharing:
214 leaves the candidate's shared201/214/567/568 CALL, and its19 sequence
sites become local to214, as in the target's incoming-action classification.
Other actions regroup into candidate{201,567,568,572,573,650}, whereas the
target group at621734 is{201,224,562,563,567,568,650}. The groups still differ.
The target also retains two physical resource comparisons while the candidate
has one. Count/group changes do not prove argument values or original source.

The initial constant1 still loads later in the candidate. Strict whole59038
comparison remains **nonexact +0x64 /620984**. No exact/partial authored credit
or general standalone/LTCG barrier is established.

## Native evidence

The expanded `--opening-branches` profile uses real whole-root entries and
real helpers. Final-source200/214/223 checks pass **0/10720 mismatches**:

- 7200 input-gate cases: five raw signed-byte facings, zero from either
  factor, both DWORD endpoints and large nonoverflowing products, negative/
  zero/positive vertical input, WORD730 thresholds1/11/45 and signed wrap,
  x87 PC53/64. The actual6214E1 and622F03 tests must execute.
- 3520 resource cases: sequences1/3/4/6/8, count736 around10 and signed wrap,
  signed WORD482 values including-32768/-1/0/1 and the4/8 cost boundaries,
  both cost modes, gate6C8 values, facings and control words. Headings avoid
  earlier unrelated sequence transitions. The genuine46BF30 deduction runs;
  both physical target resource comparisons must execute.

Per side, outcomes are3720 action entries,2440 sequence entries and4560 RETs;
464 distinct target-root instructions execute. Backend entries are the stop
boundary: final action/sequence execution and later callbacks remain unproved.
No helper return, executable byte or vtable is replaced. Products in the input
fixture stay within signed32-bit range; general overflow behavior is unproved.

A further **0/432** final-source regression checks the six actions whose
sequence tails regrouped:201/567/568/572/573/650, sequences0/1/2, three frames,
ground/air and rising/descending inputs under both control words. It requires
the actual shared target CALL621734 to execute. It observes72 action,66
sequence,12 object entries and282 RETs per side,372 target-root instructions.
This bounded grid does not establish every path through those action bodies.

Negative controls calibrate the zero boundary:

- At the intermediate two-gate source, replacing both product `<= 0` gates
  with `< 0` detects594/7200 differences:200324 and223270. The first example
  reaches target action204 with zero product and post-increment counter2;
  the control instead returns. That intermediate run also passed0/7200 before
  mutation; final-source coverage is the10720-case result above.
- On the final source, changing only resource482 `<= 0` to `< 0` detects
  1560/3520 differences. The target has2440 sequence entries/1080 RETs;
  the control instead has880/2640. It misses genuine zero-resource exits.

Both controls intentionally exit1. Older full-family native matrices and
accepted-unit matrices were not replayed.

| Profile | Input SHA-256 | Target-output SHA-256 |
| --- | --- | --- |
| Final200/214/223 |5f1c95c0a4c0ec81028ead017ccc6126d5be65f80ccdc374fea093eec0e4be6c |03b63d3b413db79166698687b613cc07c1381d916b41740266459137a17cbcd1 |
| Six-action regression |85016d878706273df6013a2ea80ecb036a4888561b54506dbd76b01456de8999 |d76f3c62ebbaaa4771a56171f4a10e17b2af9c0ac7ec462b669fdacef7191297 |
| Intermediate input control |cc977bdeff2e23e9fe4d974aab4936f0f66a8a0b2be6beb683059ff3b014679b |8f99212cad3698cbfb6dfa5c98a59352a988c27510f0afe601ee97c0a0e8f007 |
| Final resource control |d4eef2702d91679de8ec42d4e5e813719d595e632ed6e062af113a161e989cee |f41319c93b1075db8241c51a8d9737663848f3deaddaf7b33acf1c446d7ceca8 |

## Whole-root and independent analysis

Final source CRLF SHA-256:
`1bf7fcd437528a871e5297100389420fc000e791b6c0bdd54bd281303178a503`.
Configured and native-tested roots replay identically to59458-byte sections,
SHA-256 `347e4d6cf2820eef3559e53f6dd2bab14cffe2065343113d4863875ffd00917b`.
Fresh CFG audit:14990 instructions/58296 instruction bytes in58302-byte span,
six internal alignment bytes, metadata58304 and1156 following bytes,128 RETs,
862 ordinary/177 register CALLs,33/42/35 tables, no local CALLs/external tails.
Owner diagnostics remain8/109, not matches. Frame400hex/84 payload homes,
84 singleton/bijective conditional action/ordinal correlations,57 identity and
no constraint issues remain;182 spawns/190 action-site records. Candidate
pre-epilogue14734 PCs/16898 states versus target14870/16959 do not prove
payload values or feasible paths.

All six73-byte atan2 preparations still equal target at candidate628D55/
628F64/629178/6293F1/62D822/62D9A9. The17-action common surface group remains
at62ECAB/62ECB8;310/409 still share4351C0 at6245DD. Target/candidate advancement
107/106, height19/18, clear30/28 and facing9/10 remain unresolved.

Two sequential read-only Ghidra clones, each768MiB/two CPUs, independently
attest file/import identity, entry, mapped.text, language/compiler and root.
They read back the two input tests, preserved572/573 checks, actual4/8 cost
call and both resource comparisons. Primary nine files remain hash-identical;
each clone is deleted after completion. Target spans and SHA-256:

- 6214D3,36 bytes:62a105591df657a6b5a8f731d9775a85b5356c298a3f6afbbc127db7edf74633
- 622EF5,37 bytes:224a125bffc9ce23dc38a896693b130268787504e31f555d3343dacf0c94d102
- 62271B,60 bytes:8a4e72d1c4f8c163780d4b4392eff55acba3ed21d05cb348f042655ba994d8d4

Initial constant1 lifetime, joint exits/outgoing arguments, original C++/TU/
inheritance/optimizer and full payload/post-backend/exception behavior remain
unknown. Reports live under `build/iku-initial-one/`, private recipes under
`.analysis/iku-initial-one-20261017/`. Superseded objects, private source
controls, clones and caches are disposable; retain current proof objects and
the small genuine-provider cache.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --opening-branches --actions 200 214 223 --output build/iku-initial-one/IkuZeroGatesNative.obj
python3 scripts/probe-iku-upper-actions.py --opening-branches --actions 201 567 568 572 573 650 --output build/iku-initial-one/IkuZeroGateJoinsNative.obj
python3 scripts/probe-iku-upper-actions.py --opening-branches --control direction-zero --actions 200 223
python3 scripts/probe-iku-upper-actions.py --opening-branches --control resource-zero --actions 214
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/iku-initial-one/IkuZeroGatesNative.obj
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
```

The input-control command above regenerates against the final source; its
recorded594/7200 calibration was collected at the explicitly hashed intermediate
source. No fresh final-source negative result is implied by that old receipt.
