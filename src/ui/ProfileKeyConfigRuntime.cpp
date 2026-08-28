#include "ui/ProfileSubmenus.hpp"
#include "ui/MenuSelect.hpp"
#include "ui/Title.hpp"
#include "input/InputManager.hpp"
#include "input/InputSelection.hpp"

#include <string.h>
#include <cstdlib>

namespace th105 {

signed char __cdecl get_active_input_source_43b050();
struct CTileRenderView { void render(float x, float y, int column, int row); };
struct TitleResourceManagerValueView {
    TextureHandleResult load_texture_value(
        const char *path, unsigned int *width, unsigned int *height);
};
extern TitleResourceManagerValueView g_title_resource_manager_value;


struct ProfileKeyConfigDesignVirtualView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void load(const char *path);
};


extern "C" CInputManager *g_active_menu_input;
bool __cdecl is_menu_initial_press(
    unsigned char key, bool modifier0, bool modifier1, bool modifier2);
void __cdecl dispatch_indexed_event(unsigned index);

struct ProfileKeyConfigCaptureView {
    bool capture_key_input_44b540();
};

struct PlayerSlotKeyConfigSaveView {
    void save_profile(const char *path);
    void select_deck(unsigned char source);
};

void __cdecl rebind_selected_input_43b640(int slot, signed char prefer_other);

struct PlayerSlotKeyConfigView {
    unsigned char reserved_000[0x13c];
    unsigned char alternate_13c;
    unsigned char reserved_13d[3];
    unsigned char keyboard_140[0x34];
    unsigned char gamepad_174[0x34];
};

CProfileKeyConfig::CProfileKeyConfig(PlayerSlotRecord *player, int input_slot)
    : texture_3c(0), texture_e4(0)
{
    player_04 = player;
    input_slot_32c = input_slot;
    signed char source = get_active_input_source_43b050();
    PlayerSlotKeyConfigView *slot =
        reinterpret_cast<PlayerSlotKeyConfigView *>(player_04);

    if (source == -1) {
        memcpy(&character_2ec, slot->keyboard_140, 0x34);
    } else {
        memcpy(&character_2ec, slot->gamepad_174, 0x34);
        character_2ec = source;
    }

    alternate_320 = slot->alternate_13c;
    state_328 = 1;
    count_324 = 0;

    reinterpret_cast<ProfileKeyConfigDesignVirtualView *>(&design_08)->load(
        "data/profile/keyconfig/keyconfig.dat");
    design_08.bind_object_alt(&objects_18c[0], 100);
    design_08.bind_object_alt(&objects_18c[1], 103);
    objects_18c[0]->enabled = true;
    objects_18c[1]->enabled = true;
    design_08.bind_object_alt(&objects_18c[2], 120);
    design_08.bind_object_alt(&objects_18c[3], 121);
    objects_18c[2]->enabled = true;
    objects_18c[3]->enabled = true;

    texture_3c = g_title_resource_manager_value.load_texture_value(
        "data/profile/keyconfig/010_KeyConfig_moji1.bmp", 0, 0).value;
    tile_40.set_texture(texture_3c, 0, 0, 64, 16);
    texture_e4 = g_title_resource_manager_value.load_texture_value(
        "data/profile/keyconfig/011_KeyConfig_moji2.bmp", 0, 0).value;
    tile_e8.set_texture(texture_e4, 0, 0, 64, 16);

    if (alternate_320) {
        objects_18c[2]->set_color(0xff808080u);
        objects_18c[3]->set_color(0xffffffffu);
    } else {
        objects_18c[2]->set_color(0xffffffffu);
        objects_18c[3]->set_color(0xff808080u);
    }

    player_04->set_profile_color(160, 160, 255);
    guides_19c[0].load(16);
    guides_19c[1].load(17);
    guides_19c[0].visible = true;
}

void CProfileKeyConfig::render()
{
    float cursor_index = static_cast<float>(count_324);
    float cursor_y = static_cast<float>(
        objects_18c[1]->y + static_cast<double>(cursor_index) * 20.0);
    float cursor_x = static_cast<float>(
        objects_18c[1]->x + static_cast<double>(cursor_index) * 16.0);
    render_cursor(cursor_x, cursor_y, 512.0f);

    design_08.render();

    float x = static_cast<float>(objects_18c[1]->x + 176.0);
    float y = objects_18c[1]->y;
    if (character_2ec == -1) {
        for (int i = 0; i < 11; ++i) {
            if (keys_2f0[i] >= 0) {
                reinterpret_cast<CTileRenderView *>(&tile_40)->render(
                    x, y, keys_2f0[i] % 8, keys_2f0[i] / 8);
            }
            x = static_cast<float>(x + 16.0);
            y = static_cast<float>(y + 20.0);
        }
    } else if (character_2ec >= 0) {
        for (int i = 0; i < 4; ++i) {
            reinterpret_cast<CTileRenderView *>(&tile_e8)->render(x, y, i, 0);
            x = static_cast<float>(x + 16.0);
            y = static_cast<float>(y + 20.0);
        }
        for (int i = 4; i < 11; ++i) {
            if (keys_2f0[i] >= 0) {
                reinterpret_cast<CTileRenderView *>(&tile_e8)->render(
                    x, y, keys_2f0[i] % 4, keys_2f0[i] / 4 + 1);
            }
            x = static_cast<float>(x + 16.0);
            y = static_cast<float>(y + 20.0);
        }
    }

    render_profile_player_slot(player_04, 0.0f, 0.0f);
    guides_19c[0].render();
    guides_19c[1].render();
}

bool CProfileKeyConfig::update()
{
    guides_19c[0].update();
    guides_19c[1].update();

    if (is_menu_initial_press(1, false, false, false)) {
        dispatch_indexed_event(0x29);
        return false;
    }

    if (!reinterpret_cast<ProfileKeyConfigCaptureView *>(this)
             ->capture_key_input_44b540()) {
        if (std::abs(g_active_menu_input->hold.horizontal) == 1) {
            dispatch_indexed_event(0x27);
            alternate_320 = 1 - alternate_320;
            if (alternate_320) {
                objects_18c[2]->set_color(0xff808080u);
                objects_18c[3]->set_color(0xffffffffu);
            } else {
                objects_18c[2]->set_color(0xffffffffu);
                objects_18c[3]->set_color(0xff808080u);
            }
        }

        if (g_active_menu_input->hold.buttons[0] == 1) {
            guides_19c[0].visible = false;
            guides_19c[1].visible = true;
            dispatch_indexed_event(0x28);

            if (character_2ec == -1)
                memcpy(
                    reinterpret_cast<PlayerSlotKeyConfigView *>(player_04)
                        ->keyboard_140,
                    &character_2ec,
                    0x34);
            else
                memcpy(
                    reinterpret_cast<PlayerSlotKeyConfigView *>(player_04)
                        ->gamepad_174,
                    &character_2ec,
                    0x34);
            reinterpret_cast<PlayerSlotKeyConfigView *>(player_04)
                ->alternate_13c = alternate_320;

            reinterpret_cast<PlayerSlotKeyConfigSaveView *>(player_04)
                ->select_deck(static_cast<unsigned char>(character_2ec));
            reinterpret_cast<PlayerSlotKeyConfigSaveView *>(player_04)
                ->save_profile(0);

            if (input_slot_32c == 0) {
                invalidate_selected_input(0);
                rebind_selected_input_43b640(input_slot_32c, 0);
            } else if (input_slot_32c == 1) {
                invalidate_selected_input(1);
                rebind_selected_input_43b640(input_slot_32c, 1);
            }
            return false;
        }
    }

    return true;
}
} // namespace th105
