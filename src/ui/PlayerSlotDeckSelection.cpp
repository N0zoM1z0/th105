namespace th105 {

struct PlayerProfileBlock52 {
    unsigned char bytes_00[0x34];
};

struct PlayerProfileBlockOwnerView {
    void assign_profile_block(const PlayerProfileBlock52 *source);
};

struct PlayerSlotRecordScenarioView {
    void select_deck(unsigned char source);

private:
    __forceinline PlayerProfileBlockOwnerView &profile_owner_d0()
    {
        return *reinterpret_cast<PlayerProfileBlockOwnerView *>(
            reinterpret_cast<unsigned char *>(this) + 0xd0);
    }
    __forceinline PlayerProfileBlock52 &profile_140()
    {
        return *reinterpret_cast<PlayerProfileBlock52 *>(
            reinterpret_cast<unsigned char *>(this) + 0x140);
    }
    __forceinline PlayerProfileBlock52 &profile_174()
    {
        return *reinterpret_cast<PlayerProfileBlock52 *>(
            reinterpret_cast<unsigned char *>(this) + 0x174);
    }
    __forceinline unsigned char &selected_source_1a8()
    {
        return *(reinterpret_cast<unsigned char *>(this) + 0x1a8);
    }
};

void PlayerSlotRecordScenarioView::select_deck(unsigned char source)
{
    selected_source_1a8() = source;
    if (source == 0xff) {
        profile_owner_d0().assign_profile_block(&profile_140());
        return;
    }

    PlayerProfileBlock52 &profile = profile_174();
    profile.bytes_00[0] = source;
    profile_owner_d0().assign_profile_block(&profile);
}

} // namespace th105
