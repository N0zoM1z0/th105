#include "ProfileDeckEdit.hpp"
#include "input/InputManager.hpp"
#include <map>

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(int, int, int, int);

namespace th105 {
typedef std::map<int, SpellRecordView> DeckUpdateSpellMap;
struct DeckUpdateDequeAt { DeckUpdateSpellMap::iterator &at(unsigned index); };
// The target explicitly supplies ECX for both no-stack-argument menu calls.
// Their bodies do not read it; original source-level static/member identity
// remains unknown. These declarations preserve this caller ABI, not a new
// implementation or ownership claim for those helpers.
// Declaration-only call receivers; no objects of these partial views are made.
struct DeckUpdateMenuView {
    int update_confirmation_43f870();
    int update_message_43f6e0();
    void select_filter_449e90(unsigned char category);
    void show_spell_record_448b40(SpellRecordView *record);
};
struct DeckUpdatePlayerView {
    std::deque<unsigned short> *copy_deck(std::deque<unsigned short> *destination, int character);
    void save_to_profile(const char *path);
};
#define SPELL_AT(index) reinterpret_cast<DeckUpdateDequeAt *>(&filtered_3cc)->at(index)
#define MENU_VIEW reinterpret_cast<DeckUpdateMenuView *>(this)
#define PLAYER_VIEW reinterpret_cast<DeckUpdatePlayerView *>(player_04)

bool CProfileDeckEdit::update()
{
    for (int i = 0; i < 4; ++i) {
        guides_410[i].update();
        guides_410[i].visible = false;
    }
    if (flags_40c[1]) {
        guides_410[3].visible = true;
        if (MENU_VIEW->update_confirmation_43f870())
            flags_40c[1] = 0;
        return true;
    }
    if (flags_40c[2]) {
        guides_410[2].visible = true;
        switch (MENU_VIEW->update_message_43f6e0()) {
        case 2:
            flags_40c[2] = 0;
            return true;
        case 3:
            if (total_3e1 != 20) {
                show_profile_result("\x83\x66\x83\x62\x83\x4c\x82\xaa\x32\x30\x96\x87\x82\xc5\x82\xcd\x82\xa0\x82\xe8\x82\xdc\x82\xb9\x82\xf1");
                flags_40c[1] = 1;
                flags_40c[2] = 0;
                return true;
            }
            export_deck_counts(reinterpret_cast<ProfileDeckKeyDeque *>(
                PLAYER_VIEW->copy_deck(0, character_08)));
            PLAYER_VIEW->save_to_profile(0);
            return false;
        case 4:
            return false;
        default:
            return true;
        }
    }
    ProfileDeckCountMap::iterator count = counts_3c0.find(
        static_cast<short>(static_cast<unsigned short>(SPELL_AT(cursor_3e4.selection)->first)));
    if (g_active_menu_input->hold.buttons[0] == 1) {
        if (available_count_for_index_448df0(cursor_3e4.selection)) {
            dispatch_indexed_event(40);
            flags_40c[3] = !flags_40c[3];
        } else if (count != counts_3c0.end() && count->second) {
            dispatch_indexed_event(40);
            flags_40c[3] = !flags_40c[3];
        }
    } else if (g_active_menu_input->hold.buttons[1] == 1 || is_menu_initial_press(1, 0, 0, 0)) {
        dispatch_indexed_event(41);
        if (flags_40c[3])
            flags_40c[3] = 0;
        else {
            show_profile_message("\x8d\x5c\x92\x7a\x82\xf0\x8f\x49\x97\xb9\x82\xb5\x82\xdc\x82\xb7\x81\x42\x95\xd2\x8f\x57\x93\xe0\x97\x65\x82\xf0\x83\x5a\x81\x5b\x83\x75\x82\xb5\x82\xdc\x82\xb7\x82\xa9\x81\x48", false);
            flags_40c[2] = 1;
        }
    }
    if (flags_40c[3]) {
        guides_410[1].visible = true;
        if (g_active_menu_input->hold.horizontal == 1 || g_active_menu_input->hold.vertical == -1) {
            dispatch_indexed_event(39);
            if (count == counts_3c0.end()) {
                counts_3c0.insert(std::make_pair(
                    static_cast<short>(SPELL_AT(cursor_3e4.selection)->first), static_cast<signed char>(0)));
                count = counts_3c0.find(static_cast<short>(static_cast<unsigned short>(SPELL_AT(cursor_3e4.selection)->first)));
            }
            if (count->second < available_count_for_index_448df0(cursor_3e4.selection) && count->second < 4) {
                ++count->second;
                ++total_3e1;
            }
        } else if (g_active_menu_input->hold.horizontal == -1 || g_active_menu_input->hold.vertical == 1) {
            dispatch_indexed_event(39);
            if (count != counts_3c0.end() && count->second > 0) {
                --count->second;
                --total_3e1;
            }
        }
    } else {
        if (is_menu_initial_press(59, 0, 0, 0)) {
            for (ProfileDeckCountMap::iterator item = counts_3c0.begin(); item != counts_3c0.end(); ++item)
                item->second = 0;
            total_3e1 = 0;
            dispatch_indexed_event(41);
        }
        guides_410[0].visible = true;
        if (cursor_3e4.update()) {
            if (available_count_for_index_448df0(cursor_3e4.selection))
                MENU_VIEW->show_spell_record_448b40(&SPELL_AT(cursor_3e4.selection)->second);
            else {
                objects_44[17]->enabled = false;
                objects_44[5]->enabled = false;
                objects_44[6]->enabled = false;
                objects_44[12]->enabled = false;
                objects_44[13]->enabled = false;
                objects_44[14]->enabled = false;
                objects_44[15]->enabled = false;
                objects_44[16]->enabled = false;
            }
            dispatch_indexed_event(39);
        }
        if (cursor_3f8.update()) {
            MENU_VIEW->select_filter_449e90(static_cast<unsigned char>(cursor_3f8.selection));
            cursor_3f8.selection = static_cast<signed char>(flags_40c[0]);
            dispatch_indexed_event(39);
        }
    }
    return true;
}
} // namespace th105
