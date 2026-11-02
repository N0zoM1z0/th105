// JP1.06a 0x00454C70. Constructor-facing owned result resource.
// See docs/SCENARIO_RESULT_CONSTRUCTOR_2026_10_29.md.
#include "ui/DesignBaseLifetime.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"
#include "ui/Tile.hpp"
#include <stddef.h>

namespace th105 {

struct ScenarioSecondaryDesignView {
    void bind_secondary(UiDesignObject **result, int object_id);
};

struct ScenarioResultResourceOwner128 {
    unsigned char state_000;
    unsigned char unknown_001[7];
    CDesignBase design_008;
    UiDesignObject *objects_03c[4];
    UiDesignObject *secondary_04c[3];
    unsigned int texture_058;
    CTile tile_05c;
    int secondary_modes_100[3];
    unsigned char unknown_10c[0x1c];

    ScenarioResultResourceOwner128();
    ~ScenarioResultResourceOwner128();
};

typedef char CheckResult128[sizeof(ScenarioResultResourceOwner128)==0x128?1:-1];
typedef char CheckDesign8[offsetof(ScenarioResultResourceOwner128,design_008)==0x08?1:-1];
typedef char CheckTexture58[offsetof(ScenarioResultResourceOwner128,texture_058)==0x58?1:-1];
typedef char CheckTile5c[offsetof(ScenarioResultResourceOwner128,tile_05c)==0x5c?1:-1];
typedef char CheckModes100[offsetof(ScenarioResultResourceOwner128,secondary_modes_100)==0x100?1:-1];

ScenarioResultResourceOwner128::ScenarioResultResourceOwner128()
    : texture_058(0)
{
    CDesignBase *design = &design_008;
    design->load("data/infoeffect/result/result.dat");
    design->bind_object_alt(&objects_03c[0], 6);
    design->bind_object_alt(&objects_03c[1], 3);
    design->bind_object_alt(&objects_03c[2], 4);
    design->bind_object_alt(&objects_03c[3], 5);
    objects_03c[0]->enabled = true;
    objects_03c[1]->enabled = true;
    objects_03c[2]->enabled = true;
    objects_03c[3]->enabled = true;

    unsigned int loaded;
    texture_058 = *g_title_resource_manager.load_texture(
        &loaded, "data/infoeffect/result/rankFont.bmp", 0, 0);
    tile_05c.set_texture_options(
        texture_058, 0, 0, 64, 64, 32, 32);

    ScenarioSecondaryDesignView *secondary_design =
        reinterpret_cast<ScenarioSecondaryDesignView *>(&design_008);
    for (int i = 0; i < 3; ++i) {
        secondary_design->bind_secondary(&secondary_04c[i], (i + 1) * 10);
        secondary_modes_100[i] = 3;
    }
    state_000 = 0;
}

} // namespace th105
