# Global input-table compiler lifetime

43C280 is the complete73-byte checked-vector cleanup of the actual0x68-stride
input table at6FCA2C. It is now independently compiler-owned, with no authored
function or byte credit.

The unchanged SceneResourceBootstrap source provides the observed polymorphic
input type and vector declaration. A separate source file defines that actual
global lifetime, naturally emitting original std::vector<SceneBootstrapInputEx>
_Tidy. No hand-written loop, virtual-slot arithmetic, destructor body, fake ABI
or explicit instantiation barrier is added.

All73 canonical bytes match:
b129687a4a93da507520d706ac8f03e49b47f879242f8a208ceffeb6fdd86b4c.
All29 instructions are reachable, ending at43C2C8. Each live record receives
the virtual non-deleting destructor call with flag0, then the vector advances
by68. The allocation is released once after the loop, and the three pointer
fields are zeroed. This is not delete applied separately to each array element.

The sole REL32 field calls original scalar delete6898EA. Its explicit target
and69 complete non-relocation bytes uniquely identify this body across the
entire inventory under unchanged0.70/24/no-tail gates. The full unmasked
canonical comparison is a separate public unit witness.

Native static initialization at6BEB70 is12 bytes: register destruction callback
6BF090 through _atexit. The complete10-byte callback loads6FCA2C and jumps to
43C280. The source-generated .text$yc/.text$yd bodies reproduce both after
their original named relocations; the public .text comparator remains unchanged.
- initializer SHA256:7ce3cd64bf521664dda624ae33764da824bd23601e5db46aaad16a77fde0d57a;
- callback SHA256:543a55ff0b4c45ff5199620eefb66e90b1be74980b0adb3b4a60eebd826b3aa6.

This matches static zero initialization plus destructor registration; no
unnecessary runtime pointer-reset constructor is invented. These metadata
witnesses and the existing callback add no new inventory/code credit.

Selected source:src/input/ResultInputTableLifetime.cpp, including unchanged
engine/SceneResourceBootstrap.cpp. The larger bootstrap root remains nonexact
and is not promoted or modified. No accepted source consumer or shared header
changes.

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit
vc8-result-input-table-lifetime --compare --json

The origin rule freshly rebuilds the same public source and checks the existing
callback's actual E9 edge. Default CI312 passes.

Excluded1807/review412/units768. Exact1586/450027 authored bytes,
source1788/authored1808/mapped1815 stay unchanged. Among the previously reviewed
static-destructor aliases, the GameConfig string/EH topology remains a separate
closed unresolved lane, not implied recovered by these owner lifetimes.
