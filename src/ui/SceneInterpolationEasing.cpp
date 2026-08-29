extern "C" float __cdecl scene_easing_sine(float value);
extern "C" float __cdecl scene_easing_cosine(float value);

namespace th105 {

float __stdcall apply_scene_easing_450120(int mode, float value)
{
    if (value <= 0.0f)
        return 0.0f;
    if (value >= 1.0f)
        return 1.0f;
    switch (mode) {
    case 0:
        return value;
    case 1: {
        float angle = static_cast<float>(static_cast<double>(value) * 90.0);
        return static_cast<float>(1.0f - scene_easing_cosine(angle));
    }
    case 2: {
        float angle = static_cast<float>(static_cast<double>(value) * 90.0);
        return scene_easing_sine(angle);
    }
    default:
        return 1.0f;
    }
}

} // namespace th105
