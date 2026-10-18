// Original JP 1.06a Reimu CPU slot +0x58, 0x0048D390..0x0049120F.
// Source-present candidate, not an exact match. See docs/REIMU_CPU_ROLL_FIELD_2026_10_19.md.
#include "CpuActionPolicies.hpp"
#include "engine/AngleAtan2.hpp"
#include "../battle/Collision.hpp"
#include <stdlib.h>
namespace th105 {
typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;
unsigned int __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);
#define CPU_FIELD(offset) (reinterpret_cast<unsigned char *>(this) + (offset))
void ReimuCpuActionPolicyView::update_cpu_action_policy()
{
bool v18;
char v89;
int v90;
char v91;
int v93;
int v94;
double v95;
double v96;
double v97;
int v98;
double v99;
double v100;
bool v101;
char v102;
int v103;
int v104;
__int16 v105;
char v107;
int v108;
__int16 v109;
char v110;
    command_flags_724 = 0;
    command_flags_728 = 0;
    const int dx = (int)(other_fighter_170->x_ec - x_ec);
    const float horizontal_distance = (float)abs(dx);
    const int dy = (int)(other_fighter_170->y_f0 - y_f0);
    --policy_counter_768;
    const float vertical_distance = (float)abs(dy);
    control_6bc = 0; control_6c0 = 0; control_6c4 = 0;
    control_6c8 = 0; control_6cc = 0; control_6d0 = 0;
    if (action_13c > 49 && action_13c < 150) {
        policy_counter_76c = 0; policy_counter_76a = 0; policy_counter_766 = 0;
        policy_counter_768 = 0; policy_counter_764 = 0;
        if (mt19937_next_u32() % 100 <= 10) {
            control_6bc = 1;
            control_6b4 = selector_random_roll(3) - 1;
        }
    }
    if (action_13c <= 199) { policy_counter_76c = 0; policy_counter_764 = 0; }
    policy_random_76e = (short)selector_random_roll(1000);
    if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(other_fighter_170) + 0x174) <= 0) return;
    // The first switch chooses character-specific follow-ups. Each action
    // initializes the signed field independently; bounds read that word
    // directly rather than copying it into one scalar for the whole case.
#define PREPARE_COUNTER() \
    if (policy_state_180 == 0) policy_counter_764 = 0; \
    else if (policy_state_180 != 3 && policy_counter_764 == 0) \
        policy_counter_764 = (short)selector_random_roll(100)
