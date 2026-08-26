namespace th105 {
struct Fighter;
struct InfoShortRecord34Bind {
    void *combo_00;
    Fighter *fighter_04;
    unsigned char reserved_08[0x0c];
    int duration_14;
    int state_18;
    unsigned char active_1c;
    unsigned char reserved_1d[0x17];
    void bind_46a620(void *combo, Fighter *fighter);
};
typedef char InfoShortRecord34Bind_size_must_be_0x34[sizeof(InfoShortRecord34Bind) == 0x34 ? 1 : -1];
void InfoShortRecord34Bind::bind_46a620(void *combo, Fighter *fighter)
{
    combo_00 = combo;
    fighter_04 = fighter;
    duration_14 = 90;
    state_18 = 0;
    active_1c = 0;
}
}
