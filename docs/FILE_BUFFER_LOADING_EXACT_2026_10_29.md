# Plain and encoded file-buffer loading

The real CIL file/reader context now reproduces both complete authored loaders:

-419860 plain:234/234,
 58b417bec34e23b76afaceb5a5f583afd938256a3530a82ab256dda757d179da.
-419950 encoded:267/267,
 4586170018493a7ba134017243b15bd26f9eaa6265e014fafc6e9f289962b5f7.

Both also pass full cleanup EH comparison. This adds501 authored bytes. The
previous140-byte CSV wrapper and151-byte iterator reset stay exact. The already
accepted15-byte FileReaderOwner destructor moves into the same linked unit
without adding credit. CSV loading40F150 and parsing40F200 remain unaccepted.

## Visibility and argument lifetime

The preceding real CSV graph already recovered the private wrapper and encoded
receiver without any private calling-convention declaration. Its file loaders
still had the wrong frame: plain232/native234 and encoded267/native267.

FileReaderOwner::~FileReaderOwner has an independently established normal ECX
entry at40CF20, used by the target's exceptional cleanup. Retaining that actual
public destructor in the genuine CIL graph, instead of letting it become a
private EAX-only body, restores the native eight-byte local frame and closes
the entire cleanup EH. The destructor itself remains15/15. No extra source
local or alignment is introduced. The resulting normal loaders were234/267
bytes with only10/12 unequal virtual-read scheduling bytes.

Raw41990F..419920 and4199FE..419A10 capture the actual size/destination before
virtual reader dispatch. The source now passes these values through one
ordinary inline read_file_buffer forwarding helper, which calls the real
CFileReader::read. VC8 inlines it naturally and reproduces those lifetimes and
all remaining bytes. The original helper name/spelling is unknown; this is a
source-level lifetime hypothesis, not an assertion of a new native callable.
The helper gets no separate credit. No forced inlining, fake use, volatile
storage, register annotation, manually cached method pointer or ABI facade is
introduced.

The loader policy is unchanged: open failure returns false; size is published;
nonzero size frees old data, allocates size+1, appends NUL and invokes the actual
reader. Zero size does not release the old allocation. Encoded data uses the
previously recovered cached byte cursor and native key/delta schedule. The
owning reader is destroyed on all normal/exceptional paths represented by C++.

## Complete cleanup evidence

Each loader installs target handler6BDCC8 selecting FuncInfo6E4338. The existing
strict cleanup comparator verifies all four whole regions:

-27-byte handler, SHA5241ad55a1e957b5608414bf085713b7f2fb9f077f3e5b3e1d7e1837809bb9f9.
-8-byte funclet6BDCC0 calling real public destructor40CF20,
 SHAb40597562c1bba28b34e9ee3add5e4e5b054242d8b90bff6da16ec9338f58e26.
-36-byte FuncInfo, SHA f3f943b3a158a1df05232dbf389e4dd2d919c4eef33fd4821d39519c9027170e.
-8-byte unwind map, SHA3428fb229f3f8d79ed0a61b5ddc49fa56744ef4bab96e07dd24127b2f49c59d6.

Every handler/funclet branch and all HIGHLOW fields are qualified. The full EH
algorithm is unchanged; it now admits an unrenamed ordinary public member, or
a private member below a freshly replayed exact caller, with the same static
CRT-cookie requirements. Unsupported catches/extra states, aliases and missing
cleanup data still fail. This differs from the CSV caller's explicitly
source-only EH-role witness: neither its176-byte body nor its EH is accepted.

## Private encoded entry and accepted caller chain

419950 is not exported to coerce its ABI. Its explicit through_exact_caller
contract names the real accepted408E40 wrapper and native call408E93. Every
encoded comparison first performs a fresh full canonical replay of that
wrapper in the same image. The wrapper retains its independently verified
CSV-load caller edge40F193 and typed source-only caller EH roles.

The extension is bounded to one already directly witnessed private parent.
Implicit/recursive paths, nonexact parents, missing or stale raw/canonical
hashes, aliasing and undeclared calls are rejected. The actual parent source
body, every relocation and both complete call graphs are checked. No byte or
address field in either accepted body is ignored. Existing exported-caller,
two-edge constructor and static-path behavior remains unchanged.

## Reproduction and incremental checks

    scripts/repo-python scripts/build.py --unit exact-first-csv-file-loading --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-csv-file-loading --address 0x00408E40 --address 0x0040F730 --address 0x0040CF20 --address 0x00419860 --address 0x00419950 --json

Receipts are file-loaders-public-build.json/file-loaders-public-compare.json in
build/frontier-csv-load-20261029. The old standalone plain/encoded comparison
units are replaced, not counted twice. Other FileReader accessors stay exact;
its open body stays nonexact. Legacy script95/147 and BGM constructor89 replay
unchanged. Existing full-EH tests pass, with two targeted exact-parent tests.
There is no whole-corpus cold rebuild or new runtime test matrix.
