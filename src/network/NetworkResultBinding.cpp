namespace th105 {

class NetworkSessionResultView {
public:
    virtual void slot_00();
    virtual void reset_slot_04();

    void bind_result_input(void *input, void *player_records);
    void finalize_result_binding_44dcb0();

private:
    template <typename T>
    __forceinline T &field(unsigned offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }
};

void NetworkSessionResultView::bind_result_input(
    void *input, void *player_records)
{
    field<void *>(0x204) = input;
    field<void *>(0x208) = input;
    field<void *>(0x200) =
        reinterpret_cast<unsigned char *>(player_records) + 0x138;

    unsigned char one = 1;
    void *primary_input = reinterpret_cast<unsigned char *>(this) + 0xf8;
    void *alternate_input = reinterpret_cast<unsigned char *>(this) + 0x174;
    field<void *>(0x1f0) = primary_input;
    field<void *>(0x1f8) = alternate_input;
    field<unsigned char>(0x80) = one;
    field<unsigned char>(0x81) = one;

    signed char minus_one = -1;
    field<signed char>(0x78) = minus_one;
    field<signed char>(0x6c) = minus_one;
    field<signed char>(0x9c) = minus_one;
    field<unsigned char>(0x6b8) = 0;
    reset_slot_04();

    int zero = 0;
    field<int>(0x6bc) = -1;
    field<int>(0x6c4) = zero;
    field<int>(0x6c0) = zero;
    finalize_result_binding_44dcb0();
}

} // namespace th105
