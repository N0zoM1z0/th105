// Diagnostic compiler witnesses, not accepted reconstruction source.
// The used input/index alignment hypotheses are not uniquely established.
// See docs/ANGLE_RATIO_EVIDENCE_2026_09_12.md.
#pragma float_control(except, off, push)
#include <stdlib.h>
#include <math.h>

namespace th105 {

extern float g_orientation_cosine_table[3600];
typedef __declspec(align(64)) float AlignedPhase;

float aligned_absolute_phase_probe(float phase)
{
    AlignedPhase const value = phase;
    return fabsf(value);
}

float aligned_index_sine_probe(float phase)
{
    __declspec(align(64)) int const index =
        static_cast<int>(abs(phase * 10.0f - 900.0f) + 0.5f);
    return g_orientation_cosine_table[index % 3600];
}

float inlined_absolute_sine_probe(float phase)
{
    int const index =
        static_cast<int>(aligned_absolute_phase_probe(phase * 10.0f - 900.0f) + 0.5f);
    return g_orientation_cosine_table[index % 3600];
}

} // namespace th105

#pragma float_control(pop)
