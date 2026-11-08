#pragma once

namespace th105 {
// One entry in Fighter's 64-element character wave handle array at +0x164.
struct CharacterWaveHandle4 {
    unsigned value;
    CharacterWaveHandle4() : value(0) {}
};
}
