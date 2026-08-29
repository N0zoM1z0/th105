#pragma once

#include "GuideOverlay.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"
#include "../input/InputManager.hpp"

#include <new>
#include <string>
#include <vector>

namespace th105 {

struct MatchSetup {
    int game_type;
    int reserved_04;
    int scenario_id;
};

struct GameConfig {
    unsigned char reserved_00[0x64];
    int default_game_type;
};

struct SelectString24 {
    union {
        char buffer[16];
        char *allocation;
    } storage;
    unsigned int size;
    unsigned int capacity;

    SelectString24() : size(0), capacity(15) { storage.buffer[0] = 0; }

    __declspec(nothrow) ~SelectString24()
    {
        if (capacity >= 16)
            operator delete(storage.allocation);
        capacity = 15;
        size = 0;
        storage.buffer[0] = 0;
    }
};

struct SelectIntVector16;

struct SelectIntVectorIterator {
    SelectIntVector16 *owner;
    int *current;
};

typedef char SelectIntVectorIterator_size_must_be_0x08[
    sizeof(SelectIntVectorIterator) == 0x08 ? 1 : -1];

struct SelectIntVector16 {
    unsigned int allocator_state;
    int *begin;
    int *end;
    int *capacity;

    SelectIntVector16() : begin(0), end(0), capacity(0) {}

    SelectIntVectorIterator erase(
        SelectIntVectorIterator first, SelectIntVectorIterator last);

    __forceinline void clear()
    {
        int *last_position = end;
        if (begin > last_position)
            _invalid_parameter_noinfo();

        int *first_position = begin;
        if (first_position > end)
            _invalid_parameter_noinfo();

        SelectIntVectorIterator first = {this, first_position};
        SelectIntVectorIterator last = {this, last_position};
        erase(first, last);
    }
    void append(const int &value);

    __forceinline int size() const
    {
        return begin == 0 ? 0 : end - begin;
    }

    __declspec(nothrow) ~SelectIntVector16()
    {
        if (begin)
            operator delete(begin);
        begin = 0;
        end = 0;
        capacity = 0;
    }
};

class CSelectScenario : public CSceneBase {
public:
    CSelectScenario();
    virtual ~CSelectScenario();
    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);
    virtual int update_selection();

    void apply_scenario(int scenario_id);

private:
    MatchSetup *match_setup_08;
    CInputManager *input_0c;
    std::string scenario_name_10;
    SelectIntVector16 scenario_ids_2c;
    int scenario_count_3c;
    unsigned int texture_40;
    UiSprite94 color_44;
    unsigned int texture_d8;
    UiSprite94 color_dc;
    unsigned int texture_170;
    UiTileA4 color_174;
    unsigned int texture_218;
    UiSprite94 color_21c;
    UiDesignObject *selection_data_2b0;
    UiDesignObject *scenario_data_2b4;
    void *preview_data_2b8;
    MenuCursorState player_cursor_2bc;
    MenuCursorState scenario_cursor_2d0;
    TitleDesignResource design_2e4;
    UiDesignObject *design_500[3];
    UiDesignObject *design_100;
    UiDesignObject *design_600[4];
    unsigned int timer_338;
    float transition_33c;
    float preview_alpha_340;
    GuideOverlay guide_344;
};


typedef char CSelectScenario_size_must_be_0x3ec[
    sizeof(CSelectScenario) == 0x3EC ? 1 : -1];

} // namespace th105
