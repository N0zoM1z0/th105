# One original validation body and its three real caller roles

69C4BF/13 is now a complete canonical runtime body. Original validate.obj
emits byte-identical, relocation-free ValidateRead, ValidateWrite and
ValidateExecute functions. All three entire13-byte source sections match the
one native inventory body; each has a closed RET graph. Only one physical
function is counted. The formal representative is ValidateRead, not a claim
that this was the exclusive original symbol or that a particular ICF decision
has been recovered.

This is not classification from a generic pointer/nonzero test alone. The
complete original BuildCatchObjectHelper at68F452/383 and its actual28-byte
SEH4 scope at6E23C0 independently establish the roles. Its nine source
relocations name four reads, four writes and one execute validation; all nine
native fields resolve to69C4BF. The original source signatures are retained,
including their unused parameters. No invented ABI or wrapper is introduced.
The separate FindHandler caller is not newly reconstructed here.

## Complete SEH ownership, not a reachability waiver

The scope record has two local code relocations, not one: field20 targets the
filter at parent+363 and field24 targets the handler at parent+367. They are
resolved by the actual COFF symbol-table indices, owner section and offsets.
Global lookup by a repeated $LN label name is not accepted.

The three legitimate entries (main/filter/handler) reach all146 instructions
across all383 bytes. The handler's real MOV ESP,[EBP-18h] is followed by its
original E9 to terminate at68FC12. Only that exact source-backed termination
site is allowed to leave the owner. Other external branches, changed stack
restoration, arbitrary indirect jumps and unaccounted bytes fail closed.
No generic CFG function is loosened. The existing terminate provider and its
remote implementation/EH are not recounted.

## Actual memmove provider and original inline tables

The caller's memmove reference is resolved against the complete original
memmove.obj payload at68D8B0, not merely the native provisional memcpy_0 label.
All869 payload bytes compare after their original relocations. Six actual
source pointer tables contain30 entries/120 bytes; the remaining749 bytes
decode into268 instructions, and every table entry lands on a code boundary.
No new whole-provider reachability claim is made from that partition alone.

Four original biased table references are preserved: LeadUpVec-4,
TrailUpVec+16, UnwindDownVec+28 and LeadDownVec-4. They are linker addends in the
original indexed-address forms, not permission to invent data extents or
normalize away instruction differences. The original SSE availability common
word at7039C8 is independently tied to cpu_disp.obj and native PE zero-fill.
The actual VEC_memcpy provider remains its already classified227-byte entry.
The payload and all support bytes receive zero new authored/runtime credit.

## Validation and scope

Original objects are extracted from the unchanged pinned archive; all member
hashes are recorded in the proof. Fifteen tests cover complete physical-body
selection, no alias double-count, original members, exact local-symbol-index
binding, metadata owner/offset failures and the one qualified SEH tail. All1293
actual initialized-byte corruption controls fail:13 leaf bytes,383 caller
bytes,28 scope bytes and869 provider payload bytes. No raw BSS-byte controls
are fabricated.

Only13 runtime bytes and one exclusion are added. The catch helper, scope, memmove
payload, vector-copy provider, aliases and authored counts do not gain additional
credit. Current code/EH comparisons are whole and unmasked.
