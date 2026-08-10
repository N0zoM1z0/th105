#pragma once

namespace th105 {

struct NetworkSessionState {
    unsigned char unknown_0000[0x6b0];
    void *unknown_06b0;
    unsigned char unknown_06b4[0x14];
    void *unknown_06c8;

    void copy_session_field_6c8_if_unset();
};

} // namespace th105
