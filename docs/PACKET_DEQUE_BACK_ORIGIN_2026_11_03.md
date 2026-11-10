# Packet deque back: generated-code origin

The whole82-byte candidate at 0x4179D0 is the VC8 LTCG checked `back` helper
for the packet deque. It is compiler-generated, not an authored game routine.
Native SHA256:
`45252decccc5e54cbebe34eb2a4c5e49b3d25576f71d0df148891db407bc4fe2`.

## Real source and bounded owner evidence

The existing actual UDP sender CIL graph contains the real packet acquire
method. Its ordinary deque access naturally emits and calls the typed `back`
helper with the compiler-selected private EDI receiver. The native 410-byte
acquire method calls 0x4179D0 at 0x417706; its full target body hash and the
actual source-parent call are pinned. **The source acquire parent itself is
nonexact**; neither it nor a new authored function is accepted here. The
existing canonical-exact 167-byte network handle release is rebuilt/replayed
in the same genuine sender graph, with its actual caller qualification intact.

The source helper's complete82-byte, two-return CFG matches the native function
without masks after the three real relative calls are resolved. The source
thunk is independently tied to MSVCR80's named `_invalid_parameter_noinfo`
import; the matching target runtime body 0x68A143 is independently excluded
and whole-body SHA-pinned. All non-call bytes remain significant. A comparison
against all current same-size candidates yields only 0x4179D0. This demonstrates
compiler ownership, not runtime execution of malformed iterator paths.

## Checks and accounting

The scoped rule rebuilds the existing source graph, checks its five source/COFF
pins, three standard headers and compiler/runtime identities, replays the accepted
release and validates both acquire-to-helper edges. Five contract tests and corrupt
root, parent and runtime-target controls reject their mutations. Full global origin
replay and actual exception/error execution are not claimed.

Only this one row moves review → compiler-generated exclusion: review291,
excluded2080. Exact1426 /443399 bytes, source1637, authored1656, mapped1827,
units814 and candidate count4027 are unchanged. The independent deque erase
and tree cleanup leads remain unclassified; a masked resemblance is not proof.
