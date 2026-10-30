# Connect-menu address and history lists

Two complete current-target source roots are now independently bounded and
tracked. Neither is exact; no new matching bytes are claimed.

- Address file443130: target881 bytes, source870, first mismatch+111 at the
  concrete reader's stack position. Unit exact-first-connect-address-list.
- History4434B0: target714 bytes, source715, first mismatch+51 at receiver
  allocation. Unit exact-first-connect-history-list.

The earlier Factory scan passed current metadata/entry and all five mapped
samples. Fresh decompilation was checked against pinned raw PE disassembly.
Actual444830 state-machine call sites444959 and44497D select file and history
loading. The file root has266 instructions,265 reachable; its only unreachable
instruction is the native3-byte LEA ECX,[ECX] alignment at44337D. All881 bytes
remain in comparison. History has217 instructions, all reachable, with a final
RET. No switch payload or neighboring function is counted.

## Recovered policy

Both roots release texture+2FC, clear its handle and checked string deque+3A4,
then create a256x256 text texture with the observed shared font at6FD0B8, bind
its first256x16 strip to tile+300 and reset vertical cursor+3E4 to the list count
with page size1. Typed owner views agree with the existing complete connect-menu
constructor and its0xA4 tile/deque/cursor layout; they are not instantiated.

The file loader uses the real CFileReader source, opening address.txt with
native access1. GetFileSize is deliberately called four times after open;
size is not cached across calls. It allocates size+1, writes a trailing zero,
reads without a new success check, and tokenizes using the three-byte CRLF/NUL
literal. It keeps at most16 nonempty strtok_s tokens, appending each line and
<br> to texture text and storing the line in the checked deque. The native
no-token path leaks the allocated buffer; no invented cleanup is added there.
Normal success deletes the byte array before creating the texture. Reader and
strings retain normal/exception cleanup ownership.

The history loader follows config pointer+C48 to checked deque<string>+48. An
empty history fails after releasing the previous list. Otherwise it rereads the
config/history for each iteration, copies each entry to the displayed deque,
and appends entry+<br>. It does not impose the file loader's16-line cap.
The real cursor-binding definition is visible in this TU because the native
history root inlines that binding; the file root calls it out of line.

## Remaining differences and validation

The file source retains reader/buffer stack placement, temporary-constructor
return forwarding and loop-guard layout differences. A named-string scoped
control still emits870 bytes and changes local-string placement; it is not
selected. Typed concrete owner fields preserve the original870 result.
History retains EBX/EBP allocation differences; the missing byte-register form
accounts for an immediate-zero store and its one-byte size excess. Typed owner
fields are byte-neutral. No register retention, fake uses, alignment storage,
assembly or semantic padding was introduced. New evidence about the actual
caller/TU can reopen these lanes; repeating these controls cannot.

The CRLF tail relocation now has a strict one-byte NUL slice at symbol+2. It
checks initialized source bytes and the target byte actually read by443223,
without reading beyond the original three-byte source literal. This is a new
function-local mapping; no prior mappings or comparator rules were weakened.

Formal receipts: build/frontier-connect-lists-20261030/address-formal.json and
history-formal.json. Boundary/semantic evidence is retained in the same folder.
Both sources are new isolated match-unit inputs; no previous accepted unit is
affected. The two authored-origin rules attest complete target body hashes and
actual caller edges. Their classification adds no exactness credit. Existing
exact receipts and unrelated origin evidence are preserved.
