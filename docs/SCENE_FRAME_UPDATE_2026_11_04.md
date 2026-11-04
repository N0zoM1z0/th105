# Scene frame update hypothesis

The exact RTTI-owned `CSceneManager::update` at `0x0041E140` tail-calls
`0x0043B4A0`. The latter's 209-byte entry region updates the keyboard and
player inputs, visits the 0x68-byte input records, merges menu input and
integrates the scene fade. Its exits jump to the separately located shared UI
continuation at `0x004400D0`, ending at `0x00440170`. The source hypothesis in
`src/engine/SceneFrameUpdate.cpp` includes both regions in one ordinary C++
function, including the selection fade and menu-stack behavior. It is not a
claim that the shipped source had these exact declarations.

Pinned VC8 emits a 379-byte section. Comparison against the 209-byte entry
ledger reaches +104 before differing; this is only an entry-region comparison,
not a comparison of the full noncontiguous target function. The target tail
has not been replayed as a complete owned function. The complete source
hypothesis is selected as source-present; the separately located target
continuation has SHA-256
`04df783d77c940ae49bf54b8b77670edac152e0c77bf56f4bd4f43de53dd87d0`.
The function earns no exact-byte credit. No live game or
input execution was performed.
