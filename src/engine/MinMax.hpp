#pragma once

// Argument-evaluating min/max/clamp in the std::min/std::max comparison order.
// Native clamps re-read the operand after each test and re-check the upper
// bound on the in-range path, which a reference-returning template does not do.
#define TH105_MIN(a, b) ((b) < (a) ? (b) : (a))
#define TH105_MAX(a, b) ((a) < (b) ? (b) : (a))
#define TH105_CLAMP(value, low, high) TH105_MAX(TH105_MIN((value), (high)), (low))
