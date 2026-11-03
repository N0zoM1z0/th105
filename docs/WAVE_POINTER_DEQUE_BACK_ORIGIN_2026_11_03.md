# Wave pointer deque back origin, 2026-11-03

The real wave-service linked CIL graph emits a `std::deque<BgmBufferRuntime *>::back` helper. Its complete 91-byte body matches native `0x4052B0` after replaying the three named calls to the independently pinned static invalid-parameter routine. The complete same-size candidate inventory has one hit; no bytes are masked. This is compiler-generated standard-library code, not an authored exact match.

The emitted wave-load root calls the actual handle-manager acquire body, which calls the helper. The native wave-load root calls `0x405090`, whose complete body calls `0x4052B0` at `0x405111`. Those source and native root and acquire functions are separately checked as real call graphs, but neither is asserted byte-exact. The source root remains 221 bytes against native 224. This evidence does not claim a unique original pointer type or source spelling for the native helper.

The validator rebuilds the genuine source closure with pinned VC8 headers, checks the full bodies, named runtime, source/native call edges, executable target and candidate uniqueness. Target identity and all accepted game-function totals are unchanged.
