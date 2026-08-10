namespace th105 {

void __fastcall run_active_character_and_owned_object_callbacks(void *context);
void __fastcall commit_fighter_physics_status_timers(void *context);
void __fastcall update_global_6e6260_first(void *state);
void __fastcall update_global_6e6260_second(void *state);

void __cdecl run_global_fighter_action_owned_object_phase()
{
    run_active_character_and_owned_object_callbacks(
        *reinterpret_cast<void *volatile *>(0x006e623c));
}

void __cdecl run_global_fighter_position_status_timer_phase()
{
    commit_fighter_physics_status_timers(
        *reinterpret_cast<void *volatile *>(0x006e623c));
}

namespace {

struct PostUpdateContextView;
typedef void (__thiscall *PostUpdateCallback)(PostUpdateContextView *context);

struct PostUpdateContextView {
    PostUpdateCallback *vtable_00;
    unsigned unknown_04;
    unsigned clear_08;
};

struct InfoManagerVirtualView;
typedef void (__thiscall *InfoManagerCallback)(InfoManagerVirtualView *manager);

struct InfoManagerVirtualView {
    InfoManagerCallback *vtable_00;
};

} // namespace

void __fastcall run_post_update_callbacks_and_global_state(void *raw_context)
{
    PostUpdateContextView *context =
        static_cast<PostUpdateContextView *>(raw_context);
    context->vtable_00[15](context);
    context->clear_08 = 0;

    InfoManagerVirtualView *manager =
        *reinterpret_cast<InfoManagerVirtualView *volatile *>(0x006e6248);
    manager->vtable_00[4](manager);

    update_global_6e6260_first(reinterpret_cast<void *>(0x006e6260));
    update_global_6e6260_second(reinterpret_cast<void *>(0x006e6260));
}

} // namespace th105