#define RESOURCE (*reinterpret_cast<short *>(CPU_FIELD(0x482)))
#define SKILL(offset) (*reinterpret_cast<signed char *>(CPU_FIELD(offset)))
#define FRONT_SEQUENCE() (*reinterpret_cast<short *>(reinterpret_cast<FighterSequenceController *>(sequence_controller_55c)->entry_at_checked(0)))
    switch (action_13c) {
    case 200:
        if (policy_counter_764 == 0) {
            policy_counter_764 = 100;
            if (horizontal_distance >= 700.0f)
                policy_counter_764 = (short)(selector_random_roll(100) + 1);
        }
        if (((x_ec > other_fighter_170->x_ec && facing_104 == -1) ||
             (x_ec < other_fighter_170->x_ec && facing_104 == 1)) && policy_counter_764 >= 50) {
            if (horizontal_distance < 220.0 && (unsigned)selector_random_roll(1000) < 85 && vertical_distance < 50.0) {
                control_6b4 = facing_104; control_6bc = 2;
            } else if (horizontal_distance >= 400.0 && horizontal_distance <= 600.0f &&
                       vertical_distance < 80.0f && (unsigned)selector_random_roll(1000) < 50) {
                control_6b4 = facing_104; control_6c0 = 2;
            } else if (horizontal_distance >= 200.0 && horizontal_distance <= 350.0f &&
                       vertical_distance < 150.0f && (unsigned)selector_random_roll(1000) < 50) {
                control_6b4 = facing_104; control_6c4 = 2;
            }
        }
        break;
    case 300:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 10 && policy_counter_764 <= 90) {
            control_6bc = 2; control_6b4 = 0; control_6b8 = 0;
        } else if (policy_counter_764 >= 90) {
            control_6bc = 2; control_6b4 = facing_104; control_6b8 = 0;
        }
        break;
    case 301:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 30 && policy_counter_764 <= 65) {
            control_6bc = 2; control_6b4 = facing_104; control_6b8 = 0;
        } else if (policy_counter_764 >= 65 && policy_counter_764 <= 80 && RESOURCE >= 400) {
            control_6c0 = 2; control_6b4 = 0; control_6b8 = 0;
        } else if (policy_counter_764 >= 80 && policy_counter_764 <= 95 && RESOURCE >= 400 && other_fighter_170->y_f0 == 0.0f) {
            control_6c0 = 2; control_6b4 = 0; control_6b8 = 1;
        }
        break;
    case 302:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 30 && RESOURCE >= 300) {
            control_6c0 = 2; control_6b4 = 0; control_6b8 = 0;
        } else if (policy_counter_764 >= 30 && policy_counter_764 <= 50 && RESOURCE >= 400) {
            control_6c4 = 2; control_6b4 = 0; control_6b8 = 0;
        } else if (SKILL(0x60b) == 0 && policy_state_180 == 1 && policy_counter_764 >= 60 && policy_counter_764 <= 95 && RESOURCE >= 200 &&
                   ((facing_104 == 1 && x_ec > 880.0) || (facing_104 == -1 && x_ec < 300.0f))) {
            command_flags_728 = 0x200;
        } else if (policy_counter_764 >= 60 && policy_counter_764 <= 65 && RESOURCE >= 200 && other_fighter_170->y_f0 == 0.0f) {
            control_6c0 = 2; control_6b4 = 0; control_6b8 = 1;
        } else if (policy_counter_764 >= 65 && policy_counter_764 <= 75 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 75 && policy_counter_764 <= 76 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 77 && policy_counter_764 <= 78 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 79 && policy_counter_764 <= 81 && RESOURCE >= 400 && policy_state_180 != 1) command_flags_728 = 0x20;
        else if (SKILL(0x609) > 0 && policy_counter_764 >= 82 && policy_counter_764 <= 84 && RESOURCE >= 400 && policy_state_180 != 1) command_flags_728 = 0x40;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            switch (FRONT_SEQUENCE()) {
            case 200: case 201: case 202: case 204: case 205: case 206: case 209: case 210: case 212:
                control_6d0 = 2; break;
            case 214:
                if (policy_state_180 == 1 && ((facing_104 == 1 && x_ec > 980.0) || (facing_104 == -1 && x_ec < 200.0)))
                    control_6d0 = 2;
                break;
            }
        }
        break;
    case 303:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 30 && policy_counter_764 <= 65) {
            control_6bc = 2; control_6b4 = facing_104; control_6b8 = 0;
        } else if (policy_counter_764 >= 65 && policy_counter_764 <= 80 && RESOURCE >= 400) {
            control_6c0 = 2; control_6b4 = 0; control_6b8 = 0;
        } else if (policy_counter_764 >= 80 && policy_counter_764 <= 95 && RESOURCE >= 400 && other_fighter_170->y_f0 == 0.0f) {
            control_6c0 = 2; control_6b4 = 0; control_6b8 = 1;
        } else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            switch (FRONT_SEQUENCE()) {
            case 200: case 201: control_6d0 = 2; break;
            case 209:
                if (policy_state_180 == 1 && ((facing_104 == 1 && x_ec > 880.0) || (facing_104 == -1 && x_ec < 300.0f))) {
                    control_6d0 = 2; break;
                }
                // The interior branch shares the action214 wall check.
                if (policy_state_180 != 1) break;
            case 214:
                if (policy_state_180 == 1 && ((facing_104 == 1 && x_ec > 980.0) || (facing_104 == -1 && x_ec < 200.0)))
                    control_6d0 = 2;
                break;
            }
        }
        break;
    case 304:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 65 && policy_counter_764 <= 75 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 75 && policy_counter_764 <= 80 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 80 && policy_counter_764 <= 85 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            const short sequence = FRONT_SEQUENCE();
            if (sequence == 200 || sequence == 201 || sequence == 208) control_6d0 = 2;
        }
        break;
    case 305:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 65 && policy_counter_764 <= 75 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 75 && policy_counter_764 <= 80 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 80 && policy_counter_764 <= 85 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 85 && policy_counter_764 <= 100 && sequence_state_55a > 0 && FRONT_SEQUENCE() == 214 && policy_state_180 == 1)
            control_6d0 = 2;
        break;
    case 306:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 15 && y_f0 < other_fighter_170->y_f0) {
            control_6bc = 1; control_6b4 = facing_104; control_6b8 = 0;
        } else if (policy_counter_764 >= 15 && policy_counter_764 <= 25 && RESOURCE >= 300) {
            control_6c0 = 2; control_6b4 = 0;
            control_6b8 = -(int)(short)(int)atan2_degrees(other_fighter_170->y_f0 - y_f0,
                (float)facing_104 * (other_fighter_170->x_ec - x_ec)) > 29;
        } else if (policy_counter_764 >= 25 && policy_counter_764 <= 30 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 30 && policy_counter_764 <= 40 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 40 && policy_counter_764 <= 45 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0 && FRONT_SEQUENCE() == 208) control_6d0 = 2;
        break;
    case 307:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 30 && RESOURCE >= 300) {
            control_6c0 = 2; control_6b4 = 0;
            control_6b8 = -(int)(short)(int)atan2_degrees(other_fighter_170->y_f0 - y_f0,
                (float)facing_104 * (other_fighter_170->x_ec - x_ec)) > 29;
        } else if (policy_counter_764 >= 35 && policy_counter_764 <= 40 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 40 && policy_counter_764 <= 42 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 42 && policy_counter_764 <= 44 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0 && FRONT_SEQUENCE() == 208) control_6d0 = 2;
        break;
    case 308:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 25 && RESOURCE >= 300) {
            control_6c0 = 2; control_6b4 = 0;
            control_6b8 = -(int)(short)(int)atan2_degrees(other_fighter_170->y_f0 - y_f0,
                (float)facing_104 * (other_fighter_170->x_ec - x_ec)) > 19;
        } else if (policy_counter_764 >= 25 && policy_counter_764 <= 35 && RESOURCE >= 300) {
            control_6c4 = 2; control_6b4 = 0; control_6b8 = 1;
        } else if (policy_counter_764 >= 40 && policy_counter_764 <= 45 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 45 && policy_counter_764 <= 50 && RESOURCE >= 400) command_flags_728 = 0x4000;
        break;
    case 320:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 90) { control_6bc = 2; control_6b4 = 0; control_6b8 = 0; }
        break;
    case 321:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 50) { control_6bc = 2; control_6b4 = 0; control_6b8 = 0; }
        else if (policy_counter_764 >= 50 && policy_counter_764 <= 75) { control_6bc = 2; control_6b4 = facing_104; control_6b8 = 0; }
        else if (policy_counter_764 >= 75 && policy_counter_764 <= 80 && RESOURCE >= 400) { control_6bc = 2; control_6b4 = 0; control_6b8 = 0; }
        else if (policy_counter_764 >= 80 && policy_counter_764 <= 85 && RESOURCE >= 400 && other_fighter_170->y_f0 == 0.0f) {
            control_6bc = 2; control_6b4 = 0; control_6b8 = 1;
        }
        break;
    case 400: case 401:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 10 && RESOURCE >= 400) { control_6c4 = 2; control_6b4 = 0; control_6b8 = 1; }
        else if (policy_counter_764 >= 10 && policy_counter_764 <= 20 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 20 && policy_counter_764 <= 25 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 25 && policy_counter_764 <= 30 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            const short sequence = FRONT_SEQUENCE();
            if (sequence == 200 || sequence == 201 || (sequence == 209 && policy_state_180 == 1 && horizontal_distance < 300.0f)) control_6d0 = 2;
        }
        break;
    case 402:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 10 && RESOURCE >= 400) { control_6c4 = 2; control_6b4 = 0; control_6b8 = 1; }
        else if (policy_counter_764 >= 10 && policy_counter_764 <= 20 && RESOURCE >= 400) command_flags_728 = 2;
        else if (policy_counter_764 >= 20 && policy_counter_764 <= 25 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 25 && policy_counter_764 <= 30 && RESOURCE >= 400) command_flags_728 = 0x4000;
        break;
    case 404: case 405: case 406:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 5 && RESOURCE >= 400) { control_6c4 = 2; control_6b4 = 0; control_6b8 = 1; }
        else if (policy_counter_764 >= 5 && policy_counter_764 <= 20 && RESOURCE >= 400 && vertical_distance < 150.0f) command_flags_728 = 2;
        else if (policy_counter_764 >= 20 && policy_counter_764 <= 25 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 25 && policy_counter_764 <= 30 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 30 && policy_counter_764 <= 32 && RESOURCE >= 400 && vertical_distance < 100.0) command_flags_728 = 0x20;
        else if (policy_counter_764 >= 32 && policy_counter_764 <= 34 && RESOURCE >= 400 && vertical_distance < 100.0) command_flags_728 = 0x40;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            const short sequence = FRONT_SEQUENCE(); if (sequence == 200 || sequence == 201) control_6d0 = 2;
        }
        break;
    case 410: case 411:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 10 && RESOURCE >= 400 && vertical_distance < 150.0f) command_flags_728 = 2;
        else if (policy_counter_764 >= 10 && policy_counter_764 <= 15 && RESOURCE >= 400) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 15 && policy_counter_764 <= 20 && RESOURCE >= 400) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            const short sequence = FRONT_SEQUENCE(); if (sequence == 200 || sequence == 208) control_6d0 = 2;
        }
        break;
    case 414:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 0 && policy_counter_764 <= 15 && RESOURCE >= 600 && vertical_distance < 150.0f) command_flags_728 = 2;
        else if (policy_counter_764 >= 20 && policy_counter_764 <= 25 && RESOURCE >= 600) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 25 && policy_counter_764 <= 30 && RESOURCE >= 600) command_flags_728 = 0x4000;
        else if (policy_counter_764 >= 95 && policy_counter_764 <= 100 && sequence_state_55a > 0) {
            const short sequence = FRONT_SEQUENCE(); if (sequence == 200 || sequence == 208) control_6d0 = 2;
        }
        break;
    case 416:
        PREPARE_COUNTER();
        if (policy_counter_764 >= 20 && policy_counter_764 <= 25 && RESOURCE >= 600) command_flags_728 = 0x2000;
        else if (policy_counter_764 >= 25 && policy_counter_764 <= 30 && RESOURCE >= 600) command_flags_728 = 0x4000;
        break;
    }
