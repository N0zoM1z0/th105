#pragma once

#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "SelectScenario.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"

namespace th105 {

struct ResultString28 {
    unsigned int allocator_state;
    union {
        char buffer[16];
        char *allocation;
    } storage;
    unsigned int size;
    unsigned int capacity;

    ResultString28()
    {
        capacity = 15;
        size = 0;
        storage.buffer[0] = 0;
    }
    ~ResultString28()
    {
        if (capacity >= 16)
            operator delete(storage.allocation);
    }

    void assign_buffer(const char *source, unsigned int length);
    void assign_copy(
        const ResultString28 &source,
        unsigned int offset,
        unsigned int count);
    const char *c_str() const
    {
        return capacity < 16 ? storage.buffer : storage.allocation;
    }
};

struct ResultStringDeque20 {
    unsigned int allocator_state;
    ResultString28 **map;
    unsigned int map_size;
    unsigned int offset;
    unsigned int size;

    ResultStringDeque20() : map(0), map_size(0), offset(0), size(0) {}
    ~ResultStringDeque20();
    void grow(unsigned int count);
    void clear();
    __forceinline void push_back(const ResultString28 &value);
};

class ResultListBase {
public:
    ResultListBase();
    virtual ~ResultListBase();
    virtual void populate();
    virtual void finalize();
    virtual void clear_entries();
    virtual void unknown_list_method();

    int entry_count() const;
    void render_row(float x, float y, unsigned int index);

protected:
    ResultStringDeque20 rows_004;
    unsigned char reserved_018[0x90];
    int field_a8;
    int field_ac;
    unsigned char reserved_0b0[4];
    int character_id_b4;
};

struct ResultIndexDeque20 {
    unsigned int allocator_state;
    void *map;
    unsigned int map_size;
    unsigned int offset;
    unsigned int size;

    ResultIndexDeque20() : map(0), map_size(0), offset(0), size(0) {}
    ~ResultIndexDeque20();
};

struct ResultPointerDeque20 {
    unsigned int allocator_state;
    void *map;
    unsigned int map_size;
    unsigned int offset;
    unsigned int size;

    ResultPointerDeque20() : map(0), map_size(0), offset(0), size(0) {}
    ~ResultPointerDeque20();

    unsigned int *at(unsigned int index);
    void push_back(const int &value);
};

struct ResultReplayDeque20 {
    unsigned int allocator_state;
    void *map;
    unsigned int map_size;
    unsigned int offset;
    unsigned int size;

    ResultReplayDeque20() : map(0), map_size(0), offset(0), size(0) {}
    ~ResultReplayDeque20();

    short *at(unsigned int index);
    void push_back(const unsigned int &value);
};

class ResultList : public ResultListBase {
public:
    ResultList();
    virtual void populate();

    __forceinline void set_character_id(int character_id)
    {
        character_id_b4 = character_id;
    }

    __forceinline ResultPointerDeque20 &labels() { return labels_cc; }
    __forceinline ResultPointerDeque20 &values() { return values_e0; }
    __forceinline ResultReplayDeque20 &replays() { return metadata_f4; }

private:
    ResultStringDeque20 indices_b8;
    ResultPointerDeque20 labels_cc;
    ResultPointerDeque20 values_e0;
    ResultReplayDeque20 metadata_f4;
};

class CMenuResult : public Menu {
public:
    CMenuResult();
    virtual ~CMenuResult();
    virtual bool update();
    virtual void render();

private:
    void refresh_selected_character();
    bool update_active();

    unsigned int texture_004;
    UiSprite94 character_sprite_008;
    SelectIntVector16 available_characters_09c;
    int character_count_0ac;
    MenuCursorState character_cursor_0b0;
    int selected_character_0c4;
    ResultList results_0c8[15];
    bool initialized_1040[15];
    unsigned char reserved_104f;
    TitleDesignResource design_1050;
    UiDesignObject *selection_1084;
    int reserved_1088;
    MenuCursorState result_cursor_108c;
    GuideOverlay guide_10a0;
};

typedef char ResultListBase_size_must_be_0xb8[
    sizeof(ResultListBase) == 0xB8 ? 1 : -1];
typedef char ResultIndexDeque20_size_must_be_0x14[
    sizeof(ResultIndexDeque20) == 0x14 ? 1 : -1];
typedef char ResultPointerDeque20_size_must_be_0x14[
    sizeof(ResultPointerDeque20) == 0x14 ? 1 : -1];
typedef char ResultReplayDeque20_size_must_be_0x14[
    sizeof(ResultReplayDeque20) == 0x14 ? 1 : -1];
typedef char ResultString28_size_must_be_0x1c[
    sizeof(ResultString28) == 0x1C ? 1 : -1];
typedef char ResultStringDeque20_size_must_be_0x14[
    sizeof(ResultStringDeque20) == 0x14 ? 1 : -1];
typedef char ResultList_size_must_be_0x108[
    sizeof(ResultList) == 0x108 ? 1 : -1];
typedef char CMenuResult_size_must_be_0x1148[
    sizeof(CMenuResult) == 0x1148 ? 1 : -1];

} // namespace th105
