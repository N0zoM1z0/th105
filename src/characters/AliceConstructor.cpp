namespace th105 {

// Narrow current-target constructor views.  This TU intentionally models only
// the Character fields touched by Alice construction; the full derived layout
// remains owned by the lifecycle/action-state recovery lane.
class Alice;

class AliceObjectManager {
public:
    AliceObjectManager(Alice *owner);

private:
    unsigned char storage_00[0x68];
};

class Character {
public:
    Character(int init_arg);
    virtual ~Character();

protected:
    unsigned char unknown_004[0x134];
    float field_138;
    unsigned char unknown_13c[0x51c];
    AliceObjectManager *owned_manager_658;
};

class Alice : public Character {
public:
    Alice(int init_arg);
};

Alice::Alice(int init_arg)
    : Character(init_arg)
{
    field_138 = -6.0f;
    owned_manager_658 = new AliceObjectManager(this);
}

} // namespace th105
