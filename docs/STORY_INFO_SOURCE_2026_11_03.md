# Story battle-info update source, 2026-11-03

The existing complete source for `BattleInfoRecordF8::update_story_471930` is now recorded individually. The native 323-byte body has SHA-256 `7422f38ee095768cde15559079fe5d8fef4b61440a84782d4eb334753ec2285a`, 118 decoded instructions and two complete return paths. The exact InfoManager update calls it at `0x471CA7`; its unit and three other accepted roots were freshly rebuilt and passed.

The story-specific policy smooths displayed health and the secondary gauge, publishes countdown progress, and updates byte-wrapping alpha, colors and visibility. The implementation retains the observed callback reloads and does not add saturation or null guards. `STORY_INFO_UPDATE_2026_10_28.md` documents its field and control-flow evidence and bounded negative controls.

The public `exact-first-story-info-update` unit compiles to 321 bytes against native
323 and first differs at offset 67. It is source-present but nonexact. No
suffix-only or partial-byte credit is assigned.

## Shared health ownership, November 10

The shared record now declares its +0x08 cell as a union of the normal-mode
float `height_ratio_08` and Story-mode integer `story_health_08`. The exact
Story binding at `0x471A80` initializes the integer member and passes its
address to the integer gauge. The update at `0x471930` reads and writes that
same member directly, removing the former float/int lvalue reinterpretation.

Story binding also uses the actual `BattleInfoRecordF8` fields instead of a
second unrelated record view. Its UI pointers at +0x20/+0x24 are `secondary_20`
and `group_24[0]`; the number receivers at +0x70/+0x74 are `group_60[4]` and
`group_74[0]`. Normal-mode initialization and rendering retain the float union
member. The record remains 0xF8 bytes, with no new field or storage allocation.

All ten header consumers were rebuilt before and after this change. The 23
existing exact roots, including the complete 351-byte Story binding, pass.
All 322 non-debug COFF sections and 312 symbolic relocations are unchanged,
including cleanup code and metadata. Story update remains 321/323 nonexact;
the separate normal update at `0x46FF30` remains blocked at its existing local
checked-deque helper relocation. Neither receives new exact credit.

Pending input changes and source pins were not modified.

## Real Fighter ownership, November 10

The update now reads the existing `Fighter` object directly. The removed
`StoryInfoFighterView` duplicated five fields already owned by `Fighter`:
health +0x174, maximum health +0x176, secondary health +0x47C, remaining
frames +0x64C and initial duration +0x650. Compile-time offset checks cover
these accesses without changing the shared class. The raw target uses signed
word loads for the three health fields and signed dword arithmetic for the
countdown. `FighterSequenceFinalize.cpp` copies +0x650 to +0x64C, and
`FighterContinuity.cpp` decrements positive +0x64C values, linking the HUD's
countdown to the existing fighter lifecycle rather than a separate overlay.

Fresh VC8 compilation before and after this ownership change produces identical
COFF section contents and symbolic relocations (`objdump -sr`, excluding only
the file heading). The full update comparison still emits 321 bytes against
323 and first differs at +67. Native secondary smoothing keeps its target in
EBX and displayed value in EBP, computing the quotient in EDI before moving
EBP to EAX for subtraction. The current compiler instead uses EBP/EDI and an
EAX quotient. The ownership correction does not solve that allocation issue;
no padding or source-spelling sweep was used.

The directly calling `cross-v106a-info-manager-runtime-core` unit was rebuilt:
0x46E5A0, 0x471C90, 0x471D00 and 0x471D10 all remain locally exact. The focused CI
gate passes. No new exact ledger entry or Factory acceptance was added.
