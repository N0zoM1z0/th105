#include <stddef.h>

namespace th105 {

namespace {

// This is intentionally a narrow view.  The target only proves that every
// Fighter has an owned-object manager pointer at +0x658, and that the
// manager's vtable slot +0x04 consumes this exact request shape.
struct FighterOwnedObjectSpawnView;

struct OwnedObjectManagerSpawnView {
    virtual int unknown_vslot_00();
    virtual int spawn_owned_object(
        void *parent,
        FighterOwnedObjectSpawnView *related_fighter,
        int object_id,
        float x,
        float y,
        int direction,
        int arg5,
        int arg6,
        int arg7);
};

struct FighterOwnedObjectSpawnView {
    unsigned char unknown_000[0x658];
    OwnedObjectManagerSpawnView *owned_manager_658;

    int spawn_owned_object_via_manager(
        int object_id,
        float x,
        float y,
        int direction,
        int arg5,
        int arg6,
        int arg7);
};

typedef char CheckFighterOwnedObjectManagerOffset[
    offsetof(FighterOwnedObjectSpawnView, owned_manager_658) == 0x658 ? 1 : -1];

} // namespace

int FighterOwnedObjectSpawnView::spawn_owned_object_via_manager(
    int object_id,
    float x,
    float y,
    int direction,
    int arg5,
    int arg6,
    int arg7)
{
    return owned_manager_658->spawn_owned_object(
        0, this, object_id, x, y, direction, arg5, arg6, arg7);
}

} // namespace th105
