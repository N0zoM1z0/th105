#include "assets/String28.hpp"

#include <list>
#include <stddef.h>

namespace th105 {

// Current-target CsvReader lifetime view. The base/proxy dword at +0 is not
// initialized by the default lifetime; +0x04..+0x28 are zeroed. The cleanup
// call is non-throwing in the shipped EH schedule and the shared unwind thunk
// at 0x0042E980 tail-enters the same clear_rows body.
struct CsvReaderLifetime {
    unsigned unknown_00;
    void *row_map_04;
    unsigned row_map_capacity_08;
    unsigned row_start_0c;
    unsigned row_count_10;
    unsigned outer_iterator_aux_14;
    CsvReaderLifetime *outer_iterator_owner_18;
    unsigned outer_row_position_1c;
    unsigned inner_iterator_aux_20;
    void *current_row_24;
    unsigned current_field_position_28;
    unsigned char parser_comment_2c;
    unsigned char parser_quote_2d;
    unsigned char reserved_2e[2];

    CsvReaderLifetime()
        : row_map_04(0), row_map_capacity_08(0), row_start_0c(0), row_count_10(0),
          outer_iterator_aux_14(0), outer_iterator_owner_18(0), outer_row_position_1c(0),
          inner_iterator_aux_20(0), current_row_24(0), current_field_position_28(0)
    {}
    ~CsvReaderLifetime() throw() { clear_rows(); }
    void clear_rows() throw();
};
typedef char CsvReaderLifetime_size[(sizeof(CsvReaderLifetime)==0x30)?1:-1];

struct StoryScriptSubobjectLifetime {
    virtual void slot_00();
    virtual void shutdown();
    unsigned char storage_004[0x520];
    StoryScriptSubobjectLifetime();
    ~StoryScriptSubobjectLifetime();
};
typedef char StoryScriptSubobject_size[(sizeof(StoryScriptSubobjectLifetime)==0x524)?1:-1];

struct BattlePhaseBlockLifetime {
    String28 character_name_000;
    String28 secondary_name_01c;
    CsvReaderLifetime reader_038;
    StoryScriptSubobjectLifetime script_068;
    void *selected_input_58c;
    int selected_column_590;
    signed char page_index_594;
    signed char story_character_595;
    unsigned char reserved_596[2];
    std::list<int> source_values_598;
    std::list<int> destination_values_5a4;

    BattlePhaseBlockLifetime();
    ~BattlePhaseBlockLifetime();
};
typedef char BattlePhase_reader_off[(offsetof(BattlePhaseBlockLifetime,reader_038)==0x38)?1:-1];
typedef char BattlePhase_script_off[(offsetof(BattlePhaseBlockLifetime,script_068)==0x68)?1:-1];
typedef char BattlePhase_source_off[(offsetof(BattlePhaseBlockLifetime,source_values_598)==0x598)?1:-1];
typedef char BattlePhase_dest_off[(offsetof(BattlePhaseBlockLifetime,destination_values_5a4)==0x5a4)?1:-1];
typedef char BattlePhase_size[(sizeof(BattlePhaseBlockLifetime)==0x5b0)?1:-1];

BattlePhaseBlockLifetime::BattlePhaseBlockLifetime() {}
BattlePhaseBlockLifetime::~BattlePhaseBlockLifetime()
{
    script_068.shutdown();
}

} // namespace th105
