# Scene interpolation's actual receiver contract

Float interpolation450290 is now canonical exact160/160, SHA256:
ae97f4dedacde0a2c994e4b7205286ca980de07376c29222a0ccb03032a8b80d.
Existing easing450120 remains exact131/131 after its declaration is corrected
from a free stdcall helper to an ordinary member operation.

## Independent call-site evidence

Both native interpolation bodies retain their incoming scene receiver in ECX
through the easing call, at45022B and4502F7. Neither middle path writes ECX
before that call; elapsed uses EDX and the start value is kept in saved EDI.
The callee's RET8 and lack of field access alone did not distinguish a free
stdcall function from a member receiving this in ECX. The older declaration
lost the receiver requirement and let standalone VC8 reuse ECX for elapsed.

A normal nonvirtual apply_easing member call expresses the observed contract.
It closes all160 float-interpolator bytes with no register annotation, dummy
use, extra parameter, fake fastcall or forced calling convention. The actual
member implementation independently remains131 bytes exact. The method-only
view is never constructed; original nominal class/helper spelling is unknown.

The x87 easing result is consumed directly in the arithmetic expression.
A named float result creates an extra narrowing spill in the byte path; it is
not inserted into the accepted model. Progress itself retains the real float
normalization before the easing argument is passed.

## Recovered behavior

Unsigned elapsed>=end or start==end publishes the target to both output and
current. Before or at start, output receives current. Otherwise unsigned deltas
produce normalized float progress and the mode-dependent easing result weights
(target-current)+current. Float publication matches every native instruction.
The byte path uses an unsigned current byte and signed32-bit target difference,
then publishes the low byte after conversion; no additional saturation is added.

The byte body remains214/native211. Its ordinary source reloads the start after
using EDI for the current pointer, whereas native loads/zero-extends the base
through EBX directly. No arithmetic/call/guard is replaced to force that last
schedule. Byte-base and later-base-lifetime controls remain nonexact and are
not selected. Full selected source SHA256:
70809ebfdd29807d174d6fc300b0ea534ba9cd6e29d8f8f54669b12ec4c3be0d.
The formal211-byte compared-prefix hash80779674 is not a complete-source hash
or exact acceptance. Only the160-byte float root adds credit.

## Focused validation

scripts/repo-python scripts/build.py --unit gpt-web-scene-interpolation-easing --compare --json
scripts/repo-python scripts/build.py --unit exact-first-scene-interpolation --compare --json

Receipts:build/frontier-scene-interpolation-20261029/formal-easing.json and
formal.json. The latter is mixed: byte mismatch, float exact. No new data
mapping or compiler flag is introduced. Existing SceneRenderCluster caller
source is unchanged; its normal member-call ABI already supplies ECX. Default
CI validates the corrected symbol contract, source selection and progress.
