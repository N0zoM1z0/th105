#pragma once
namespace th105 {
// Four-byte value element. The cleanup's native assignment loop distinguishes
// this class value from VC8's scalar-vector memmove specialization. Original
// handle API spelling remains unknown; ownership stays with the design object.
struct DesignTextureHandle {
    unsigned int value;
    DesignTextureHandle(unsigned int token = 0) : value(token) {}
    operator unsigned int() const { return value; }
};

} // namespace th105
