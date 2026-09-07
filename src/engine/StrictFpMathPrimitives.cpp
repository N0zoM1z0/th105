namespace th105 {

float __cdecl square_float_value(float value)
{
    double const promoted = value;
    return static_cast<float>(promoted * promoted);
}

int __cdecl square_int_value(int value)
{
    return value * value;
}

} // namespace th105
