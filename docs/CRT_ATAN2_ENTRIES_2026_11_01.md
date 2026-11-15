# Original atan2 dispatch entries

The native entries 68BB70 and 68BB7A are the complete original ten-byte _atan2
and __CIatan2 entries from 87ctriga.obj, not atan2.obj or atan2_sse2.obj. The
pinned original 20-byte text section contains precisely both entries, at 0/10.
Each loads EDX with the same operation table 6F8990 then tail-jumps to its
actual named dispatch path 6965AB/696530. Both whole roots are inventory-unique.
The canonical section-tail API returns 20 bytes for the first symbol; the gate
first checks the full 20-byte owner and actual 0/10 symbol offsets, then compares
the complete independently closed ten-byte entry. No arbitrary prefix is used.

## Original ownership witnesses

The whole source sections are canonical without masks:
- 87ctriga.obj text 20 at 68BB70.
- 87triga.obj text 168 at 696480 and data 80 at 6F8990.
- 87cdisp.obj text 640 at 696530 and readonly constants 48 at 6CE590.
- 87disp.obj text 458 at 690BA0 and data 44 at 6F8080.

The 80-byte operation table has its exact 16-byte header and sixteen original
DIR32 slots. Every pointer targets an actual original label and decoded
instruction boundary in the complete owners. All original relocation fields
retain their actual zero addends. Original object and archive hashes are pinned.
The full supporting code is canonically compared and instruction-decoded;
this does not claim complete reachability through all indirect dispatch states.
Only the two small roots receive closed CFG proofs with their exact named E9
exit. No generic CFG rule changes.

__matherr_flag is particularly important: the common declaration in 87cdisp.obj
is resolved by matherr.obj's initialized four-byte definition 94260000 at 6F92FC.
It is not fabricated zero-fill. The separate fastflag is the actual fpinit.obj
BSS subobject at 6FD3A4, verified as PE zero-fill without reading raw BSS bytes.
Existing dispatch/exception provider ownership is reused, not newly counted.

Thirteen tests and 1462 individual initialized-byte corruption controls are rejected.
No fake BSS byte controls are claimed. Formal replay verifies both entries. Scope:20
new runtime bytes only, no source/game exact, table, support or provider credit.
Authored exact remains 1431/443916; source-present1636. Excluded 2061, review 311,
units 804.
