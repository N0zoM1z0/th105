#include "battle/InfoLongRecordBinding.hpp"
#include "battle/InfoLongRecordRuntime.hpp"
#include "ui/UiPrimitives.hpp"
#include "ui/Title.hpp"

namespace th105 {
extern unsigned g_common_spell_extra_handle;

void InfoLongRecordBindView::bind_432550(void *resource, unsigned char side)
{
    InfoLongRecord154Runtime &record =
        *reinterpret_cast<InfoLongRecord154Runtime *>(this);
    record.resource_000 = resource;
    record.mirrored_132 = side;

    unsigned width, height;
    g_title_resource_manager.get_texture_size(
        g_common_spell_extra_handle, &width, &height);
    reinterpret_cast<UiSprite94 *>(&record.primary_004)->set_texture(
        g_common_spell_extra_handle, 0, 0, width, height);

    record.active_14c = 0;
    record.alpha_primary_130 = 0;
    record.alpha_secondary_131 = 0;
    record.timer_12c = 0;
}
}
