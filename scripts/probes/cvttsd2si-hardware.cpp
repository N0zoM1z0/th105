// Host x86/SSE2 diagnostic, not reconstructed game source.
// Feed an IEEE binary64 word and observe the real conversion and MXCSR.
#include <emmintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return 2;
    const uint64_t bits = strtoull(argv[1], 0, 16);
    double value;
    memcpy(&value, &bits, sizeof(value));
    _mm_setcsr(0x1f80);
    const __m128d input = _mm_load_sd(&value);
    const int result = _mm_cvttsd_si32(input);
    const unsigned flags = _mm_getcsr();
    printf("EAX=%08x MXCSR=%08x\n", (unsigned)result, flags);
    return 0;
}
