namespace th105 {
struct CollisionListArrayElement {
    unsigned unknown_00; void *sentinel_04; unsigned count_08;
    CollisionListArrayElement(); ~CollisionListArrayElement();
};
struct CBattleManagerBaseLifecycle {
    virtual ~CBattleManagerBaseLifecycle();
    unsigned char reserved_004[0x28];
    CollisionListArrayElement group_2c[2];
    CollisionListArrayElement group_44[2];
    CollisionListArrayElement group_5c[2];
    CBattleManagerBaseLifecycle();
};
CBattleManagerBaseLifecycle::CBattleManagerBaseLifecycle() {}
CBattleManagerBaseLifecycle::~CBattleManagerBaseLifecycle() {}
}
