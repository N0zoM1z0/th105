# Renderer device-loss callback: source, not exact

CRenderer callback401610 has complete22-byte authored policy: bind a zero
texture handle to stage0 through404DF0, then return. The actual two-slot
renderer vtable6D6930 references it first and the independently exact reset
method4014C0 second. COL6DC6CC and type descriptor6FA27C name CRenderer.
The focused origin rule replays the entire native body, table/COL/type and
actual direct binder call401620. This is application resource-reset policy,
not a generic compiler helper inferred from its short size.

Target SHA-256 remains the original Japanese v1.06a
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Whole callback SHA-256:
9dbce8e125d60a54ca8be7d26d6ba4aeab6c5a8fe32a0e153683b93242838e75.

RenderModeLost.cpp implements the existing RenderModeManager virtual callback
using the existing four-byte TextureHandleResult value. The narrow binder
view declares the already established target entry and ordinary by-value ABI;
it does not construct or allocate a manager. No old header or accepted source
is changed. The original nominal handle spelling is not proved.

Ordinary source emits15/native22 and is nonexact at byte0. Both the existing
owned DesignTextureHandle and the existing returned TextureHandleResult types
scalarize the zero argument into register/push operations. Native allocates its
outgoing argument cell and initializes it through its address. This unresolved
argument lifetime/context is not replaced by an explicit stack recipe, fake
ABI or more nominal-type spelling trials. No exact bytes are added.

Public unit: exact-first-render-mode-lost. Only the new authored-origin rule is
validated/materialized; unchanged census evidence is retained. Default CI210 and
whitespace checks pass, with no cold all-unit replay.

Source1772, authored1792, mapped1799, review577, excluded1658, units757.
Authored exact stays1576 /448613 bytes.
