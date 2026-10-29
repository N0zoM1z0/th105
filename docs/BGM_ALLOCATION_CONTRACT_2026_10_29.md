# BGM handle allocation contract, JP1.06a

The28-byte service4036C0 has a real semantic/type correction. Previous source
returned a supposed manager value result directly and emitted20 bytes. The
corrected source constructs a zero token, passes it by reference to the manager,
then returns that value. It emits26/28 and remains nonexact; no credit is added.
Source SHA256:d4544004c450a0d9e94d0cc57edcb2531773210ec0c696f793b1bd2fe1e89654.

## Direct observations

4036CA zeroes the caller's result cell before4036D0 calls4040D0. The wrapper
ignores that call's EAX and returns its own result-cell pointer at4036D6.
Inside complete401-byte4040D0, the stack argument receives separate slot and
generation WORD stores at404144/404150 and4041CA/4041D1. The normal return instead
loads a stream pointer from a checked manager slot and returns it in EAX at
40424B. Thus the manager call is pointer-returning with an explicit token output,
not itself the service's four-byte value return.

BgmHandleResult now has an ordinary value(0) constructor in a small shared header
used by allocation and playback. The wrapper uses a normal named result and
ordinary reference argument; there is no manual hidden-result storage access.
The target manager's private EDI receiver remains unresolved. The source keeps
a standard C++ member declaration, so its ECX call is intentionally nonexact.
The old claim that the full eight-byte deficit was solely scheduling/ABI is
superseded: six bytes represented missing output initialization.

## Focused verification

scripts/repo-python scripts/build.py --unit gpt-web-bgm-handle-allocation --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-bgm-playback --compare --json

The actual playback TU is rebuilt with the same result class. Transition43D030
208/208, load43CF00123/123, play43CF80168/168 and path-key43BB9036/36 all remain
exact. Their hidden result/caller ABI is unchanged. No compiler flag, private
register convention or stub provider was introduced.

Sources:src/audio/BgmHandleAllocation.cpp, BgmHandleResult.hpp and BgmPlayback.cpp.
Receipts:build/frontier-bgm-allocation-contract-20261029/formal-allocation.json
and formal-playback.json. Manager4040D0 is not promoted by this contract review.
