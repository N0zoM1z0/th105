namespace th105 {

struct ProfileMenuBaseDataView {
    unsigned char storage_000[0x33c];

    ProfileMenuBaseDataView();
    ~ProfileMenuBaseDataView();
    bool load_profile(const char *path);
    void initialize_defaults();
    bool save_to_profile(const char *path);
};

void __cdecl create_default_profile_for_list()
{
    ProfileMenuBaseDataView profile;
    if (!profile.load_profile("Profile1P.dat")) {
        profile.initialize_defaults();
        profile.save_to_profile("Profile1P.dat");
    }
    if (!profile.load_profile("Profile2P.dat")) {
        profile.initialize_defaults();
        profile.save_to_profile("Profile2P.dat");
    }
}

typedef char ProfileMenuBaseDataView_size_must_be_0x33c[
    sizeof(ProfileMenuBaseDataView) == 0x33c ? 1 : -1];

} // namespace th105
