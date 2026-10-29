#include "battle/EffectManager.hpp"
#include "battle/EffectSprite.hpp"
#include "battle/EventEffectState.hpp"
#include "ui/Title.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "battle/SpriteTextureSetup.hpp"

#include <deque>
#include <map>
#include <vector>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);

namespace th105 {

struct CsvReaderRuntimeInit {
    unsigned unknown_00;
    void *row_map_04;
    unsigned row_map_capacity_08;
    unsigned row_start_0c;
    unsigned row_count_10;
    unsigned outer_iterator_aux_14;
    CsvReaderRuntimeInit *outer_iterator_owner_18;
    unsigned outer_row_position_1c;
    unsigned inner_iterator_aux_20;
    void *current_row_24;
    unsigned current_field_position_28;
    unsigned char parser_comment_2c;
    unsigned char parser_quote_2d;
    unsigned char reserved_2e[2];

    CsvReaderRuntimeInit()
        : row_map_04(0), row_map_capacity_08(0), row_start_0c(0), row_count_10(0),
          outer_iterator_aux_14(0), outer_iterator_owner_18(0), outer_row_position_1c(0),
          inner_iterator_aux_20(0), current_row_24(0), current_field_position_28(0)
    {}
    ~CsvReaderRuntimeInit() throw() { clear_rows(); }
    bool load(const char *path);
    int next_int();
    bool advance_row();
    void clear_rows() throw();
};

struct EventTextureLoadView {
    DesignTextureHandle load_texture(const char *,unsigned *,unsigned *);
};

struct EffectRuntimeLoaderView {
    virtual void slot_00();
    virtual void load_runtime(const char *path, unsigned option);
};

struct EventEffectRuntimeInitializerView {
    unsigned current_event_id_00;
    signed char current_stage_04;
    unsigned char reserved_05[3];
    std::vector<unsigned> resources_08;
    std::vector<CEffectSprite> sprites_18;
    std::deque<BackgroundRenderEntry> background_entries_28;
    std::map<signed char, std::vector<unsigned char> > stage_rows_3c;
    CEffectManager<WeatherEffectObject> emitter_48;
    float runtime_x_dc;
    float runtime_y_e0;
    float runtime_z_e4;

    void initialize_effect_runtime();
    void publish_stage_state(signed char state);
};

extern int g_event_runtime_state;
extern int g_event_runtime_zero;
extern unsigned char g_battle_transition_mode;

void EventEffectRuntimeInitializerView::initialize_effect_runtime()
{
    reinterpret_cast<EffectRuntimeLoaderView *>(&emitter_48)
        ->load_runtime("data/weather/effect/effect.pat", 0);

    resources_08.assign(17,0);
    {
        CEffectSprite prototype;
        sprites_18.assign(17, prototype);
    }

    for (int i = 0; i < 17; ++i) {
        char path[260];
        wsprintfA(path, "data/weather/%02d.bmp", i);
        unsigned width;
        unsigned height;
        resources_08[i] = reinterpret_cast<EventTextureLoadView *>(&g_title_resource_manager)->load_texture(path, &width, &height).value;
        reinterpret_cast<SpriteTextureSetupView *>(&sprites_18[i])
            ->set_texture_options(
                resources_08[i], 0, 0, width, height, width >> 1, height);
    }

    CsvReaderRuntimeInit reader;
    reader.load("data/csv/background/sky.csv");
    // Advance while the row remains alive; native cleanup follows that call.
    for (;;) {
        signed char key = static_cast<signed char>(reader.next_int());
        std::vector<unsigned char> row;
        const unsigned char zero = 0;
        row.insert(row.begin(), 17, zero);
        for (int i = 0; i <= 16; ++i)
            row[i] = static_cast<unsigned char>(reader.next_int());
        stage_rows_3c.insert(
            std::pair<signed char, std::vector<unsigned char> >(key, row));
        if (!reader.advance_row())
            break;
    }

    emitter_48.release_all_tracked_objects();
    current_stage_04 = -2;
    current_event_id_00 = 16;
    g_event_runtime_state = 16;
    g_event_runtime_zero = 0;
    background_entries_28.clear();
    publish_stage_state(g_battle_transition_mode);
    runtime_x_dc = 0.0f;
    runtime_y_e0 = 0.0f;
    runtime_z_e4 = 0.0f;
}
}
