# BGM gain threshold's unordered path

Native transition402B70 compares minimum gain against effective gain with
FCOMP at402B9B, then tests only status CF via TEST AH,1 at402B9F. The gain
provider418990 is called on both below and unordered comparisons. The native
master-volume loop403A30 has the same sequence at403AF3..403B09.

The previous source used !(minimum < effective), which also clamped NaN to
-10000. The correct source condition is effective <= minimum: finite low
values clamp, while unordered values continue through the original provider.
No extra saturation or defensive behavior is introduced. This is direct x87
flag evidence, not a claim that NaN appears during ordinary gameplay.

The genuine CIL BgmServiceRuntime unit was rebuilt. Previously accepted fade
403940 and set-level403990 remain exact70/69. Scheduling403840 and stop4038D0
retain their earlier nonexact status. The gain provider and private transition
body are not promoted by exact callers; no exact-byte total changes.

Receipt:build/frontier-bgm-master-volume-20261029/threshold-formal.json.
The obsolete source comment calling the gain provider accepted is corrected.
The current source-integrity withdrawal of418990 remains in force.

Private master-volume continuation establishes the full284-byte native policy
and active-list88/master-gainAC/secondary-gainB0 fields. A real COFF gain-provider
boundary in a CIL caller recovers the native8-byte-aligned frame, unlike the
fully inlined gain variant's64-byte alignment. Source clamp/loop/buffer-load
scheduling remains different, and the strict linked decoder rejects an internal
unreachable alignment gap. The gate was not weakened. Std min/max materialized
reference temporaries and an unbound double literal; that variant is not selected.
No public master-volume source or exact credit is claimed.
