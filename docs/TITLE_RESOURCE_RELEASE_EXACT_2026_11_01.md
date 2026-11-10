# Genuine C++ Title resource release, 00404D70

TitleResourceManager::release_title_resource_handle is now canonical115/115
from the existing ordinary C++ in src/ui/TextureHandleRuntime.cpp, compiled in
the real DesignBaseCleanupLinked.cpp context. Complete target SHA256:
84ceca2dfdde55fc4ff7e0e10ee9071de7ba4ac9aa34367baf0f090e1ba76e03.

This does not revive the withdrawn naked-assembly transcription. The October29
withdrawal remains correct. A fresh build, current source inspection and whole
canonical comparison independently establish this natural-source result.
Title texture load404C90 remains nonexact and is not restored.

## Source and observed policy

No C++ statement, source ABI, field layout, compiler flag, helper implementation
or export set changed in this recovery. Only stale source comments are updated.
The genuine source keeps the actual zero-handle guard, eight cached texture
slots, D3D SetTexture(stage,0), checked token lookup, COM Release, cell clearing
and token recycle. The existing0x64 pointer-only token-manager view has real
VC8 deque/vector/list members and the independently established critical-section
prefix. It neither constructs a fake manager nor writes a vptr by hand.

The selected real context already included both genuine texture providers and
CDesignBase cleanup, plus the original unsigned-list COFF instantiation. Release
and lookup were already ordinary public exports. Selection moves release from
the preserved-provider list into the actual comparison entries and leaves
lookup preserved. The real export set and normal thiscall ABI are unchanged.
The source and target therefore retain the same actual caller/provider context;
no new visibility barrier is introduced to force a match.

## Full canonical proof and support boundary

Both selected bodies freshly pass: cleanup40BB40/310 and release404D70/115.
The release comparison covers every byte, two named E8 relocations and the
existing cache-host global binding at the native operand. Actual source callees
are CHandleManager4::lookup_token ->417800 and TextureTokenManager::release
->405200. Their nominal source views/ordinary declarations are retained; no
private EAX or EDI convention is declared. The compiler generates its own
private helper lowering. Those callees gain no inherited exact credit.

The recorded cache-host operand is at function offset32. Its four-byte data
binding is independently pinned, not a code address or instruction mask.
Only relative call addresses are replayed under the actual named providers;
no instruction, field width, loop byte or suffix is discarded.

The standalone119/115 TitleResourceRelease.cpp candidate is not selected.
Its prior unit definition is retained privately as historical negative evidence.
The single-function cross-v106a-title-resource-release unit is removed, and
404D70 occurs only once in the public manifest, in gpt-web-design-base-cleanup.
There is no duplicate function credit or changed public header/caller contract.
The remaining load-only authored-origin rule preserves99-byte404C90 evidence.

## Reproduction and incremental accounting

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit gpt-web-design-base-cleanup --compare --json
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/ci.py

Freshness is essential: initial retained DLL/MAP matches alone were not accepted. No
DLL or game function is executed. No shared header or semantic source change
requires unrelated native rebuilds; cleanup310 is the actual affected owner and
freshly remains exact.

Authored exact becomes1585 functions/449721 bytes, adding only115 bytes.
Source1783, authored1803, mapped1810, excluded1798 and review426 stay. Unit count
is764 after removing the redundant former single-function probe. No push.
