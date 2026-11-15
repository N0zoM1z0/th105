# Title/result match-mode setup, JP1.06a

43B8F0 now has complete 286-byte selected source. It remains nonexact at+3;
no exact bytes are added. Native SHA256:
beaf3460ffa40456b209c220f737c4b74565b3ec45cb5b2a916540123ce18b59.
Source SHA256:
84abc83c3207c049e97ce72763c30907fc4407ca052d2151fd2873fc4b9e5317.

## Complete behavior

The first argument is game mode and the second is setup option, as independently
used by TitleUpdateRuntime and MenuResultUpdate. The function initializes the
existing ScenarioMatchRuntimeState startup/deck fields, stores both arguments,
invalidates both selected-input slots, and rebinds slot 0 without requiring a
distinct device. The already-selected rebind_selected_input_43b640 source is
visible in this TU and naturally inlines. It retains the duplicate-source
handling, signed negative fallback and checked 68-byte input-record access.

Modes 4/5 bind the current network session to input 0 and the profile-record
base, publish the local input pointer at session+6B4, then replace selected
inputs with session+1F0/+1F8. Mode 6 performs the same bind/local publication
without replacing the selected pointers. Every path launches async scene 2.
The network view is pointer-only; no full allocation extent is asserted.

Raw PE reaches both RET 0 exits across all 286 bytes, with no external tail or
indirect exit. All four callees are independently exact: active-source40A4E0,
checked input lookup 43B300, network binding 43B410 and scene launch 43B840.
The existing authored-origin rule pins the full target hash and exact Title
caller edges 4259D6/425B29. It remains active because this body is not exact.

## Residual and validation

Ordinary global views give the same 286-byte complete body but publish the
initial mode/option values in a different schedule. Existing getter TUs use
volatile views for these globals; reproducing both qualifiers here grows the
body to 302 and breaks the shared selection suffix, so that control was not
selected. Original declarations/visibility are not claimed. Moving the mode
publication before startup initialization also remains nonexact. No source
barrier, register annotation or artificial volatile local is introduced.

scripts/repo-python scripts/build.py --unit exact-first-match-mode-preparation --compare --json

Source:src/ui/MatchModePreparation.cpp. The fresh changed-TU object also reproduces
the existing standalone selected input rebind and scenario preparation bodies
exactly, recorded in rebind-regression.json and scenario-regression.json. No shared
source, header, relocation key or accepted caller is changed. Mapping/source
presence is kept separate from exact acceptance.

## November 9 storage-type control

Changing only the mode storage declaration from `GameMode` to an ordinary 32-bit
`int`, with the corresponding typed relocation, produces the identical 286-byte
canonical candidate and SHA above. It does not resolve the native option-before-mode
publication schedule. This private control is not selected; no input source or
shared type changed.
