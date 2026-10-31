# Original VC8 vector operations over the actual frame type

The corrected shared FrameData definition supplies a real28-byte polymorphic
value type with eight raw WORDs, byte14, pointer18 and natural padding. An
explicit instantiation of the unchanged original VC8 std::vector<FrameData>
now reproduces thirteen previously reviewed library bodies /1,315 bytes.

The probe contains only the real type include and explicit library-template
instantiation. It does not implement copy/fill loops, hand-build a container,
change vendor code or introduce register/ABI controls.

## Whole canonical witnesses

Six complete functions, totaling580 bytes, replay with zero differences:

- 421C30: forward nonscalar copy,105 bytes.
- 421CA0: backward nonscalar copy,105 bytes.
- 421DD0: fill,102 bytes.
- 4220A0: element destruction,38 bytes.
- 421EB0: uninitialized copy,115 bytes.
- 421F70: uninitialized fill,115 bytes.

The copy/fill constructors include the actual FrameData vtable binding; the
remaining four witnesses have no relocation fields. Complete comparison is
separate from the generated-origin fingerprint evidence.

## Full inventory provenance

The existing validator independently verifies all thirteen complete bodies,
their current inventory names, native body hashes and full-inventory uniqueness.
The other seven are vector copy construction4228D0/202, erase4221E0/126,
random-access wrappers421E40/99 and421D70/94, allocation422710/81,
tidy422260/73 and uninitialized-fill wrapper422100/60.

The const/nonconst uninitialized-copy source instantiations share one physical
native body; it receives one row, not two counts. The selected representative
does not claim uniquely recoverable template constness where code is identical.

The202-byte copy-constructor source section has one original trailing CC byte.
The corresponding following target byte is independently CC. The existing
maximum-one-CC tail rule is used; no callable instruction is truncated and
coverage/minimum-byte thresholds are unchanged. Other selected bodies have
no tail. These are compiler-generated/std exclusions only, not game-authored
or helper-inflated exact progress.

Public source: scripts/probes/FrameDataVectorOrigin.cpp.
Unit: vc8-frame-vector-origin.
Anchor: config/vc8-frame-vector-origin-anchors.toml.
Receipts: build/frontier-frame-vector-20261031/{formal.json,scan.txt,selected.json}.
The new origin rule was natively validated; unchanged prior evidence is
retained rather than cold-rebuilt.

Exclusions become1,655 and review becomes600. Match units become748.
Authored exact stays1,555 /441,708 bytes; source1,752, ownership1,772 and
mapped1,779 are unchanged.
