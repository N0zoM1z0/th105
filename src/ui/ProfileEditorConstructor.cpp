#include <stddef.h>

namespace th105 {

// Constructor-facing physical view. The shared ProfileMenu.hpp keeps UiTileA4
// as an ABI facade for existing runtime methods. The target constructor instead
// proves real polymorphic CTile members: their non-polymorphic color base clears
// +4 first, then VC8 writes the CTile vptr.
struct ProfileEditorTileColorBase {
    unsigned int reserved_04;
    ProfileEditorTileColorBase() : reserved_04(0) {}
};

class CTile : public ProfileEditorTileColorBase {
public:
    CTile() {}
    virtual ~CTile();
    virtual void set_color(unsigned int color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float x, float y);

private:
    unsigned char reserved_08[0x9c];
};

struct ProfileEditor168 {
    unsigned int texture_primary_000;
    unsigned int texture_secondary_004;
    void *source_008;
    CTile primary_tile_00c;
    CTile secondary_tile_0b0;
    int width_154;
    int x_158;
    int y_15c;
    int state_160;
    int record_limit_164;

    ProfileEditor168();
};

ProfileEditor168::ProfileEditor168()
    : texture_primary_000(0),
      texture_secondary_004(0)
{
}

typedef char ProfileEditorCTileSize[sizeof(CTile) == 0xa4 ? 1 : -1];
typedef char ProfileEditor168Size[sizeof(ProfileEditor168) == 0x168 ? 1 : -1];
typedef char ProfileEditorPrimaryTileOffset[
    offsetof(ProfileEditor168, primary_tile_00c) == 0x0c ? 1 : -1];
typedef char ProfileEditorSecondaryTileOffset[
    offsetof(ProfileEditor168, secondary_tile_0b0) == 0xb0 ? 1 : -1];

} // namespace th105
