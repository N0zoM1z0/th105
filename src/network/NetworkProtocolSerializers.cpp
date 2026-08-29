namespace th105 {

struct NetworkPacketByte12 {
    unsigned char reserved_000[8];
    unsigned char value_008;

    unsigned int serialize_type1(unsigned char *out) const;
    void parse_type1(const unsigned char *in);
    unsigned int serialize_type2(unsigned char *out) const;
    unsigned int serialize_type7(unsigned char *out) const;
};

struct NetworkPacketTypeOnly8 {
    unsigned int serialize_type5(unsigned char *out) const;
    unsigned int serialize_type8(unsigned char *out) const;
};

unsigned int NetworkPacketByte12::serialize_type1(unsigned char *out) const
{
    out[0] = 1;
    out[1] = value_008;
    return 2;
}

void NetworkPacketByte12::parse_type1(const unsigned char *in)
{
    value_008 = in[1];
}

unsigned int NetworkPacketByte12::serialize_type2(unsigned char *out) const
{
    out[0] = 2;
    out[1] = value_008;
    return 2;
}

unsigned int NetworkPacketTypeOnly8::serialize_type5(unsigned char *out) const
{
    out[0] = 5;
    return 1;
}

unsigned int NetworkPacketByte12::serialize_type7(unsigned char *out) const
{
    out[0] = 7;
    out[1] = value_008;
    return 2;
}

unsigned int NetworkPacketTypeOnly8::serialize_type8(unsigned char *out) const
{
    out[0] = 8;
    return 1;
}

} // namespace th105
