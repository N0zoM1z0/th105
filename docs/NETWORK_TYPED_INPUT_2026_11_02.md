# Named resolved-input field in network publishers

The client and server input publishers now use the existing CInputManagerEx
input layout and its unsigned-short resolved_mask member at62. Their input208
fields are typed pointers; three raw byte-pointer/offset casts are removed.
Each TU asserts the62 offset. No shared input header or instance layout changes.
This is an offset-checked source view, not a claim that full dynamic-type,
constructor, RTTI naming or whole-program input ownership has been recovered.

Independent fresh exact support remains:

- Input logical-mask producer409F70/378 uses the same named resolved field.
- Selected-input initialization43B640/153 chooses the established input source.
- Network result binding43B410/136 publishes the selected pointer to204/208.

These source/native bodies corroborate the field and handoff; they are not
used to invent stronger pointer or lifetime guarantees.

The server sender declaration in NetworkPrimaryStateRuntime.cpp is also
corrected to void, consistent with the real inactive-path sender behavior and
the publisher TU's prior correction. Its result is discarded. Only this TU's
actual decorated call binding changes; unrelated sender views are not edited.

## Focused verification

The typed-field control was built before adoption, independently of the
second sender declaration correction. All seven complete bodies remain
byte-identical after final adoption:

- Existing accepted packet sender48 and adaptive update162.
- Existing accepted client sync166, client publication152 and server sync175.
- ACK tail78 still has8 differences; server publisher404/native409 remains
  nonexact. Their previous candidate hashes are unchanged.

Only two source-owning units are affected; no other tracked source includes
these CPPs. Both units are freshly compared in full. The three supporting
producer/selection/binding units and critical-section unit are also freshly
exact. The server static CFG audit and all six guarded ACK cases/negative
control pass. No extra stateful testing, OS input/network activity, source
spelling grid, register forcing or new exactness credit is introduced.

Authored/source/exact counts remain unchanged: source1636, authored1655,
mapped1825, review298, excluded2074, exact1427/443604, units812.

Original pinned target only; serial CPU0/nice10 native work and no push.
