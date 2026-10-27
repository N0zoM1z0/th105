#include "battle/BattleManagerVirtuals.hpp"
#include <windows.h>
#include <string>

namespace th105 {
const char *__cdecl character_key_to_name(int);
extern "C" void *__cdecl get_combined_menu_input();
int __cdecl selector_random_roll(int);

struct PhaseFiveOwnerView { void *prefix_00[3]; Fighter *fighters_0c[2]; };
struct PhaseFiveScenarioView {
    virtual void configure_input(void *);
    int load_page(const char *);
    void install_character(std::string, std::string, int, int, int,
                           unsigned char, unsigned char, unsigned char);
    unsigned char select_label(std::string);
};

void CBattleManager::run_transition_phase_5_4724e0()
{
    char label[32];
    char path[32];
    char formats[4][64];
    int loser_key;
    int i = 0;
    Fighter **cursor = reinterpret_cast<PhaseFiveOwnerView *>(this)->fighters_0c;
    for (; i < 2; ++i, ++cursor) {
        if ((*cursor)->terminal_finalize_4eb != 0) {
            int winner_key = reinterpret_cast<PhaseFiveOwnerView *>(this)->fighters_0c[i]->other_fighter_170->record_key_330;
            loser_key = reinterpret_cast<PhaseFiveOwnerView *>(this)->fighters_0c[i]->record_key_330;
            wsprintfA(path, "data/scenario/%s/win.txt", character_key_to_name(winner_key));
            PhaseFiveScenarioView *scenario = reinterpret_cast<PhaseFiveScenarioView *>(
                reinterpret_cast<unsigned char *>(this) + 0x8c);
            scenario->configure_input(get_combined_menu_input());
            scenario->load_page(path);
            scenario->install_character("win", character_key_to_name(winner_key),
                reinterpret_cast<PhaseFiveOwnerView *>(this)->fighters_0c[i]->other_fighter_170->player_index_334,160,0,160,160,255);
            scenario->install_character("lose", character_key_to_name(loser_key),
                reinterpret_cast<PhaseFiveOwnerView *>(this)->fighters_0c[i]->player_index_334,160,0,160,160,255);
            break;
        }
    }
    // The phase-5 caller is expected to supply a terminal fighter. Native code
    // also lacks a fallback key when neither of the two flags is set.
    wsprintfA(formats[0], "%sR%%d", character_key_to_name(loser_key));
    wsprintfA(formats[1], "%sU%%d", character_key_to_name(loser_key));
    wsprintfA(formats[2], "%s%%d", character_key_to_name(loser_key));
    wsprintfA(formats[3], "common%%d");
    int weights[4] = {1,6,3,10};
    int budget = 10;
    for (int group = 0; group < 4; ++group) {
        if (budget > 0 && selector_random_roll(budget) >= weights[group]) {
            budget -= weights[group];
            continue;
        }
        for (int count = 0; count < 128; ++count) {
            wsprintfA(label, formats[group], count);
            if (!reinterpret_cast<PhaseFiveScenarioView *>(
                    reinterpret_cast<unsigned char *>(this)+0x8c)->select_label(label)) {
                if (count != 0) {
                    wsprintfA(label, formats[group], selector_random_roll(count));
                    reinterpret_cast<PhaseFiveScenarioView *>(
                        reinterpret_cast<unsigned char *>(this)+0x8c)->select_label(label);
                    return;
                }
                break;
            }
        }
    }
}
}
