#include "ScenarioCommandUpdate.hpp"
#include "ScenarioData.hpp"
#include "BattleController.hpp"
#include "BattleSetup.hpp"
#include "ui/Title.hpp"

#include <string.h>
#include <mbstring.h>

extern "C" __declspec(dllimport) void *__stdcall CreateEventA(
    void *, int, int, const char *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);

namespace th105 {

extern int g_pair_state;
extern BattleSlotState *scenario_slot_state;
void __cdecl play_bgm(const char *);
void __cdecl stop_bgm();
void __cdecl set_bgm_volume(int, int);
void __cdecl scenario_play_sound(const char *, int, unsigned char);

struct ScenarioInputView {
    unsigned char prefix_00[0x40];
    int pressed_40;
    unsigned char gap_44[4];
    int held_48;
};

class ScenarioCharacterView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void prepare_44();
    virtual void slot_48();
    virtual unsigned char action_4c(int);
    void reset_for_roster(ScenarioCharacterView *);
    void dispatch_wave(unsigned int);
};

struct ScenarioSlotSetupView {
    unsigned char finish(int slot);
};

struct ScenarioScriptPopView {
    CCommandBase *next_command();
};

typedef std::map<std::string, ScenarioTextEntryDC> ScenarioTextMap;
struct ScenarioTextFindView {
    ScenarioTextMap::iterator find(const std::string &);
};
struct ScenarioTextIteratorView {
    void increment();
};
struct ScenarioTextAdvanceView {
    int update_dynamic_state();
};
struct ScenarioUpdateOperations {
    void update_list(std::list<ScenarioRenderEntry9C> *);
    void rebuild_text(std::string *);
    void install_character(std::string, std::string, signed char, int, int,
                           unsigned char, unsigned char, unsigned char);
};
struct ScenarioEffectOperations {
    void stage_music(int, int);
    SystemEffectObject *spawn(const char *, unsigned short, float, float);
};

struct ScenarioResultStartView {
    void start();
};

struct ScenarioEventHandle {
    void *handle;
    ScenarioEventHandle() : handle(CreateEventA(0, 0, 0, 0)) {}
    ~ScenarioEventHandle() { CloseHandle(handle); }
};

static ScenarioCharacterView *scenario_character(int slot)
{
    return reinterpret_cast<ScenarioCharacterView *>(
        scenario_slot_state->get_slot_character(slot));
}

typedef char ScenarioShortDeque_size[sizeof(std::deque<short>) == 0x14 ? 1 : -1];

// The checked deque's real front read and pop are inlined at two native sites.
static __forceinline unsigned short scenario_peek_inline()
{
    BattleInputGate *input = get_player2_input();
    input->lock_124.enter();
    std::deque<short> &queue = *reinterpret_cast<std::deque<short> *>(
        &input->input_104->controls_3c);
    unsigned short word = queue.empty() ? 0 :
        static_cast<unsigned short>(queue.front());
    input->lock_124.leave();
    return word;
}

static __forceinline void scenario_pop_inline()
{
    BattleInputGate *input = get_player2_input();
    input->lock_124.enter();
    std::deque<short> &queue = *reinterpret_cast<std::deque<short> *>(
        &input->input_104->controls_3c);
    if (!queue.empty()) {
        queue.front();
        queue.pop_front();
    }
    input->lock_124.leave();
}

