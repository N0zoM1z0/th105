# Timeline entry handle ownership, JP1.06a

RenderTimelineEntry destruction41EC10 is canonical exact223/223, SHA256:
55b92aa9496b748719f4c9fb417aa3ef2e8aa1f927b514cb4edd4378c15c95f7.

The first deque in the7C-byte record was incorrectly declared as another
CSpriteEx deque. The actual first deque owns unsigned texture tokens. The
second deque014 owns CSpriteEx values. This is not inferred from the identical
empty-deque constructor stores: native loader4540F0 passes the texture loader's
four-byte result to unsigned-deque push_back417240, then independently appends
a real sprite to the second deque. Native destruction confirms four token
elements per block, DWORD loads, resource release404D70, and first-deque tidy
413A90 after second-deque tidy420AF0.

RenderTimeline.hpp now declares texture_handles_00 as std::deque<unsigned> and
an explicit destructor. The body releases front() before pop_front() until the
count is zero. Normal member destruction then tears down sprites014 followed
by the empty handle deque000. The native release-before-pop order is preserved,
including behavior if a resource-release operation does not return normally.
No raw deque internals, manual vptr stores or synthetic destructor calls appear
in the source.

The first full223-byte build with !empty() differed in its initial condition
and loop alignment. Using the observed actual count comparison size()!=0
naturally reproduces all223 bytes. The equivalent size()>0 control retains a
JBE difference and is not selected. No padding or instruction substitution is
used to close the guard.

## Incremental validation

scripts/repo-python scripts/build.py --unit exact-first-render-timeline-entry-destructor --compare --json

Receipt directory:build/frontier-timeline-entry-lifetime-20261029/.
All three existing shared-header consumers recompile and remain exact:
RenderTimelineEntry constructor450E30, entry rendering450EA0 and list rendering
450FC0. The physical7C size and all transform/color offsets stay unchanged.
The independently recovered opening/ending timeline loader remains a separate
unselected body; no exactness is inferred for it or compiler-generated deque
providers. One new complete EH-handler binding is local to the new destructor.
Default CI validates the final selection/ledgers, without a cold-corpus rebuild.
