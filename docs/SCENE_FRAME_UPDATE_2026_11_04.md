# Scene frame update

`update_scene_runtime` 0x43B4A0 (209 bytes) and the UI selection update
`update_profile_ui_selection` 0x4400D0 (160 bytes) are both exact.

The exact `CSceneManager::update` 0x41E140 tail-calls 0x43B4A0. That function
refreshes the keyboard and player inputs, visits the 0x68-byte result input
records, merges the menu input and integrates the scene fade. Its three exits
pop the callee-saved registers and then `jmp 0x4400D0`.

Earlier ledgers treated 0x4400D0..0x44016F as a remote chunk of 0x43B4A0. It
is an ordinary function, and the three jumps are tail calls:
- it has its own two `ret`s;
- it uses no callee-saved registers;
- it sits in the profile UI code, between `trim_profile_ui_menu_stack`
  0x440010 and `render_profile_ui_frame` 0x440170.

Calling it as a separate `void` function from the end of 0x43B4A0 reproduces
the epilogue-then-`jmp` exits exactly.

The UI update fades the selection overlay in or out by 15 per frame. While a
menu is active it pops the menu once both confirm buttons are released and no
initial press is pending. Otherwise it marks the stack active when a
scene-22 menu above the snapshot is not ready. Three source details were
needed:
- the fade direction is tested as `state - snapshot != 0` (`mov; sub; je`);
- the fade-in guard is `fade < 255` (`jae`);
- the dismiss test reads `buttons[0]` and `buttons[1]` (+0x40/+0x44). The old
  single-function hypothesis read `vertical` and `buttons[0]`, which was wrong.
