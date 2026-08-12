#pragma once

#include "ResourceHandleManager.hpp"

namespace th105 {

struct CompositeTextureUploadState {
    unsigned char unknown_000[0x11d];
    unsigned char render_via_intermediate_11d;
    unsigned char unknown_11e[0x22];
    void *surface_base_140;
    void *surface_cursor_144;
    unsigned surface_height_148;
    unsigned surface_width_14c;
    int surface_pitch_dwords_150;
    unsigned *active_color_154;
    unsigned *base_color_158;
    void *transient_list_15c;
    unsigned transient_count_160;
    unsigned fallback_color_164;

    // These source-facing members preserve the recovered ownership and call
    // graph.  The linked target lowers begin/end through ESI, draw/blend
    // through EAX, and passes the markup cursor through EDX.
    void begin_text_render();
    void end_text_render();
    void draw_text_glyph(unsigned character_code);
    void draw_text_accent_dot(int center_x, int top_y);
    int parse_text_markup(const char *cursor);
    unsigned char *blend_intermediate_text_surface(
        const unsigned *source,
        unsigned *destination);
    void render_composite_text(const char *text);
};

typedef char CompositeTextureUploadState_observed_size_must_be_0x168[
    sizeof(CompositeTextureUploadState) == 0x168 ? 1 : -1];

// Source-facing view of the texture manager used by spell-card parsing.  The
// shipped LTCG image lowers acquire/release and composite population to
// target-private EDI/EAX/ESI register contracts; these ordinary members retain
// the original ownership model for standalone source and linked-TU work.
struct SpellTexturePool : CHandleManager4 {
    ResourceSlotCell *acquire_4byte_slot(ResourceHandleToken *out_token);
    void release_token(ResourceHandleToken token);

    unsigned *load_texture(
        unsigned *result,
        const char *path,
        void *width_or_load_state,
        void *height_or_upload_state);
    unsigned *create_composite_texture(
        unsigned *result,
        const char *path_list,
        CompositeTextureUploadState *upload_state,
        int width,
        int height);
};

extern SpellTexturePool g_spell_texture_pool;

} // namespace th105
