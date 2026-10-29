# Audio scheduler listener creation, 00419350

The unchanged source in `src/audio/AudioSchedulerListeners.cpp`, compiled as a
real VC8 SP1 one-CIL linked unit with its actual checked STL implementations,
reproduces the complete create-listener function: **169/169 canonical exact**.
The optimizer naturally specializes list::_Incsize's constant-one argument.
There is no invented private ABI, forced register, replacement helper or source
change. Existing pinned compiler/runtime inputs and explicit already-attested
scheduler-global/Win32-IAT bindings are used. The generated DLL is never run.

The Japanese1.06a target SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete [419350,4193F9) body has SHA256
`6672968faeba6f812cadbeee3ec008e316c178f6c6f97dd1b0997ff4b68b25ea`.
Raw CFG traversal reaches all169 bytes and RET0; seven following INT3 bytes are
outside the callable. The game application worker4081E0 directly calls it at
40821C and consumes the returned event. Existing ownership evidence separately
closes the wait/remove calls and scheduler state703864.

The selected `gpt-web-audio-scheduler-listeners` unit now uses the existing
`vc8-sp1-ltcg-o2` profile. All three existing source bodies are replayed together.
Remove419400 is178/native193, first difference+6; wait4194D0 is129/native184,
first difference+23. Their checked-iterator lifetime/helper differences remain
unresolved. Only create419350 gains exact credit. No library helper is claimed
as authored and no matching callee result is inferred from a relocated call.

Receipts: `build/frontier-419350-20261029/formal-build.json` and `boundary.json`.
Private first linked experiment and recording scripts are retained under
`.analysis/frontier-419350-20261029/`. No shared source/header or profile changed;
other units' accepted receipts remain unchanged. Validation is focused, not a
cold corpus rebuild.


## Later native end-iterator lifetime correction

Removal419400 loads list head at419419, stores that end at419425 and compares
against the retained slot at419441 across backedge41946E. It does not reload
end() on every iteration. The source now explicitly initializes both begin
and cached end in the for initializer. This is target-backed iterator lifetime,
not a padding/register experiment. Pure CIL becomes198/native193, first+6;
creation419350 remains169 exact and wait4194D0 remains129/184 first+23.
Initializing cached end before begin gives the same result, unselected.

The target193-byte remove body contains checked iterator dereference/increment
inside the loop, unlike the unchecked std::find search used by D3D registration.
Do not substitute find here: the earlier find diagnostic was235/193. Source
and target erase-helper call ABIs remain different; whole-image raw call scan
finds414DE0 callers only414D50 and419400. The recovered nominal pointer list
types differ, so that shared code alone does not prove a common source type
or authorize a fabricated ABI. No exact credit changes. Focused receipts:
build/frontier-audio-listener-cached-end-20261029/formal-build.json and ci.log.
