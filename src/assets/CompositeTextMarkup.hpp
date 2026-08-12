#pragma once

namespace th105 {

struct MarkupTokenRing {
    void *unknown_00;
    void **storage_04;
    unsigned capacity_08;
    unsigned logical_begin_0c;
    unsigned size_10;

    void *checked_at(int relative_index);
};

typedef char MarkupTokenRing_size_must_be_0x14[
    sizeof(MarkupTokenRing) == 0x14 ? 1 : -1];

} // namespace th105