#undef PREPARE_COUNTER
    if (policy_counter_766 == 0) {
        if (policy_counter_76c == 0) policy_counter_76c = (short)selector_random_roll(100);
        if (((x_ec > other_fighter_170->x_ec && facing_104 == -1) ||
             (x_ec < other_fighter_170->x_ec && facing_104 == 1)) &&
            (other_fighter_170->action_13c < 96 || other_fighter_170->action_13c > 139)) {
#define TRY_SEQUENCE(condition, limit, code) \
    if ((condition) && sequence_state_55a > 0 && (unsigned)selector_random_roll(1000) < (limit) && FRONT_SEQUENCE() == (code)) { \
        control_6d0 = 2; goto policy_dispatch; \
    }
            if (y_f0 == 0.0f) {
                if (other_fighter_170->y_f0 == 0.0f) {
                    if (horizontal_distance <= 90.0f) {
                        if ((unsigned)selector_random_roll(1000) < 75) {
                            control_6bc = 2; control_6b8 = 0; control_6b4 = 0; goto policy_dispatch;
                        }
                        if ((unsigned)selector_random_roll(1000) < 10 && SKILL(0x60b) == 0 && RESOURCE < 801) {
                            command_flags_728 = 0x2000; goto policy_dispatch;
                        }
                        TRY_SEQUENCE(true, 10, 214);
                    }
                    if ((unsigned)selector_random_roll(1000) < 75 && horizontal_distance < 350.0f && horizontal_distance > 120.0) goto approach_policy;
                    TRY_SEQUENCE(horizontal_distance < 280.0f, 10, 206);
                    TRY_SEQUENCE(horizontal_distance > 240.0, 10, 210);
                    TRY_SEQUENCE(horizontal_distance > 240.0, 10, 201);
                    TRY_SEQUENCE(horizontal_distance > 180.0f, 20, 200);
                    TRY_SEQUENCE(horizontal_distance > 320.0f, 10, 208);
                    if (horizontal_distance <= 240.0 && horizontal_distance >= 90.0f) {
                        if ((unsigned)selector_random_roll(1000) < 20 && RESOURCE >= 600) { command_flags_728 = 0x2000; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 20 && RESOURCE >= 600) { command_flags_728 = 0x4000; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 100) { control_6bc = 2; control_6b8 = 0; control_6b4 = 0; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 125) { control_6bc = 2; control_6b8 = 1; control_6b4 = 0; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 50) { control_6b4 = facing_104; control_6bc = 2; control_6b8 = 0; goto policy_dispatch; }
                    }
                    if (horizontal_distance <= 180.0f && horizontal_distance >= 120.0 && (unsigned)selector_random_roll(1000) <= 50) {
                        control_6bc = 2; control_6b4 = facing_104; control_6b8 = 1; goto policy_dispatch;
                    }
                    if (horizontal_distance < 520.0f && horizontal_distance > 180.0f) {
                        if ((unsigned)selector_random_roll(1000) < 11 && RESOURCE >= 400) { command_flags_728 = 0x20; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 11 && RESOURCE >= 400) { command_flags_728 = 0x40; goto policy_dispatch; }
                    }
                    if (policy_random_76e <= RESOURCE) {
                        if (horizontal_distance >= 120.0 && (unsigned)selector_random_roll(1000) < 6) {
                            control_6c0 = 2; control_6b8 = 1; control_6b4 = 0; goto policy_dispatch;
                        }
                        if (horizontal_distance >= 180.0f) {
                            if ((unsigned)selector_random_roll(1000) < 11) { control_6c0 = 2; control_6b8 = 0; control_6b4 = 0; goto policy_dispatch; }
                            if (horizontal_distance >= 240.0 && (unsigned)selector_random_roll(1000) < 6) {
                                control_6c4 = 2; control_6b8 = 0; control_6b4 = 0;
                            }
                        }
                    }
                } else {
                    if (horizontal_distance < 520.0f && horizontal_distance > 240.0) {
                        if ((unsigned)selector_random_roll(1000) < 6 && RESOURCE >= 600) { command_flags_728 = 0x20; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 6 && RESOURCE >= 600) { command_flags_728 = 0x40; goto policy_dispatch; }
                    }
                    TRY_SEQUENCE(horizontal_distance < 280.0f, 10, 206);
                    TRY_SEQUENCE(horizontal_distance > 240.0, 10, 210);
                    TRY_SEQUENCE(horizontal_distance > 240.0, 10, 201);
                    if (horizontal_distance > 180.0f && sequence_state_55a > 0 && (unsigned)selector_random_roll(1000) < 20 && FRONT_SEQUENCE() == 200 && vertical_distance < 150.0f) {
                        control_6d0 = 2; goto policy_dispatch;
                    }
                    TRY_SEQUENCE(horizontal_distance > 320.0f, 10, 208);
                    if (horizontal_distance <= 90.0f && vertical_distance < 80.0f && (unsigned)selector_random_roll(1000) < 5 && SKILL(0x60b) == 0) {
                        command_flags_728 = 0x2000; goto policy_dispatch;
                    }
                    if (horizontal_distance <= 150.0f && vertical_distance > 250.0 && (unsigned)selector_random_roll(1000) < 5 && SKILL(0x60b) == 0) {
                        command_flags_728 = 0x4000; goto policy_dispatch;
                    }
                    if ((unsigned)selector_random_roll(1000) < 75 && horizontal_distance < 350.0f && horizontal_distance > 120.0 && vertical_distance < 75.0f) goto approach_policy;
                    if (horizontal_distance <= 240.0 && horizontal_distance >= 150.0f) {
                        if ((unsigned)selector_random_roll(1000) < 10 && RESOURCE >= 600) { command_flags_728 = 0x2000; goto policy_dispatch; }
                        if ((unsigned)selector_random_roll(1000) < 20 && vertical_distance < 100.0) {
                            control_6b4 = facing_104; control_6bc = 2; control_6b8 = 0; goto policy_dispatch;
                        }
                    }
                    if (horizontal_distance <= 200.0 && horizontal_distance >= 100.0 && vertical_distance > 50.0 && vertical_distance < 150.0f && (unsigned)selector_random_roll(1000) < 10) {
                        control_6bc = 2; control_6b4 = facing_104; control_6b8 = 1; goto policy_dispatch;
                    }
                    if (policy_random_76e <= RESOURCE) {
                        if (horizontal_distance > 480.0 && (unsigned)selector_random_roll(1000) < 10 && RESOURCE >= 600) command_flags_728 = 0x2000;
                        else if (horizontal_distance <= 150.0f && (unsigned)selector_random_roll(1000) < 6) {
                            control_6c4 = 2; control_6b8 = 1; control_6b4 = 0;
                        }
                    }
                }
            } else if (other_fighter_170->y_f0 != 0.0f) {
                TRY_SEQUENCE(horizontal_distance > 240.0 && vertical_distance < 100.0, 10, 201);
                if (horizontal_distance > 120.0 && sequence_state_55a > 0 && (unsigned)selector_random_roll(1000) < 20 && FRONT_SEQUENCE() == 200 && vertical_distance < 150.0f) {
                    control_6d0 = 2; goto policy_dispatch;
                }
                TRY_SEQUENCE(horizontal_distance > 320.0f, 10, 208);
                if ((unsigned)selector_random_roll(1000) < 10 && RESOURCE >= 600) { command_flags_728 = 0x2000; goto policy_dispatch; }
                if ((unsigned)selector_random_roll(1000) < 10 && RESOURCE >= 600) { command_flags_728 = 0x4000; goto policy_dispatch; }
                if (horizontal_distance <= (float)(((0.0f < *reinterpret_cast<float *>(CPU_FIELD(0xf4))) + 1) * 120)) {
                    const int rising_toward_peer = !(other_fighter_170->y_f0 <= y_f0 || *reinterpret_cast<float *>(CPU_FIELD(0xf8)) <= 0.0f);
                    if (vertical_distance < (float)(rising_toward_peer * 150 + 100) && (unsigned)selector_random_roll(1000) < 50) {
                        control_6bc = 2; control_6b8 = 0; control_6b4 = 0; goto policy_dispatch;
                    }
                }
                if (horizontal_distance <= (float)((0.0f < *reinterpret_cast<float *>(CPU_FIELD(0xf4))) * 120 + 180)) {
                    const int falling_toward_peer = !(0.0f <= *reinterpret_cast<float *>(CPU_FIELD(0xf8)) || y_f0 <= other_fighter_170->y_f0);
                    if (vertical_distance < (float)((falling_toward_peer + 2) * 50) && (unsigned)selector_random_roll(1000) < 75) {
                        control_6bc = 2; control_6b8 = 1; control_6b4 = 0; goto policy_dispatch;
                    }
                }
                if (horizontal_distance <= 210.0 && horizontal_distance >= 90.0f && vertical_distance < 100.0 &&
                    other_fighter_170->y_f0 > y_f0 && (unsigned)selector_random_roll(1000) < 75) {
                    control_6b4 = facing_104; control_6bc = 2; control_6b8 = 0;
                } else {
                    // These three tests are independent: later choices can add
                    // another button and overwrite the aim of an earlier one.
                    if ((float)((vertical_distance < 200.0) * 180 + 120) < horizontal_distance && (unsigned)selector_random_roll(1000) < 50) {
                        control_6c0 = 2;
                        const short aim = (short)(int)atan2_degrees(other_fighter_170->y_f0 - y_f0,
                            (float)facing_104 * (other_fighter_170->x_ec - x_ec));
                        control_6b4 = 0; control_6b8 = -(int)aim > 29;
                    }
                    if (horizontal_distance > 250.0 && vertical_distance < 200.0 && (unsigned)selector_random_roll(1000) < 20) {
                        control_6c4 = 2; control_6b8 = 0; control_6b4 = 0;
                    }
                    if (horizontal_distance < 300.0f && vertical_distance > 200.0 && other_fighter_170->y_f0 < y_f0 && (unsigned)selector_random_roll(1000) < 25) {
                        control_6c4 = 2; control_6b8 = 0; control_6b4 = 0;
                    }
                }
            } else {
                TRY_SEQUENCE(horizontal_distance > 240.0 && vertical_distance < 100.0, 10, 201);
                if (horizontal_distance > 180.0f && sequence_state_55a > 0 && (unsigned)selector_random_roll(1000) < 20 && FRONT_SEQUENCE() == 200 && vertical_distance < 150.0f) {
                    control_6d0 = 2; goto policy_dispatch;
                }
                TRY_SEQUENCE(horizontal_distance > 320.0f, 10, 208);
                if (horizontal_distance < 520.0f && horizontal_distance > 180.0f) {
                    if ((unsigned)selector_random_roll(1000) < 6 && RESOURCE >= 600) { command_flags_728 = 0x20; goto policy_dispatch; }
                    if ((unsigned)selector_random_roll(1000) < 6 && RESOURCE >= 600) { command_flags_728 = 0x40; goto policy_dispatch; }
                }
                if (horizontal_distance <= (float)(((0.0f < *reinterpret_cast<float *>(CPU_FIELD(0xf4))) + 1) * 120)) {
                    const int rising_toward_peer = !(other_fighter_170->y_f0 <= y_f0 || *reinterpret_cast<float *>(CPU_FIELD(0xf8)) <= 0.0f);
                    if (vertical_distance < (float)(rising_toward_peer * 150 + 100) && (unsigned)selector_random_roll(1000) < 50) {
                        control_6bc = 2; control_6b8 = 0; control_6b4 = 0; goto policy_dispatch;
                    }
                }
                if (horizontal_distance <= (float)((0.0f < *reinterpret_cast<float *>(CPU_FIELD(0xf4))) * 120 + 180)) {
                    const int falling_toward_peer = !(0.0f <= *reinterpret_cast<float *>(CPU_FIELD(0xf8)) || y_f0 <= other_fighter_170->y_f0);
                    if (vertical_distance < (float)((falling_toward_peer + 3) * 50) && (unsigned)selector_random_roll(1000) < 75) {
                        control_6bc = 2; control_6b8 = 1; control_6b4 = 0; goto policy_dispatch;
                    }
                }
                if (policy_random_76e <= RESOURCE) {
                    if ((float)((vertical_distance < 200.0) * 180 + 120) < horizontal_distance && (unsigned)selector_random_roll(1000) < 50) {
                        control_6c0 = 2;
                        const short aim = (short)(int)atan2_degrees(other_fighter_170->y_f0 - y_f0,
                            (float)facing_104 * (other_fighter_170->x_ec - x_ec));
                        control_6b4 = 0; control_6b8 = -(int)aim > 29;
                    }
                    if (horizontal_distance > 250.0 && vertical_distance < 200.0 && (unsigned)selector_random_roll(1000) < 20) {
                        control_6c4 = 2; control_6b8 = 0; control_6b4 = 0;
                    }
                    if (horizontal_distance < 300.0f && vertical_distance > 200.0 && other_fighter_170->y_f0 < y_f0 && (unsigned)selector_random_roll(1000) < 25) {
                        control_6c4 = 2; control_6b8 = 1; control_6b4 = 0;
                    }
                }
            }
#undef TRY_SEQUENCE
        }
    }
    goto policy_dispatch;
