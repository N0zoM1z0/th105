namespace th105 {

int g_mt19937_index = 625;
unsigned g_mt19937_state[624];
unsigned g_mt19937_twist_xor[2] = { 0, 0x9908b0dfU };

void __cdecl mt19937_seed_u32(unsigned seed)
{
    g_mt19937_state[0] = seed;
    int index;
    for (index = 1; index < 624; ++index) {
        g_mt19937_state[index] = index + 1812433253U *
            (g_mt19937_state[index - 1] ^
             (g_mt19937_state[index - 1] >> 30));
    }
    g_mt19937_index = index;
}

unsigned __cdecl mt19937_next_u32()
{
    unsigned value;

    if (g_mt19937_index >= 624) {
        if (g_mt19937_index == 625) {
            mt19937_seed_u32(5489U);
        }

        int index;
        for (index = 0; index < 227; ++index) {
            value = (g_mt19937_state[index] & 0x80000000U) |
                (g_mt19937_state[index + 1] & 0x7fffffffU);
            g_mt19937_state[index] =
                g_mt19937_state[index + 397] ^
                (value >> 1) ^
                g_mt19937_twist_xor[value & 1U];
        }
        for (; index < 623; ++index) {
            value = (g_mt19937_state[index] & 0x80000000U) |
                (g_mt19937_state[index + 1] & 0x7fffffffU);
            g_mt19937_state[index] =
                g_mt19937_state[index - 227] ^
                (value >> 1) ^
                g_mt19937_twist_xor[value & 1U];
        }

        value = (g_mt19937_state[623] & 0x80000000U) |
            (g_mt19937_state[0] & 0x7fffffffU);
        g_mt19937_state[623] =
            g_mt19937_state[396] ^
            (value >> 1) ^
            g_mt19937_twist_xor[value & 1U];
        g_mt19937_index = 0;
    }

    value = g_mt19937_state[g_mt19937_index++];
    value ^= value >> 11;
    value ^= (value & 0xff3a58adU) << 7;
    value ^= (value & 0xffffdf8cU) << 15;
    return value ^ (value >> 18);
}

} // namespace th105