signed char ScenarioCommandUpdateView::update()
{
    CScenarioData &s = *reinterpret_cast<CScenarioData *>(this);
    ScenarioUpdateOperations *operations =
        reinterpret_cast<ScenarioUpdateOperations *>(this);
    s.field_514 = 0;
    s.system_effects_004.update_and_prune(&SystemEffectObjectBase::update_state);
    operations->update_list(&s.render_entries_338);
    operations->update_list(&s.render_entries_344);
    ScenarioTextMap::iterator it = s.text_entries_32c.begin();
    while (it != s.text_entries_32c.end()) {
        reinterpret_cast<ScenarioTextAdvanceView *>(&it->second)
            ->update_dynamic_state();
        reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
    }

    if (s.state_50d) {
        if (s.field_324 < 40)
            s.field_324 += 4;
        else
            operations->update_list(&s.render_entries_350);
    } else if (s.render_entries_350.empty()) {
        if (s.field_324 > 0)
            s.field_324 -= 4;
    } else {
        for (std::list<ScenarioRenderEntry9C>::iterator p =
                 s.render_entries_350.begin();
             p != s.render_entries_350.end(); ++p)
            p->reserved_098[1] = -20;
        operations->update_list(&s.render_entries_350);
    }

    it = s.text_entries_32c.begin();
    while (it != s.text_entries_32c.end()) {
        if (it->second.flags_0d4[4]) {
            if (get_session_setup_option() == 2) {
                if (scenario_peek_inline() !=
                    static_cast<unsigned short>(g_pair_state))
                    return 1;
                scenario_pop_inline();
                if (!scenario_slot_state->is_slot_active(
                        it->second.flags_0d4[0])) {
                    ScenarioEventHandle event;
                    while (!reinterpret_cast<ScenarioSlotSetupView *>(
                                scenario_slot_state)->finish(
                                    it->second.flags_0d4[0]))
                        WaitForSingleObject(event.handle, 16);
                    ScenarioCharacterView *fighter =
                        scenario_character(it->second.flags_0d4[0]);
                    fighter->prepare_44();
                    fighter->reset_for_roster(scenario_character(0));
                }
            } else if (!scenario_slot_state->is_slot_active(
                           it->second.flags_0d4[0])) {
                if (!reinterpret_cast<ScenarioSlotSetupView *>(
                         scenario_slot_state)->finish(
                             it->second.flags_0d4[0]))
                    return 1;
                ScenarioCharacterView *fighter =
                    scenario_character(it->second.flags_0d4[0]);
                fighter->prepare_44();
                fighter->reset_for_roster(scenario_character(0));
            }
            if (get_session_setup_option() == 1)
                get_player2_input()->queue_control_word(
                    static_cast<unsigned short>(g_pair_state));
            it->second.flags_0d4[4] = scenario_character(
                it->second.flags_0d4[0])->action_4c(it->second.values_0b8[6]);
            if (!it->second.flags_0d4[4])
                s.state_50c = 0;
            return 1;
        }
        reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
    }

    if (s.result_resources_390.update()) {
        if (get_session_setup_option() == 2) {
            if (scenario_peek_inline() !=
                static_cast<unsigned short>(g_pair_state))
                return 1;
            scenario_pop_inline();
            s.result_resources_390.enter_phase_three();
        } else {
            ScenarioInputView *input =
                reinterpret_cast<ScenarioInputView *>(s.scenario_id_064);
            if (input->pressed_40 == 1 || input->held_48 != 0) {
                if (get_session_setup_option() == 1)
                    get_player2_input()->queue_control_word(
                        static_cast<unsigned short>(g_pair_state));
                s.result_resources_390.enter_phase_three();
            }
        }
        return 1;
    }
    if (s.field_518 != 0) {
        --s.field_518;
        return 1;
    }
    if (s.state_50f) {
        it = s.text_entries_32c.begin();
        while (it != s.text_entries_32c.end()) {
            if (it->second.flags_0d4[5])
                return -1;
            reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
        }
        s.reset_runtime_state();
        return 0;
    }
    if (s.state_511) {
        if (s.field_51c != 0 && --s.field_51c == 0)
            s.state_50c = 0;
    } else if (s.state_50c) {
        if (s.field_51c != 0) {
            if (--s.field_51c == 0)
                s.state_50c = 0;
            return 1;
        }
        if (get_session_setup_option() == 2) {
            unsigned short word;
            if (get_player2_input()->peek_front_control_word(&word) !=
                static_cast<unsigned short>(g_pair_state))
                return 1;
            BattleInputGate *input = get_player2_input();
            input->lock_124.enter();
            input->input_104->pop_control_word(&word);
            input->lock_124.leave();
        } else {
            ScenarioInputView *input =
                reinterpret_cast<ScenarioInputView *>(s.scenario_id_064);
            if (input->pressed_40 != 1 && input->held_48 == 0)
                return 1;
            if (get_session_setup_option() == 1)
                get_player2_input()->queue_control_word(
                    static_cast<unsigned short>(g_pair_state));
        }
        s.field_51c = 0;
        s.state_50c = 0;
    }
    if (s.state_50c)
        return 1;

    do {
        CCommandBase *command =
            reinterpret_cast<ScenarioScriptPopView *>(&s.script_35c)
                ->next_command();
        if (!command)
            return 0;
        int command_id = static_cast<CCommand0 *>(command)->command_id_04;
        switch (command_id) {
        case 0:
            if (static_cast<TCommand1<std::string> *>(command)->arg0_08
                    .compare("Start") == 0)
                return 1;
            break;
        case 1: {
            if (s.state_510) {
                s.string_4b8 = s.string_4d4;
                it = s.text_entries_32c.begin();
                while (it != s.text_entries_32c.end()) {
                    it->second.flags_0d4[3] = 0;
                    reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
                }
                s.trim_render_entries_and_begin_fade_455cd0();
                s.state_510 = 0;
            }
            it = reinterpret_cast<ScenarioTextFindView *>(&s.text_entries_32c)
                     ->find(s.string_4f0);
            if (it != s.text_entries_32c.end())
                it->second.flags_0d4[3] = 1;
            TCommand1<std::string> *text =
                static_cast<TCommand1<std::string> *>(command);
            s.state_50d = 1;
            s.string_4b8 += text->arg0_08;
            const char *at = reinterpret_cast<const char *>(_mbsrchr(
                reinterpret_cast<const unsigned char *>(text->arg0_08.c_str()), '@'));
            const char *slash = reinterpret_cast<const char *>(_mbsrchr(
                reinterpret_cast<const unsigned char *>(text->arg0_08.c_str()), '\\'));
            bool wait = at && at - text->arg0_08.c_str() + 1 ==
                                  text->arg0_08.size();
            bool continuation = slash && slash - text->arg0_08.c_str() + 1 ==
                                             text->arg0_08.size();
            if (wait) {
                s.string_4b8.erase(s.string_4b8.end() - 1, s.string_4b8.end());
                operations->rebuild_text(&s.string_4b8);
                s.string_4b8.append("<br>", 4);
                s.state_50c = 1;
            } else if (continuation) {
                s.string_4b8.erase(s.string_4b8.end() - 1, s.string_4b8.end());
                operations->rebuild_text(&s.string_4b8);
                s.state_510 = 1;
                s.state_50c = 1;
            } else {
                s.string_4b8.append("<br>", 4);
            }
            break;
        }
        case 2: {
            CComCharacter *c = static_cast<CComCharacter *>(command);
            operations->install_character(c->name_08, c->name_08,
                c->value_2c, c->value_24, c->value_28,
                c->color_2d[0], c->color_2d[1], c->color_2d[2]);
            break;
        }
        case 3: {
            typedef TCommand2<std::string, std::string> StandCommand;
            StandCommand *c = static_cast<StandCommand *>(command);
            it = reinterpret_cast<ScenarioTextFindView *>(&s.text_entries_32c)
                     ->find(c->arg0_08);
            if (it != s.text_entries_32c.end()) {
                std::string path;
                if (c->arg1.empty()) {
                    it->second.flags_0d4[2] = 0;
                } else {
                    path = "data/character/" + it->first + "/stand/" +
                           c->arg1 + ".bmp";
                    g_title_resource_manager.release_title_resource_handle(
                        it->second.resource_handle_000);
                    unsigned int width, height, handle;
                    g_title_resource_manager.load_texture(
                        &handle, path.c_str(), &width, &height);
                    it->second.resource_handle_000 = handle;
                    it->second.sprite_004.set_texture_options(
                        handle, 0, 0, width, height, width >> 1, height);
                    *reinterpret_cast<float *>(
                        it->second.sprite_004.reserved_08 + 0x80) =
                            static_cast<float>(it->second.flags_0d4[1]);
                    *reinterpret_cast<float *>(
                        it->second.sprite_004.reserved_08 + 0x84) = 1.0f;
                    it->second.flags_0d4[2] = 1;
                }
                s.set_effect_color_bytes(it->second.flags_0b4[1],
                    it->second.flags_0b4[2], it->second.flags_0b4[3]);
                s.string_4f0 = it->first;
            }
            break;
        }
        case 4: {
            TCommand2<std::string, int> *c =
                static_cast<TCommand2<std::string, int> *>(command);
            it = reinterpret_cast<ScenarioTextFindView *>(&s.text_entries_32c)
                     ->find(c->arg0_08);
            if (it != s.text_entries_32c.end()) {
                it->second.flags_0d4[4] = 1;
                it->second.values_0b8[6] = c->arg1;
                s.state_50c = 1;
                if (it->second.flags_0d4[0] != 0 &&
                    it->second.flags_0d4[0] != 1)
                    return 1;
                it->second.flags_0d4[4] = scenario_character(
                    it->second.flags_0d4[0])->action_4c(
                        it->second.values_0b8[6]);
                if (it->second.flags_0d4[4])
                    return 1;
                s.state_50c = 0;
            }
            break;
        }
        case 5: {
            typedef TCommand4<std::string, unsigned short, float, float> Effect;
            Effect *c = static_cast<Effect *>(command);
            reinterpret_cast<ScenarioEffectOperations *>(&s.system_effects_004)
                ->spawn(c->arg0_08.c_str(), c->arg1, c->arg2, c->arg3);
            break;
        }
        case 6: {
            TCommand2<int, int> *c = static_cast<TCommand2<int, int> *>(command);
            reinterpret_cast<ScenarioEffectOperations *>(&s.system_effects_004)
                ->stage_music(c->arg0_08, c->arg1);
            break;
        }
        case 7: {
            TCommand1<std::string> *c =
                static_cast<TCommand1<std::string> *>(command);
            for (std::list<ScenarioRenderEntry9C>::iterator p =
                     s.render_entries_338.begin();
                 p != s.render_entries_338.end(); ++p)
                p->reserved_098[1] = -5;
            if (!c->arg0_08.empty()) {
                {
                ScenarioRenderEntry9C entry;
                entry.resource_handle_000 = 0;
                entry.reserved_098[0] = 0;
                entry.reserved_098[1] = 5;
                s.render_entries_338.push_back(entry);
            }
                unsigned int width, height, handle;
                g_title_resource_manager.load_texture(
                    &handle, c->arg0_08.c_str(), &width, &height);
                s.render_entries_338.back().resource_handle_000 = handle;
                s.render_entries_338.back().sprite_004.set_texture(
                    s.render_entries_338.back().resource_handle_000,
                    0, 0, width, height);
                s.render_entries_338.back().sprite_004.set_color(0x00ffffff);
            }
            break;
        }
        case 8: {
            typedef TCommand3<std::string, int, int> Backdrop;
            Backdrop *c = static_cast<Backdrop *>(command);
            for (std::list<ScenarioRenderEntry9C>::iterator p =
                     s.render_entries_344.begin();
                 p != s.render_entries_344.end(); ++p)
                p->reserved_098[1] = -5;
            {
                ScenarioRenderEntry9C entry;
                entry.resource_handle_000 = 0;
                entry.reserved_098[0] = 0;
                entry.reserved_098[1] = 5;
                s.render_entries_344.push_back(entry);
            }
            if (c->arg0_08.compare(0, c->arg0_08.size(), "BLACK", 5) == 0) {
                s.render_entries_344.back().resource_handle_000 = 0;
                s.render_entries_344.back().sprite_004.set_texture(0, 0, 0, 640, 480);
                s.render_entries_344.back().sprite_004.set_color(0);
                s.field_520 = 4;
            } else if (!c->arg0_08.empty()) {
                unsigned int width, height, handle;
                g_title_resource_manager.load_texture(
                    &handle, c->arg0_08.c_str(), &width, &height);
                s.render_entries_344.back().resource_handle_000 = handle;
                s.render_entries_344.back().sprite_004.set_texture_options(
                    s.render_entries_344.back().resource_handle_000,
                    0, 0, width, height, -c->arg1, -c->arg2);
                s.render_entries_344.back().sprite_004.set_color(0x00ffffff);
            }
            break;
        }
        case 9:
            play_bgm(static_cast<TCommand1<std::string> *>(command)->arg0_08.c_str());
            break;
        case 10:
            stop_bgm();
            break;
        case 11: {
            TCommand2<int, int> *c = static_cast<TCommand2<int, int> *>(command);
            set_bgm_volume(c->arg0_08, c->arg1);
            break;
        }
        case 12: {
            TCommand2<std::string, int> *c =
                static_cast<TCommand2<std::string, int> *>(command);
            it = reinterpret_cast<ScenarioTextFindView *>(&s.text_entries_32c)
                     ->find(c->arg0_08);
            if (it == s.text_entries_32c.end())
                dispatch_indexed_event(c->arg1);
            else
                scenario_character(it->second.flags_0d4[0])->dispatch_wave(c->arg1);
            break;
        }
        case 13: {
            typedef TCommand3<std::string, int, bool> Sound;
            Sound *c = static_cast<Sound *>(command);
            scenario_play_sound(c->arg0_08.c_str(), c->arg1, c->arg2);
            break;
        }
        case 14:
            s.field_518 = static_cast<TCommand1<int> *>(command)->arg0_08;
            return 1;
        case 15:
            s.field_51c = static_cast<TCommand1<int> *>(command)->arg0_08;
            s.state_511 = 1;
            break;
        case 16: {
            typedef TCommand4<std::string, int, int, int> Font;
            Font *c = static_cast<Font *>(command);
            strcpy_s(s.effect_config_1fc.text_000, 256, c->arg0_08.c_str());
            s.effect_config_1fc.count_108 = c->arg1;
            s.effect_config_1fc.mode_118 = 0;
            s.effect_config_1fc.state_11c = c->arg2;
            s.effect_config_1fc.option_120 = 0;
            s.effect_config_1fc.option_124 = c->arg3;
            s.effect_owner_068.configure(&s.effect_config_1fc);
            break;
        }
        case 17:
            if (!s.string_4d4.empty())
                s.string_4b8.append("</color>");
            s.string_4d4.assign("<color ", 7);
            s.string_4d4 += static_cast<TCommand1<std::string> *>(command)->arg0_08;
            s.string_4d4.append(">", 1);
            s.string_4b8 += s.string_4d4;
            break;
        case 18: {
            typedef TCommand4<unsigned char, unsigned char, unsigned char,
                              unsigned char> Color;
            Color *c = static_cast<Color *>(command);
            if (c->arg0_08)
                s.field_328 = (static_cast<unsigned>(c->arg0_08) << 24) |
                    (static_cast<unsigned>(c->arg1) << 16) |
                    (static_cast<unsigned>(c->arg2) << 8) | c->arg3;
            else
                s.field_328 = 0;
            break;
        }
        case 19:
            if (static_cast<TCommand1<int> *>(command)->arg0_08 == 0) {
                it = s.text_entries_32c.begin();
                while (it != s.text_entries_32c.end()) {
                    it->second.flags_0d4[2] = 1;
                    reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
                }
            } else {
                it = s.text_entries_32c.begin();
                while (it != s.text_entries_32c.end()) {
                    it->second.flags_0d4[2] = 0;
                    reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
                }
                s.state_50d = 0;
            }
            break;
        case 20:
            reinterpret_cast<ScenarioResultStartView *>(&s.result_resources_390)
                ->start();
            return 1;
        case 21:
            s.field_514 = 1;
            s.state_511 = 1;
            return 1;
        case 22:
            it = s.text_entries_32c.begin();
            while (it != s.text_entries_32c.end()) {
                it->second.flags_0d4[2] = 0;
                reinterpret_cast<ScenarioTextIteratorView *>(&it)->increment();
            }
            s.state_50d = 0;
            s.state_50f = 1;
            return -1;
        }
    } while (!s.state_50c);
    return 1;
}

} // namespace th105
