# System-effect manager spawn

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
