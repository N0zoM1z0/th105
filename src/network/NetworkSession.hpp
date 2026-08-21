#pragma once

namespace th105 {

struct NetworkSessionState {
    unsigned char unknown_0000[0x6c0];
    void *unknown_06c0;
    unsigned char unknown_06c4[0x14];
    void *unknown_06d8;

    void copy_session_field_6c8_if_unset();
};

} // namespace th105
