# Music and result menu indexing providers

Music selection at 0x445360 calls 0x412980 twice on the embedded
`deque<string>` at menu +0xB8. The source used `at()`, but that provider
contains an out-of-range exception path absent from the native helper.
Both providers happen to be 94 bytes, so body length alone did not expose
the bad binding. The actual native operator[] has three invalid-parameter
calls and now comes directly from the music source's two indexing expressions.

Result selection at 0x4472A0 similarly calls the 100-byte operator[] at
0x42D1B0 for the value and label queues, at result-list +0xE0 and +0xCC.
The existing population source writes both as `deque<int>`. The reader now
uses that type through its existing storage views instead of the undefined
pointer-returning `at` facade. No shared layout was changed.

The two complete units were built before and after the change. All six music
roots remain exact (442, 281, 38, 185, 318 and 30 bytes). The result update
remains the same 620-byte candidate against 619 native bytes, with mismatch
+81. All seven canonicalized root bodies and fifteen complete root/EH sections
are unchanged. The actual emitted string operator[] compares 94/94 and the
integer operator[] 100/100, including every relocation.

These provider corrections add no authored exact credit. The input migration and
source pins remain separate.
