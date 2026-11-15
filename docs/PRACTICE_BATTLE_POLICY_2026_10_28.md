# Practice battle policy 0x00428260

Complete raw-target candidate:553 callable bytes through 428489 exclusive, followed
by three alignment bytes and a five-entry switch table at 42848C. All decoded
instructions are reachable from entry using that table.

The controller snapshots both scene fighters into a two-pointer local array.
Practice mode 8 applies guard policy cases 0/2/3=1 and 1=0; case 4 uses the existing
fighter state predicates. Below-state32 gates health restoration and spirit
counters. First fighter receives 1000 spirit and zero floors; second receives
the signed minimum of existing spirit and configured spirit*1000/5, plus the
observed remaining resets. The two paths intentionally differ.

The mode option maps zero to 16 and other values to option-1, publishing the
16-bit999/0 mode value and invoking the existing mode selector only on change.
Input mode 3 can rebind slot 1, choose its deck and expose the slot's138 subobject.
Other input modes clear fighter 6B0. Outside Practice, mode_lock08 can publish 999,
and restore 04==1 iterates both captured fighters with the two state gates.
Callbacks and fresh global/player-slot reads are retained; no null guards,
saturation or recovery policy was added.

The new source uses existing gate/input APIs and relocation identities.
Local option names and owner views describe observed accesses, not proof of
the original nominal types. The existing presentation-phase caller consumes
no result; this full body likewise does not establish a meaningful return value.

Strict initial comparison is nonexact at+9. Candidate callable 554 bytes plus
two alignment and 20 table bytes totals 576, versus native 553+3+20=576.
Equal total section sizes do not establish equality. Native first pointer
is EBX and controller EDI; candidate uses EDI and EBX, with different zero
lifetimes through the non-Practice path. Capturing the two fighter locals before
forming the array was byte-neutral; no register/liveness forcing was attempted.
No source-selection or exact credit is added.

Only this new unit was compiled. Shared headers, existing callers and settings are
unchanged.
