# System-effect manager spawn

The November 9 value-return recovery closes the complete root at **125/125**.
The earlier frame mismatch below is retained as the failed explicit-result
model, not the current status.

Scope: Japanese TH105 1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete 125-byte body at `0x00458340` has SHA-256
`fb7c209236cf71b44bfd6bdebd6831442618fd0f2d5310c6c6744faec56182e1`.
The Scenario command interpreter calls it at `0x0045942A`.

The body obtains a tracked SystemEffectObject from the actual manager, loads
and assigns a texture handle, configures its sprite with the returned width and
height, stores x/y and the sign-extended 16-bit mode, then calls the object's
virtual reset and returns it. Exact existing acquire/link and sprite setup
providers independently support the owner and operation identities. The
texture-loader source remains nonexact; its full-system behavior is not claimed.

The selected ordinary C++ source uses the shared real manager, object and
sprite types and connects the command-interpreter hypothesis to that member.
Its full candidate is 125 bytes, with canonical SHA-256
`de9097da0f5e072f9fe6588040bdb36e7b285b6ac3842c60498fb48f3625b63e`.
It is nonexact starting at +2: the compiler allocates a 12-byte stack frame
where the target uses 8 bytes. It is recorded as authored/source-present but
adds **no exact bytes**. No register coercion, parameter-slot aliasing or
fabricated helper is used. No full executable link or behavior test is claimed.

## Virtual member-pointer thunks

Native Scenario update and render materialize `0x00454F30` and `0x00454F40`
as pointers to the SystemEffectObjectBase update and render virtual members.
A tracked pinned-VC8 witness emits the same complete five-byte thunks, each
unique among the current candidate spans. Their native bodies and the two
pointer-immediate sites are pinned as compiler-generated origin evidence.
These ten bytes are excluded from authored progress, not newly matched game
functions.

## Bounded observer, 2026-11-04

A fresh pinned-compiler build and the hash-attested native body were executed
in an isolated x86 observer with five signed mode values, including both
16-bit extremes, and five finite coordinate pairs. The observer substitutes
controlled allocation, texture-loading, sprite-setup and virtual-reset calls;
it checks their order and arguments, the signed mode and coordinate stores,
return object and stack cleanup. All five native/source traces agree. A test
mutating the emitted mode-store offset is rejected by the trace comparison.

This covers only those fixtures and stubbed dependencies. It does not exercise
actual resource I/O, GPU rendering, allocation failure, operating-system EH or
the full game, and does not change the nonexact byte status.

## Four-byte texture return closes the frame, 2026-11-09

The texture loader's result is the existing four-byte `TextureHandleResult`
value, returned through VC8's hidden member-result pointer. Other recovered
texture callers already use this contract. Applying it to this caller removes
the named `token` local without changing the texture loader or shared headers.

Native `0x458349` loads the path before `0x45835A` takes the same, now-dead
argument slot for the result. Ordinary C++ value-return lowering reproduces
that lifetime automatically. The fresh frame changes from 12 to 8 bytes and
all 125 bytes match, including the three direct-call relocations, the title
manager address and the virtual-reset tail ending in `ret 16`. No explicit
argument-slot aliasing or register constraint is used.

Reproduction: `scripts/repo-python scripts/build.py --unit
gpt-web-system-effect-manager-spawn --compare --json`. The relocated source SHA-256
now equals the target hash above. Both existing observer tests pass, including the
changed-mode-store negative case.

Factory forced-recompile job `job:d97cbbccf07c4a739d36185e86996fd1` returned
`pass` / `accepted`; receipt
`receipt:85f48a5df3fc4de463364c9241075cfb4c004a901cc059ad0fe71a4012f4110d`.
The local source/unit checkpoint preserves all unrelated input-migration work.
