#include "ui/ProfileDeckEdit.hpp"
#include "ui/UiPrimitives.hpp"
#include "ui/ProfileUiInfrastructure.hpp"
#include "ui/ProfileMenu.hpp"
#include <map>
#include <deque>

namespace th105 {
extern unsigned g_spell_texture_upload_state;
extern unsigned g_spell_texture_load_state;
typedef std::map<int, SpellRecordView> DeckRenderSpellMap;
typedef std::deque<DeckRenderSpellMap::iterator> DeckRenderIteratorDeque;
struct DeckRenderAtView { DeckRenderSpellMap::iterator &at(unsigned index); };
struct DeckTypedSprite94 {
    const unsigned *vtable;
    unsigned value_04;
    SpriteVertex28 vertices_08[4];
    float texture_width_78, texture_height_7c;
    float pivot_x_80, pivot_y_84, scale_x_88, scale_y_8c, angle_90;
    DeckTypedSprite94() : value_04(0) { vtable = select_sprite_vtable_anchor; }
    ~DeckTypedSprite94() { vtable = title_color_vtable_anchor; }
};
typedef char deck_typed_sprite_size[sizeof(DeckTypedSprite94) == 0x94 ? 1 : -1];
struct DeckFooterView { void render_profile_menu_footer(); };
template<class T> static T &deck_render_field(void *object, unsigned offset)
{
    return *reinterpret_cast<T *>(static_cast<unsigned char *>(object) + offset);
}
#define DECK_AT(index) reinterpret_cast<DeckRenderAtView *>(&filtered_3cc)->at(index)
#define DECK_INDEX(index) reinterpret_cast<DeckRenderIteratorDeque &>(filtered_3cc)[index]
#define SPRITE_CALL reinterpret_cast<ProfileSpriteView *>(&sprite)

void CProfileDeckEdit::render()
{
    DeckTypedSprite94 sprite;
    deck_render_field<float>(objects_44[0], 8) = static_cast<float>(
        (cursor_3e4.selection - cursor_3e4.window_start) * 16.0);
    objects_44[18]->enabled = total_3e1 != 20;
    objects_44[19]->enabled = !objects_44[18]->enabled;
    deck_render_field<UiDesignObject *>(this, 0x0C)->render(-64.0f, 0.0f);
    render_cursor(static_cast<float>(objects_44[0]->x + 8.0),
                  static_cast<float>(deck_render_field<float>(objects_44[0], 8) + objects_44[0]->y),
                  384.0f);
    float grid_x = static_cast<float>(objects_44[2]->x + 304.0 - 128.0);
    float grid_y = static_cast<float>(objects_44[2]->y + 64.0 + 2.0);
    ProfileDeckCountMap::iterator count;
    count = counts_3c0.begin();
    int pending = 0;
    int drawn = 0;
    while ((count != counts_3c0.end() || pending > 0) && drawn < 40) {
        if (pending == 0) {
            pending = count->second;
            if (pending != 0) {
                SPRITE_CALL->set_texture(
                    reinterpret_cast<unsigned>(reinterpret_cast<SpellDataOwner *>(&resources_398)->find_local_then_common_spell_record(count->first)->optional_resource_44),
                    0, 0, g_spell_texture_load_state, g_spell_texture_upload_state);
                deck_render_field<float>(&sprite, 0x88) = 0.5f;
                deck_render_field<float>(&sprite, 0x8C) = 0.5f;
            }
            ++count;
            if (pending == 0)
                continue;
        }
        float x = static_cast<float>(static_cast<float>(drawn % 10) *
            static_cast<float>((g_spell_texture_load_state >> 1) + 4) + grid_x);
        float y = static_cast<float>(static_cast<float>((g_spell_texture_upload_state >> 1) + 6) *
            (drawn / 10) + grid_y + 128.0 + 2.0);
        if (drawn >= 33) {
            unsigned color = (static_cast<unsigned>(39 - drawn) * 0x28000000u) | 0x00FFFFFFu;
            CSpriteBase &base = *reinterpret_cast<CSpriteBase *>(&sprite);
            base.vertices_08[0].color = base.vertices_08[1].color =
                base.vertices_08[2].color = base.vertices_08[3].color = color;
        }
        SPRITE_CALL->render(x, y);
        ++drawn;
        --pending;
    }
    design_10.render();
    if (common_tree_3bc == 0)
        _invalid_parameter_noinfo();
    for (int row = 0; row < 15 && row + cursor_3e4.window_start < static_cast<int>(filtered_3cc.size()); ++row) {
        float x = static_cast<float>(objects_44[0]->x + 16.0);
        float y = static_cast<float>(16.0 * row + objects_44[0]->y);
        int available = available_count_for_index_448df0(cursor_3e4.window_start + row);
        if (available != 0) {
            int width = static_cast<int>(DECK_AT(cursor_3e4.window_start + row)->second.name_00.size()) * 8 < 200
                ? static_cast<int>(DECK_AT(cursor_3e4.window_start + row)->second.name_00.size()) * 8 : 200;
            SPRITE_CALL->set_texture(
                reinterpret_cast<unsigned>(DECK_AT(cursor_3e4.window_start + row)->second.batch_resource_40),
                0, DECK_AT(cursor_3e4.window_start + row)->second.value_48, width, 16);
        } else {
            SPRITE_CALL->set_texture(texture_258, 0, 160, 160, 16);
        }
        SPRITE_CALL->render(x, y);
        // The native clear is at ESP+0x20 while an index argument is pushed.
        int owned = 0;
        count = counts_3c0.find(
            static_cast<short>(static_cast<unsigned short>(DECK_AT(cursor_3e4.window_start + row)->first)));
        if (count != counts_3c0.end())
            owned = count->second;
        const int highlight = cursor_3e4.window_start + row == cursor_3e4.selection && flags_40c[3] != 0;
        reinterpret_cast<ProfileTileView *>(&tile_25c)->render(
            static_cast<float>(objects_44[1]->x + 40.0 + 21.0), y,
            highlight,
            available % 10);
        reinterpret_cast<ProfileTileView *>(&tile_25c)->render(
            static_cast<float>(objects_44[1]->x + 40.0 + 7.0), y,
            (cursor_3e4.window_start + row == cursor_3e4.selection && flags_40c[3] != 0) + 2,
            available / 10);
        reinterpret_cast<ProfileTileView *>(&tile_25c)->render(
            static_cast<float>(objects_44[1]->x + 40.0), y,
            cursor_3e4.window_start + row == cursor_3e4.selection && flags_40c[3] != 0,
            owned);
    }
    if (available_count_for_index_448df0(cursor_3e4.selection) != 0) {
        int width = static_cast<int>(DECK_INDEX(cursor_3e4.selection)->second.name_00.size()) * 8 < 272
            ? static_cast<int>(DECK_AT(cursor_3e4.selection)->second.name_00.size()) * 8 : 272;
        SPRITE_CALL->set_texture(
            reinterpret_cast<unsigned>(DECK_INDEX(cursor_3e4.selection)->second.batch_resource_40),
            0, DECK_INDEX(cursor_3e4.selection)->second.value_48, width, 16);
        SPRITE_CALL->render(static_cast<float>(grid_x + 56.0), static_cast<float>(grid_y + 4.0));
        if (DECK_INDEX(cursor_3e4.selection)->second.optional_resource_44 != 0)
            reinterpret_cast<UiSprite94 *>(&sprite_1c4)->render(grid_x, grid_y);
        reinterpret_cast<UiSprite94 *>(&sprite_98)->render(grid_x, grid_y);
    }
    reinterpret_cast<UiSprite94 *>(&sprite_304)->render(0.0f, 0.0f);
    render_profile_player_slot(player_04, 0.0f, 0.0f);
    reinterpret_cast<DeckFooterView *>(this)->render_profile_menu_footer();
    for (int index = 0; index < 4; ++index)
        guides_410[index].render();
}
#undef DECK_AT
#undef DECK_INDEX
#undef SPRITE_CALL
} // namespace th105
