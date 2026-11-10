# Float-bound number value accessors

Two complete custom game TNumberValue<float*> virtual methods now compare
canonically: integer conversion46A640/10 and floating read46A650/6. The existing
CNumberRuntime.hpp source is unchanged; actual story-info binding in
BattleInfoGaugeRuntime.cpp already emits both methods.

Their short bodies alone would not establish ownership. Current raw RTTI
independently identifies vtable6C35C8, COL6D9744, type descriptor6E7B38
(`.?AV?$TNumberValue@PAM@@`), and a two-entry hierarchy with INumberValue at
6E6C1C. Both hierarchy offsets are zero and vtable slots0/4 are46A640/46A650.
This is the game's custom numeric adapter, not a standard-library function or
an anonymous compiler thunk. The already accepted signed-char specialization
uses the same ownership distinction.

The integer method dereferences the bound float at receiver+4 and tail-enters
the canonical __ftol2_sse helper68A1A0. The floating method returns the loaded
float in ST0. Ordinary static_cast expressions reproduce all bytes; no typed
memory guess, assembly or register constraint is introduced.

The exact story binder471A80/351 binds the same actual progress_10 float to two
number objects. Fresh full-unit replay preserves the existing gauge virtuals
20/27, general binding648 and story binding351 while adding both complete
getters. No source, header, compiler flag, data alias or verification tool changes.

The unit remains gpt-web-battle-info-gauge-runtime. Only16 authored bytes/two
functions are added: exact1580/448995, source1778/authored1798/mapped1805,
excluded1783/review446/units762.
