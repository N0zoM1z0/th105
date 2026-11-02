#pragma once
#include "battle/GameMode.hpp"
#include <stddef.h>
namespace th105 {
// Shared offset-constrained selection setup; never allocated by these owners.
struct SelectSetupEntryView {
 int identifier_00;
 signed char stage_04,bgm_05;
 unsigned char unknown_06[2];
 MatchSetup::Side sides_08[2];
 unsigned seed_48;
 unsigned char random_4c[3];
};
typedef char SelectSetupRandomOffset[offsetof(SelectSetupEntryView,random_4c)==0x4c?1:-1];
}
