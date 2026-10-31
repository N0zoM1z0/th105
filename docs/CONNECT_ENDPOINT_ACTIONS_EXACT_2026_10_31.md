# Connect endpoint actions: three complete exact functions

Three real dependencies of the middle-state handler are now canonical exact:
- 4424D0: clipboard confirmation wrapper,84 bytes.
- 4430D0: history confirmation wrapper,85 bytes.
- 442CE0: combined address/port action wrapper,329 bytes.

This adds498 authored bytes and three exact functions:1550 /439926.
Source1746, authored1766, excluded1421 and review840. The separate27-byte CRT
header instance receives no authored byte or function credit.

## Actual caller and source behavior

The current-target middle-state444490 calls these wrappers from its outer-mode
2/3/4/5 entry paths and ignores their residual EAX results. Ordinary void methods
therefore express the observed call contract without invented return values.

The clipboard/history wrappers preserve profile-choice or history-selection
outcomes, clear outer mode on cancellation, and format the selected endpoint
from its real0x1C small-string object into the260-wide-character buffer at448.
The history wrapper enables guide103C first. Successful selection sets substate1.

The combined editor enables guideD9C and consumes the real digit-editor result.
It formats all four unsigned16-bit address components into both the wide
destination and a genuine260-byte narrow local, assigns the narrow string with
its actual length, copies four words into configuration+3C..42, stores port+44,
and sets substate1. The target /GS cookie and both return paths match completely.
No truncation rule, guard or additional network operation is invented.

The first ordinary source already reproduced84/85 exactly. Its full329-byte
sibling differed only in third-word load scheduling. Replacing four manually
expanded assignments with the normal four-element array loop lets VC8 unroll
the true array copy in exactly the native order. No assembly, register directive,
volatile, padding, fake lifetime or forced optimizer boundary is involved.

## Original header, genuine private argument

The pinned VC8 include/swprintf.inl supplies the actual counted swprintf
definition: va_start, _vswprintf_c_l(buffer,count,format,NULL,args), va_end.
Header SHA-256:
d92946b2263736a620b151ae80a1e7f4963112f72b1e6257b021e7c33d0dbf3f.

Ordinary /O2 compilation in the real three-caller TU naturally passes count in
EDX and leaves the other variadic arguments on the stack, producing native4418B0
at27/27. No fabricated register-specific source declaration is used.
Its complete canonical SHA-256 is
72d421962b54962fb5747badaabb4e2dcb808ae0232bbbe52d10bfb67af3fbc6.
The origin rule identifies this as VC8 runtime-header code and checks the full
body plus all three exact incoming calls. It is not entered into matches.csv
or implemented.csv as authored game code.

The wide %S and wide/narrow IPv4 formats use complete original literal bytes.
The initially guessed narrow-format location was rejected by the strict data
gate; raw442D84 establishes the correct6C1C08 address. No failed binding or
literal mismatch was waived.

## Full comparison and scope

The unit exact-first-connect-endpoint-actions builds all three complete
application bodies and the actual header helper. Canonical application hashes:
-84:0ccf58445692e9b41d7ad8b1769bbd4d1a074af526291371fb86406ee0a16c88.
-85:ff35ee1158affe4c98f4b99368f1b570454998d489827e6bda76830f2ef978cf.
-329:2c0ceb4f14cb6c7a304946801fa044bc16169c36be3f750807e7543468d98d00.

Formal command:

    scripts/repo-python scripts/build.py --unit exact-first-connect-endpoint-actions --compare --json

This is an append-only unit/source/literal checkpoint. No shared header or
existing provider changes, so unrelated accepted receipts remain valid.
The middle-state699 body and combined891-byte digit editor remain nonexact;
exact callers do not promote them.

Receipts and the single real-array source control are retained under
build/frontier-connect-endpoint-actions-20261031/ and its .analysis counterpart.
The new header rule and three canonical origin rows are updated incrementally
after their witnesses pass; unchanged origin evidence is retained. Progress is
regenerated. Final CI and whitespace checks gate the local commit; no push.
