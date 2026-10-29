# System-effect tracked acquisition, JP1.06a

TObjectManagerBase<SystemEffectObject,SystemEffectObjectBase>::acquire_and_link_object
at457110 is canonical exact91/91. Native and fresh source SHA256:
bf41da756949996863b341e5546d6597465d98e98c25e0d32a22e515e495a48e.

The method creates a zero-initialized real output handle, calls the manager's
CHandleManagerEx member at004, publishes that token in the returned object's
CObjectBase handle at008, appends the object's primary SystemEffectObjectBase
pointer to the checked list054, and returns the object. The ordinary helper
inlines; it is not mapped or credited as a separate native function.

The pointer-only manager view exposes the existing actual50-byte handle pool
and12-byte std::list at054, with compile-time60-byte/offset checks. It is never
constructed. The real SystemEffectObject/CObjectBase declarations supply the
initializing four-byte handle value and primary base conversion. No raw object
prefix, manually manipulated list node, fabricated return or register forcing
is used. Existing manager construction, the pool's SystemEffectObject vtable
publication and the actual spawn call at458344 establish the specialization.

Normal VC8 list push_back generates the native node creation421F30 and checked
size growth440370, followed by the two link publications. The entire function
through45716A RET0 is compared. The STL helpers receive no authored credit.

## Boundaries and remaining neighbors

The separate pool acquire456B70 is not accepted by implication. A fresh typed
specialization copied from the existing effect-pool policy remains498/native499,
SHA4706bfb83829b329ddb53c6e91d1beb0711560e7001ab3b37c12943f8f101d4f,
with EBP/EDI value allocation and addressing-length differences. It stays
private and unselected. Its two allocation/reuse branches both use the real
SystemEffectObject ownership and144-byte allocation, but that is not equality.

Release436E60 also remains119/119 with two unequal bytes (EAX versus EDX handle
load/push). Real typed handle conversion and explicit access to its value are
byte-neutral. These fresh controls do not justify register coercion or repeat
old spelling searches. The historical tracked-acquire stop is superseded only
for457110, not its neighboring allocation/release/spawn methods.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-system-effect-tracked-acquire --compare --json

Source:src/battle/SystemEffectTrackedAcquire.cpp.
Receipt:build/frontier-system-effect-acquire-20261029/formal.json.
No shared source/header or data relocation changes. Default CI validates the
selection and ledgers; this is an incremental replay, not a cold-corpus claim.
