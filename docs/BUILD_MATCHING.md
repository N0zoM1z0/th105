# Build and byte-matching plan

## Current evidence

The PE uses Microsoft linker 8.0. Its Rich header is dominated by tool build
50727, placing the build in the Visual C++ 2005 family. The executable imports
Direct3D 9 and `d3dx9_33`, links a static C/C++ runtime, uses a fixed image base,
and retains an RSDS path for `th105.pdb`.

The decoded Rich header contains 279 `Utc1400_CPP`, 165 `Utc1400_C`, and 42
`Utc1400_LTCG_CPP` records. The LTCG records strongly indicate `/GL` inputs and
an `/LTCG` link for at least part of the C++ program. Consequently, executable-
level comparison is authoritative; object boundaries and object-level codegen
can be altered or erased by the linker.

Still unknown:

- exact VC8 service pack/hotfix;
- compiler options, runtime-library mode, LTCG use, and per-file overrides;
- original translation-unit names and link order;
- resource compiler and library versions beyond evidence in the PE;
- which routines are compiler/runtime/third-party library code.

These unknowns are why the initial repository does not claim a working matching
build.

## Matching stages

1. **Toolchain probe** — compile controlled VC8 functions and compare codegen,
   exception data, RTTI, string pooling, and section layout.
2. **Object partition** — group functions/vtables/statics using RTTI ownership,
   initializer clusters, strings, alignment, and link-order experiments.
3. **ABI skeleton** — recover shared types, calling conventions, class layouts,
   vtables, and global initialization.
4. **Function matching** — use small non-LTCG object probes for fast iteration,
   then confirm LTCG-sensitive functions in a linked executable.
5. **Executable comparison** — use reccmp as the acceptance report and retain
   explicit mappings for functions/globals/floats/strings.

## reccmp

After placing the exact original executable in `resources/`:

```bash
reccmp-project detect --search-path resources/
```

After a reconstructed executable exists:

```bash
cd build
reccmp-project detect --what recompiled
reccmp-reccmp --target th105 --html report.html
```

`reccmp-project.yml` refuses a target hash mismatch. The reccmp CSVs are
generated/maintained from the same supported-name inventory as the function
ledger.

## objdiff

`objdiff.json` is intentionally empty until an object boundary is supported by
evidence. Adding a unit requires both an extracted original object/slice and a
reproducible rebuilt object. Do not invent translation-unit boundaries merely
to populate the UI.

## First code-generation results

The pinned VC8 SP1 compiler (`14.00.50727.762`) compiles
`src/battle/GameMode.cpp` to the exact target bytes for both small accessors:

```text
0x00439860 get_game_mode:   A1 EC 62 6E 00 C3
0x00439870 get_match_setup: B8 E8 6F 6E 00 C3
```

Each standalone function has no code relocation and is recorded as `matching`.
They prove the probe path and source expressions, but six-byte accessors cannot
distinguish VC8 RTM from SP1 or prove the final `/GL`/`/LTCG` configuration.
