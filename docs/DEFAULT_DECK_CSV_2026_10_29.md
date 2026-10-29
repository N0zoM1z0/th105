# Default character deck CSV loader, JP1.06a

431E80 is canonical exact463/463, SHA256
 aaee5a80c6dfc0305066fd25e5118dcbe98df5337f067db310529fd0badf6697.
Source:src/config/DefaultDeckLoader.cpp.

## Complete source and ownership

The null destination returns null. Otherwise character_key_to_name43BF80
selects the directory, and a real chained std::string expression builds
"data/csv/" + character name + "/deck.csv". Both intermediate strings have
ordinary SSO/heap destruction. An owned CsvReader has the ten observed
zero-initialized row/iterator fields; unused flags remain untouched. It loads
the file, clears the destination deque, converts each next_int result to an
unsigned16-bit value and appends exactly twenty values. Reader/path lifetimes
end before returning the destination pointer. No new error handling is added.

The destination is a real std::deque<unsigned short>. Its generated push_back
42AA90 independently has eight elements per16-byte block and WORD loads/stores;
MOVZX AX in this caller proves the unsigned conversion. The compiler naturally
stores the converted temporary through a DWORD stack home. No artificial
four-byte argument object is necessary.

The full target body ends at RET8 with no remote tail or indirect exit. Existing
exact callers43AC60 at43ACE3,473520 at4737C0 and432050 at432189 establish
profile/battle ownership. Current declarations use a member boundary with an
unused receiver; no target instruction reads incoming ECX. This matching view
preserves the observed stack ABI but does not claim the original class name or
prove that its original source was a member rather than a compatible static
entry. No object of the view is allocated.

Native handler6B81C3 is46 bytes and references FuncInfo6DE3C4 and six-state
unwind map6DE3E8. Remote cleanup actions6B81A0/6B81A8/6B81B0 enter the real
string destructor401E00;6B81B8 enters CsvReader destructor42E980. The latter is
already independently exact. The ordinary source reproduces the full main
body and its EH-state publications; handler address canonicalization does not
claim byte-exact compiler metadata beyond the attested original binding.

## Focused verification

scripts/repo-python scripts/build.py --unit exact-first-default-deck-csv --compare --json

Formal receipt:build/frontier-default-deck-loader-20261029/formal.json.
Only the new source/unit and one new target-attested EH relocation key were
added. Existing prefix/suffix literal bindings and generated string/deque
callees are reused. Shared sources and accepted caller TUs are unchanged.
The source-only origin rule is replaced by canonical-exact baseline ownership;
no generated string/container helper receives authored credit.
