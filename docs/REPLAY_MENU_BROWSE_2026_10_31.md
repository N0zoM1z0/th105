# Replay browser: complete source, nonexact return sharing

446860 now has a durable source/unit rather than only an external dispatcher
contract and historical private hypothesis. No exact bytes are added. The
complete native511-byte function has156 instructions, one RET at446A5E and no
escaping branches. Exact dispatcher446C90 tail-jumps to it at446D05.
Canonical native SHA-256:
28cfe1f2393ce046a13f4e40a105c281d3209f30023e037026ebc6ba43e9d74f.

## Recovered policy

One actual input-record pointer supplies horizontal/confirm/cancel state.
Horizontal+1/-1 pages forward/back; only the other branch calls vertical cursor
update. Each successful movement emits39. Confirm emits40. Entering a directory
pushes the old selection onto a genuine checked list<int>, changes directory and
refreshes the file list. A selected file is looked up twice, exactly as native;
the selected name is captured before the current directory. A real260-byte
wsprintfA path is passed to the replay service's exact loader42C5C0. Successful
loading changes scene mode to6.

Cancel emits41 and asks the file list to go to its parent. At the root, state4
is cleared and the original item pointers atF4/F8 are recolored white. This is
not the F0/F8 pair used by the separate delete-state method. Otherwise the real
checked list back/pop_back restores the previous selection before refresh.
The byte result is always1, matching the dispatcher's observed AL contract.
The offset-only receiver view is never instantiated; each accessed member uses
its actual existing CReplayList/MenuCursorState/std::list/UiDesignObject type.

## Bounded controls and stopping point

An initial function-wide set of named cursor/list/history references hoisted
receiver lifetimes, producing488 bytes and a10C-byte frame. Direct owner-member
accesses recover the native108-byte frame, the first127 exact bytes, and the
native input, file lookup, checked-node publication and filename sequence.

The full source is559 bytes, first differing at a branch displacement+127.
The substantive residual begins after the replay-loader call: VC8 duplicates
three GS return paths where native shares one. This reproduces the historical
559/511 stop; it is not claimed as a newly solved codegen issue. Bool/byte result
and scoped/function-wide real path-buffer controls are byte-neutral. No artificial
goto, fake lifetime, volatile/register state, padding or optimizer barrier was
introduced. Further equivalent-spelling grids are not justified.

The earlier dispatcher manifest note saying browse was already exact was stale;
it now explicitly distinguishes exact mode/delete from nonexact browse. The
unchanged132-byte dispatcher was freshly rebuilt and remains exact. No shared
header/provider was modified and no unrelated corpus replay was performed.

## Evidence and accounting

    scripts/repo-python scripts/build.py --unit exact-first-replay-menu-browse --compare --json
    scripts/repo-python scripts/build.py --unit gpt-web-replay-menu-update --compare --json

Formal receipts and bounded controls are retained under
build/frontier-replay-browse-20261031 and its .analysis counterpart.
The authored rule pins the full511-byte target hash, exact incoming tail and
outgoing exact replay-loader call. Only that new rule is materialized and
validated incrementally; previous rule witnesses remain unchanged.
Source1750, authored1770, excluded1421, review836, mapped1777 and units742.
Exact progress stays1553 /441679. Final CI gates a local checkpoint; no push.
