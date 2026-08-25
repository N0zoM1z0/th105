namespace th105 {

int __cdecl selector_random_roll(int limit);

int __stdcall selector_random_range(int lower, int upper)
{
    return lower + selector_random_roll(upper - lower);
}

} // namespace th105
