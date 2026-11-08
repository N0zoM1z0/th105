#pragma once

#include "ui/ProfileDeckResourceLifetime.hpp"
#include <deque>

namespace th105 {
// Character-owned spell resources, including the two spell ID queues.
struct CharacterSpellResources {
    ProfileDeckResourceGroupNative20 core;
    std::deque<short> loaded, selection;
    unsigned char values_48[0x20];
    void initialize_side_payload(const ShortDeque8 *payload);
    void clear_resources();
    ~CharacterSpellResources() { clear_resources(); }
};
}
