#include "ScoreData.hpp"

namespace th105 {

ScoreData *get_score_data()
{
    return reinterpret_cast<ScoreData *>(0x006e7238);
}

} // namespace th105
