# MusicList population exact, JP1.06a

445830 is canonical exact867/867, SHA256
 d1da15029ec6113132dea13bf860638adf6c8eecc4e1909287cc9f4bd9a0ba68.
The complete body ends at445B92 RET0. MusicList vtable6C1E98 owns it through
slot+4 at6C1E9C. Independently exact CMenuMusic constructor4456D0 dispatches
that virtual slot at445782, after constructing the MusicList member at+4.
This is game-owned music/score/UI policy, not generated STL code.

## Recovered behavior

The source clears the inherited visible-row deque+4, paths+B4 and titles+C8.
An owned30-byte CsvReader zeroes its ten observed row/iterator words and loads
data/csv/system/music.csv. Each do-while iteration creates title then path
strings, reads the path and appends it to+B4, then reads the title. An exact
ScoreData path-hash lookup decides whether the visible row gets the real title
or the target38-byte grey locked-track label. The+C8 deque is cleared but not
appended in this body; the source does not invent that missing operation.
After the reader stops advancing, the real virtual finalize slot+8 is called,
then the reader is destroyed. Load failure is not given a new guard.

Real std::deque<std::string>, std::string and CsvReader lifetimes reproduce
seven EH states and the native94-byte local frame. The two per-row strings
are destroyed before advance_row; the locked-label temporary is branch-local.
The existing CsvReader non-throwing destructor calls clear_rows exactly once.

## Why the previous stop was incomplete

A const-char-pointer plus explicit length string constructor let VC8 inline
_Copy/memcpy_s and moved the reader/temporary stack slots. The native code
instead calls assign(const char*,unsigned) with constant38. A normal C-string
constructor given the actual target label literal naturally knows that length
and selects the observed assign boundary. This restores the full instruction
stream and stack placement with no padding, forced scopes, fake derived
strings, register annotations or new compiler flags.

The Shift-JIS label bytes are ordinary UI data, written as portable C++ hex
escapes for the eight full-width question marks. The generated literal is
strictly checked against existing target-owned _music_locked_label bytes at
6C1EE4; no machine instructions are copied into source. The path and EH
bindings likewise reuse existing target-attested keys.

## Focused verification

scripts/repo-python scripts/build.py --unit exact-first-music-list-populate --compare --json

Source:src/ui/MusicListPopulate.cpp.
Receipt:build/frontier-music-list-populate-20261029/formal.json.
Only this new source and its unit/ledger selection change. Shared headers,
MenuMusicRuntime.cpp, MusicList lifetime source, compiler flags and existing
relocation keys remain unchanged. No corpus rebuild or new runtime matrix is
needed. The867 new authored bytes are added only after the formal exact replay.
