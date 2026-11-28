#include "SakuyaObjectActionEntry.hpp"
#include "characters/CharacterObjectEffects.hpp"
#include "characters/CharacterObjectRuntime.hpp"
// JP1.06a 0x004E8060: reviewed action entry with a residual in action 803.
// Evidence and finite trials: docs/SAKUYA_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
// The motion method receives the animation subobject at +0x4.
#define MOTION reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)

__forceinline static void select_requested_sequence(SakuyaObjectEntryView *entry)
{
    if (entry->parameters_340[2] > 0.0f)
        entry->select_sequence(static_cast<int>(entry->parameters_340[2]));
}

__forceinline static CharacterObjectEffectEmitter *object_effects(SakuyaObjectEntryView *entry)
{
    return reinterpret_cast<CharacterObjectEffectEmitter *>(entry);
}

__forceinline static void spawn_entry_child(SakuyaObjectEntryView *entry, int action,
                                           const float *payload, int count)
{
    object_effects(entry)->spawn_parented_related_object(
        action, entry->x_ec, entry->y_f0, entry->facing_104, -1,
        reinterpret_cast<const unsigned *>(payload), count);
}

__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void SakuyaObjectEntryView::initialize_action_entry()
{
    velocity_x_f4=0.0f; velocity_y_f8=0.0f;
    field_370=0.0f; field_374=0.0f; field_378=0.0f; field_37c=0.0f;
    field_384=0; field_380=0.0f; field_386=0; phase_index_184=0;
    field_364=0; field_366=0; field_368=0; field_36a=0; field_36c=0;
    switch (action_id_13c) {
    case 800: {
        float payload[4];
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e<=2) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 800, payload, 3);
        }
        if (sequence_id_13e>=4 && sequence_id_13e<=6) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=7.0f; spawn_entry_child(this, 800, payload, 3);
        }
        return;
    }
    case 801: {
        float payload[4];
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e<=2) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 801, payload, 3);
        }
        return;
    }
    case 802:
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e<=2) MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
        return;
    case 803: {
        float payload[4];
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        field_374 = 255.0f;
        select_requested_sequence(this);
        if (sequence_id_13e == 0 || sequence_id_13e == 3) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0] = field_12c;
            payload[1] = 0.0f;
            payload[2] = 2.0f;
            spawn_entry_child(this, 803, payload, 3);
        }
        return;
    }
    case 804:
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this); return;
    case 805:
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this); return;
    case 810:
        field_124=0.0f; field_17c=0; field_128=0.0f; field_344=1; select_requested_sequence(this); return;
    case 811: {
        float payload[4];
        field_17c=1; phase_index_184=3; select_requested_sequence(this);
        if (sequence_id_13e==0) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            field_12c = -atan2_degrees(velocity_y_f8, velocity_x_f4);
            payload[0]=field_12c; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 811, payload, 3);
        }
        return;
    }
    case 812: {
        float payload[4];
        field_17c=2; phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e==0) { payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=1.0f; spawn_entry_child(this, 812, payload, 3); }
        return;
    }
    case 813:
        field_370=1.0f; field_17c=3; field_344=1; select_requested_sequence(this);
        if (sequence_id_13e<=5) {
            field_12c=random_float(90)-45.0;
            field_364=static_cast<short>(selector_random_roll(11));
            field_366=static_cast<short>(selector_random_roll(11));
            field_368=static_cast<short>(selector_random_roll(11));
            field_36a=static_cast<short>(selector_random_roll(5));
            field_36c=static_cast<short>(selector_random_roll(5));
            velocity_x_f4=random_float(9)-4.0;
            velocity_y_f8=-random_float(10)*static_cast<double>(0.1f);
        }
        if (sequence_id_13e==6 || sequence_id_13e==7 || sequence_id_13e==9 || sequence_id_13e==10) {
            velocity_y_f8=parameters_340[1]; velocity_x_f4=parameters_340[0];
        }
        return;
    case 815:
        field_124=0.0f; field_17c=4; field_128=0.0f;
        field_364=static_cast<short>(static_cast<int>(x_ec));
        field_366=static_cast<short>(static_cast<int>(y_f0));
        phase_index_184=1; phase_state_180=0; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e==2) field_370=0.5f;
        if (sequence_id_13e==3) field_370=0.5f;
        if (sequence_id_13e==4) field_370=0.6f;
        return;
    case 816: {
        float payload[4];
        field_17c=5;
        if (*reinterpret_cast<signed char *>(owner_348+0x609)==4) {
            phase_index_184=6; if (parameters_340[3]==1.0f) phase_index_184=7;
        } else { phase_index_184=5; if (parameters_340[3]==1.0f) phase_index_184=6; }
        field_374=255.0f; select_requested_sequence(this);
        if (sequence_id_13e==0) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            field_12c = -atan2_degrees(velocity_y_f8, velocity_x_f4);
            payload[0]=field_12c; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 816, payload, 3);
        }
        return;
    }
    case 817:
        field_17c=6;
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e<=2) MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
        return;
    case 818:
        field_17c=7; phase_index_184=1; field_12c=parameters_340[0]; phase_state_180=0; select_requested_sequence(this);
        if (sequence_id_13e==0) {
            field_344=1;
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
        }
        if (sequence_id_13e==2) { field_344=1; field_11c=1.5f; field_120=1.5f; }
        return;
    case 849: field_344=1; select_requested_sequence(this); return;
    case 850:
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this); return;
    case 851: field_344=1; alpha_113=0; select_requested_sequence(this); return;
    case 852: {
        field_120=field_11c=static_cast<float>(random_float(7)*static_cast<double>(0.1f)+1.0);
        field_124=static_cast<unsigned>(selector_random_roll(50))+30.0f+(static_cast<unsigned>(selector_random_roll(100))<50)*180;
        field_12c=random_float(60); field_128=random_float(90)-25.0;
        select_requested_sequence(this);
        if (sequence_id_13e==0) velocity_x_f4=random_float(12);
        if (sequence_id_13e==1) {
            phase_index_184=1;
            MOTION->set_oriented_components_f0_f4(static_cast<float>(random_float(90)-45.0),20.0f);
        }
        return;
    }
    case 853: {
        float payload[4];
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e==1) {
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=4.0f; payload[3]=0.0f; spawn_entry_child(this, 853, payload, 4);
            payload[2]=5.0f; spawn_entry_child(this, 853, payload, 4);
        }
        return;
    }
    case 854: alpha_113=0; field_344=1; select_requested_sequence(this); return;
    case 855:
        select_requested_sequence(this);
        if (sequence_id_13e==0) {
            velocity_x_f4=random_float(12);
            field_120=field_11c=static_cast<float>(random_float(9)*static_cast<double>(0.1f)+static_cast<double>(1.7f));
            field_124=static_cast<unsigned>(selector_random_roll(50))+30.0f+(static_cast<unsigned>(selector_random_roll(100))<50)*180;
            field_12c=random_float(60); field_128=random_float(90)-25.0;
        }
        if (sequence_id_13e==1) {
            field_120=2.0f; parameters_340[1]=60.0f; parameters_340[0]=static_cast<unsigned>(selector_random_roll(40))-20.0f; field_12c=parameters_340[0];
        }
        if (sequence_id_13e==2) {
            phase_index_184=1;
            MOTION->set_oriented_components_f0_f4(static_cast<float>(random_float(80)-40.0),60.0f);
        }
        return;
    case 856: {
        float payload[4];
        phase_index_184=1; select_requested_sequence(this);
        if (sequence_id_13e==0) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            field_12c = -atan2_degrees(velocity_y_f8, velocity_x_f4);
            payload[0]=field_12c; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 856, payload, 3);
        }
        return;
    }
    case 857: {
        float payload[4];
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e==0 || sequence_id_13e==1) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (sequence_id_13e==0) { payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=2.0f; spawn_entry_child(this, 857, payload, 3); }
            if (sequence_id_13e==1) { payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 857, payload, 3); }
        }
        return;
    }
    case 858: {
        float payload[4];
        phase_index_184=1; field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e==0) {
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=1.0f; payload[3]=0.0f; spawn_entry_child(this, 858, payload, 3);
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
        }
        if (sequence_id_13e==2) {
            payload[0]=0.0f; payload[1]=0.0f; payload[2]=3.0f; payload[3]=0.0f;
            object_effects(this)->spawn_unparented_related_object(
                858, x_ec, y_f0, facing_104, 1,
                reinterpret_cast<const unsigned *>(payload), 4);
        }
        return;
    }
    case 859: {
        float payload[4];
        select_requested_sequence(this);
        if (sequence_id_13e==0) {
            field_11c=0.0f; field_120=0.0f; alpha_113=128;
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=1.0f;
            object_effects(this)->spawn_parented_related_object(
                859, x_ec, y_f0, 1, -1,
                reinterpret_cast<const unsigned *>(payload), 3);
            payload[2] = 2.0f;
            object_effects(this)->spawn_parented_related_object(
                859, x_ec, y_f0, 1, -1,
                reinterpret_cast<const unsigned *>(payload), 3);
            payload[2] = 3.0f;
            object_effects(this)->spawn_parented_related_object(
                859, x_ec, y_f0, 1, -1,
                reinterpret_cast<const unsigned *>(payload), 3);
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
        }
        if (sequence_id_13e==1) { field_11c=0.0f; field_120=0.0f; }
        if (sequence_id_13e==2) { field_12c=random_float(360); field_11c=0.0f; field_120=0.0f; }
        if (sequence_id_13e==3) { field_12c=random_float(360); field_11c=0.0f; field_120=0.0f; }
        if (sequence_id_13e==4) field_370=0.75f;
        if (sequence_id_13e==5) field_370=0.75f;
        if (sequence_id_13e==6) field_370=0.9f;
        return;
    }
    case 900: {
        float payload[4];
        phase_index_184=1; select_requested_sequence(this);
        if (sequence_id_13e==0) {
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            field_12c = -atan2_degrees(velocity_y_f8, velocity_x_f4);
            payload[0]=field_12c; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 856, payload, 3);
        }
        return;
    }
    case 901: {
        float payload[4];
        select_requested_sequence(this);
        if (sequence_id_13e==0) {
            field_11c=0.0f; field_120=0.0f; alpha_113=128;
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=1.0f;
            object_effects(this)->spawn_parented_related_object(
                901, x_ec, y_f0, 1, -1,
                reinterpret_cast<const unsigned *>(payload), 3);
            payload[2] = 2.0f;
            object_effects(this)->spawn_parented_related_object(
                901, x_ec, y_f0, 1, -1,
                reinterpret_cast<const unsigned *>(payload), 3);
            payload[2] = 3.0f;
            object_effects(this)->spawn_parented_related_object(
                901, x_ec, y_f0, 1, -1,
                reinterpret_cast<const unsigned *>(payload), 3);
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
        }
        if (sequence_id_13e==1) { field_11c=0.0f; field_120=0.0f; }
        if (sequence_id_13e==2) { field_12c=random_float(360); field_11c=0.0f; field_120=0.0f; }
        if (sequence_id_13e==3) { field_12c=random_float(360); field_11c=0.0f; field_120=0.0f; }
        if (sequence_id_13e==4) field_370=0.75f;
        if (sequence_id_13e==5) field_370=0.75f;
        if (sequence_id_13e==6) field_370=0.9f;
        if (sequence_id_13e==7) {
            double const heading=parameters_340[0]; phase_index_184=1; field_12c=heading;
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=8.0f; spawn_entry_child(this, 901, payload, 3);
        }
        if (sequence_id_13e==8) field_12c=parameters_340[0];
        return;
    }
    case 920: {
        float payload[4];
        field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e<=1) {
            field_374=10.0f; field_370=random_float(10)+20.0;
            if (static_cast<unsigned>(selector_random_roll(100))<50) field_370*=-1.0;
            phase_index_184=1; field_344=1;
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 920, payload, 3);
        }
        if (sequence_id_13e==2) {
            phase_index_184=1;
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 920, payload, 3);
        }
        if (sequence_id_13e==3) { field_344=1; field_12c=parameters_340[0]; }
        return;
    }
    case 930: {
        float payload[4];
        field_12c=parameters_340[0]; select_requested_sequence(this);
        if (sequence_id_13e<=1) {
            field_374=10.0f; field_370=random_float(10)+20.0;
            if (static_cast<unsigned>(selector_random_roll(100))<50) field_370*=-1.0;
            phase_index_184=1; field_344=1;
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 930, payload, 3);
        }
        if (sequence_id_13e==2) {
            phase_index_184=1;
            MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            payload[0]=parameters_340[0]; payload[1]=0.0f; payload[2]=3.0f; spawn_entry_child(this, 930, payload, 3);
        }
        if (sequence_id_13e==3) { field_344=1; field_12c=parameters_340[0]; }
        return;
    }
    case 980: continue_action_980(); return;
    case 998: return;
    case 999:
        select_sequence(static_cast<int>(parameters_340[2]));
        if (sequence_id_13e==4) { velocity_x_f4=parameters_340[0]; velocity_y_f8=parameters_340[1]; }
        return;
    }
}
#undef MOTION
}
