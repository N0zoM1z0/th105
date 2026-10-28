# Exact long InfoManager record binding 0x00432550

The complete107-byte Japanese1.06a body432550..4325BB exclusive is canonical
exact. Target and relocated object SHA-256:
1650d4b1fb2d5af3e53307d1f6e2cc5b743260d95f04640271d8abdd11d0cd5d.
The target executable remains SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The authored operation publishes the resource pointer at000 and the side byte
at132, queries the common spell texture6FA6DC through404E60, binds primary
sprite+004 through virtual slot14, then clears active14C, alpha130/131 and
timer12C in native order. Complete raw decoding ends with RET8; no missing
tail or generated auxiliary code is part of this extent.

## Byte-side contract

The target consumes only the low byte of its second stack argument. Its three
accepted callers pass sides0/1. A coherent unsigned-byte formal parameter
reproduces the native reuse of the two dead argument slots for width/height.
The earlier int-side facade compiled107 bytes but exchanged those two output
homes. Swapping scalar declaration order was byte-neutral, and grouping the
outputs in a struct unnecessarily allocated eight new stack bytes. Neither
control is retained.

The new shared declaration is used by the callee and both caller TUs. All
five functions in those two directly affected accepted units remain exact.
No assembly, manual stack-home access, copied instructions, padding, volatile
storage, dummy locals or fake returns are used. The existing typed record and
sprite interfaces retain their layouts and virtual slots.

## Focused reproduction

    scripts/repo-python scripts/build.py --unit exact-first-info-long-record-binding --compare --json
    scripts/repo-python scripts/build.py --unit cross-v106a-info-manager-base-binding --compare --json
    scripts/repo-python scripts/build.py --unit cross-v106a-info-manager-story-binding --compare --json

All three formal reports are under build/frontier-432550-20261028/formal-*.json.
The accepted consumer extents are214,35,78,215 and31 bytes. Only these affected
units were rebuilt, not the full corpus. No new compiler flag or relocation
binding was introduced. The previous unknown/review origin becomes the
existing canonical-exact-authored baseline; no excluded compiler bytes are
reclassified. This adds one authored exact function and107 bytes.
