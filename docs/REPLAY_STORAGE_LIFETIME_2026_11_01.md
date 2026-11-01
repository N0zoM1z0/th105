# Replay storage implicit teardown

The existing replay-storage source now includes its actual static lifetime.
This emits implicit destructor43F260, canonical208/208, without an authored
destructor declaration or body. It is classified compiler-generated and adds
no authored exact bytes. Existing constructor43F1B0/161 and input constructor
42C930/27 remain canonical exact.

## Observed member ownership

The unchanged source already models two embedded0x68 injected-input owners
at+08, the0x50 replay-slot vector at+F4, filename string+108 and real
CriticalSectionWrapper at+124. The destructor reverses the actual member order:
critical section, string, replay-slot vector, then both injected-input owners.
Non-owning input/selected-slot pointers are not deleted.

The whole208-byte body has all62 instructions reachable and RET at43F32F:
ceddb2c1fc924702f1dc4c1c005ac27e65c8715ddb35cd2c3b39371ba996f19d.
Each original call field resolves to the real17-byte critical-section
destructor40AC10, scalar delete6898EA at both sites, original range destruction
42B230, and VC8 array destruction68A2A9. Callback42C950 has the existing
source-array identity; its complete5-byte source tail to CInputManager
destructor409D50 also compares exactly.

The unchanged original range helper42B230 separately matches all52 bytes.
It destroys each slot's private short deque at+3C and its two short deques at
+08, then advances by50. Its full5-byte deque callback448DE0 also compares.
The range helper and deque callback were already excluded. The5-byte input
callback remains review; no small-body threshold is relaxed.

The handler6B9032 receives an address-ownership binding using16 native bytes.
This does not establish full remote EH FuncInfo/unwind equality or runtime
exception behavior. Normal source destruction and all bounded root code bytes
are preserved without handwritten cleanup or fake storage.

## Actual global witness

Native static initializer6BE9F0/22 constructs object6FBDD0 and registers the
existing6BF180/10 destruction callback. The callback loads the same receiver
and jumps to43F260. The source-generated .text$yc/.text$yd functions reproduce
both complete bodies after their named relocations:
- initializer:e8f67739a0618b30f16e1eaadf748f5e820f25ce94b47e07343b809e0954789a;
- callback:fab9e476eabf5af11a4aea29abd6fcd8e34a30b325233c60d6d6273336eac3d7.

These are separate section-aware metadata witnesses. The ordinary .text
comparator is unchanged; no new inventory entry or metadata credit is added.

## Verification and limits

The selected source change is only the real static-lifetime definition in
ReplayStorageConstructor.cpp. Member layouts, constructor statements and
shared headers are unchanged. The original two unit functions remain exact.
The separate origin rule freshly compiles the implicit208-byte body, checks176
non-relocation bytes under unchanged0.70/24/no-tail gates, verifies every
named repeated call destination and whole-inventory uniqueness, and replays
the existing global callback's E9 edge plus the exact critical-section call.

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-replay-storage-constructor --compare --json

All three functions pass. Receipts:build/frontier-replay-storage-lifetime-20261101/
formal.json, canonical.json and static-witness.json. Default CI312 passes.

Excluded1806/review413. Exact1586/450027 authored bytes, source1788/authored1808/
mapped1815/units767 remain unchanged.
