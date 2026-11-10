# Application static initialization

The application singleton at `702820` now has a source-owned initialization
candidate. `ApplicationState.hpp` describes its B8-byte layout using the actual
startup options, four shared thread handles, checked scene list and critical
section. `ApplicationInitialization.cpp` supplies the constructor, and
`ApplicationLifecycle.cpp` defines the real static object with those member
implementations visible. Existing application views and selected units are
unchanged.

## Original lifetime and source result

The pinned Japanese 1.06a executable calls constructor `407CA0` from the
17-byte initializer at `6BE780`. The real CRT table slot is `6C036C`; the
initializer registers `6BEDF0` with `_atexit`. That 73-byte callback directly
performs automatic member destruction, rather than jumping to a separate
application destructor. It releases the critical section, destroys the retired
scene list and waits for the four threads in reverse member order. Application
shutdown `407F80`, called by WinMain, is a separate operation.

Construction first initializes the 40-byte startup options at +08, then the
four handle fields at +50/+58/+64/+6C. It allocates the list sentinel at +88,
sets the count at +8C to zero, publishes the critical-section vptr at +94 and
initializes its Win32 member at +98. Only then does the constructor body clear
the scene pointers at +7C/+80 and set running at +4C. The source preserves that
exception ordering. It does not add writes to thread IDs, events, counters or
other fields that are zero because the object has static storage.

A public constructor export emits a generic 189-byte method. With the genuine
static owner and no exported constructor, ordinary VC8 SP1 `/O2 /GL /GS` and
LTCG reproduce the native constant-receiver 255-byte body. No private calling
convention annotation or synthetic caller is needed.

A fresh complete-region comparison through the existing canonicalizer passes:

- Application constructor `407CA0`: 255 bytes.
- Generated exit callback `6BEDF0`: all 73 bytes, including its final thread-wait
  tail call.
- All four constructor unwind funclets, handler, FuncInfo and unwind map:
  139 bytes, with the native four-state cleanup graph.
- Real initializer: 17 bytes and its unique CRT table slot.
- Actual supporting thread destructor/wait: 5/73 bytes; critical-section
  deleting wrapper: 41; list sentinel allocator/cleanup: 26/71.

The source's native COFF object owns one B8-byte zero BSS allocation. Both PE
loader extents are checked as zero storage, not read through nonexistent BSS
file bytes. The adjacent bootstrap-mode byte at `7028D8` is separately written
by `407DCC`. Every source HIGHLOW field in the compared regions is accounted
for; the original executable has no relocation directory.

## Selection limit

This remains an unselected candidate. The configured paired-global proof
requires a distinct destructor with cleanup EH and a five-byte atexit tail
wrapper. Here the compiler emits the whole no-EH member cleanup directly in
the callback. The ordinary runtime-only linked comparison correctly rejects
the unqualified source initializer. No validator, manifest, source pin or
exact ledger was changed. Supporting the observed generated callback safely
requires a separately bounded proof change, not a fictitious destructor or EH
record.

Evidence: `.analysis/frontier-application-initialization-20261109/` and
`build/frontier-application-initialization-20261109/`. The final source build is
`ApplicationPublished.dll`; `verification.json` records the full comparisons
and `ApplicationLayout.obj` supplies the compiler-owned BSS extent. No existing
configured unit includes these new files, so there are no old consumer rebuilds.

## Follow-up: the scene-base member is a fade pointer

This layout also resolves a misleading existing declaration. Bootstrap
`407DDD` stores its secondary callback pointer into application +78, address
`702898`. WinMain allocates the twelve-byte `CFade`, publishes its RTTI-owned
table `6C74C4` at `6659EF`, and places that pointer in the startup options.
Opening construction copies `702898` to its base +4 at `41F99F/41F9A4`.
Opening update `41F873/41F876` then loads that pointer and writes `00FFFFFF`
to its color member at +4. Title and SelectScenario constructors copy the same
pointer.

`SceneBase.hpp` currently calls this value `g_active_scene_id` / `scene_id` and
stores it as an integer; Opening casts it back to a pointer. It should become
a typed `CFade *` after checking the actual scene-base users. This checkpoint
does not expand into that shared-header migration.

Follow-up: the scene-base pointer type and Opening color access are now
corrected, with all affected output unchanged. See
`docs/SCENE_BASE_FADE_POINTER_2026_11_09.md`, which also records why the currently
supported strict global callback routes do not cover this Application candidate.

Follow-up, 2026-11-10: the observed inline cleanup now has a complete strict
global-lifecycle proof, and the Application constructor is selected and locally
canonical exact. See `docs/APPLICATION_INLINE_CLEANUP_2026_11_10.md`.
