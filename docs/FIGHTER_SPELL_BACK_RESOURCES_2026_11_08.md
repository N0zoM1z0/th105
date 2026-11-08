# Fighter spell-back texture handles

`Fighter::initialize_fighter_spell_resources` at `0x463070` loads up to ten
`back/spell%03d.bmp` textures and appends each nonzero handle to the deque at
Fighter `+0x68C`. `0x45F560` selects a handle from the same deque and publishes
it to the battle object manager's two texture slots. Fighter `+0x6A0` records
the duration and `+0x6A2` the signed-byte index. Character cleanup releases
the stored handles and clears the deque.

The loader and publisher now use the same `DwordDeque4` physical view. The
checked entry call remains bound to `0x42D1B0`; that body is shared with other
32-bit deque specializations, so the binding does not establish the original
nominal C++ element type. The loader, publisher, wave-resource loader and cutin
loader remained exact against Japanese TH10.5 1.06a with the pinned VC8 profile.
The character destructor remains nonexact.
