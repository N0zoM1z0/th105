# Complete FileList parent-navigation source

Native4398B0/91 is owned by the exact555-byte replay-delete workflow446A60,
which calls it at446C21 on its CFileList subobject. The method compares current
directory08C with root/filter070 and returns AL1 if already at that root.
Otherwise it creates one real slash character, finds its final occurrence with
count1/npos, erases from that position through the end, and returns AL0.
The native does not guard npos before erase; the source adds no such behavior.

FileListParent.cpp is complete ordinary C++. The formal91-byte result differs
only in the two stack-home operand bytes: native slash at low byte, source at
byte+3. First difference is+64. It is source-present, not an exact or partial
match. No char array, union, aligned dummy or extra lifetime is introduced.

A fresh genuine VC8 /GL + /LTCG control with the actual standard-library bodies
emits123 bytes: comparison is partially inlined and a real private
char_traits::compare entry is called. The strict linked comparator rejects that
unmapped private entry. Independent whole-body inspection already establishes
the size mismatch and unchanged high-byte slash home. No private ABI mapping,
forced export, artificial COFF split or comparison-gate waiver was added.
Both the ordinary and real-library LTCG lanes are now closed pending new facts.

The exact555-byte caller freshly remains canonical. A focused authored-origin
rule pins the complete target body and exact caller edge. No shared headers or
other selected source changed. Source1635/authored1655/mapped1820/review403;
excluded1969/units772; exact1431 /443916 bytes unchanged.

The private linked image/map and RESULT.txt record the negative control. No new
library or prefix credit, whole-corpus rebuild or push.
