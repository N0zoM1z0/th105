namespace th105 {
struct EventEffectStateView;
extern EventEffectStateView *g_event_effect_state;
extern unsigned char g_battle_transition_mode;
extern int g_event_runtime_state;
extern int g_event_runtime_zero;
int __cdecl selector_random_roll(int);
void __cdecl dispatch_indexed_event(unsigned);
int __cdecl emit_weather_effect_665470(int, float, float, int, int);
#define V(o) (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(g_event_effect_state)+(o)))
#define T static_cast<unsigned>(g_event_runtime_zero)
#define R(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
void __cdecl update_weather_emission_660b30(int event)
{
    ++g_event_runtime_zero;
    if (g_event_runtime_state != event) {
        g_event_runtime_state = event;
        g_event_runtime_zero = 0;
    }
    short category = 0;
    switch (static_cast<signed char>(g_battle_transition_mode)) {
    case 4: case 6: case 14: case 16: category = 1; break;
    case 5: category = 2; break;
    case 0: category = 0; break;
    case 1: category = 0; break;
    case 2: category = 0; break;
    case 3: category = 0; break;
    case 10: category = 0; break;
    case 11: category = 0; break;
    case 12: category = 0; break;
    case 13: category = 0; break;
    case 15: category = 0; break;
    case 17: category = 0; break;
    case 18: category = 0; break;
    }
    switch (event) {
    case 16:
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        break;
    case 0:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
            if (T == 0) emit_weather_effect_665470(5,1280.0f,900.0f,1,1);
            if (category == 0) {
                if (T % 180u == 0) emit_weather_effect_665470(1,R(1280),900.0f,1,1);
                if (T % 180u == 45) emit_weather_effect_665470(2,R(1280),900.0f,1,1);
                if (T % 180u == 90) emit_weather_effect_665470(3,R(1280),900.0f,1,1);
                if (T % 180u == 135) emit_weather_effect_665470(4,R(1280),900.0f,1,1);
            }
        }
        break;
    case 1:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            if (T == 0) dispatch_indexed_event(100);
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
            if (T % 90u == 0) emit_weather_effect_665470(11,-R(480),1560.0f,1,1);
        }
        break;
    case 2:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            V(0xdc) = -0.03f; V(0xe0) = -0.03f; V(0xe4) = -0.03f;
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 3:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 4:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            V(0xdc) = -0.1f; V(0xe0) = -0.1f; V(0xe4) = -0.1f;
            if (T == 0) dispatch_indexed_event(105);
            if (T % 4u == 0) {
                emit_weather_effect_665470(41,static_cast<float>(R(1280)-480.0),static_cast<float>(1560.0 - R(280)),1,1);
            }
            if (T % 4u == 2) {
                emit_weather_effect_665470(42,static_cast<float>(R(1280)-480.0),static_cast<float>(1560.0 - R(280)),1,-1);
            }
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 5:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 6:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0 || g_battle_transition_mode == 16) {
            V(0xdc) = 0.05f; V(0xe0) = 0.05f; V(0xe4) = 0.05f;
            if (T == 0) emit_weather_effect_665470(61,640.0f,-100.0f,1,1);
            if (T % 30u == 0) {
                emit_weather_effect_665470(62,R(1280),R(480),1,1);
            }
            if (T % 30u == 15) {
                emit_weather_effect_665470(63,R(1280),R(480),1,1);
            }
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 7:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            V(0xdc) = -0.1f; V(0xe0) = -0.1f; V(0xe4) = -0.1f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 6u == 0) {
                if (static_cast<unsigned>(selector_random_roll(100)) <= 50)
                    emit_weather_effect_665470(71,R(1280),static_cast<float>(R(640) + 480.0),1,1);
                else
                    emit_weather_effect_665470(71,R(1280),static_cast<float>(R(640) + 480.0),-1,1);
            }
            if (T % 90u == 0) {
                emit_weather_effect_665470(72,R(1280),static_cast<float>(R(640) + 480.0),1,1);
            }
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 8:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
            if (T == 0) {
                dispatch_indexed_event(101);
                emit_weather_effect_665470(81,0.0f,860.0f,1,1);
                emit_weather_effect_665470(86,0.0f,0.0f,1,-1);
            }
            if (T % 240u == 0) emit_weather_effect_665470(82,R(1280),900.0f,1,1);
            if (T % 240u == 60) emit_weather_effect_665470(83,R(1280),900.0f,1,1);
            if (T % 240u == 120) emit_weather_effect_665470(84,R(1280),900.0f,1,1);
            if (T % 240u == 180) emit_weather_effect_665470(85,R(1280),900.0f,1,1);
        }
        break;
    case 9:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            if (T == 0) dispatch_indexed_event(100);
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
            if (T % 3u == 0) {
                if (static_cast<unsigned>(selector_random_roll(100)) <= 50)
                    emit_weather_effect_665470(91,R(1280),static_cast<float>(R(320) + 960.0),1,1);
                else
                    emit_weather_effect_665470(91,R(1280),static_cast<float>(R(320) + 960.0),-1,1);
            }
        }
        break;
    case 17:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = -0.15f;
            if (T == 0) {
                dispatch_indexed_event(104);
                emit_weather_effect_665470(101,0.0f,-120.0f,1,1);
            }
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 10:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            if (T == 0) dispatch_indexed_event(104);
            V(0xdc) = -0.1f; V(0xe0) = -0.1f; V(0xe4) = -0.1f;
            if (T % 20u == 0) emit_weather_effect_665470(111,static_cast<float>(static_cast<unsigned>(selector_random_roll(640))+556u),2400.0f,1,1);
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 11:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            if (T == 0) dispatch_indexed_event(104);
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
            if (T % 15u == 0) {
                emit_weather_effect_665470(121,static_cast<float>(-400.0-R(128)),static_cast<float>(static_cast<unsigned>(selector_random_roll(640))-180u),1,1);
            }
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 12:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            V(0xdc) = -0.05f; V(0xe0) = -0.05f; V(0xe4) = -0.05f;
            if (T == 0) emit_weather_effect_665470(131,0.0f,-240.0f,1,1);
            if (T % 90u == 0) {
                if (static_cast<unsigned>(selector_random_roll(100)) <= 50)
                    emit_weather_effect_665470(132,R(1600),-R(40),1,1);
                else
                    emit_weather_effect_665470(132,R(1600),R(40),1,-1);
            }
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 13:
        if (category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else if (category == 0) {
            if (T == 0) dispatch_indexed_event(104);
            V(0xdc) = -0.2f; V(0xe0) = -0.2f; V(0xe4) = -0.2f;
            if (T % 20u == 0) emit_weather_effect_665470(141,static_cast<float>(static_cast<unsigned>(selector_random_roll(640))+556u),2400.0f,1,1);
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 14:
        if (category == 0 || category == 2) {
            V(0xdc) = -0.5f; V(0xe0) = -0.5f; V(0xe4) = -0.0f;
            if (T == 0) emit_weather_effect_665470(151,0.0f,900.0f,1,-2);
            if (T % 180u == 0) emit_weather_effect_665470(152,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 45) emit_weather_effect_665470(153,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
            if (T % 180u == 90) emit_weather_effect_665470(154,static_cast<float>(R(640)+320.0),1980.0f,1,1);
            if (T % 180u == 135) emit_weather_effect_665470(155,static_cast<float>(R(640)+320.0),1980.0f,-1,1);
        } else {
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        }
        break;
    case 15:
            V(0xdc) = 0.0f; V(0xe0) = 0.0f; V(0xe4) = 0.0f;
        break;
    }
}
}
