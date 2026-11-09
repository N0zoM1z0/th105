# Call-contract differences that do not establish a bug

A bounded join of selected root symbols and REL32 bindings found several
incompatible-looking aliases. The following original JP 1.06a observations
prevent changing source merely to make their declarations agree:

- Fade query `0x43B2C0` returns full EAX values 0 or 1. Its 24-byte body has
  explicit `mov eax,1` and `xor eax,eax` exits. Existing boolean consumers
  observe those same two values, unlike the scenario's three-state result.
- Replay browse `0x446860` has one return in its complete 511-byte body.
  Every returning path reaches `0x446A51`, which sets AL to 1 before the
  security-cookie epilogue. Its unsigned-byte provider and boolean consumer
  do not reveal a lost third status.
- The three-byte body `0x44E8E0` is just `ret 4`. Script parsing, an empty
  Story renderer and network notifications legitimately share this folded
  body. A float-versus-pointer alias is not evidence that these unrelated
  operations should become one source method.
- Slot finalization `0x465100` has explicit AL 0/1 exits in all 38 bytes.
  Some callers discard its result through void views. That alone does not
  establish a behavioral error or recover the original return-type spelling.

Complete decoded bodies and target hashes are in
`build/frontier-call-contract-triage-20261109/native.json`. No native build or
source modification was needed for these read-only checks.

The animation sequence families remain a more substantial open contract:
several int-returning frame/sequence methods forward the separately recovered
void sprite-frame operation at `0x436760`. Changing that chain requires the
complete virtual-call consumer closure, including finalize overrides; local
byte equality or the leaf declaration alone is insufficient. No change to
those methods or their exact status is made here.
