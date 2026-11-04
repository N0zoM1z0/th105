# System-effect tracked update and prune

Japanese TH105 1.06a `0x00456D70` is a 201-byte SystemEffect manager helper,
SHA-256 `3d388c3213b3e439b25969e50cbc0a28982fa4e44133e2d618c5db2e7846cba5`.
The Scenario command update calls it with the verified two-word virtual-member
pointer. It invokes the callback for each tracked object, retains a live object,
and otherwise releases its handle and erases the checked-list node. The native
release target is an independently exact 170-byte handle-manager function.

The selected `TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>`
source uses the actual manager/pool and a typed standard-list view of its
physical `0x54` list storage. Its ordinary VC8 body is 201 bytes, SHA-256
`8a0b422d86622752dde63ee7ce1af9bc48a4876d94806d157e0a6fa4e6c764f4`,
but differs from native at +159 in erase-path register scheduling. It is
source-present and nonexact, with no authored exact credit.

A bounded x86 observer compares five valid checked-list fixtures: empty,
single live, single dead, mixed live/dead, and a callback that changes one
object from live to dead. It checks update/release/free order and arguments,
forward and backward list links, count and stack cleanup. Native and source
traces agree, and a state-offset mutation is detected. The callback, handle
release and node free are controlled mocks; real object lifetimes, invalid
list behavior, allocation failures and whole-game execution are not proved.
