# Wave service buffer release401A80

Canonical exact97/97, SHA
1d59d7e68c7c493a75f24f41e78454b0cc8bcd1d0e24d49a782dc5994b075251.
Unit exact-first-wave-buffer-release, receipt
build/frontier-401a80-20261028/formal-build.json. All38 native instructions and
the complete RET0 boundary are reachable.

Scene teardown41E120 calls this at41E12A with global wave service702288.
Independent constructor401880 supplies stronger layout evidence than the loop:
EH arrays use base constructor418280/destructor4182E0 with32 elements of0x0C
at702350 (owner+C8), then derived constructor4180B0/destructor4180F0 with32
of0x10 at7024D0 (owner+248). Those resource lifetimes were independently reviewed.

The source uses real polymorphic buffer slots and existing COM interfaces.
For each paired slot it releases and clears the ordinary buffer, spatial
interface, then spatial buffer, retaining all three null guards. It neither
destroys the slot objects nor clears their unrelated size/state fields. The
natural index loop becomes the target's two pointer-induction streams without
manual strides, vptr recipes, forced registers or synthetic locals.

The complete service prefix is not claimed reconstructed or instantiated by
this TU. No shared header/profile changes and no generated constructor/array
helper credit. Only the focused new unit is replayed.
