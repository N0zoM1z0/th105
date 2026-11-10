# Network rejection: full EH prevents a false exact promotion

The real four-TU receive and seven-TU initialization CIL graphs both reproduce
all122 main-body bytes of415B90 after the two known handler/cookie address
replays. This is still NOT a complete exact acceptance. The former main-only
diagnostic did not check the cleanup ABI.

## Newly closed metadata question

The full source handler27 strictly replays to6BD688 through its actual named
security-cookie check, C++ frame handler and FuncInfo reference. Complete
FuncInfo36 at6E3C5C and one-state unwind map8 at6E3C54 agree after their typed
pointer fields are replayed; all source HIGHLOW fields are accounted for.
Their SHA256 values are:
- FuncInfo:1b16dd044ca1c20e94f302ecc12d859fb62fa2dcaa1b408c287da5eb179b568b
- unwind:8ee39b90c026f2cff8df2a14ae48cc4f2254eb4920d07e070d1276993c8be6c3

But native cleanup6BD680/8 derives ECX from EBP-10 and tail-jumps to401870.
Source cleanup derives EAX instead. Even after diagnostic tail-target replay,
one nonrelocation byte at action+1 differs. The real source guard destructor
is13 bytes and consumes EAX; native401870/13 consumes ECX. Their instruction
register fields differ at+1/+3/+5. Both call the real LeaveCriticalSection IAT,
but that semantic similarity does not make their ABI or bytes identical.
No caller or EH credit is awarded from the matching main body and metadata.

## One genuine shared-type control

Peer removal, acceptance and receive currently use three independent nominal
lock-guard views with the same pointer field and Enter/Leave behavior. Native
unwind paths call the same401870 entry. A private all-CIL control replaces
these three views with one shared RAII definition, preserving all actual
callers, operations and storage. It introduces no extra export, COFF barrier,
noinline, fake register declaration or padding.

That source-backed type-sharing hypothesis does not close the difference:
root122 still matches only as a main-body diagnostic; the shared destructor
still uses EAX, and the same action+1 / destructor+1,+3,+5 differences remain.
The hypothesis is not retained in gameplay source or promoted as original
nominal-type recovery. A guessed COFF destructor barrier or forced ECX would
not be evidence and was not introduced.

The caller's switch-bearing receive graph also remains outside the ordinary
private-caller closed-CFG contract. Fixing only its selection would therefore
not solve the independently demonstrated full-EH mismatch.

Source, match units, origins and all progress totals stay unchanged. This path is
closed under these current source graphs until independent source/build-boundary
evidence changes the cleanup ABI.
