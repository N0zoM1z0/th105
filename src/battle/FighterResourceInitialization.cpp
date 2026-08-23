#include "Collision.hpp"
#include "FighterResources.hpp"
#include "PatResourceContracts.hpp"
#include "SpellData.hpp"

#include "ui/Title.hpp"

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *destination,
    const char *format,
    ...);
const char *__cdecl character_key_to_name(int character_key);

struct OpaqueWaveHandleService {
    unsigned char opaque_00[0x68];

    unsigned *__thiscall load_wave_handle(
        unsigned *out_handle,
        const char *path);
};

extern OpaqueWaveHandleService g_wave_handle_service;

void Fighter::load_indexed_character_wave_resources()
{
    unsigned loaded_handle;
    char path[260];
    const char *const character_name = character_key_to_name(record_key_330);

    for (int index = 0; index < 64; ++index) {
        wsprintfA(
            path,
            "data/se/%s/%03d.wav",
            character_name,
            index);
        (*reinterpret_cast<unsigned **>(
            reinterpret_cast<unsigned char *>(this) + 0x164))[index] =
            *g_wave_handle_service.load_wave_handle(&loaded_handle, path);
    }
}

void FighterCutinResource::load_for_character(
    int character_key,
    int selector)
{
    unsigned first_loader_extent;
    unsigned second_loader_extent;
    unsigned loaded_handle;
    char path[260];

    selector_98 = selector;
    wsprintfA(
        path,
        "data/stand/cutin/%s.bmp",
        character_key_to_name(character_key));
    sprite_04.configure_texture(
        handle_00 = *g_title_resource_manager.load_texture(
            &loaded_handle,
            path,
            &first_loader_extent,
            &second_loader_extent),
        0,
        0,
        first_loader_extent - 1,
        second_loader_extent);

    FighterCutinSpriteWork *const sprite = &sprite_04;
    if (selector_98 == 1) {
        sprite->field_88 = -1.0f;
        sprite->field_8c = 1.0f;
    }
    state_9c = -1;
}

void Fighter::initialize_fighter_spell_resources()
{
    unsigned first_loader_extent;
    unsigned second_loader_extent;
    unsigned loaded_handle;
    char path[260];

    load_pat_data_and_palette_resources();
    load_indexed_character_wave_resources();

    reinterpret_cast<SpellDataOwner *>(
        reinterpret_cast<unsigned char *>(this) + 0x4f0)->load_spell_data(
            record_key_330,
            state_72c == 2,
            0);

    const char *const character_name = character_key_to_name(record_key_330);
    wsprintfA(
        path,
        "data/character/%s/face/face%03d.bmp",
        character_name,
        0);

    FighterFaceResource *const face =
        reinterpret_cast<FighterFaceResource *>(
            reinterpret_cast<unsigned char *>(this) + 0x338);
    face->sprite_04.configure_texture(
        face->handle_00 = *g_title_resource_manager.load_texture(
            &loaded_handle,
            path,
            &first_loader_extent,
            &second_loader_extent),
        0,
        0,
        first_loader_extent,
        second_loader_extent);

    FighterCutinSpriteWork *const sprite = &face->sprite_04;
    if (player_index_334 == 1) {
        sprite->field_88 = -1.0f;
        sprite->field_8c = 1.0f;
    }

    DwordDeque4 *const back_resources =
        reinterpret_cast<DwordDeque4 *>(
            reinterpret_cast<unsigned char *>(this) + 0x68c);
    for (int index = 0; index < 10; ++index) {
        wsprintfA(
            path,
            "data/character/%s/back/spell%03d.bmp",
            character_name,
            index);
        g_title_resource_manager.load_texture(
            &loaded_handle,
            path,
            0,
            0);
        if (loaded_handle == 0) {
            break;
        }
        back_resources->push_back(&loaded_handle);
    }

    reinterpret_cast<FighterCutinResource *>(
        reinterpret_cast<unsigned char *>(this) + 0x3d0)->load_for_character(
            record_key_330,
            static_cast<signed char>(player_index_334));
}

} // namespace th105
