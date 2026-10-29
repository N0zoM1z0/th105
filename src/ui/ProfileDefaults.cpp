#include "../input/InputManager.hpp"
#include <deque>
#include <string>
#include <string.h>
#include <stddef.h>
extern "C" const char profile_name_empty[];
namespace th105 {
struct StringAssignBytesView { std::string &assign_bytes(const char *, unsigned int); };
struct ProfileDefaultsView {
 // Texture/sprite prefix is not accessed by this method.
 unsigned char prefix[0x98];
 std::string string_098, string_0b4;
 unsigned char gap[0x6c];
 unsigned char flag_13c;
 InputBindings primary, secondary;
 unsigned char flag_1a8;
 std::deque<unsigned short> decks_1ac[20];
 void initialize_defaults();
 void initialize_default_deck(std::deque<unsigned short> *,int);
};
typedef char ProfileDefaultsDeckOffset[
    offsetof(ProfileDefaultsView, decks_1ac) == 0x1ac ? 1 : -1];
void ProfileDefaultsView::initialize_defaults()
{
    reinterpret_cast<StringAssignBytesView *>(&string_098)
        ->assign_bytes(profile_name_empty, 0);
    reinterpret_cast<StringAssignBytesView *>(&string_0b4)
        ->assign_bytes(profile_name_empty, 0);

    memset(&primary, 0, sizeof(primary));
    primary.source_id = -1;

    primary.up = 200;
    primary.down = 208;
    primary.left = 203;
    primary.right = 205;
    primary.buttons[0] = 44;
    primary.buttons[1] = 45;
    primary.buttons[2] = 46;
    primary.buttons[3] = 30;
    primary.buttons[4] = 31;
    primary.buttons[5] = 32;
    primary.buttons[6] = 16;

    memset(&secondary, 0, sizeof(secondary));
    std::deque<unsigned short> *decks = decks_1ac;
    secondary.source_id = 0;
    secondary.buttons[0] = 0;
    secondary.buttons[1] = 1;
    secondary.buttons[2] = 2;
    secondary.buttons[3] = 3;
    secondary.buttons[4] = 4;
    secondary.buttons[5] = 5;
    secondary.buttons[6] = 6;

    flag_13c = 0;
    flag_1a8 = 0xff;

    for (int i = 0; i < 20; ++i)
        decks[i].clear();
    for (int i = 0; i < 15; ++i)
        initialize_default_deck(&decks[i], i);
}


}
