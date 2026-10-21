#pragma once

#include "TextFontOwner.hpp"

namespace th105 {
// Preserve the runtime source-view spelling while using the same real native
// class as construction, destruction and configuration. No separate prefix.
typedef TextFontOwner194 TextTextureFontView;

typedef char TextFontHeightOffset[
    offsetof(TextFontOwner194, config_00c) + offsetof(TextFontConfig128, height_108) == 0x114 ? 1 : -1];
typedef char TextFontAccentOffset[
    offsetof(TextFontOwner194, accent_16c) == 0x16c ? 1 : -1];
typedef char TextFontSurfaceOffset[
    offsetof(TextFontOwner194, surface_base_140) == 0x140 ? 1 : -1];
typedef char TextFontPitchOffset[
    offsetof(TextFontOwner194, surface_pitch_dwords_150) == 0x150 ? 1 : -1];
}
