#pragma once

namespace th105 {

// The float-return VC8 atan2f/strict-FP implementation replays 0x00406540.
// Consumers may still require double arithmetic before a later float store.
float __cdecl atan2_degrees(float y, float x);

} // namespace th105
