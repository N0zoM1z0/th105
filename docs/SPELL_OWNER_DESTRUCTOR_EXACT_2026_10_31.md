# Spell owner destruction: complete canonical 101 bytes

SpellDataOwner destruction at4619C0 is canonical exact101/101, SHA-256
e5b0d25b6d0957fa6b5dce35156673fe67f0d6be156367db00fcb2200d9e0f45.
All28 native instructions form a straight-line body ending in RET0. Its
ordinary source was already emitted as CharacterDtorSpell68 in the complete
Character destructor translation unit. No source surgery, ABI changes, new
profile or artificial context is required.

The actual SpellDataOwner68 layout is independently established: resource
core00..1F, loaded short deque20, selection short deque34 and value array48.
Its explicit destructor body calls clear_resources before automatic member
cleanup. Native4321A0 is a five-byte jump to the already exact171-byte spell
cleanup433A80. This application resource-release policy distinguishes the
owner destructor from generic compiler-generated member cleanup.

The complete function calls that cleanup, destroys selection34, destroys
loaded20, then destroys the core through42E900. The source's actual checked
VC8 deque and resource-group members reproduce the same reverse lifetime.
Fresh canonical comparison binds every call and the attested EH handler.

## Full generated exception state

The generated code section at6BAF90 is57 bytes: three cleanup funclets at
6BAF90/6BAF98/6BAFA3 (8/11/11 bytes) followed by the27-byte handler6BAFAE.
The three-state unwind map at6E0C10 and FuncInfo6E0C28 form a complete60-byte
data section. All117 bytes, including every call, pointer, state and flag,
compare exactly. The deque unwind action uses448DE0, distinct from the normal
inlined destructor call to tidy420A80. No cleanup metadata is masked or counted
as additional authored bytes.

The full auxiliary audit is retained in the corresponding .analysis scope. The
source and compiler profiles are unchanged.

The parent Character destructor462CE0 still emits905 bytes and retains its
single commutative SIB mismatch at462DF8 (0F versus39). It remains nonexact;
its905 bytes are not added. The shared source unit therefore has a mixed
comparison result, with only4619C0 promoted. The directly called spell cleanup
171 and resource-core destructor126/constructor118 freshly replay exactly.

Reproduction:

Only101 authored bytes are added: exact1578/448979, source1776, authored1796,
mapped1803, excluded1721, review510, units760. The wider existing-object scan
that found this candidate remains diagnostic only; other hits require their
own complete source/origin and canonical checks.
