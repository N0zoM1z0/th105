#include "ScoreData.hpp"

namespace th105 {

extern ScoreData g_score_data;

ScoreData *get_score_data()
{
    return &g_score_data;
}

} // namespace th105
