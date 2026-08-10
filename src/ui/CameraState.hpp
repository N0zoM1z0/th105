#pragma once

namespace th105 {

class CameraState {
public:
    void set_target_20_enabled_2c(bool enabled, float target);

private:
    unsigned char reserved_00[0x20];
    float target_20;
    unsigned char reserved_24[0x08];
    bool enabled_2c;
};

} // namespace th105
