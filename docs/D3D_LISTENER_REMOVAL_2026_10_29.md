# Global D3D reset-listener removal414D50

Newly source-selected and authored, not exact. Complete140/native140 compares
with first mismatch+10; selected compiled SHA-256
514d35f5c04428774120162de04f76ab94b95bcd8980140b9a78a1ff032dd373.
Canonical native SHA-256
70b69513f402cfbe3ff69959a6b972429b7e2abcb257ff63a3c1aab85fe30d18.

Exact effect shutdown418040 calls it at418044 before releasing the COM effect.
The native49-instruction CFG locks the global backend critical section7036A4,
searches reset-listener list70384C/head703850, compares the checked result to
end, conditionally calls erase414DE0 and always unlocks. All140 bytes, including
one internal NOP, are compared; four subsequent INT3 bytes are outside the body.
The global listener ownership operation is application code, independently of
the compiler-library origin of its list helpers.

Source preserves the existing ordinary stdcall facade and actual effect-pointer
parameter, converting it to the reset-listener pointer view. It uses standard
find with a named result, conditional erase and the real critical-section
implementation. Only the complete removal entry is exported/selected in
exact-first-d3d-listener-removal-linked. The original nominal declaration/TU
and private erase calling convention remain unknown; no fake ABI is asserted.

An isolated data binding verifies backend+0/+4/+1AC/+1B0 as loader-zero DWORDs.
The preexisting aggregate binding and consumers are unchanged. The source
and target consume the same actual list/lock fields; comparison masks nothing.

The target loads the pointer argument into EBX before entering the critical
section; this source loads it later. Target erase passes its private receiver
on the stack, whereas pure CIL chooses EBX. A genuine ordinary COFF explicit
std::list<DeviceResetListener*> provider changes that call to normal ECX but
still yields140/140 first+10. Direct listener-pointer parameter and effect-pointer
facade produce the same pure-CIL bytes. Those diagnostic alternatives are not
selected, and no register/stack padding trial is justified by these results.

Receipts in build/frontier-d3d-listener-remove-20261029/: formal-build.json,
boundary.json, mixed-result.log and ci.log. Private replay requires restoring
the retained DeviceResetListenerList.cpp only for the unselected mixed trial;
its temporary src/library file was removed after byte comparison. No native
jobs or scratch sources are left active. Existing exact initializer/registration
and five lifetime methods retain their acceptance; this scope adds140 authored
source bytes and zero exact bytes. Continue elsewhere until genuine missing
caller/provider context resolves the two residuals.
