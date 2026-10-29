// JP1.06a scene interpolation. Easing is a real member call preserving ECX.
// Float root is exact; byte root retains a pointer-register scheduling residual.
#include "SceneInterpolationRuntime.hpp"
namespace th105 {

void SceneInterpolationRuntimeView::interpolate_byte(
    unsigned char *output,unsigned char *current,const SceneInterpolationEntry24 *entry,unsigned elapsed)
{
    if(elapsed>=entry->end_08 || entry->start_04==entry->end_08) {
        unsigned char value=entry->target.byte_0c;
        *output=value;
        *current=value;
    } else if(elapsed<=entry->start_04) {
        *output=*current;
    } else {
        int base=*current;
        float progress=static_cast<float>(elapsed-entry->start_04)/static_cast<float>(entry->end_08-entry->start_04);
        *output=static_cast<unsigned char>((static_cast<int>(entry->target.uint_0c)-base)*apply_easing(entry->easing_10,progress)+base);
    }
}
void SceneInterpolationRuntimeView::interpolate_float(
    float *output,float *current,const SceneInterpolationEntry24 *entry,unsigned elapsed)
{
    if(elapsed>=entry->end_08 || entry->start_04==entry->end_08) {
        float value=entry->target.float_0c;
        *output=value;
        *current=value;
    } else if(elapsed<=entry->start_04) {
        *output=*current;
    } else {
        float progress=static_cast<float>(elapsed-entry->start_04)/static_cast<float>(entry->end_08-entry->start_04);
        *output=(entry->target.float_0c-*current)*apply_easing(entry->easing_10,progress)+*current;
    }
}
}
