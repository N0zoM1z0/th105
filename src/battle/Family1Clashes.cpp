#include "Collision.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace {

unsigned frame_flags_50(const CollisionObject *object)
{
    return *reinterpret_cast<const unsigned *>(
        reinterpret_cast<const unsigned char *>(object->frame_1a4) + 0x50);
}

struct CheckedCollisionListIterator {
    CollisionListNode *node;
    CollisionListNode *sentinel;

    CollisionObject *payload() const
    {
        if (node == sentinel) {
            _invalid_parameter_noinfo();
        }
        return static_cast<CollisionObject *>(node->payload);
    }

    void increment()
    {
        if (node == sentinel) {
            _invalid_parameter_noinfo();
        }
        node = node->next;
    }
};

} // namespace

void CollisionContext::dispatch_family1_object_clashes()
{
    int list_count = 2;
    CollisionList *list = family_1;
    do {
        CollisionListNode *const sentinel = list->sentinel;
        CheckedCollisionListIterator outer = { sentinel->next, sentinel };
        while (outer.node != sentinel) {
            if ((frame_flags_50(outer.payload()) & 0x100000) != 0 &&
                (outer.payload()->frame_1a4->flags_4c & 0x40) == 0 &&
                outer.payload()->source_1a0 != 0 &&
                (outer.payload()->frame_1a4->flags_4c & 0x80000) == 0) {
                CheckedCollisionListIterator inner = {
                    sentinel->next, sentinel
                };
                while (inner.node != sentinel) {
                    if ((inner.payload()->frame_1a4->flags_4c & 0x40) == 0 &&
                        inner.payload()->source_1a0 != 0 &&
                        (inner.payload()->frame_1a4->flags_4c & 0x80000) == 0 &&
                        inner.payload() != outer.payload()) {
                        resolve_group_b_object_clash(
                            outer.payload(), inner.payload());
                    }
                    inner.increment();
                }
            }
            outer.increment();
        }
        ++list;
    } while (--list_count != 0);

    CollisionListNode *const left_sentinel = family_1[0].sentinel;
    CheckedCollisionListIterator outer = {
        left_sentinel->next, left_sentinel
    };
    while (outer.node != left_sentinel) {
        if ((outer.payload()->frame_1a4->flags_4c & 0x40) == 0 &&
            outer.payload()->source_1a0 != 0 &&
            (outer.payload()->frame_1a4->flags_4c & 0x80000) == 0) {
            CollisionListNode *const right_sentinel = family_1[1].sentinel;
            CheckedCollisionListIterator inner = {
                right_sentinel->next, right_sentinel
            };
            while (inner.node != right_sentinel) {
                if ((inner.payload()->frame_1a4->flags_4c & 0x40) == 0 &&
                    inner.payload()->source_1a0 != 0 &&
                    (inner.payload()->frame_1a4->flags_4c & 0x80000) == 0) {
                    resolve_group_b_object_clash(
                        outer.payload(), inner.payload());
                }
                inner.increment();
            }
        }
        outer.increment();
    }
}

} // namespace th105
