namespace th105 {

unsigned __cdecl mt19937_next_u32();

int __cdecl selector_random_roll(int limit)
{
    const unsigned value = mt19937_next_u32();
    return static_cast<int>(
        value / (0xffffffffU / static_cast<unsigned>(limit)));
}

} // namespace th105
