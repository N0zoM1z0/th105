#pragma once
#include "ui/SceneTimelineEntries.hpp"
namespace th105 {
// Method-only view. Both interpolation callers retain this in ECX for easing.
struct SceneInterpolationRuntimeView {
    float apply_easing(int mode, float value);
    void interpolate_byte(unsigned char *output, unsigned char *current,
        const SceneInterpolationEntry24 *entry, unsigned elapsed);
    void interpolate_float(float *output, float *current,
        const SceneInterpolationEntry24 *entry, unsigned elapsed);
};
}
