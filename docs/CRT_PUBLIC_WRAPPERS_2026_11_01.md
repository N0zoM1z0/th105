# Three complete original CRT forwarding entries

Three whole runtime bodies now have strict original-object proofs:
- atof at68B420/14 from atof.obj, calling __atof_l at68B377.
- fread at68CEEF/27 from fread.obj, calling fread_s at68CE59.
- _flushall at69A81E/9 from fflush.obj, calling flsall at69A744.

All50 bytes are canonical exact, all three entire bodies are unique in the
4027-candidate inventory, and their RET control flow closes completely. Each
has exactly one original zero-addend REL32 field, at offsets7/19/3 respectively.
There are no data references, padding tails, masks or partial-body claims.
The complete source section extents are14/27/9, not inferred prefixes.

The original call structure preserves the actual ABI and argument forwarding:
atof supplies the null locale, fread inserts the original size_t(-1) buffer
bound while forwarding the four arguments, and _flushall supplies flag1.
No handwritten wrapper implementation or stack/register facade is created.
The actual unchanged vendor objects are extracted from the pinned SP1 libcmt.

Original member SHA256 values:
- atof.obj:5cc546a67742f332f8c1444152bc01f241dec0d749f1677a1a2150c5ec86bddd.
- fread.obj:ce3e59fd30d7574daed5675a2c932e0aedf2c1069f9b2ccca06737f23b42d60a.
- fflush.obj:5a8e4eb928eb6799550b44945111c046795f83bd6051f64051fe547bd586c74a.

The callee roles reuse their existing independently classified pinned-runtime
entries. Their native inventory names and169/150/218-byte extents agree with
the provider symbols in the same original objects. This checkpoint does not
claim a new whole-provider implementation/EH proof or a uniform patch version
for the entire runtime. Only the three complete forwarding bodies gain credit.

Eight tests reject missing/duplicate bodies, masks/shortening, wrong member,
wrong provider, the different fread_nolock symbol and archive drift. All50
actual byte corruption controls fail. All three new public units freshly
compare exact. Generic origin coverage/size thresholds are unchanged.

Only50 runtime bytes and three exclusions are added. Authored exact functions,
authored exact bytes and source-present counts remain unchanged.

Evidence: build/origin-anchors/vc8-public-wrappers/proof.json and
build/frontier-crt-public-wrappers-20261101/mutations.json. Private scripts and
original-member probes are under the corresponding .analysis/build scope.
