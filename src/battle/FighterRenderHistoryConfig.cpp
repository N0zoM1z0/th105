namespace th105 {

struct FighterPhaseRenderStateConfigView {
    signed char set_period(signed char value);
    int set_color_mask(int value);
};

struct FighterRenderHistoryConfigView {
    unsigned char reserved_000[0x670];
    int countdown_670;
    FighterPhaseRenderStateConfigView render_state_674;

    int configure_render_history(
        int countdown,
        signed char period,
        int color_mask);
};

int FighterRenderHistoryConfigView::configure_render_history(
    int countdown,
    signed char period,
    int color_mask)
{
    countdown_670 = countdown;
    render_state_674.set_period(period);
    return render_state_674.set_color_mask(color_mask);
}

} // namespace th105
