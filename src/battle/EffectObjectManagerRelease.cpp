#include <list>
#include <stddef.h>

namespace th105 {

class EffectObjectReleaseView {
public:
    unsigned char unknown_000[0x15c];
    unsigned handle_token_15c;
};

class EffectHandlePool50View {
public:
    void release_handle(unsigned handle_token);
    unsigned char storage_00[0x50];
};

class EffectObjectManagerReleaseView {
public:
    void release_all_tracked_objects();

    void *vtable_00;
    EffectHandlePool50View handle_pool_04;
    std::list<EffectObjectReleaseView *> linked_objects_54;
};

typedef char EffectObjectManagerRelease_pool_offset[
    offsetof(EffectObjectManagerReleaseView, handle_pool_04) == 0x04 ? 1 : -1];
typedef char EffectObjectManagerRelease_list_offset[
    offsetof(EffectObjectManagerReleaseView, linked_objects_54) == 0x54 ? 1 : -1];
typedef char EffectObjectRelease_handle_offset[
    offsetof(EffectObjectReleaseView, handle_token_15c) == 0x15c ? 1 : -1];

void EffectObjectManagerReleaseView::release_all_tracked_objects()
{
    for (std::list<EffectObjectReleaseView *>::iterator current =
             linked_objects_54.begin();
         current != linked_objects_54.end(); ++current) {
        unsigned const handle_token = (*current)->handle_token_15c;
        handle_pool_04.release_handle(handle_token);
    }
    linked_objects_54.clear();
}

} // namespace th105
