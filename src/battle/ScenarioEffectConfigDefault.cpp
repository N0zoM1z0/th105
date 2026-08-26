namespace th105 {

struct ScenarioEffectConfigDefaultView {
    char text_000[0x100];
    unsigned char color_100[6];
    unsigned char reserved_106[2];
    int count_108;
    int duration_10c;
    unsigned char flag_110;
    unsigned char flag_111;
    unsigned char flag_112;
    unsigned char reserved_113;
    int interval_114;
    int mode_118;
    int state_11c;
    int option_120;
    int option_124;

    ScenarioEffectConfigDefaultView();
};

ScenarioEffectConfigDefaultView::ScenarioEffectConfigDefaultView()
{
    duration_10c = 400;
    flag_110 = 0;
    flag_111 = 0;
    flag_112 = 0;
    option_120 = 0;
    option_124 = 0;
    mode_118 = 0;
    state_11c = 0;
    interval_114 = 100000;
}

} // namespace th105
