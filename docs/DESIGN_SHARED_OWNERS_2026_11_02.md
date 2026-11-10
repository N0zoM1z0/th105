# Shared design-object owners, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

DesignObjects.hpp supplies one CDesignObjectBase / CDesignSprite / CDesignGage /
CDesignNumber hierarchy for the loader, lifetime code and renderers. Their
ordinary members remain the shared CSprite, CGage and CNumber. The base uses
the observed float positions and enabled byte, with 0x18 extent and AC / BC / E4
derived sizes. Actual member offsets and every position offset are asserted.
Separate constructor definitions and color forwarding bodies are shared by the
existing comparison contexts; original TU placement and a full-program link are
not claimed. No dummy construction, manual vptr or artificial emission barrier.

All four complete native RTTI graphs match, with 499 unique metadata bytes.
The seven slots of each native table at 6D6A60 / 6D6A80 / 6D6AA0 / 6D6AC0 agree
with the actual source methods, including their weak deleting-destructor
fallbacks. This validates all 28 slots, not just the first pointer.

All 17 previously accepted authored roots in the five affected units remain
canonical, including the linked 55 / 63 / 95 / 581 numeric render chain. The
four already excluded scalar roots remain exact. Their two origin gates pass
2 / 120 and 2 / 121 after source selector names change to the common classes;
native addresses, hashes and owner constraints are unchanged. The loader's
existing generated-origin rule also passes 9 / 948 without threshold changes.

Additional whole comparisons verify the three color methods for each concrete
class, both sprite render aliases, all four owner scalar wrappers, and the
one-byte base render witness. These 16 logical/support bodies are not new
physical authored functions. Shared color and sprite-render bodies are counted
only at their existing addresses; scalar helpers stay excluded, and the
one-byte base render remains unselected/review. No classification is inferred
from short size or RTTI alone, and no new exact/source count is added here.

The main loader remains blocked by its existing unqualified EH relocation.
Its raw emitted section is now 2576 bytes, SHA-256
e9871ce0bd80c905454aad212c21713e8e4bd3a8d39115afd86186e71e3f6a68.
That source-size change is not a native comparison or byte improvement claim.
Gauge initialization retains its 360-byte nonexact candidate hash and first +5
residual. No guessed EH binding, private ABI facade or compiler-profile change.

Final CI passed all 962 tests in 119.765 seconds. Both diff checks gate the local
checkpoint. Totals remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2076, review 296 and units 813.
