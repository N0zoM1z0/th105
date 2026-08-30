namespace th105 {
extern "C" const unsigned int select_sprite_vtable_anchor[];
struct UiSpriteCtorProbe {
    const unsigned int *vtable_00;
    unsigned int value_04;
    unsigned char rest_08[0x8c];
    UiSpriteCtorProbe();
};
UiSpriteCtorProbe::UiSpriteCtorProbe() : value_04(0)
{
    vtable_00 = select_sprite_vtable_anchor;
}
}
