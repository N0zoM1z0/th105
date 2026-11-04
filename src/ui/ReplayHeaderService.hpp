#pragma once

namespace th105 {

// Pointer-only service view: the two independently observed methods share the
// same receiver returned by get_replay_header_service().
struct ReplayHeaderServiceView {
    int read_header_code(const char *path);
    bool load_recording(const char *path);
};

ReplayHeaderServiceView *get_replay_header_service();

} // namespace th105
