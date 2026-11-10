# Original runtime member-call bridge

68998E/7 is now completely exact and inventory-unique against the original
libcmt:trnsctrl.obj member-call bridge family. The actual original COMDATs for
CallMemberFunction0, CallMemberFunction1 and CallMemberFunction2 are each seven
bytes and have no relocations. All three complete bodies match the same native
physical candidate. The formal unit uses the0 spelling as a representative;
bytes alone do not identify it exclusively or prove which compatible aliases
the shipped linker retained. One physical runtime body receives seven bytes
of library credit, never three function credits.

Archive SHA256:
3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3.
Original trnsctrl.obj SHA256:
a14106ba2d01aa5b86d80b3eee4e8c267af1dbabfec1a845a6bb5545d29de7d7.

No implementation is synthesized. The validator proves the exact original
four-instruction linear transfer: preserve the return address in EAX, establish
ECX this, exchange the next stack DWORD with EAX, then jump indirectly through
EAX. The saved return remains on the stack for the actual member callee; any
remaining member arguments are untouched. Exact instruction widths, register
roles, stack address and complete terminal transfer are checked. This is a
single typed bridge contract, not a generic indirect-jump or unreachable-byte
waiver. The general closed-CFG validator remains unchanged.

The whole original sections, absence of relocations, native hash and complete
same-sized candidate inventory are checked. No masks, copied implementation,
private ABI declaration or generic minimum-threshold relaxation is introduced.

Ten focused tests cover original archive/member identity, single physical credit, no
shortened/masked comparisons, exact stack/register roles and rejection of direct
jumps or extra/truncated instructions. All seven actual code-byte corruption
controls fail. The narrow origin rule passes before reclassifying the single review
row. Authored exact totals do not change.
