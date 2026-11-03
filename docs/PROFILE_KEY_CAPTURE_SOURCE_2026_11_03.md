# Profile key capture source

The complete `CProfileKeyConfig::capture_key_input` source at `44B540` is now
selected in `src/ui/ProfileKeyCapture.cpp`. It uses the existing actual
`CProfileKeyConfig` and `DirectInputBackend` definitions. The exact key-config
update calls this member at `44B8A5`. The original body and owner edge are
independently pinned by `ui-input-result-policy-authored-106a`.

The source retains keyboard scan codes 1 through 254 except 148, duplicate
checking, controller axis threshold 500, button scans, binding resets and the
held-frame/count policy. No input hardware or gameplay execution is claimed.
The `+0x120` controller count and backend base are attested by the existing
exact input poll and accessor witnesses. A unit-local relocation alias permits
only the actually used base and count offsets, leaving existing mappings intact.

A fresh strict comparison produces 785 source bytes against the 790-byte
native body. The first 780 bytes agree after relocation; the final return
lowers to SETNE rather than the target branch to its shared false return.
The canonical candidate hash is
`0ec1f2917554765f7cc3956c617ffe025fe6d1a5caf1544ecd400f6cc1dd4410`.
It is nonexact and receives no matching-byte credit. The preceding private
standalone and genuine CIL controls reached the same result; no return, ABI,
register or padding coercion is introduced. The target's seven-byte internal
alignment remains part of the full original 790-byte body, not an omitted span.

Reproduce using `scripts/repo-python scripts/build.py --unit
exact-first-profile-key-capture --compare --json`; the mismatch is expected.
The full retained candidate does not establish original variable names or
all runtime behavior.
