// JP1.06a binary design loader and source-visible gauge initialization.
// Source-present only; EH/TU/private-ABI comparison remains open.
// See docs/DESIGN_BASE_LOADER_SOURCE_2026_10_21.md.
#define TH105_FILE_READER_OWNER_DTOR_VISIBLE
#include "DesignBaseLifetime.hpp"
#include "assets/FileReader.hpp"
#include "ui/Title.hpp"
#include <stdlib.h>
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);

#pragma float_control(except, off, push)

namespace th105 {

struct DesignLoaderVertex {
    float x, y, z, rhw;
    unsigned int color;
    float u, v;
};

class DesignLoaderSpriteStorage : public DesignColorLifetimeView {
public:
    DesignLoaderSpriteStorage() : texture_04(0) {}
    virtual ~DesignLoaderSpriteStorage() {}
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    unsigned int texture_04;
    DesignLoaderVertex vertices_08[4];
    float width_78, height_7c;
};

class DesignLoaderSprite : public DesignLoaderSpriteStorage {
public:
    virtual ~DesignLoaderSprite() {}
    virtual void set_texture_options(unsigned int, int, int, unsigned int,
                                     unsigned int, int, int);
    virtual void set_texture(unsigned int, int, int, unsigned int, unsigned int);
    virtual void render_rectangle(float, float, float, float);
    virtual void render(float, float);
    virtual void render_plain(float, float);
    float pivot_x_80, pivot_y_84;
    float scale_x_88, scale_y_8c, angle_90;
};

class DesignLoaderGage : public DesignLoaderSprite {
public:
    DesignLoaderGage() : value_a0(0) {}
    virtual ~DesignLoaderGage()
    {
        if (value_a0 != 0)
            ::operator delete(value_a0);
    }
    virtual void render(float, float);
    virtual void render_plain(float, float);
    float u_span_94, v_span_98;
    int mode_9c;
    void *value_a0;
};

class DesignLoaderTile : public DesignLoaderSpriteStorage {
public:
    virtual ~DesignLoaderTile() {}
    void set_texture_options(unsigned int, int, int, int, int, int, int);
    float pivot_x_80, pivot_y_84, scale_x_88, scale_y_8c, angle_90;
    float texture_u_94, texture_v_98, texture_width_9c, texture_height_a0;
};

class DesignLoaderNumber : public DesignColorLifetimeView {
public:
    DesignLoaderNumber() : value_24(0) {}
    virtual ~DesignLoaderNumber()
    {
        if (value_24 != 0)
            ::operator delete(value_24);
    }
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    float glyph_width_04, spacing_08, scale_0c, secondary_scale_10;
    int columns_14, integer_digits_18, fractional_digits_1c;
    unsigned char mode_20;
    void *value_24;
    DesignLoaderTile tile_28;
};

class DesignLoaderObjectBase : public DesignColorLifetimeView {
public:
    DesignLoaderObjectBase() : base_x_04(0), base_y_08(0), enabled_14(true) {}
    virtual ~DesignLoaderObjectBase() {}
    virtual void set_color(unsigned int) {}
    virtual void set_vertex_colors(const unsigned int *) {}
    virtual void multiply_color(unsigned int) {}
    virtual void render_offset(float, float) {}
    virtual void render() {}
    virtual void set_render_parameters(unsigned int, unsigned int, float) {}
    float base_x_04, base_y_08, x_0c, y_10;
    bool enabled_14;
};

class DesignLoaderSpriteObject : public DesignLoaderObjectBase {
public:
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    virtual void set_render_parameters(unsigned int, unsigned int, float);
    DesignLoaderSprite sprite_18;
};

class DesignLoaderGageObject : public DesignLoaderObjectBase {
public:
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    DesignLoaderGage gage_18;
};

class DesignLoaderNumberObject : public DesignLoaderObjectBase {
public:
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    DesignLoaderNumber number_18;
};

struct DesignTextureRectangle {
    int x, y, width, height;
};

static void __stdcall initialize_design_gage(DesignLoaderGage *gage,
    int mode, unsigned int handle, int width, int height)
{
    gage->width_78 = static_cast<float>(width);
    gage->mode_9c = mode;
    gage->height_7c = static_cast<float>(height);
    gage->pivot_x_80 = 0;
    gage->pivot_y_84 = 0;
    gage->texture_04 = handle;
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
            DesignLoaderSpriteObject *object = new DesignLoaderSpriteObject;
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
            DesignLoaderObjectBase *object = new DesignLoaderObjectBase;
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
            DesignLoaderGageObject *object = new DesignLoaderGageObject;
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
            DesignLoaderNumberObject *object = new DesignLoaderNumberObject;
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
            object->number_18.fractional_digits_1c = fractional_digits;
            object->number_18.scale_0c = object->number_18.secondary_scale_10 = 1;
            object->number_18.integer_digits_18 = integer_digits;
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

typedef char LoaderObjectSize[sizeof(DesignLoaderObjectBase) == 0x18 ? 1 : -1];
typedef char LoaderSpriteSize[sizeof(DesignLoaderSprite) == 0x94 ? 1 : -1];
typedef char LoaderGageSize[sizeof(DesignLoaderGage) == 0xa4 ? 1 : -1];
typedef char LoaderTileSize[sizeof(DesignLoaderTile) == 0xa4 ? 1 : -1];
typedef char LoaderNumberSize[sizeof(DesignLoaderNumber) == 0xcc ? 1 : -1];
typedef char LoaderSpriteObjectSize[sizeof(DesignLoaderSpriteObject) == 0xac ? 1 : -1];
typedef char LoaderGageObjectSize[sizeof(DesignLoaderGageObject) == 0xbc ? 1 : -1];
typedef char LoaderNumberObjectSize[sizeof(DesignLoaderNumberObject) == 0xe4 ? 1 : -1];
typedef char LoaderNumberOffset[offsetof(DesignLoaderNumberObject, number_18) == 0x18 ? 1 : -1];
typedef char LoaderTileOffset[offsetof(DesignLoaderNumber, tile_28) == 0x28 ? 1 : -1];

} // namespace th105

#pragma float_control(pop)
