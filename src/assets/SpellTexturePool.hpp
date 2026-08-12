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

    void render_composite_text(const char *path_list);
};

typedef char CompositeTextureUploadState_observed_size_must_be_0x154[
    sizeof(CompositeTextureUploadState) == 0x154 ? 1 : -1];

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
