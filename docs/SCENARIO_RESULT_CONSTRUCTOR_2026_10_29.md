# Scenario result construction, JP1.06a

ScenarioResultResource constructor454C70 is now canonical exact298/298.
Native and fresh source SHA256:
90e375ff6e10b1db8c63ded6c2e7416e13314d6e09d831ecbf210a1c5c46829f.

## Real member initialization closes the old stop

The result resource owns CDesignBase at008, a texture token at058 and CTile
at05C. Its complete size is128, independently exercised by the existing exact
result destructor, render, reset, level and accumulator methods.
CTile's native vtable6C0718 has precisely four slots: destructor and the three
IColor methods. Its texture setter and rendering methods are nonvirtual.

The constructor-facing color view now owns the existing four-byte
DesignTextureHandle value at004. Its real value constructor initializes the
token before the base initialization completes. Consequently VC8 naturally
emits the native sequence: clear texture058, clear tile token060, publish EH
state0, then publish the derived tile vptr. This closes the old CTile/EH store
ordering mismatch without manual vptr stores, barriers, inert locals or
register forcing. The same value model already closed Character construction.
The view is local; shared IColor and destructor-facing declarations are intact.

## Complete construction

After constructing CDesignBase and the tile, the body loads
"data/infoeffect/result/result.dat" and binds primary objects6,3,4,5.
All four are enabled. It loads"data/infoeffect/result/rankFont.bmp", stores
the returned texture token, and configures the tile for64x64 with32x32 source
parameters. It binds secondary objects10,20,30 while setting their three
values to3, then clears only state000. Unobserved scalar fields are not zeroed.

CDesignBase is used directly for load/bind calls. The external texture loader
and secondary-binding/texture-setup views retain the independently observed
normal member-call ABI. The scalar loader output remains uninitialized before
the out-parameter call, as in native code.

Native handler6BA856 is27 bytes. FuncInfo6E03B8 has two unwind states at6E03A8:
state0 cleans CDesignBase008 through421890; state1 cleans tile05C through40AD50.
Fresh generated cleanup funclets match both complete11-byte native blocks at
6BA840 and6BA84B after ordinary call relocation, and the emitted tile normal
destructor matches the existing7-byte IColor destructor. These checks add no
separate authored credit. See build/frontier-scenario-result-constructor-20261029/cleanup.json.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-scenario-result-constructor --compare --json

Source:src/battle/ScenarioResultConstructor.cpp.
Receipt:build/frontier-scenario-result-constructor-20261029/formal.json.
The complete298-byte normal body is exact. Four new relocation keys bind the
native tile vtable, full handler and both complete strings. No existing
relocation, shared header or accepted consumer source changes. Default CI is
required; no full cold-corpus build is claimed.

The old297/298 and298/298 nonexact constructor notes are historical and are
superseded by this receipt. Result update454A50 remains nonexact: fresh403-byte
shared-header probes reproduce the old allocation/publication differences.
