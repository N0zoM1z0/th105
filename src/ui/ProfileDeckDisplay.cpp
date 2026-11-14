// Complete JP1.06a selected-card refresh; source remains nonexact440/439.
// Actual global nine-slot CSprite; no manually loaded vtable.
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"
#include "battle/SpellData.hpp"
#include "battle/EffectSprite.hpp"
#include "assets/TextFontOwner.hpp"
namespace th105 {
extern TextFontOwner194 g_profile_deck_font;
extern unsigned g_spell_texture_load_state;
extern unsigned g_spell_texture_upload_state;


// Only accessed member offsets are represented; no objects of this view are made.
struct ProfileDeckDisplayView {
 unsigned char prefix_00[0x44];
 UiDesignObject *objects_44[20];
 DesignTextureHandle texture_94;
 CSprite sprite_98;
 unsigned field_12c;
 CSprite sprite_130, sprite_1c4;
 unsigned char gap_258[0x3e0-0x258];
 unsigned char color_3e0;
 void show_record(SpellRecordView *record);
};
void ProfileDeckDisplayView::show_record(SpellRecordView *record)
{
    if (record == 0) {
        objects_44[17]->enabled = false;
        objects_44[5]->enabled = false;
        objects_44[6]->enabled = false;
        objects_44[12]->enabled = false;
        objects_44[13]->enabled = false;
        objects_44[14]->enabled = false;
        objects_44[15]->enabled = false;
        objects_44[16]->enabled = false;
        return;
    }

    g_title_resource_manager.release_title_resource_handle(texture_94);
    if (record->card_texture_handle_44 != 0) {
        sprite_1c4.set_texture_options(
            record->card_texture_handle_44,
            0,
            0,
            g_spell_texture_load_state,
            g_spell_texture_upload_state,
            -5,
            -5);
    }

    texture_94 = g_title_resource_manager.create_text_texture(
        record->description_20.c_str(), &g_profile_deck_font, 220, 256, 0, 0).value;
    sprite_98.set_texture_options(
        texture_94, 0, 0, 220, 256, -70, -26);

    color_3e0 = static_cast<unsigned char>(record->value_1e.value);
    if (record->selector_1c == 1) {
        objects_44[12]->enabled = color_3e0 == 0;
        objects_44[13]->enabled = color_3e0 == 1;
        objects_44[14]->enabled = color_3e0 == 2;
        objects_44[15]->enabled = color_3e0 == 3;
        objects_44[16]->enabled = color_3e0 == 4;
        objects_44[5]->enabled = false;
        objects_44[6]->enabled = false;
        color_3e0 = 1;
        objects_44[17]->enabled = false;
    } else {
        objects_44[17]->enabled = true;
        if (record->selector_1c == 2) {
            objects_44[5]->enabled = false;
            objects_44[6]->enabled = true;
        } else {
            objects_44[5]->enabled = true;
            objects_44[6]->enabled = false;
        }
        objects_44[12]->enabled = false;
        objects_44[13]->enabled = false;
        objects_44[14]->enabled = false;
        objects_44[15]->enabled = false;
        objects_44[16]->enabled = false;
    }
}
}
