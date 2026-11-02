// JP1.06a binary design loader and source-visible gauge initialization.
// Source-present only; EH/TU/private-ABI comparison remains open.
// See docs/DESIGN_BASE_LOADER_SOURCE_2026_10_21.md.
#define TH105_FILE_READER_OWNER_DTOR_VISIBLE
#include "DesignBaseLifetime.hpp"
#include "assets/FileReader.hpp"
#include "ui/Title.hpp"
#include "ui/Tile.hpp"
#include "ui/CNumberRuntime.hpp"
#include "ui/GageConstructor.cpp"
#include "ui/DesignObjects.hpp"
#include "ui/DesignGageConstructor.cpp"
#include "ui/DesignNumberConstructor.cpp"
#include <stdlib.h>
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);

#pragma float_control(except, off, push)

namespace th105 {

struct DesignTextureRectangle {
    int x, y, width, height;
};

static void __stdcall initialize_design_gage(CGage *gage,
    int mode, unsigned int handle, int width, int height)
{
    gage->texture_width_78 = static_cast<float>(width);
    gage->fill_mode_9c = mode;
    gage->texture_height_7c = static_cast<float>(height);
    gage->pivot_x_80 = 0;
    gage->pivot_y_84 = 0;
    gage->value_04.value = handle;
    unsigned int texture_height;
    g_title_resource_manager.get_texture_size(handle, &handle, &texture_height);
    gage->u_span_94 = static_cast<float>(width) / handle;
    gage->v_span_98 = static_cast<float>(height) / texture_height;
    float left = 0.0f / handle;
    gage->vertices_08[0].u = left;
    float top = 0.0f / texture_height;
    gage->vertices_08[0].v = top;
    float right = static_cast<float>(width) / handle;
    gage->vertices_08[1].u = right;
    gage->vertices_08[1].v = top;
    gage->vertices_08[2].u = left;
    float bottom = static_cast<float>(height) / texture_height;
    gage->vertices_08[2].v = bottom;
    gage->vertices_08[3].v = bottom;
    gage->vertices_08[3].u = right;
    gage->vertices_08[0].color = gage->vertices_08[1].color =
        gage->vertices_08[2].color = gage->vertices_08[3].color = ~0u;
    gage->vertices_08[0].z = gage->vertices_08[1].z =
        gage->vertices_08[2].z = gage->vertices_08[3].z = 0.5f;
    gage->vertices_08[0].rhw = gage->vertices_08[1].rhw =
        gage->vertices_08[2].rhw = gage->vertices_08[3].rhw = 1;
    gage->scale_x_88 = gage->scale_y_8c = 1;
    gage->angle_90 = 0;
}

void CDesignBase::load(const char *path)
{
    FileReaderOwner file;
    file.open(path);
    char directory[260], filename[260], texture_path[260];
    _splitpath_s(path, 0, 0, directory, 260, 0, 0, filename, 256);
    CFileReader *reader = file.reader;
    unsigned int signature, texture_count;
    reader->read(&signature, 4);
    reader->read(&texture_count, 4);
    DesignTextureRectangle zero_rectangle = {0, 0, 0, 0};
    std::vector<DesignTextureRectangle> rectangles(texture_count, zero_rectangle);
    texture_handles_04.assign(texture_count, 0);
    for (unsigned int index = 0; index < texture_count; ++index) {
        memset(filename, 0, sizeof(filename));
        unsigned int filename_size;
        reader->read(&filename_size, 4);
        reader->read(filename, filename_size);
        wsprintfA(texture_path, "%s%s", directory, filename);
        unsigned int handle;
        g_title_resource_manager.load_texture(&handle, texture_path, 0, 0);
        texture_handles_04.at(index) = handle;
        reader->read(&rectangles.at(index).x, 4);
        reader->read(&rectangles.at(index).y, 4);
        reader->read(&rectangles.at(index).width, 4);
        reader->read(&rectangles.at(index).height, 4);
    }
    unsigned int object_count;
    reader->read(&object_count, 4);
    for (unsigned int index = 0; index < object_count; ++index) {
        unsigned int object_id;
        signed char kind;
        reader->read(&object_id, 4);
        reader->read(&kind, 1);
        switch (kind) {
        case 0: {
            CDesignSprite *object = new CDesignSprite;
            unsigned int texture;
            reader->read(&texture, 4);
            const DesignTextureRectangle &rectangle = rectangles[texture];
            object->sprite_18.set_texture_options(texture_handles_04[texture],
                rectangle.x, rectangle.y, rectangle.width, rectangle.height,
                -rectangle.x, -rectangle.y);
            int coordinate;
            reader->read(&coordinate, 4);
            object->x_0c = static_cast<float>(coordinate);
            reader->read(&coordinate, 4);
            object->y_10 = static_cast<float>(coordinate);
            unsigned int flags;
            reader->read(&flags, 4);
            if (flags & 1) {
                object->sprite_18.scale_x_88 = -1;
                object->sprite_18.scale_y_8c = 1;
            }
            if (object_id != 0) {
                object_tree_20.insert(std::make_pair(object_id,
                    reinterpret_cast<UiDesignObject *>(object)));
                object->enabled_14 = false;
            }
            objects_14.push_back(reinterpret_cast<UiDesignObject *>(object));
            break;
        }
        case 1: {
            CDesignObjectBase *object = new CDesignObjectBase;
            int coordinate;
            reader->read(&coordinate, 4);
            object->x_0c = static_cast<float>(coordinate);
            reader->read(&coordinate, 4);
            object->y_10 = static_cast<float>(coordinate);
            if (object_id != 0) {
                object_tree_20.insert(std::make_pair(object_id,
                    reinterpret_cast<UiDesignObject *>(object)));
                object->enabled_14 = false;
            }
            objects_14.push_back(reinterpret_cast<UiDesignObject *>(object));
            break;
        }
        case 2: case 3: case 4: case 5: {
            CDesignGage *object = new CDesignGage;
            unsigned int texture;
            reader->read(&texture, 4);
            const DesignTextureRectangle &rectangle = rectangles[texture];
            initialize_design_gage(&object->gage_18, kind - 2,
                texture_handles_04[texture], rectangle.width, rectangle.height);
            int coordinate;
            reader->read(&coordinate, 4);
            object->x_0c = static_cast<float>(coordinate);
            reader->read(&coordinate, 4);
            object->y_10 = static_cast<float>(coordinate);
            unsigned int flags;
            reader->read(&flags, 4);
            if (flags & 1) {
                object->gage_18.scale_x_88 = -1;
                object->gage_18.scale_y_8c = 1;
            }
            if (object_id != 0) {
                object_tree_20.insert(std::make_pair(object_id,
                    reinterpret_cast<UiDesignObject *>(object)));
                object->enabled_14 = false;
            }
            objects_14.push_back(reinterpret_cast<UiDesignObject *>(object));
            break;
        }
        case 6: {
            CDesignNumber *object = new CDesignNumber;
            unsigned int texture;
            reader->read(&texture, 4);
            // The original validates this index even though number dimensions
            // are supplied separately, rather than using the rectangle value.
            static_cast<void>(rectangles[texture]);
            int coordinate;
            reader->read(&coordinate, 4);
            object->x_0c = static_cast<float>(coordinate);
            reader->read(&coordinate, 4);
            object->y_10 = static_cast<float>(coordinate);
            int width, height, columns, spacing, integer_digits, fractional_digits;
            reader->read(&width, 4);
            reader->read(&height, 4);
            reader->read(&columns, 4);
            reader->read(&spacing, 4);
            reader->read(&integer_digits, 4);
            reader->read(&fractional_digits, 4);
            unsigned int handle = texture_handles_04[texture];
            object->number_18.glyph_width_04 = static_cast<float>(width);
            object->number_18.spacing_08 = static_cast<float>(spacing);
            object->number_18.reserved_1c = fractional_digits;
            object->number_18.scale_0c = object->number_18.secondary_scale_10 = 1;
            object->number_18.reserved_18 = integer_digits;
            object->number_18.columns_14 = columns;
            object->number_18.mode_20 = 0;
            object->number_18.tile_28.set_texture_options(handle, 0, 0,
                width, height, 0, 0);
            if (object_id != 0) {
                object_tree_20.insert(std::make_pair(object_id,
                    reinterpret_cast<UiDesignObject *>(object)));
                object->enabled_14 = false;
            }
            objects_14.push_back(reinterpret_cast<UiDesignObject *>(object));
            break;
        }
        default:
            break;
        }
    }
    current_2c = objects_14.begin();
}

typedef char LoaderObjectSize[sizeof(CDesignObjectBase) == 0x18 ? 1 : -1];
typedef char LoaderSpriteSize[sizeof(CSprite) == 0x94 ? 1 : -1];
typedef char LoaderGageSize[sizeof(CGage) == 0xa4 ? 1 : -1];
typedef char LoaderTileSize[sizeof(CTile) == 0xa4 ? 1 : -1];
typedef char LoaderNumberSize[sizeof(CNumber) == 0xcc ? 1 : -1];
typedef char LoaderSpriteObjectSize[sizeof(CDesignSprite) == 0xac ? 1 : -1];
typedef char LoaderGageObjectSize[sizeof(CDesignGage) == 0xbc ? 1 : -1];
typedef char LoaderNumberObjectSize[sizeof(CDesignNumber) == 0xe4 ? 1 : -1];
typedef char LoaderNumberOffset[offsetof(CDesignNumber, number_18) == 0x18 ? 1 : -1];

} // namespace th105

#pragma float_control(pop)
