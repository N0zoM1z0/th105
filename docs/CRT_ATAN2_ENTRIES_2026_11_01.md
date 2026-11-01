# Original atan2 dispatch entries

The native entries68BB70 and68BB7A are the complete original ten-byte _atan2
and __CIatan2 entries from87ctriga.obj, not atan2.obj or atan2_sse2.obj. The
pinned original20-byte text section contains precisely both entries, at0/10.
Each loads EDX with the same operation table6F8990 then tail-jumps to its
actual named dispatch path6965AB/696530. Both whole roots are inventory-unique.
The canonical section-tail API returns20 bytes for the first symbol; the gate
first checks the full20-byte owner and actual0/10 symbol offsets, then compares
the complete independently closed ten-byte entry. No arbitrary prefix is used.

## Original ownership witnesses

The whole source sections are canonical without masks:
- 87ctriga.obj text20 at68BB70.
- 87triga.obj text168 at696480 and data80 at6F8990.
- 87cdisp.obj text640 at696530 and readonly constants48 at6CE590.
- 87disp.obj text458 at690BA0 and data44 at6F8080.

The80-byte operation table has its exact16-byte header and sixteen original
DIR32 slots. Every pointer targets an actual original label and decoded
instruction boundary in the complete owners. All original relocation fields
retain their actual zero addends. Original object and archive hashes are pinned.
The full supporting code is canonically compared and instruction-decoded;
this does not claim complete reachability through all indirect dispatch states.
Only the two small roots receive closed CFG proofs with their exact named E9
exit. No generic CFG rule changes.

__matherr_flag is particularly important: the common declaration in87cdisp.obj
is resolved by matherr.obj's initialized four-byte definition94260000 at6F92FC.
It is not fabricated zero-fill. The separate fastflag is the actual fpinit.obj
BSS subobject at6FD3A4, verified as PE zero-fill without reading raw BSS bytes.
Existing dispatch/exception provider ownership is reused, not newly counted.

Thirteen tests and1462 individual initialized-byte corruption controls are
rejected. No fake BSS byte controls are claimed. Formal replay verifies both
entries. Scope:20 new runtime bytes only, no source/game exact, table, support
or provider credit. Authored exact remains1431/443916; source-present1636.
Excluded2061, review311, units804. Private evidence is retained under
.analysis/frontier-atan2-dispatch-20261101/ and build/origin-anchors/vc8-atan2-entries/.
