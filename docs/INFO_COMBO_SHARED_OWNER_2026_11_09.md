# Shared combo design and number owners

The combo loader and renderer now use one 0x6C layout with the actual
CDesignBase prefix. Short-record rendering uses that same design object's
color method. The old independent derived loader and eight-slot renderer
facade are gone. Item placement now names CDesignObjectBase's base_x/base_y
fields explicitly, keeping them distinct from the coordinates loaded from the
design file.

The loader also calls the actual `CDesignBase::bind_object_alt` provider at
`420B90`. Previously its manifest rebound `find_object`, whose own implementation
is the separate 121-byte function at `40CC50`, to that 118-byte entry. Their
lookup semantics agree, but the new connection supplies the correct existing
provider without that alias.

## Original layout and dispatch evidence

Raw Japanese 1.06a PE SHA-256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- InfoManager construction loads `this+100` at `46F629` and calls the real
  CDesignBase constructor `4217F0` at `46F634`. That constructor installs
  table `6C08AC`, identified by RTTI as CDesignBase.
- The table's color, load and offset-render slots are `40BFE0`, `40B000`,
  and `40BE20`. Combo rendering's final virtual call at `46A7F4` uses +1C,
  the offset-render operation, rather than an independent move interface.
- The six item pointers occupy +44..58; counters occupy +5C/+60/+64/+68.
  Runtime item positions are at object +4/+8, with enabled at +14. The shared
  CDesignObjectBase declaration distinguishes those base offsets from the
  loaded coordinates at +0C/+10.
- The loader binds four CNumber values through object +18. The independent
  design-loader factory at `40B7ED` allocates E4 bytes, publishes CDesignNumber
  table `6D6AC0` at `40B809`, CNumber at whole +18, and CTile at whole +40.
  The loader now uses this existing CDesignNumber declaration.

The shared structure remains a pointer-only reconstruction view. The evidence
fixes its prefix and offsets, not the original aggregate's class name or whether
its source used inheritance. Outer InfoManager construction and its separate
resource interfaces are unchanged.

## Complete affected comparisons

Three affected units were rebuilt. Combo render remains 413/413, short-record
render 156/156, and short-record update 572/572. All 427 bytes of the nonexact
loader candidate are unchanged; native size remains 413 and first mismatch +2.
No register-allocation trial was introduced. The actual bind_object_alt provider
was rebuilt separately and remains 118/118.

All 191 previously emitted non-debug sections preserve their bytes and
relocation roles, except that the ten loader call relocations now name the
actual binding provider. One new four-byte deque block-size constant is
unreferenced. The existing generated-code proof independently rebuilds and
revalidates both InfoShortRecord deque helpers over the complete candidate
inventory. Source pins and acceptance rules are unchanged.

Tracking and lightweight CI pass; no new authored exact credit is added.