approach_policy:
    policy_counter_766 = 100;
    policy_counter_768 = (short)(selector_random_roll(20) + 10);
policy_dispatch:
#undef RESOURCE
#undef SKILL
#undef FRONT_SEQUENCE
// Decisions read the signed word stored at76A. VC8 forwards the producing
// value into ECX and eliminates reloads; see REIMU_CPU_ROLL_FIELD_2026_10_19.md.
switch ( policy_counter_766 )
{
case 0:
if ( policy_counter_768 > 0 )
return;
policy_counter_76a = (short)selector_random_roll(0x64u);
if ( *(float *)CPU_FIELD(240) == 0.0f )
{
}
else
{
v98 = *(_DWORD *)CPU_FIELD(368);
if ( 0.0 == *(float *)(v98 + 240) )
{
v99 = horizontal_distance;
if ( horizontal_distance <= 90.0 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f) )
goto LABEL_888;
if ( policy_counter_76a >= 0 && policy_counter_76a <= 29 && vertical_distance > 200.0 )
{
policy_counter_766 = (v89 == -1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( policy_counter_76a < 30 || policy_counter_76a > 44 )
{
LABEL_888:
if ( policy_counter_76a < 45 || policy_counter_76a > 59 || vertical_distance <= 150.0 )
goto LABEL_1025;
goto LABEL_889;
}
goto LABEL_953;
}
if ( v99 <= 240.0 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f) )
goto LABEL_900;
if ( policy_counter_76a >= 0 && policy_counter_76a <= 29 && vertical_distance > 100.0 )
goto LABEL_960;
if ( policy_counter_76a < 30 || policy_counter_76a > 44 )
{
LABEL_900:
if ( policy_counter_76a >= 45 && policy_counter_76a <= 54 )
goto LABEL_901;
if ( policy_counter_76a < 55 )
goto LABEL_SIGNED_RANGE_27;
if ( policy_counter_76a <= 64 )
goto LABEL_889;
LABEL_SIGNED_RANGE_27:
LABEL_992:
policy_counter_768 = selector_random_roll(0x28u);
return;
}
LABEL_953:
policy_counter_766 = 11;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( v99 >= 520.0 )
{
if ( policy_counter_76a < 0 || policy_counter_76a > 34 )
{
if ( policy_counter_76a < 35 || policy_counter_76a > 39 )
goto LABEL_875;
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 10;
}
else
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 20;
}
return;
}
if ( v99 < 240.0 )
return;
if ( policy_counter_76a >= 0 && policy_counter_76a <= 9 )
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
policy_counter_768 = selector_random_roll(0xFu) + 15;
return;
}
if ( policy_counter_76a >= 10 && policy_counter_76a <= 19 )
{
policy_counter_766 = 11;
policy_counter_768 = selector_random_roll(0x1Eu) + 30;
return;
}
if ( policy_counter_76a >= 20 && policy_counter_76a <= 24 )
{
policy_counter_766 = 12;
policy_counter_768 = selector_random_roll(0x1Eu) + 20;
return;
}
if ( policy_counter_76a < 45 || policy_counter_76a > 54 )
{
if ( policy_counter_76a < 55 )
goto LABEL_875;
if ( policy_counter_76a > 64 )
goto LABEL_875;
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
policy_counter_768 = selector_random_roll(0x14u) + 15;
return;
}
LABEL_972:
v93 = *(_BYTE *)CPU_FIELD(260) == 0xFF;
goto LABEL_982;
}
v100 = horizontal_distance;
if ( horizontal_distance > 90.0 )
{
if ( v100 <= 240.0 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 14 && *(float *)(v98 + 240) < (double)*(float *)CPU_FIELD(240) )
goto LABEL_953;
if ( policy_counter_76a >= 15 && policy_counter_76a <= 29 && vertical_distance > 150.0 )
goto LABEL_960;
}
if ( policy_counter_76a >= 30 && policy_counter_76a <= 34 )
goto LABEL_960;
if ( policy_counter_76a >= 35 && policy_counter_76a <= 44 )
goto LABEL_889;
if ( policy_counter_76a < 45 || policy_counter_76a > 47 )
{
if ( policy_counter_76a < 48 || policy_counter_76a > 50 )
{
if ( policy_counter_76a < 51 || policy_counter_76a > 54 )
goto LABEL_1025;
goto LABEL_969;
}
goto LABEL_989;
}
goto LABEL_986;
}
if ( v100 < 520.0 )
{
if ( v100 < 240.0 )
return;
if ( policy_counter_76a >= 0 && policy_counter_76a <= 4 )
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
policy_counter_768 = selector_random_roll(0x1Eu);
return;
}
if ( policy_counter_76a >= 5 && policy_counter_76a <= 9 )
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu);
return;
}
if ( policy_counter_76a < 45 || policy_counter_76a > 47 )
{
if ( policy_counter_76a < 48 || policy_counter_76a > 50 )
{
if ( policy_counter_76a < 51 || policy_counter_76a > 54 )
goto LABEL_992;
goto LABEL_969;
}
LABEL_989:
policy_counter_766 = 16;
policy_counter_768 = selector_random_roll(0x14u) + 5;
return;
}
LABEL_986:
policy_counter_766 = 17;
policy_counter_768 = selector_random_roll(0x14u) + 5;
return;
}
if ( policy_counter_76a >= 0 && policy_counter_76a < 4 )
goto LABEL_972;
if ( policy_counter_76a < 4 || policy_counter_76a > 5 )
goto LABEL_983;
}
else if ( policy_counter_76a < 0 || policy_counter_76a > 5 )
{
if ( vertical_distance <= 320.0 )
goto LABEL_1025;
if ( *(float *)(v98 + 240) > (double)*(float *)CPU_FIELD(240) )
{
if ( policy_counter_76a >= 5 && policy_counter_76a <= 9 )
{
policy_counter_766 = 12;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( policy_counter_76a >= 10 && policy_counter_76a <= 14 )
goto LABEL_953;
if ( policy_counter_76a >= 15 && policy_counter_76a <= 24 )
goto LABEL_972;
}
if ( *(float *)(v98 + 240) >= (double)*(float *)CPU_FIELD(240) )
goto LABEL_1025;
if ( policy_counter_76a < 25 || policy_counter_76a > 27 )
{
if ( policy_counter_76a < 28 || policy_counter_76a > 31 )
{
if ( policy_counter_76a < 32 || policy_counter_76a > 35 )
{
if ( policy_counter_76a < 36 || policy_counter_76a > 39 )
goto LABEL_1025;
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu);
return;
}
}
LABEL_969:
policy_counter_766 = 18;
policy_counter_768 = selector_random_roll(0x14u) + 5;
return;
}
goto LABEL_989;
}
goto LABEL_986;
}
LABEL_975:
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu);
return;
}
if ( !*(float *)(*(_DWORD *)CPU_FIELD(368) + 240) )
{
}
else
{
if ( horizontal_distance <= 90.0 )
{
v95 = vertical_distance;
if ( vertical_distance > 100.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 6 )
goto LABEL_671;
if ( policy_counter_76a >= 7 && policy_counter_76a <= 10 && v95 >= 200.0 )
goto LABEL_800;
if ( policy_counter_76a >= 11 && policy_counter_76a <= 18 )
goto LABEL_804;
if ( policy_counter_76a >= 19 && policy_counter_76a <= 24 && v95 >= 200.0 )
goto LABEL_808;
}
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f)
|| policy_counter_76a < 25
|| policy_counter_76a > 49
|| v95 < 250.0 )
{
if ( policy_counter_76a >= 50 && policy_counter_76a <= 69 )
{
policy_counter_766 = (v89 == 1) + 1;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( policy_counter_76a >= 70 && policy_counter_76a <= 74 )
goto LABEL_889;
goto LABEL_875;
}
{
policy_counter_766 = (v89 == -1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
}
if ( horizontal_distance <= 240.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 6 )
goto LABEL_671;
if ( policy_counter_76a < 7 || policy_counter_76a > 10 )
{
v96 = vertical_distance;
}
else
{
v96 = vertical_distance;
if ( vertical_distance >= 200.0 )
goto LABEL_800;
}
if ( policy_counter_76a >= 11 && policy_counter_76a <= 18 )
goto LABEL_804;
if ( policy_counter_76a >= 19 && policy_counter_76a <= 24 && v96 >= 200.0 )
goto LABEL_808;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 )
{
v97 = v96;
if ( *(float *)CPU_FIELD(236) < 240.0 )
{
LABEL_815:
if ( policy_counter_76a >= 35 && policy_counter_76a <= 50 && v97 >= 400.0 )
goto LABEL_788;
LABEL_819:
if ( policy_counter_76a < 50 || policy_counter_76a > 69 )
{
if ( policy_counter_76a < 70 )
goto LABEL_875;
if ( policy_counter_76a > 74 )
goto LABEL_875;
goto LABEL_889;
}
goto LABEL_725;
}
}
else
{
v97 = v96;
}
if ( v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f )
goto LABEL_819;
goto LABEL_815;
}
if ( horizontal_distance >= 520.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 9 )
goto LABEL_826;
if ( policy_counter_76a >= 10 && policy_counter_76a <= 19 )
goto LABEL_829;
if ( policy_counter_76a >= 20 && policy_counter_76a <= 24 )
goto LABEL_832;
if ( policy_counter_76a >= 25 && policy_counter_76a <= 29 )
goto LABEL_835;
if ( policy_counter_76a >= 30 && policy_counter_76a <= 39 )
{
policy_counter_766 = 3;
return;
}
if ( policy_counter_76a < 40 || policy_counter_76a > 49 )
{
if ( policy_counter_76a >= 50 && policy_counter_76a <= 54 )
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 1;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( policy_counter_76a >= 55 && policy_counter_76a <= 95 )
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 45;
return;
}
goto LABEL_875;
}
goto LABEL_863;
}
if ( horizontal_distance < 240.0 )
return;
if ( policy_counter_76a >= 0 && policy_counter_76a <= 6 )
goto LABEL_671;
if ( policy_counter_76a >= 7 && policy_counter_76a <= 12 )
goto LABEL_800;
if ( policy_counter_76a >= 13 && policy_counter_76a <= 20 )
goto LABEL_804;
if ( policy_counter_76a >= 21 && policy_counter_76a <= 30 )
goto LABEL_808;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( policy_counter_76a >= 40 && policy_counter_76a <= 49 )
{
policy_counter_766 = 3;
return;
}
if ( policy_counter_76a >= 50 && policy_counter_76a <= 59 )
{
LABEL_863:
policy_counter_766 = 6;
return;
}
}
if ( policy_counter_76a >= 60 && policy_counter_76a <= 64 )
{
policy_counter_766 = (v89 == -1) + 1;
policy_counter_768 = selector_random_roll(0x1Eu) + 10;
return;
}
if ( policy_counter_76a < 65 || policy_counter_76a > 79 )
{
if ( policy_counter_76a >= 80 && policy_counter_76a <= 89 )
{
policy_counter_766 = (v89 == 1) + 1;
policy_counter_768 = selector_random_roll(0x28u) + 10;
return;
}
if ( policy_counter_76a >= 90 && policy_counter_76a <= 99 )
policy_counter_766 = (v89 == 1) + 9;
goto LABEL_875;
}
LABEL_901:
policy_counter_766 = (v89 == -1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 20;
return;
}
if ( horizontal_distance <= 90.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 9 )
goto LABEL_826;
if ( policy_counter_76a >= 10 && policy_counter_76a <= 14 )
goto LABEL_829;
if ( policy_counter_76a >= 15 && policy_counter_76a <= 29 )
goto LABEL_832;
if ( policy_counter_76a >= 30 && policy_counter_76a <= 39 )
goto LABEL_835;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( policy_counter_76a >= 40 && policy_counter_76a <= 44 )
{
LABEL_654:
policy_counter_766 = 3;
return;
}
if ( policy_counter_76a >= 45 && policy_counter_76a <= 49 )
goto LABEL_658;
}
if ( policy_counter_76a < 50 || policy_counter_76a > 74 )
{
if ( policy_counter_76a >= 75
&& policy_counter_76a <= 89
&& (v89 == 1 && *(float *)CPU_FIELD(236) >= 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) <= 1040.0f) )
{
goto LABEL_889;
}
LABEL_875:
policy_counter_768 = selector_random_roll(0xAu);
return;
}
goto LABEL_725;
LABEL_835:
policy_counter_766 = 8;
return;
LABEL_832:
policy_counter_766 = 5;
return;
LABEL_829:
policy_counter_766 = 7;
return;
LABEL_826:
policy_counter_766 = 4;
return;
}
if ( horizontal_distance <= 240.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 2 )
{
LABEL_671:
policy_counter_766 = 4;
return;
}
if ( policy_counter_76a < 3 || policy_counter_76a > 5 )
{
if ( policy_counter_76a < 6 || policy_counter_76a > 8 )
{
if ( policy_counter_76a < 9 || policy_counter_76a > 11 )
{
if ( policy_counter_76a >= 12 && policy_counter_76a <= 14 )
{
policy_counter_766 = 3;
return;
}
if ( policy_counter_76a >= 15 && policy_counter_76a <= 17 )
goto LABEL_682;
v89 = *(_BYTE *)CPU_FIELD(260);
if ( (v89 != 1 || *(float *)CPU_FIELD(236) >= 240.0) && (v89 != -1 || *(float *)CPU_FIELD(236) <= 1040.0f) )
{
LABEL_691:
if ( policy_counter_76a >= 30 && policy_counter_76a <= 39 )
{
v90 = v89 == -1;
LABEL_726:
policy_counter_766 = v90 + 1;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( policy_counter_76a < 40 || policy_counter_76a > 54 )
{
if ( policy_counter_76a < 55 || policy_counter_76a > 69 )
{
if ( policy_counter_76a < 70 || policy_counter_76a > 89 )
goto LABEL_875;
LABEL_889:
policy_counter_766 = (v89 == 1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu);
return;
}
LABEL_725:
v90 = v89 == 1;
goto LABEL_726;
}
LABEL_788:
policy_counter_766 = (v89 == -1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 15;
return;
}
if ( policy_counter_76a < 20 || policy_counter_76a > 24 )
{
if ( policy_counter_76a < 25 || policy_counter_76a > 29 )
goto LABEL_691;
LABEL_757:
policy_counter_766 = 6;
return;
}
LABEL_860:
policy_counter_766 = 3;
return;
}
LABEL_808:
policy_counter_766 = 8;
return;
}
LABEL_804:
policy_counter_766 = 5;
return;
}
LABEL_800:
policy_counter_766 = 7;
return;
}
if ( horizontal_distance >= 520.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 4 )
goto LABEL_671;
if ( policy_counter_76a >= 5 && policy_counter_76a <= 9 )
goto LABEL_800;
if ( policy_counter_76a >= 10 && policy_counter_76a <= 14 )
goto LABEL_804;
if ( policy_counter_76a >= 15 && policy_counter_76a <= 17 )
goto LABEL_808;
if ( policy_counter_76a >= 18 && policy_counter_76a <= 24 )
{
policy_counter_766 = 3;
return;
}
if ( policy_counter_76a >= 25 && policy_counter_76a <= 29 )
{
LABEL_658:
policy_counter_766 = 6;
return;
}
if ( policy_counter_76a >= 30 && policy_counter_76a <= 44 )
{
policy_counter_766 = (*(_BYTE *)CPU_FIELD(260) == 0xFF) + 1;
policy_counter_768 = selector_random_roll(0x1Eu) + 30;
return;
}
if ( policy_counter_76a >= 45 && policy_counter_76a <= 79 )
{
policy_counter_766 = 9;
policy_counter_768 = selector_random_roll(0x1Eu) + 60;
return;
}
if ( policy_counter_76a >= 80 && policy_counter_76a <= 82 )
{
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) >= 240.0 )
goto LABEL_725;
if ( v89 == -1 && *(float *)CPU_FIELD(236) <= 1040.0f )
goto LABEL_725;
}
if ( policy_counter_76a < 83 || policy_counter_76a > 89 )
goto LABEL_875;
v91 = *(_BYTE *)CPU_FIELD(260);
if ( v91 == 1 && *(float *)CPU_FIELD(236) >= 240.0 )
{
v93 = 1;
LABEL_982:
policy_counter_766 = v93 + 9;
LABEL_983:
policy_counter_768 = selector_random_roll(0x1Eu);
return;
}
if ( v91 != -1 || *(float *)CPU_FIELD(236) > 1040.0f )
goto LABEL_875;
v93 = 0;
goto LABEL_982;
}
if ( horizontal_distance >= 240.0 )
{
if ( policy_counter_76a >= 0 && policy_counter_76a <= 2 )
goto LABEL_671;
if ( policy_counter_76a >= 3 && policy_counter_76a <= 5 )
goto LABEL_800;
if ( policy_counter_76a >= 6 && policy_counter_76a <= 8 )
goto LABEL_804;
if ( policy_counter_76a >= 9 && policy_counter_76a <= 11 )
goto LABEL_808;
if ( policy_counter_76a >= 12 && policy_counter_76a <= 15 )
{
policy_counter_766 = 3;
return;
}
if ( policy_counter_76a >= 16 && policy_counter_76a <= 18 )
{
LABEL_682:
policy_counter_766 = 6;
return;
}
v89 = *(_BYTE *)CPU_FIELD(260);
if ( v89 == 1 && *(float *)CPU_FIELD(236) < 240.0 || v89 == -1 && *(float *)CPU_FIELD(236) > 1040.0f )
{
if ( policy_counter_76a >= 20 && policy_counter_76a <= 29 )
goto LABEL_860;
if ( policy_counter_76a >= 30 && policy_counter_76a <= 39 )
{
policy_counter_766 = 6;
return;
}
}
if ( policy_counter_76a >= 40 && policy_counter_76a <= 54 )
{
v94 = v89 == -1;
goto LABEL_766;
}
if ( policy_counter_76a < 55 || policy_counter_76a > 79 )
{
if ( policy_counter_76a < 80 || policy_counter_76a > 84 )
{
if ( policy_counter_76a < 85 || policy_counter_76a > 99 )
goto LABEL_875;
goto LABEL_889;
}
v94 = v89 == 1;
LABEL_766:
policy_counter_766 = v94 + 1;
policy_counter_768 = selector_random_roll(0x1Eu) + 10;
return;
}
LABEL_960:
policy_counter_766 = (v89 == -1) + 9;
policy_counter_768 = selector_random_roll(0x1Eu);
}
return;
case 1:
v101 = policy_counter_768 <= 0;
*(_DWORD *)CPU_FIELD(1716) = 1;
if ( v101 )
{
policy_counter_766 = 0;
if ( selector_random_roll(0x64u) <= 0xAu )
policy_counter_768 = selector_random_roll(0x3Cu);
}
return;
case 2:
v101 = policy_counter_768 <= 0;
*(_DWORD *)CPU_FIELD(1716) = -1;
if ( v101 )
{
LABEL_994:
policy_counter_766 = 0;
if ( selector_random_roll(0x64u) <= 0xAu )
policy_counter_768 = selector_random_roll(0x3Cu);
}
return;
case 3:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = -1;
goto LABEL_1003;
case 4:
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = -1;
goto LABEL_1003;
case 5:
*(_DWORD *)CPU_FIELD(1716) = 1;
*(_DWORD *)CPU_FIELD(1720) = -1;
goto LABEL_1003;
case 6:
*(_DWORD *)CPU_FIELD(1828) = 16;
goto LABEL_1003;
case 7:
*(_DWORD *)CPU_FIELD(1828) = 4;
goto LABEL_1003;
case 8:
*(_DWORD *)CPU_FIELD(1828) = 8;
LABEL_1003:
if ( !(*(float *)CPU_FIELD(240) > 0.0f) )
return;
goto LABEL_1023;
case 9:
v102 = *(_BYTE *)CPU_FIELD(260);
v103 = v102 != 1;
v104 = v102;
v105 = *(_WORD *)CPU_FIELD(316);
*(_DWORD *)CPU_FIELD(1716) = v104;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1828) = v103 + 1;
if ( v105 == 200 )
goto LABEL_1022;
if ( v105 == 202 )
goto LABEL_1022;
goto LABEL_1008;
case 0xA:
v107 = *(_BYTE *)CPU_FIELD(260);
v108 = -v107;
v18 = v107 == -1;
v109 = *(_WORD *)CPU_FIELD(316);
*(_DWORD *)CPU_FIELD(1716) = v108;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1828) = !v18 + 1;
if ( v109 == 201 )
goto LABEL_1022;
if ( v109 == 203 )
goto LABEL_1022;
goto LABEL_1008;
case 0xB:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = -1;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0xC:
*(_DWORD *)CPU_FIELD(1716) = 0;
*(_DWORD *)CPU_FIELD(1720) = -1;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0xD:
*(_DWORD *)CPU_FIELD(1716) = -*(char *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1720) = -1;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0xE:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
goto LABEL_1016;
case 0xF:
*(_DWORD *)CPU_FIELD(1716) = -*(char *)CPU_FIELD(260);
LABEL_1016:
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1736) = 1;
goto LABEL_1021;
case 0x10:
*(_DWORD *)CPU_FIELD(1716) = *(char *)CPU_FIELD(260);
goto LABEL_1020;
case 0x11:
*(_DWORD *)CPU_FIELD(1716) = 0;
goto LABEL_1020;
case 0x12:
*(_DWORD *)CPU_FIELD(1716) = -*(char *)CPU_FIELD(260);
LABEL_1020:
*(_DWORD *)CPU_FIELD(1720) = 1;
*(_DWORD *)CPU_FIELD(1736) = 1;
LABEL_1021:
if ( *(_WORD *)CPU_FIELD(316) == 214 )
{
LABEL_1022:
if ( policy_counter_768 <= 0 )
{
LABEL_1023:
policy_counter_766 = 0;
if ( selector_random_roll(0x64u) > 0x64u )
return;
goto LABEL_1025;
LABEL_1025:
policy_counter_768 = selector_random_roll(0x3Cu);
}
}
else
{
LABEL_1008:
policy_counter_766 = 0;
}
return;
case 0x64:
v110 = *(_BYTE *)CPU_FIELD(260);
*(_DWORD *)CPU_FIELD(1716) = v110;
*(_DWORD *)CPU_FIELD(1720) = 0;
*(_DWORD *)CPU_FIELD(1724) = 0;
v101 = policy_counter_768 <= 0;
*(_DWORD *)CPU_FIELD(1828) = (v110 != 1) + 1;
*(_DWORD *)CPU_FIELD(1728) = 0;
*(_DWORD *)CPU_FIELD(1732) = 0;
*(_DWORD *)CPU_FIELD(1736) = 0;
if ( v101 )
{
policy_counter_766 = 0;
if ( selector_random_roll(0x64u) <= 0x64u )
policy_counter_768 = selector_random_roll(0x3Cu);
return;
}
if ( *(_WORD *)CPU_FIELD(316) == 200 && horizontal_distance < 220.0 )
*(_DWORD *)CPU_FIELD(1724) = 2;
return;
default:
return;
}
}
#undef CPU_FIELD

} // namespace th105
