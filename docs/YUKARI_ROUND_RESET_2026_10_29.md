# Yukari round-state reset, JP1.06a

58A470 now has complete125-byte selected source; it is not exact.
Native SHA256: 08e7dca8e622185443192b80c7ff2614af9fb091aefa0a60d31232eed7de3b21.
Source SHA256:5e62065f683c1d275fc6adc3204adf5ed86190033163d56f089e9be27b18587a.

The existing canonical-target roster pointer manifest independently assigns
6C5910, primary Yukari vtable6C58CC slot44, to this entry. All125 bytes decode
to the complete RET0 body, with no other branch or remote tail. It invokes
exact Fighter reset4776D0, writes gravity+138=-6, clears the paired float
coordinates+7AC/+7B4/+7B0/+7B8, then seven16-bit counters+7BC..+7C8,
two16-bit counters+7A4/+7A6 and byte flags+7A8/+7A9. Existing YukariObject
consumers independently use the four floats as paired X/Y endpoints.

The new pointer-only derived-tail view reuses FighterResetBaseView. Its void
method does not claim that the native incidental EAX=0 is a returned result.
No runtime object is allocated from this partial view. Unknown holes remain
explicit; no fake locals, padding instructions, assembly or forced ABI is used.

The natural125-byte body first differs at+14: VC8 hoists XOR EAX before the
gravity store and interleaves subsequent word/float zero stores. A single
chained-coordinate-assignment control was byte-neutral and was not selected.
This is full source coverage, not exact-byte credit. The original nominal
class declaration and compilation context remain unknown.

scripts/repo-python scripts/build.py --unit gpt-web-character-round-reset-runtime --compare --json

Formal receipt:build/frontier-yukari-reset-20261029/formal.json.
All thirteen prior reset bodies remain exact in that fresh changed-TU build:
97/54/38/71/89/97/43/38/77/37/17/47/156 bytes. The existing authored vtable
origin rule stays unchanged; no generated helper is promoted.
