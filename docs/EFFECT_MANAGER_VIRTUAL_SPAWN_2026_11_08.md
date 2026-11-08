# Effect manager virtual spawn

`CEffectManager<T>::spawn_effect` is virtual at primary vtable offset `+0x0C`.
The previous declaration omitted `virtual`, shifting every later slot in a
newly generated table. The declaration now matches the original dispatch
layout, and the InfoEffectObject implementation is the corresponding template
specialization rather than a separate manager facade.

The Japanese TH10.5 1.06a image has four matching nine-slot primary tables:
CSelectObject `0x6C08E0`, WeatherEffectObject `0x6C1418`, EffectObject
`0x6C1490`, and InfoEffectObject `0x6C37C0`. Their spawn slots point to
`0x422FB0`, `0x4377C0`, `0x437C00`, and `0x46F460`, respectively. The
fresh VC8 object emits the same slot roles in all four tables. Its primary and
secondary RTTI graphs, including the secondary-base adjustment, were checked
against the original image; the four secondary destructor thunks also replayed.

All four complete spawn bodies and the four manager constructor/destructor/
scalar-deleting-destructor families remain exact. Relevant manager virtuals,
tracked-object operations, event/effect users and Select's exact neighboring
functions were compared. The already nonexact event initializer, Select
constructor and update/prune helper retained their existing residuals. The 56
emitted manager EH symbols and their relocations were unchanged between builds
before and after restoring `virtual`; that is a before/after check, not an
independent comparison of every EH byte against the executable. No new exact
function is counted for this change.
