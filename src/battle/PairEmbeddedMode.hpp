#pragma once

namespace th105 {

// Current-target narrow view. Exact battle-pair initialization calls this as
// a member; the recovered body intentionally leaves the receiver unused.
struct PairEmbeddedModeView {
    void select_pair_mode_434780(int mode, unsigned char publish);
};

} // namespace th105
