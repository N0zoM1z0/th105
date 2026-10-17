"""Local native-execution bindings for the staged Iku upper-action source.

These aliases qualify dependency execution only; they are not canonical match
relocations, source-boundary claims or whole-root source selection.
"""

NEW_ENTRIES = {560: 0x628EAD, 561: 0x6290BA, 562: 0x62924D, 563: 0x6294CA,
               570: 0x62B784, 571: 0x62B873, 572: 0x62B930, 573: 0x62BAAD,
               599: 0x62BBEB}
ENTRIES = dict(sorted((NEW_ENTRIES | {
    565: 0x6296BE, 566: 0x629E96, 567: 0x62A668, 568: 0x62AEF6,
    600: 0x62BDC2, 601: 0x62BF12, 602: 0x62C232, 603: 0x62C619,
    606: 0x62C7A6, 607: 0x62C91B, 609: 0x62CA58, 610: 0x62CC24,
    650: 0x62D02A, 660: 0x62D1DE, 695: 0x62D5C7, 696: 0x62D72D,
    710: 0x62D7E1, 720: 0x62D8B0, 730: 0x62DA63, 740: 0x62E341,
    770: 0x62E4F1, 780: 0x62E588, 781: 0x62E909, 795: 0x62EADA,
    797: 0x62EB17, 798: 0x62ED65}).items()))
DATA_KEYS = ("?g_match_identifier@th105@@3HA",)
METHODS = {
    "spawn_owned_object_via_manager": 0x465190,
    "emit_fighter_effect_433cc0": 0x435240,
    "dispatch_character_wave_handle": 0x45C030,
    "add_phase_scaled_counter_558": 0x478DF0,
    "adjust_counter_482": 0x46BF30,
    "zero_velocity_acceleration": 0x45AF40,
    "has_crossed_stage_surface_while_descending": 0x5F9310,
    "advance_frame_and_dispatch": 0x4351C0,
    "resolve_stage_surface_landing_transition": 0x473DD0,
    "stage_surface_height_at_x": 0x435D60,
    "publish_texture_state": 0x45F560,
    "dispatch_indexed_event_member": 0x4359F0,
    "dispatch_indexed_sequence_window_45c8b0": 0x45DEB0,
    "advance_secondary_event_effect_cycle": 0x473F90,
    "selector_random_roll": 0x4067D0,
    "mt19937_next_u32": 0x4066B0,
    "face_opponent_and_flip_horizontal_velocity": 0x478E60,
    "finalize_sequence_entry": 0x45D110,
    "copy_action_word_176_to_174": 0x45B250,
    "set_shared_first_target": 0x476AB0,
    "set_shared_second_target": 0x476AD0,
    "set_shared_third_target": 0x476AF0,
    "set_global_pair": 0x434E10,
    "lookup_orientation_cosine_quantized_abs": 0x4063D0,
    "lookup_orientation_sine_quantized_abs": 0x406360,
    "atan2_degrees": 0x406540,
    "absolute_scalar_float": 0x406330,
    "__ftol2_sse": 0x68A1A0,
    "reset_fighter_action_scratch": 0x435110,
    "update_common_action_state": 0x4740C0,
    "try_dispatch_directional_action_208_210": 0x478EE0,
    "is_y_at_or_below_stage_surface": 0x435DC0,
}
