#include "characters/ReimuInputPolicy.hpp"
#include <cmath>
namespace th105 {
#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define I(offset) FIELD(int, offset)
#define U(offset) FIELD(unsigned, offset)
#define S(offset) FIELD(short, offset)
#define C(offset) FIELD(signed char, offset)
#define B(offset) FIELD(unsigned char, offset)
#define F(offset) FIELD(float, offset)
#define FRONT (*reinterpret_cast<ReimuInputSequenceView *>(reinterpret_cast<unsigned char *>(this) + 0x55C)->at(0))
#define SURFACE (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) != 0)
#define PERMITTED ((S(0x13C) > 299 && I(0x180) != 0 && I(0x180) != 3) || S(0x13C) < 300)
#define OVERRIDE(flag) (S(0x13C) >= 500 && S(0x13C) <= 599 && B(flag) == 0)
#define COMMAND_OK(key, flag) (window <= command_window(key) || OVERRIDE(flag))
#define UP (I(0x6B8) > 0 || I(0x6D8) > 0)
#define FORWARD (I(0x6B4) * C(0x104) > 0 || I(0x6D4) * C(0x104) > 0)
#define DISPATCH(key, flag) { B(flag) = 1; pack_input(); if (window >= 10) B(0x491) |= 8; set_action(key); return; }
#define ACTION(key) { set_action(key); reset_input(); return; }
void ReimuInputPolicyView::dispatch_input()
{
    short const window = *reinterpret_cast<short *>(FIELD(unsigned char *, 0x15C) + 0x12);
    unsigned const flags = *reinterpret_cast<unsigned *>(FIELD(unsigned char *, 0x158) + 0x4C);
    unsigned const primary = flags & 0x20;
    unsigned const secondary = flags & 0x200000;
    if (I(0x6CC) == 1 && S(0x13C) <= 599) {
        I(0x6CC) = 4;
        pop_sequence();
        return;
    }
    if (primary || secondary) {
        if (U(0x728) >= 700 && U(0x728) < 800) {
            set_action(static_cast<unsigned short>(U(0x728)));
            pack_input();
            return;
        }
    }
    if (primary || secondary) {
        if (SURFACE) {
            if (secondary && window >= 10 && gate493ac0()) return;
            if (gate493b40()) return;
            if (gate493d90(window, secondary)) return;
            if (gate493f90(window, secondary)) return;
        } else {
            if (gate493c50()) return;
            int const count = (I(0x4B8) == 10) + 2;
            if (gate4940e0(window, secondary, count, 2)) return;
            if (gate4941d0(window, secondary, count, 2)) return;
            if (gate4942c0(window, secondary, count)) return;
        }
    }
    if (!primary) return;
    if (S(0x4B0) == 0) {
        if (SURFACE) {
            if (((U(0x6D0) > 0 && U(0x6D0) < 3) || U(0x6F0) > 0) && front_ready(0)) {
                if (gate494450(window)) return;
                if (window <= 100 && FRONT >= 200 && FRONT <= 299 && PERMITTED) {
                    pack_input();
                    switch (FRONT) {
                    case 200: finalize_command(600, window); return;
                    case 201: finalize_command(601, window); return;
                    case 206: finalize_command(606, window); return;
                    case 208: finalize_command(608, window); return;
                    case 209: finalize_command(609, window); return;
                    case 210: finalize_command(610, window); return;
                    case 214: finalize_command(614, window); return;
                    case 219: finalize_command(619, window); return;
                    }
                }
            }
            if (S(0x482) >= 200 && PERMITTED) {
                if (U(0x728) & 0x4000) {
                    if (C(0x60E) >= 1 && COMMAND_OK(550, 0x756)) DISPATCH(550, 0x756);
                    if (C(0x60A) >= 1 && COMMAND_OK(546, 0x756)) DISPATCH(546, 0x756);
                    if (COMMAND_OK(541, 0x756)) DISPATCH(541, 0x756);
                }
                if (U(0x728) & 0x2000) {
                    if (C(0x60E) >= 1 && COMMAND_OK(550, 0x756)) DISPATCH(550, 0x756);
                    if (C(0x60A) >= 1 && COMMAND_OK(545, 0x756)) DISPATCH(545, 0x756);
                    if (COMMAND_OK(540, 0x756)) DISPATCH(540, 0x756);
                }
                if (U(0x728) & 0x400) {
                    if (C(0x60B) >= 1 && COMMAND_OK(566, 0x757)) DISPATCH(566, 0x757);
                    if (COMMAND_OK(561, 0x757)) DISPATCH(561, 0x757);
                }
                if (U(0x728) & 0x200) {
                    if (C(0x60B) >= 1 && COMMAND_OK(565, 0x757)) DISPATCH(565, 0x757);
                    if (COMMAND_OK(560, 0x757)) DISPATCH(560, 0x757);
                }
                if (U(0x728) & 0x40) {
                    if (C(0x60D) >= 1 && COMMAND_OK(531, 0x755)) DISPATCH(531, 0x755);
                    if (C(0x609) >= 1 && COMMAND_OK(526, 0x755)) DISPATCH(526, 0x755);
                    if (COMMAND_OK(521, 0x755)) DISPATCH(521, 0x755);
                }
                if (U(0x728) & 0x20) {
                    if (C(0x60D) >= 1 && COMMAND_OK(530, 0x755)) DISPATCH(530, 0x755);
                    if (C(0x609) >= 1 && COMMAND_OK(525, 0x755)) DISPATCH(525, 0x755);
                    if (COMMAND_OK(520, 0x755)) DISPATCH(520, 0x755);
                }
                if (U(0x728) & 4) {
                    if (C(0x60C) >= 1 && COMMAND_OK(511, 0x754)) DISPATCH(511, 0x754);
                    if (C(0x608) >= 1 && COMMAND_OK(506, 0x754)) DISPATCH(506, 0x754);
                    if (COMMAND_OK(500, 0x754)) DISPATCH(501, 0x754);
                }
                if (U(0x728) & 2) {
                    if (C(0x60C) >= 1 && COMMAND_OK(510, 0x754)) DISPATCH(510, 0x754);
                    if (C(0x608) >= 1 && COMMAND_OK(505, 0x754)) DISPATCH(505, 0x754);
                    if (COMMAND_OK(500, 0x754)) DISPATCH(500, 0x754);
                }
            }
        } else {
            if (((U(0x6D0) > 0 && U(0x6D0) < 3) || U(0x6F0) > 0) && front_ready(0)
                && window <= 100 && FRONT >= 200 && FRONT <= 299 && PERMITTED) {
                switch (FRONT) {
                case 200: finalize_command(650, window); return;
                case 201: finalize_command(651, window); return;
                case 208: finalize_command(658, window); return;
                }
            }
            if (S(0x482) >= 200 && PERMITTED) {
                if (U(0x728) & 0x4000) {
                    if (C(0x60A) >= 1 && COMMAND_OK(546, 0x756)) DISPATCH(546, 0x756);
                    if (C(0x60A) == 0 && C(0x60E) == 0 && COMMAND_OK(541, 0x756)) DISPATCH(541, 0x756);
                }
                if (U(0x728) & 0x2000) {
                    if (C(0x60A) >= 1 && COMMAND_OK(545, 0x756)) DISPATCH(545, 0x756);
                    if (C(0x60A) == 0 && C(0x60E) == 0 && COMMAND_OK(540, 0x756)) DISPATCH(540, 0x756);
                }
                if ((U(0x728) & 0x40) && C(0x609) == 0 && C(0x60D) == 0 && COMMAND_OK(523, 0x755)) DISPATCH(523, 0x755);
                if ((U(0x728) & 0x20) && C(0x609) == 0 && C(0x60D) == 0 && COMMAND_OK(522, 0x755)) DISPATCH(522, 0x755);
                if (U(0x728) & 4) {
                    if (C(0x60C) >= 1 && COMMAND_OK(513, 0x754)) DISPATCH(513, 0x754);
                    if (C(0x608) >= 1 && COMMAND_OK(508, 0x754)) DISPATCH(508, 0x754);
                    if (C(0x608) == 0 && C(0x60C) == 0 && COMMAND_OK(502, 0x754)) DISPATCH(503, 0x754);
                }
                if (U(0x728) & 2) {
                    if (C(0x60C) >= 1 && COMMAND_OK(512, 0x754)) DISPATCH(512, 0x754);
                    if (C(0x608) >= 1 && COMMAND_OK(507, 0x754)) DISPATCH(507, 0x754);
                    if (C(0x608) == 0 && C(0x60C) == 0 && COMMAND_OK(502, 0x754)) DISPATCH(502, 0x754);
                }
            }
        }
    }

    if (I(0x4B8) != 5 && ((U(0x6F4) > 0 && U(0x6F4) < 3) || I(0x6BC) == 2 || U(0x6DC) > 0)) {
        if (SURFACE) {
            if (S(0x13C) == 200 && I(0x6B8) == 0 && FORWARD && window <= command_window(305)) ACTION(305);
            if (PERMITTED) {
                if (UP && FORWARD && window <= command_window(304)) ACTION(304);
                if (UP && window <= command_window(303)) ACTION(303);
                if (I(0x6B8) == 0 && FORWARD && window <= command_window(302)) ACTION(302);
            }
            if (S(0x13C) > 299 && I(0x180) != 0 && I(0x180) != 3) {
                if (S(0x13C) == 321) ACTION(322);
                if (S(0x13C) == 320) ACTION(321);
                if (S(0x13C) == 300) ACTION(320);
            }
            float const delta = F(0xEC) - *reinterpret_cast<float *>(FIELD(unsigned char *, 0x170) + 0xEC);
            float const distance = static_cast<float>(std::fabs(delta));
            if (distance > 120.0 && window <= command_window(301) && PERMITTED) ACTION(301);
            if (window <= command_window(300) && PERMITTED) ACTION(300);
        } else {
            if (PERMITTED) {
                if ((I(0x6B8) < 0 || I(0x6D8) < 0) && I(0x6B4) == 0
                    && window <= command_window(309)) ACTION(309);
                if (UP && window <= command_window(308)) ACTION(308);
                if (I(0x6B8) == 0 && FORWARD && window <= command_window(307)) ACTION(307);
                if (window <= command_window(306) && PERMITTED) ACTION(306);
            }
        }
    }

    if ((U(0x6F8) > 0 && U(0x6F8) < 3) || I(0x6C0) == 2 || U(0x6E0) > 0) {
        if (SURFACE) {
            if (S(0x13C) == 200 && I(0x4B8) != 5 && I(0x6B8) == 0 && FORWARD && window <= command_window(408)) ACTION(408);
            if (PERMITTED) {
                if (UP && FORWARD && window <= command_window(402) && S(0x482) >= 200) ACTION(402);
                if (UP && window <= command_window(402) && S(0x482) >= 200) ACTION(402);
                if (I(0x6B8) == 0 && FORWARD && window <= command_window(401) && S(0x482) >= 200) ACTION(401);
                if (window <= command_window(400) && S(0x482) >= 200 && PERMITTED) ACTION(400);
            }
        } else {
            if (PERMITTED) {
                if (UP && window <= command_window(406) && S(0x482) >= 200) ACTION(406);
                if (window <= command_window(404) && S(0x482) >= 200 && PERMITTED) ACTION(404);
            }
        }
    }
    if ((U(0x6FC) > 0 && U(0x6FC) < 3) || I(0x6C4) == 2 || U(0x6E4) > 0) {
        if (SURFACE) {
            if (S(0x13C) == 200 && I(0x4B8) != 5 && I(0x6B8) == 0 && FORWARD && window <= command_window(418)) ACTION(418);
            if (S(0x482) >= 200 && PERMITTED) {
                if (UP && FORWARD && window <= command_window(412)) ACTION(412);
                if (UP && window <= command_window(412)) ACTION(412);
                if (I(0x6B8) == 0 && FORWARD && window <= command_window(410)) ACTION(410);
                if (window <= command_window(410) && PERMITTED) ACTION(410);
            }
        } else {
            if (S(0x482) >= 200 && PERMITTED) {
                if (UP && window <= command_window(416)) ACTION(416);
                if (window <= command_window(414) && PERMITTED) ACTION(414);
            }
        }
    }
}
#undef ACTION
#undef DISPATCH
#undef FORWARD
#undef UP
#undef COMMAND_OK
#undef OVERRIDE
#undef PERMITTED
#undef SURFACE
#undef FRONT
#undef F
#undef B
#undef C
#undef S
#undef U
#undef I
#undef FIELD
}
