namespace th105 {

class Character {
public:
    Character(int init_arg);
    virtual ~Character();
protected:
    unsigned char unknown_004[0x134];
    float field_138;
    unsigned char unknown_13c[0x51c];
    void *owned_manager_658;
};

#define TH105_DECLARE_ROSTER_CTOR(Name)                                      \
class Name;                                                                  \
class Name##ObjectManager {                                                  \
public:                                                                      \
    Name##ObjectManager(Name *owner);                                        \
private:                                                                     \
    unsigned char storage_00[0x68];                                          \
};                                                                           \
class Name : public Character {                                              \
public:                                                                      \
    Name(int init_arg);                                                      \
};                                                                           \
Name::Name(int init_arg) : Character(init_arg)                               \
{                                                                            \
    owned_manager_658 = new Name##ObjectManager(this);                       \
}

TH105_DECLARE_ROSTER_CTOR(Reimu)
TH105_DECLARE_ROSTER_CTOR(Marisa)
TH105_DECLARE_ROSTER_CTOR(Sakuya)
TH105_DECLARE_ROSTER_CTOR(Patchouli)
TH105_DECLARE_ROSTER_CTOR(Remilia)
TH105_DECLARE_ROSTER_CTOR(Yuyuko)
TH105_DECLARE_ROSTER_CTOR(Yukari)
TH105_DECLARE_ROSTER_CTOR(Suika)
TH105_DECLARE_ROSTER_CTOR(Udonge)
TH105_DECLARE_ROSTER_CTOR(Komachi)
TH105_DECLARE_ROSTER_CTOR(Aya)
TH105_DECLARE_ROSTER_CTOR(Tenshi)

class Iku;
class IkuObjectManager {
public:
    IkuObjectManager(Iku *owner);
private:
    unsigned char storage_00[0x68];
};
class Iku : public Character {
public:
    Iku(int init_arg);
};
Iku::Iku(int init_arg) : Character(init_arg)
{
    field_138 = -6.0f;
    owned_manager_658 = new IkuObjectManager(this);
}

#undef TH105_DECLARE_ROSTER_CTOR

} // namespace th105
