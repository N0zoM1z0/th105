from __future__ import annotations

import csv
import importlib.util
from pathlib import Path
import sys
import tomllib
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_script(name: str):
    path = ROOT / "scripts" / name
    spec = importlib.util.spec_from_file_location(name.removesuffix(".py"), path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"cannot import {path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class WorkflowToolingTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.validator = load_script("validate-tracking.py")
        cls.comparator = load_script("compare-function.py")
        cls.literals = load_script("match_literals.py")
        cls.manifest = load_script("workflow_manifest.py")
        cls.progress = load_script("progress.py")
        cls.exact_replay = load_script("verify-exact-units.py")
        cls.byte_ownership = load_script("function_byte_ownership.py")
        cls.ida_check = load_script("check-ida-mcp.py")
        cls.inventory = load_script("export-ida-inventory.py")
        cls.typed = load_script("typed-re.py")
        cls.mcp_runtime = load_script("mcp_runtime.py")
        cls.xiph_sdk = load_script("fetch-xiph-sdk-object.py")

    def test_corrected_target_identity(self) -> None:
        manifest = self.validator.validate_target(require_bytes=False)
        self.assertEqual(manifest["target"]["size"], 3_129_344)
        self.assertEqual(
            manifest["target"]["sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(manifest["pe"]["entry_point"], "0x0068B9D2")

    def test_corrected_inventory_tracks_only_current_target_progress(self) -> None:
        with (ROOT / "config" / "functions.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            functions = list(csv.DictReader(stream))
        self.assertEqual(len(functions), 4011)
        matching = [row for row in functions if row["status"] == "matching"]
        self.assertEqual(len(matching), 1284)
        self.assertTrue(all(row["match_percent"] == "100.00" for row in matching))
        with (ROOT / "config" / "implemented.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            implemented = [row[0] for row in csv.reader(stream) if row]
        self.assertEqual(len(implemented), 1326)
        self.assertEqual(
            len(self.validator.rows(ROOT / "config" / "matches.csv")), 1284
        )

    def test_match_unit_graph_covers_current_exact_baseline(self) -> None:
        manifest = self.manifest.load_manifest()
        self.assertEqual(len(manifest["units"]), 466)
        self.assertEqual(
            sum(len(unit["functions"]) for unit in manifest["units"].values()),
            1331,
        )

    def test_source_present_rows_do_not_fall_back_to_origin_review(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        pending = [
            address for address, row in functions.items()
            if row["status"] == "implemented"
            and origins[address]["disposition"] == "review"
        ]
        self.assertEqual(pending, [])
        for address in [
            "0x004098E0", "0x00414E40", "0x00417800",
            "0x00412B10", "0x00412CC0", "0x00431AC0", "0x00463500",
        ]:
            self.assertEqual(origins[address.upper()]["origin"], "authored_game")
            self.assertEqual(origins[address.upper()]["disposition"], "authored")

        units = self.manifest.load_manifest()["units"]
        cnumber = units["gpt-web-cnumber-runtime"]
        fighter = units["gpt-web-fighter-command-flags-runtime"]
        self.assertTrue(any(row["address"].upper() == "0X00414E40" for row in cnumber["functions"]))
        self.assertTrue(any(row["address"].upper() == "0X00463500" for row in fighter["functions"]))

    def test_new_authored_nonexact_helper_contracts_stay_nonexact(self) -> None:
        units = self.manifest.load_manifest()["units"]
        accepted = self.exact_replay.accepted_functions(units)
        checks = [
            ("0x004036C0", "src/audio/BgmHandleAllocation.cpp", "gpt-web-bgm-handle-allocation"),
            ("0x004064D0", "src/engine/AngleLookup.cpp", "cross-v106a-angle-lookup"),
            ("0x004180F0", "src/audio/DirectSoundResourceLifetime.cpp", "gpt-web-direct-sound-resource-lifetime"),
            ("0x0041FA20", "src/ui/MenuCursor.cpp", "cross-v106a-menu-cursor"),
            ("0x00421FF0", "src/battle/EffectSprite.cpp", "cross-v106a-effect-sprite-scalar-dtor"),
            ("0x0042BAF0", "src/battle/BattleSetupSlots.cpp", "cross-v106a-fixed-slot-select"),
            ("0x0042D010", "src/config/ScoreObservations.cpp", "gpt-web-score-observations"),
            ("0x0043F330", "src/ui/GuideOverlay.cpp", "cross-v106a-guide-overlay"),
            ("0x0043F450", "src/ui/GuideOverlay.cpp", "cross-v106a-guide-overlay"),
            ("0x0044B9D0", "src/ui/ProfileSubmenuLifetime.cpp", "cross-v106a-profile-submenu-lifetimes"),
            ("0x0045CED0", "src/battle/HitCounters.cpp", "cross-v106a-deferred-counter"),
            ("0x0045D040", "src/battle/SpellRuntime.cpp", "cross-v106a-front-sequence-ready"),
            ("0x0045D230", "src/battle/SpellRuntime.cpp", "cross-v106a-front-sequence-ready"),
            ("0x004695F0", "src/battle/EventEffectState.cpp", "cross-v106a-event-effect-state"),
            ("0x0046C930", "src/battle/ObjectResponses.cpp", "cross-v106a-object-responses"),
            ("0x0046EEB0", "src/battle/EffectObjectManagerRelease.cpp", "gpt-web-effect-object-manager-release"),
            ("0x0056DA90", "src/characters/RosterObjectRelease.cpp", "gpt-web-roster-object-release-all"),
            ("0x0058BE10", "src/characters/CharacterObjectManagerRuntime.cpp", "gpt-web-character-object-manager-runtime"),
        ]
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            rows = {row["address"].upper(): row for row in csv.DictReader(stream)}
        for address, source, unit_name in checks:
            row = rows[address.upper()]
            self.assertEqual(row["status"], "implemented")
            self.assertEqual(row["source_file"], source)
            self.assertIn(unit_name, units)
            self.assertNotIn(address.upper(), {value.upper() for value in accepted.get(unit_name, set())})

        effect = units["gpt-web-effect-manager-virtuals"]
        self.assertTrue(any(function["address"].upper() == "0X00422D30" for function in effect["functions"]))
        self.assertNotIn("0x00422D30", {value.lower() for value in accepted.get("gpt-web-effect-manager-virtuals", set())})

        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        for address in [
            "0x004036C0", "0x00406360", "0x004063D0", "0x004064D0",
            "0x004180F0", "0x0041FA20", "0x00421FF0", "0x00422D30",
            "0x0042BAF0", "0x0042D010", "0x0043F330", "0x0043F450", "0x0044B9D0",
            "0x0045CED0", "0x0045D040", "0x0045D230", "0x004695F0", "0x0046C930",
            "0x0046EEB0", "0x0056DA90", "0x0058BE10",
        ]:
            self.assertEqual(origins[address.upper()]["origin"], "authored_game")
            self.assertEqual(origins[address.upper()]["disposition"], "authored")

    def test_exact_owner_callee_promotions_and_generated_collision_are_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        expected_exact = {
            "0X0040CF10": ("BattleThreadHandle_ctor", "src/platform/BattleThreadHandleRuntime.cpp"),
            "0X0043AA40": ("get_current_replay_header_code", "src/ui/ReplayHeaderVersion.cpp"),
            "0X0043B100": ("trim_profile_ui_menu_stack_facade", "src/ui/UiSceneStateFacades.cpp"),
            "0X0043B110": ("set_ui_selection_state_tracking_facade", "src/ui/UiSceneStateFacades.cpp"),
            "0X0046A610": ("InfoComboResourceSubobject_release_combo_resources_46a610", "src/battle/InfoComboResourceRelease.cpp"),
        }
        for address, (name, source) in expected_exact.items():
            self.assertEqual(functions[address]["status"], "matching")
            self.assertEqual(functions[address]["proposed_name"], name)
            self.assertEqual(functions[address]["source_file"], source)
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        generated = origins["0X004040B0"]
        self.assertEqual(generated["origin"], "compiler_generated")
        self.assertEqual(generated["disposition"], "exclude")
        self.assertEqual(generated["evidence_id"], "handle-manager-list-uint-sentinel-generated-106a")
        # Its 26-byte machine-code twin is independently game-authored, which
        # is why raw fingerprint uniqueness is not accepted as origin proof.
        self.assertEqual(functions["0X00435E50"]["status"], "matching")
        self.assertEqual(origins["0X00435E50"]["origin"], "authored_game")

    def test_second_exact_owner_leaf_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        exact = {
            "0X00415D50": "NetworkSendStateView_status",
            "0X00428B70": "NetworkReplayBufferView_reset_428b70",
            "0X00439570": "CFileList_current_directory",
            "0X0043B050": "get_active_input_source_43b050",
            "0X0043B0F0": "push_ui_selection_menu_facade",
        }
        for address, name in exact.items():
            self.assertEqual(functions[address]["status"], "matching")
            self.assertEqual(functions[address]["proposed_name"], name)
            self.assertEqual(origins[address]["origin"], "authored_game")

        cleanup = functions["0X00431390"]
        self.assertEqual(cleanup["status"], "implemented")
        self.assertEqual(cleanup["source_file"], "src/ui/ProfileMenuCleanup.cpp")
        self.assertEqual(origins["0X00431390"]["evidence_id"], "profile-menu-base-cleanup-authored-106a")

        c_str = origins["0X00401E30"]
        self.assertEqual(c_str["origin"], "compiler_generated")
        self.assertEqual(c_str["disposition"], "exclude")
        self.assertEqual(c_str["evidence_id"], "std-string-c-str-generated-106a")

        units = self.manifest.load_manifest()["units"]
        self.assertEqual(len(units["gpt-web-ui-scene-state-facades"]["functions"]), 3)
        self.assertEqual(len(units["gpt-web-network-small-accessors"]["functions"]), 2)
        self.assertIn("gpt-web-profile-menu-base-cleanup", units)

    def test_third_exact_owner_leaf_and_caller_identity_exclusions_are_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        for address, name, source in [
            ("0X00409CF0", "CInputManager_ctor", "src/input/InputManagerConstructor.cpp"),
            ("0X004406F0", "push_ui_selection_menu", "src/ui/UiSelectionMenuStack.cpp"),
        ]:
            self.assertEqual(functions[address]["status"], "matching")
            self.assertEqual(functions[address]["proposed_name"], name)
            self.assertEqual(functions[address]["source_file"], source)
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        generated = {
            "0X0040C100": "vc8-vector-uint-at-caller-identity-106a",
            "0X0040DCF0": "vc8-vector-uint-push-back-caller-identity-106a",
            "0X0040FE30": "vc8-deque-string-growmap-xlen-caller-identity-106a",
            "0X004101F0": "vc8-deque-string-growmap-xlen-caller-identity-106a",
            "0X004306D0": "event-background-deque-push-generated-106a",
            "0X00436D30": "scenario-text-tree-erase-generated-106a",
        }
        for address, evidence in generated.items():
            self.assertEqual(origins[address]["origin"], "compiler_generated")
            self.assertEqual(origins[address]["disposition"], "exclude")
            self.assertEqual(origins[address]["evidence_id"], evidence)
            self.assertEqual(functions[address]["status"], "unclassified")

        self.assertEqual(origins["0X004036C0"]["evidence_id"], "bgm-handle-allocation-authored-106a")
        self.assertEqual(origins["0X004695F0"]["evidence_id"], "event-effect-emitter-dispatch-authored-106a")

    def test_strict_fp_profile_is_explicit_and_local(self) -> None:
        manifest = self.manifest.load_manifest()
        unit = manifest["units"]["gpt-web-strict-fp-math-primitives"]
        self.assertEqual(unit["profile"], "vc8-sp1-probe-o2-fp-strict")
        self.assertEqual(unit["source"], "src/engine/StrictFpMathPrimitives.cpp")
        self.assertIn("vc8-sp1-probe-o2-fp-strict", self.manifest.ALLOWED_PROFILES)

    def test_cold_replay_selects_only_accepted_exact_functions(self) -> None:
        units = self.manifest.load_manifest()["units"]
        accepted = self.exact_replay.accepted_functions(units)
        self.assertEqual(len(accepted), 447)
        self.assertEqual(sum(map(len, accepted.values())), 1284)
        secondary = accepted["gpt-web-secondary-animation-runtime"]
        self.assertEqual(
            secondary,
            {"0x0042FD80", "0x00430050", "0x00430080", "0x004302A0", "0x00430750"},
        )
        self.assertNotIn("0x004309F0", secondary)
        view = self.exact_replay.comparison_view(
            units["gpt-web-secondary-animation-runtime"], secondary
        )
        self.assertEqual(len(view["functions"]), 5)

    def test_progress_reports_current_exact_baseline(self) -> None:
        markdown = self.progress.render()
        self.assertIn("Tracked 1.06a function candidates | 4,011", markdown)
        self.assertIn("Confirmed authored functions | 1,413", markdown)
        self.assertIn("Confirmed authored code bytes | 2,075,762", markdown)
        self.assertIn("Classified exclusions | 1,293", markdown)
        self.assertIn("Origin/boundary review pending | 1,305", markdown)
        self.assertIn("Canonical exact functions | 1,284", markdown)
        self.assertIn("Canonical exact authored bytes | 215,583", markdown)
        self.assertIn("Source-present authored mappings | 1,326", markdown)
        self.assertIn(
            "former 1.06 reconstruction state is intentionally excluded", markdown
        )

    def test_giant_action_switch_manifest_tracks_common_root(self) -> None:
        with (ROOT / "config" / "giant-action-switches.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        root = next(row for row in manifest["roots"] if row["name"] == "fighter-common-action")
        self.assertEqual(root["address"], "0x004740C0")
        self.assertEqual(root["callable_end"], "0x004768AB")
        self.assertEqual(root["expected_unique_destinations"], 65)
        self.assertEqual(root["candidate_unique_destination_counts"], [64, 65])
        self.assertEqual(root["expected_direct_call_sites"], 198)
        self.assertEqual(root["expected_direct_call_targets"], 16)
        self.assertEqual(root["expected_ret_opcodes"], 49)
        regions = {row["name"]: row for row in root["regions"]}
        self.assertEqual(regions["low"]["destination_count"], 51)
        self.assertEqual(regions["low"]["candidate_destination_counts"], [50, 51])
        self.assertEqual(regions["high"]["destination_count"], 15)
        self.assertEqual(regions["high"]["candidate_destination_counts"], [15])


    def test_giant_action_switch_manifest_tracks_default_cpu_policy(self) -> None:
        with (ROOT / "config" / "giant-action-switches.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        root = next(row for row in manifest["roots"] if row["name"] == "default-cpu-action-policy")
        self.assertEqual(root["address"], "0x005F1F80")
        self.assertEqual(root["callable_end"], "0x005F5DA6")
        self.assertEqual(root["metadata_end"], "0x005F6020")
        self.assertEqual(root["expected_unique_destinations"], 40)
        self.assertEqual(root["expected_direct_call_sites"], 150)
        self.assertEqual(root["expected_direct_call_targets"], 5)
        self.assertEqual(root["expected_ret_opcodes"], 52)
        regions = {row["name"]: row for row in root["regions"]}
        actions = regions["actions"]
        self.assertEqual((actions["case_min"], actions["case_max"]), (200, 416))
        self.assertEqual(actions["destination_table"], "0x005F5DA8")
        self.assertEqual(actions["index_table"], "0x005F5DF4")
        self.assertEqual(actions["destination_count"], 19)
        self.assertEqual(actions["expected_physical_groups"], 19)
        policy = regions["policy"]
        self.assertEqual((policy["case_min"], policy["case_max"]), (0, 100))
        self.assertEqual(policy["destination_table"], "0x005F5F64")
        self.assertEqual(policy["index_table"], "0x005F5FB8")
        self.assertEqual(policy["destination_count"], 21)
        self.assertEqual(policy["expected_physical_groups"], 21)


    def test_giant_action_switch_manifest_tracks_roster_object_roots(self) -> None:
        with (ROOT / "config" / "giant-action-switches.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        roots = {row["name"]: row for row in manifest["roots"]}
        expected = {
            "reimu-object-vslot28": (
                "0x00496540", "0x004A197A", "0x004A1CE0", 42, 405, 26, 68,
                800, 999, "0x004A197C", 42, "0x004A1A24",
            ),
            "alice-object-vslot28": (
                "0x004FCAB0", "0x0050BDF6", "0x0050C1C0", 39, 425, 29, 120,
                800, 999, "0x0050BDF8", 39, "0x0050BE94",
            ),
            "youmu-object-vslot28": (
                "0x0053CEA0", "0x005433F8", "0x00543670", 29, 224, 20, 49,
                800, 999, "0x005433F8", 29, "0x0054346C",
            ),
            "aya-object-vslot28": (
                "0x0061A290", "0x0061EED2", "0x0061F0B0", 33, 122, 17, 40,
                800, 998, "0x0061EED4", 33, "0x0061EF58",
            ),
        }
        for name, values in expected.items():
            root = roots[name]
            (
                address, callable_end, metadata_end, destinations,
                calls, targets, rets, case_min, case_max,
                destination_table, destination_count, index_table,
            ) = values
            self.assertEqual(root["address"], address)
            self.assertEqual(root["callable_end"], callable_end)
            self.assertEqual(root["metadata_end"], metadata_end)
            self.assertEqual(root["expected_unique_destinations"], destinations)
            self.assertEqual(root["expected_direct_call_sites"], calls)
            self.assertEqual(root["expected_direct_call_targets"], targets)
            self.assertEqual(root["expected_ret_opcodes"], rets)
            region = root["regions"][0]
            self.assertEqual((region["case_min"], region["case_max"]), (case_min, case_max))
            self.assertEqual(region["destination_table"], destination_table)
            self.assertEqual(region["destination_count"], destination_count)
            self.assertEqual(region["index_table"], index_table)
            self.assertEqual(region["expected_physical_groups"], destinations)

    def test_aya_object_semantic_scaffold_and_full_source_are_both_tracked(self) -> None:
        with (ROOT / "config" / "giant-action-switches.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        root = next(row for row in manifest["roots"] if row["name"] == "aya-object-vslot28")
        self.assertEqual(
            root["partial_semantic_scaffold"],
            "src/characters/AyaObjectActionStateScaffold.cpp",
        )
        self.assertEqual(
            root["verified_semantic_cases"],
            [800, 801, 804, 807, 810, 811, 812, 815, 816, 817, 820, 821, 822, 825, 826, 850, 851, 852, 853, 854, 855, 856, 861, 862, 900, 901, 902, 903, 980, 990, 997, 998],
        )
        self.assertEqual(root["verified_shared_default_owner"], "0x0061EEC5")
        self.assertEqual(root["verified_semantic_closed_regions"], ["actions"])

        scaffold = ROOT / "src" / "characters" / "AyaObjectActionStateScaffold.cpp"
        text = scaffold.read_text(encoding="utf-8")
        self.assertIn("try_dispatch_verified_update_action", text)
        for case in root["verified_semantic_cases"]:
            self.assertIn(f"case {case}:", text)
        for snippet in [
            "owner_action >= 520 && owner_action <= 524",
            "owner_action < 525 || owner_action > 529",
            "motion_core()->component_f0 * 0.1f",
            "time_counter_144 > 90",
            "owner_action != 601",
            "sprite_004.reset_one_11c * 0.8999999761581421",
            "owner_action == 612 || owner_action == 662",
            "emit_repeated_effects_for_owner_state(0, 3, 7)",
            "spawn_owned_object_via_manager",
            "emit_repeated_effects_for_owner_state(0, 0, 7)",
            "motion_core()->advance_phase_counter_conditional(3)",
            "state_370 * 0.949999988079071",
            "heading_340[0] + heading_340[1]",
            "selector_random_roll(100) - 50",
            "emit_repeated_effects_for_owner_state(0, 5, 10)",
            "lookup_orientation_sine_quantized_abs",
            "mt19937_next_u32() & 1u",
            "owner_action != 545 || owner_sequence == 2",
            "owner_action == 565 || owner_action == 567",
            "time_counter_144 == 240",
            "spawn_unparented_related_object(852",
            "case 900",
            "case 901",
            "case 902",
            "case 903",
            "owner_state_730",
            "time_counter_144 >= 180",
            "alpha = alpha > 245 ? 255",
        ]:
            self.assertIn(snippet, text)
        self.assertNotIn("AyaObject_dispatch_action_state_vslot28(", text)

        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            row = next(row for row in csv.DictReader(stream) if row["address"].lower() == "0x0061a290")
        self.assertEqual(row["status"], "implemented")
        self.assertEqual(row["source_file"], "src/characters/AyaObjectActionState.cpp")
        self.assertEqual(row["proposed_name"], "AyaObject_update_action_state_vslot28")

        units = self.manifest.load_manifest()["units"]
        unit = units["gpt-web-aya-object-vslot28-full-root"]
        self.assertEqual(unit["source"], "src/characters/AyaObjectActionState.cpp")
        self.assertEqual(unit["functions"][0]["address"], "0x0061A290")
        self.assertNotIn("0x0061A290", self.exact_replay.accepted_functions(units).get(
            "gpt-web-aya-object-vslot28-full-root", set()
        ))
        full = (ROOT / "src" / "characters" / "AyaObjectActionState.cpp").read_text(
            encoding="utf-8"
        )
        self.assertIn("void AyaObjectActionStateView::update_action_state()", full)
        self.assertIn("case 856:", full)
        self.assertIn("double object_y;", full)
        self.assertEqual(full.count("float payload[3];"), 1)
        self.assertNotIn("float payload[3] =", full)
        self.assertIn("direction = 1;", full)
        self.assertIn("time_counter_144 >= 180", full)
        action815 = full[full.index("    case 815: {"):full.index("    case 816: {")]
        self.assertIn("if (owner_action < 520)", action815)
        self.assertIn("else if (owner_action > 524)", action815)
        for owner_action in [520, 521, 522, 523]:
            self.assertIn(f"== {owner_action}", action815)
        action816 = full[full.index("    case 816: {"):full.index("    case 817: {")]
        self.assertGreaterEqual(action816.count("if (sequence_index_13e < 2)"), 2)
        self.assertIn("owner_sequence >= 16 || owner_sequence == 0", action816)
        action825 = full[full.index("    case 825:"):full.index("    case 826: {")]
        self.assertIn("switch (sequence_index_13e)", action825)
        for sequence in [0, 1, 2]:
            self.assertIn(f"case {sequence}:", action825)


    def test_default_cpu_policy_owner_source_checkpoint(self) -> None:
        text = (ROOT / "src" / "characters" / "CpuActionPolicies.cpp").read_text(
            encoding="utf-8"
        )
        self.assertNotIn("(unsigned __int16)v84", text)
        self.assertEqual(text.count("goto LABEL_654;"), 0)
        self.assertEqual(text.count("goto LABEL_860;"), 1)
        self.assertEqual(text.count("goto LABEL_658;"), 1)
        signed_guard_labels = [
            1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 13, 14, 17, 18, 19, 20, 21, 22, 24, 25, 26
        ]
        for label in signed_guard_labels:
            self.assertEqual(text.count(f"LABEL_SIGNED_RANGE_{label:02d}:"), 1)
        for rejected_label in [8, 12, 15, 16, 23]:
            self.assertNotIn(f"LABEL_SIGNED_RANGE_{rejected_label:02d}:", text)
        self.assertIn(
            "if ( v84 >= 30 && v84 <= 39 )\n{\n"
            "*(_WORD *)CPU_FIELD(1894) = 3;\nreturn;\n}", text)
        for low, high, label in [(40, 49, 11), (12, 14, 17), (18, 24, 19), (12, 15, 24)]:
            self.assertIn(
                f"if ( v84 < {low} )\ngoto LABEL_SIGNED_RANGE_{label:02d};\n"
                f"if ( v84 > {high} )\ngoto LABEL_SIGNED_RANGE_{label:02d};\n{{\n"
                "*(_WORD *)CPU_FIELD(1894) = 3;\nreturn;\n}\n"
                f"LABEL_SIGNED_RANGE_{label:02d}:", text)
        self.assertIn(
            "if ( v84 >= 20 && v84 <= 29 )\ngoto LABEL_860;", text
        )
        self.assertIn(
            "if ( v84 >= 45 && v84 <= 49 )\ngoto LABEL_658;", text
        )
        self.assertEqual(
            text.count("v101 = *(__int16 *)CPU_FIELD(1896) <= 0;"), 3
        )
        self.assertNotIn("v101 = *(_WORD *)CPU_FIELD(1896) <= 0;", text)
        self.assertNotIn("v106 = v105 == 202;", text)
        self.assertNotIn("v106 = v109 == 203;", text)
        self.assertNotIn("bool v106;", text)
        self.assertNotIn("LABEL_1024:", text)
        self.assertEqual(text.count("if ( selector_random_roll(0x64u) <= 0xA )"), 2)
        self.assertIn(
            "case 1:\nv101 = *(__int16 *)CPU_FIELD(1896) <= 0;\n"
            "*(_DWORD *)CPU_FIELD(1716) = 1;\nif ( v101 )\n{\n"
            "*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) <= 0xA )\n"
            "*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);\n}\n"
            "return;",
            text,
        )
        self.assertIn(
            "LABEL_994:\n*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) <= 0xA )\n"
            "*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);",
            text,
        )
        self.assertIn(
            "if ( v105 == 202 )\ngoto LABEL_1022;\ngoto LABEL_1008;",
            text,
        )
        self.assertIn(
            "if ( v109 == 203 )\ngoto LABEL_1022;\ngoto LABEL_1008;",
            text,
        )
        self.assertIn(
            "LABEL_1023:\n*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) > 0x64 )\nreturn;\n"
            "goto LABEL_1025;\nLABEL_1025:\n"
            "*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);",
            text,
        )
        self.assertIn(
            "case 0x64:\nv110 = *(_BYTE *)CPU_FIELD(260);", text
        )
        self.assertIn(
            "if ( v101 )\n{\n*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) <= 0x64 )\n"
            "*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);\n"
            "return;\n}\nif ( *(_WORD *)CPU_FIELD(316) == 200",
            text,
        )


    def test_giant_action_switch_manifest_tracks_alice_root(self) -> None:
        with (ROOT / "config" / "giant-action-switches.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        root = next(row for row in manifest["roots"] if row["name"] == "alice-vslot28")
        self.assertEqual(root["address"], "0x004E9F50")
        self.assertEqual(root["callable_end"], "0x004F4631")
        self.assertEqual(root["metadata_end"], "0x004F4B80")
        self.assertEqual(root["expected_unique_destinations"], 103)
        self.assertEqual(root["expected_direct_call_sites"], 674)
        self.assertEqual(root["expected_direct_call_targets"], 27)
        self.assertEqual(root["expected_ret_opcodes"], 128)
        self.assertEqual(root["partial_semantic_scaffold"], "src/characters/AliceActionStateScaffold.cpp")
        self.assertEqual(root["reference_semantic_root"], "youmu-vslot28")
        self.assertEqual(root["verified_semantic_cases"], [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 197, 198, 199, 200, 201, 202, 203, 204, 208, 209, 210, 211, 212, 214, 215, 220, 221, 222, 223, 224, 225, 226, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 320, 321, 322, 408, 409, 411, 412, 500, 501, 505, 506, 507, 695, 696])
        self.assertEqual(root["verified_semantic_closed_regions"], ["low"])
        regions = {row["name"]: row for row in root["regions"]}
        self.assertEqual((regions["low"]["case_min"], regions["low"]["case_max"], regions["low"]["destination_count"]), (0, 226, 31))
        self.assertEqual((regions["mid"]["case_min"], regions["mid"]["case_max"], regions["mid"]["destination_count"]), (301, 508, 34))
        self.assertEqual((regions["high"]["case_min"], regions["high"]["case_max"], regions["high"]["destination_count"]), (521, 770, 40))


    def test_alice_partial_action_scaffold_stays_off_ledger(self) -> None:
        scaffold = ROOT / "src" / "characters" / "AliceActionStateScaffold.cpp"
        text = scaffold.read_text(encoding="utf-8")
        self.assertIn("try_dispatch_verified_action", text)
        for case in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 197, 198, 199, 200, 201, 202, 203, 204, 208, 209, 210, 211, 212, 214, 215, 220, 221, 222, 223, 224, 225, 226, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 320, 321, 322, 408, 409, 411, 412, 500, 501, 505, 506, 507, 695, 696]:
            self.assertIn(f"case {case}:", text)
        for snippet in [
            "-10.0 - 13.0 * spawn_index",
            "spawn_payload[2] = 16.0f",
            "spawn_payload[2] = 17.0f",
            "spawn_payload[2] = 24.0f",
            "*reinterpret_cast<float *>(raw + 256) = 0.5f",
            "33 * static_cast<signed char>(facing)",
            "*reinterpret_cast<float *>(raw + 240) + 112.0",
            "*reinterpret_cast<float *>(raw + 244) = 19.0f",
            "spawn_payload[2] = 19.0f",
            "spawn_payload[0] = -80.0f",
            "adjust_counter_482(200, 60)",
            "dispatch_character_wave_handle(2)",
            "counter > 45",
            "set_action(212)",
            "*reinterpret_cast<float *>(raw + 244) + 2.0",
            "is_y_at_or_below_stage_surface(this)",
            "*reinterpret_cast<float *>(raw + 244) = 8.5f",
            "*reinterpret_cast<float *>(raw + 244) = -8.5f",
            "face_opponent_and_flip_horizontal_velocity()",
            "*reinterpret_cast<_WORD *>(raw + 1198) = 2",
            "adjusted < -20.0f",
            "*reinterpret_cast<float *>(raw + 244) = 9.0f",
            "*reinterpret_cast<float *>(raw + 244) = -9.0f",
            "counter >= 13",
            "0.30000001192092896",
            "magnitude > 12.0f",
            "adjust_counter_482(10, 1)",
            "adjust_counter_482(5, 1)",
            "set_action(215)",
            "spawn_payload[0] = 20.0f",
            "spawn_payload[0] = -25.0f",
            "spawn_payload[0] = -45.0f",
            "dispatch_character_wave_handle(3)",
            "adjust_counter_482(200, 120)",
            "17 * static_cast<signed char>(facing)",
            "*reinterpret_cast<float *>(raw + 240) + 104.0",
            "spawn_payload[0] = -74.0f",
            "adjust_counter_482(200, 45)",
            "*reinterpret_cast<int *>(raw + 324) >= 40",
            "spawn_payload[1] = 7.0f",
            "20 * static_cast<signed char>(facing)",
            "spawn_payload[0] = -45.0f",
            "adjust_counter_482(200, 60)",
        ]:
            self.assertIn(snippet, text)
        self.assertNotIn("Alice_dispatch_action_state_vslot28(", text)

        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            row = next(row for row in csv.DictReader(stream) if row["address"].lower() == "0x004e9f50")
        self.assertEqual(row["status"], "unclassified")
        self.assertEqual(row["source_file"], "src/characters/Vslot28ActionStateRoots.hpp")


    def test_xiph_origin_anchor_manifest_is_pinned(self) -> None:
        with (ROOT / "config" / "xiph-origin-anchors.toml").open("rb") as stream:
            anchors = tomllib.load(stream)
        self.assertEqual(
            anchors["target_sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(anchors["sdk_sha256"], self.xiph_sdk.ARCHIVE_SHA256)
        rows = anchors["anchors"]
        self.assertEqual(len(rows), 39)
        self.assertEqual(len({row["address"] for row in rows}), 39)
        self.assertEqual(sum(row["size"] for row in rows), 2704)

    def test_xiph_relocated_origin_anchor_manifest_is_pinned(self) -> None:
        with (ROOT / "config" / "xiph-relocated-origin-anchors.toml").open("rb") as stream:
            anchors = tomllib.load(stream)
        self.assertEqual(
            anchors["target_sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(anchors["sdk_sha256"], self.xiph_sdk.ARCHIVE_SHA256)
        self.assertEqual(anchors["min_nonreloc_coverage"], 0.70)
        self.assertEqual(anchors["min_nonreloc_bytes"], 24)
        rows = anchors["anchors"]
        self.assertEqual(len(rows), 156)
        self.assertEqual(len({row["address"] for row in rows}), 156)
        self.assertEqual(sum(row["size"] for row in rows), 57665)
        groups = [row for row in rows if row.get("equivalence_group") == "vorbis-residue-inverse-clones"]
        self.assertEqual({row["address"] for row in groups}, {"0x00686360", "0x00686E20"})


    def test_runtime_and_roster_origin_evidence_is_pinned(self) -> None:
        with (ROOT / "config" / "msvc-runtime-relocated-origin-anchors.toml").open("rb") as stream:
            runtime = tomllib.load(stream)
        self.assertEqual(runtime["target_sha256"], "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e")
        self.assertEqual(runtime["min_nonreloc_coverage"], 0.70)
        self.assertEqual(len(runtime["anchors"]), 24)
        self.assertEqual(sum(row["size"] for row in runtime["anchors"]), 7_735)

        with (ROOT / "config" / "function-origin-rules.toml").open("rb") as stream:
            rules = tomllib.load(stream)["rules"]
        roster = next(
            rule
            for rule in rules
            if rule["id"] == "roster-fighter-primary-vtable-authored-106a"
        )
        self.assertTrue(roster["skip_matching"])
        self.assertEqual(roster["expected_count"], 64)
        self.assertEqual(roster["expected_bytes"], 1_124_191)
        with (ROOT / roster["pointer_anchor_file"]).open("rb") as stream:
            roster_manifest = tomllib.load(stream)
        roots = roster_manifest["anchors"]
        self.assertEqual(len(roots), 73)
        self.assertEqual(sum(row["size"] for row in roots), 1_133_382)
        self.assertEqual(
            {row["address"] for row in roots if row["address"] in {"0x00539B70", "0x0053A160"}},
            {"0x00539B70", "0x0053A160"},
        )

        object_roster = next(
            rule
            for rule in rules
            if rule["id"] == "roster-character-object-vtable-authored-106a"
        )
        self.assertTrue(object_roster["skip_matching"])
        self.assertEqual(object_roster["expected_count"], 31)
        self.assertEqual(object_roster["expected_bytes"], 676_773)
        with (ROOT / object_roster["pointer_anchor_file"]).open("rb") as stream:
            object_manifest = tomllib.load(stream)
        object_roots = object_manifest["anchors"]
        self.assertEqual(len(object_roots), 32)
        self.assertEqual(sum(row["size"] for row in object_roots), 676_774)
        self.assertEqual(
            {row["address"] for row in object_roots if row["address"] in {"0x00496540", "0x00520890", "0x00657150"}},
            {"0x00496540", "0x00520890", "0x00657150"},
        )
        shared_render = next(row for row in object_roots if row["address"] == "0x00435360")
        self.assertEqual(len(shared_render["pointer_slots"]), 15)
        self.assertEqual({slot["slot_offset"] for slot in shared_render["pointer_slots"]}, {"0x34"})
        shared_idle = next(row for row in object_roots if row["address"] == "0x0041F890")
        self.assertEqual(shared_idle["size"], 1)
        self.assertEqual(len(shared_idle["pointer_slots"]), 15)
        self.assertEqual({slot["slot_offset"] for slot in shared_idle["pointer_slots"]}, {"0x40"})

    def test_adjustor_thunk_origin_manifests_are_pinned(self) -> None:
        expected = [
            (
                "config/vc8-generated-character-object-manager-adjustor-thunks-origin-anchors.toml",
                "src/characters/CharacterObjectManagerCtors.cpp",
                15,
                120,
            ),
            (
                "config/vc8-generated-effect-manager-adjustor-thunks-origin-anchors.toml",
                "src/battle/EffectManagerLifetime.cpp",
                4,
                32,
            ),
        ]
        for relpath, source, count, byte_total in expected:
            with (ROOT / relpath).open("rb") as stream:
                manifest = tomllib.load(stream)
            self.assertEqual(
                manifest["target_sha256"],
                "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
            )
            self.assertEqual(
                manifest["compiler_sha256"],
                "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c",
            )
            self.assertEqual(manifest["source"], source)
            self.assertTrue(manifest["enable_gs"])
            self.assertEqual(manifest["min_nonreloc_coverage"], 0.50)
            rows = manifest["anchors"]
            self.assertEqual(len(rows), count)
            self.assertEqual(sum(row["size"] for row in rows), byte_total)
            self.assertTrue(all(row["size"] == 8 for row in rows))
            self.assertTrue(all(len(row["pointer_slots"]) == 1 for row in rows))
            self.assertTrue(all(len(row["rel32_targets"]) == 1 for row in rows))

    def test_multichunk_function_byte_ownership_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {int(row["address"], 0): row for row in csv.DictReader(stream)}
        ownership = self.byte_ownership.load(functions)
        if (ROOT / "resources" / "th105.exe").is_file():
            self.assertEqual(
                self.byte_ownership.load(functions, require_bytes=True), ownership
            )
        self.assertEqual(set(ownership), {0x00496540, 0x004CADB0})
        sakuya = ownership[0x004CADB0]
        self.assertEqual(sakuya["main_size"], 41_511)
        self.assertEqual(sakuya["main_excluded_bytes"], 21)
        self.assertEqual(sakuya["owned_main_bytes"], 41_490)
        self.assertEqual(sakuya["remote_bytes"], 33_451)
        self.assertEqual(sakuya["owned_bytes"], 74_941)
        self.assertFalse(sakuya["remote_exact"])
        self.assertEqual(len(sakuya["main_exclusions"]), 3)
        self.assertEqual(len(sakuya["chunks"]), 10)
        self.assertEqual(sakuya["chunks"][0]["start"], 0x004D4FE0)
        self.assertEqual(sakuya["chunks"][-1]["end"], 0x004DD2D1)
        self.assertEqual(
            self.byte_ownership.exact_owned_size(0x004CADB0, 41_511, ownership),
            41_490,
        )

        reimu_object = ownership[0x00496540]
        self.assertEqual(reimu_object["main_size"], 39_853)
        self.assertEqual(reimu_object["main_excluded_bytes"], 7)
        self.assertEqual(reimu_object["owned_main_bytes"], 39_846)
        self.assertEqual(reimu_object["remote_bytes"], 6_282)
        self.assertEqual(reimu_object["owned_bytes"], 46_128)
        self.assertFalse(reimu_object["remote_exact"])
        self.assertEqual(len(reimu_object["main_exclusions"]), 1)
        self.assertEqual(reimu_object["chunks"][0]["start"], 0x004A00F0)
        self.assertEqual(reimu_object["chunks"][0]["end"], 0x004A1979)
        self.assertEqual(
            self.byte_ownership.exact_owned_size(0x00496540, 39_853, ownership),
            39_846,
        )

    def test_secondary_animation_generated_manifest_covers_new_leaves(self) -> None:
        with (ROOT / "config" / "vc8-generated-secondary-animation-deque-origin-anchors.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        rows = manifest["anchors"]
        self.assertEqual(len(rows), 3)
        self.assertEqual(sum(row["size"] for row in rows), 259)
        self.assertEqual(
            {row["address"] for row in rows},
            {"0x004300B0", "0x0042FDC0", "0x006A0C60"},
        )


    def test_vc8_generated_origin_anchor_manifest_is_pinned(self) -> None:
        with (ROOT / "config" / "vc8-generated-origin-anchors.toml").open("rb") as stream:
            anchors = tomllib.load(stream)
        self.assertEqual(
            anchors["target_sha256"],
            "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e",
        )
        self.assertEqual(
            anchors["compiler_sha256"],
            "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c",
        )
        self.assertEqual(anchors["source"], "src/battle/PatGroup.cpp")
        self.assertTrue(anchors["enable_gs"])
        self.assertEqual(anchors["min_nonreloc_coverage"], 0.70)
        self.assertEqual(anchors["min_nonreloc_bytes"], 24)
        rows = anchors["anchors"]
        self.assertEqual(
            [(row["address"], row["size"]) for row in rows],
            [("0x0045FC30", 76), ("0x00461320", 129)],
        )
        with (ROOT / "config" / "vc8-generated-pat-copy-origin-anchors.toml").open("rb") as stream:
            copy_anchors = tomllib.load(stream)
        self.assertEqual(copy_anchors["target_sha256"], anchors["target_sha256"])
        self.assertEqual(copy_anchors["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(copy_anchors["source"], "scripts/probes/pat_vector_generated.cpp")
        self.assertTrue(copy_anchors["enable_gs"])
        self.assertEqual(copy_anchors["max_alignment_tail"], 1)
        self.assertEqual(copy_anchors["alignment_tail_hex"], "cc")
        self.assertEqual(
            [(row["address"], row["size"]) for row in copy_anchors["anchors"]],
            [
                ("0x00461420", 249),
                ("0x00461940", 123),
                ("0x004607F0", 230),
                ("0x004608E0", 149),
                ("0x00460F50", 56),
                ("0x00461120", 92),
                ("0x00461180", 177),
                ("0x00461240", 41),
                ("0x00461270", 166),
                ("0x004613E0", 58),
            ],
        )
        with (ROOT / "config" / "vc8-generated-pat-nested-origin-anchors.toml").open("rb") as stream:
            nested_anchors = tomllib.load(stream)
        self.assertEqual(nested_anchors["target_sha256"], anchors["target_sha256"])
        self.assertEqual(nested_anchors["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(nested_anchors["source"], "scripts/probes/pat_nested_vectors.cpp")
        self.assertTrue(nested_anchors["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in nested_anchors["anchors"]],
            [
                ("0x0045FBD0", 88),
                ("0x00460AD0", 317),
                ("0x0040C240", 42),
                ("0x00435F90", 42),
                ("0x00464B40", 90),
                ("0x0040DF70", 90),
            ],
        )
        with (ROOT / "config" / "vc8-generated-pat-record-copy-origin-anchors.toml").open("rb") as stream:
            record_copy = tomllib.load(stream)
        self.assertEqual(record_copy["target_sha256"], anchors["target_sha256"])
        self.assertEqual(record_copy["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(record_copy["source"], "scripts/probes/pat_record_copy_generated.cpp")
        self.assertTrue(record_copy["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in record_copy["anchors"]],
            [("0x00460C90", 311)],
        )
        with (ROOT / "config" / "vc8-generated-ui-map-origin-anchors.toml").open("rb") as stream:
            ui_map = tomllib.load(stream)
        self.assertEqual(ui_map["target_sha256"], anchors["target_sha256"])
        self.assertEqual(ui_map["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(ui_map["source"], "scripts/probes/ui_design_map_generated.cpp")
        self.assertFalse(ui_map["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in ui_map["anchors"]],
            [("0x0046EA60", 105)],
        )
        with (ROOT / "config" / "vc8-generated-list-voidptr-origin-anchors.toml").open("rb") as stream:
            list_nodes = tomllib.load(stream)
        self.assertEqual(list_nodes["target_sha256"], anchors["target_sha256"])
        self.assertEqual(list_nodes["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(list_nodes["source"], "scripts/probes/list_voidptr_buynode_generated.cpp")
        self.assertFalse(list_nodes["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"], row["equivalence_group"]) for row in list_nodes["anchors"]],
            [
                ("0x004129E0", 51, "list-voidptr-buynode-clones"),
                ("0x00421F30", 51, "list-voidptr-buynode-clones"),
            ],
        )
        with (ROOT / "config" / "vc8-generated-list-voidptr-tidy-origin-anchors.toml").open("rb") as stream:
            list_tidy = tomllib.load(stream)
        self.assertEqual(list_tidy["target_sha256"], anchors["target_sha256"])
        self.assertEqual(list_tidy["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(list_tidy["source"], "scripts/probes/list_voidptr_tidy_generated.cpp")
        self.assertFalse(list_tidy["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"], row["equivalence_group"]) for row in list_tidy["anchors"]],
            [
                ("0x004023E0", 72, "list-voidptr-tidy-clones"),
                ("0x00435EB0", 72, "list-voidptr-tidy-clones"),
            ],
        )
        with (ROOT / "config" / "vc8-generated-scenario-event-map-find-origin-anchors.toml").open("rb") as stream:
            scenario_map_find = tomllib.load(stream)
        self.assertEqual(scenario_map_find["target_sha256"], anchors["target_sha256"])
        self.assertEqual(scenario_map_find["compiler_sha256"], anchors["compiler_sha256"])
        self.assertEqual(scenario_map_find["source"], "src/battle/ScenarioEventNameResolver.cpp")
        self.assertFalse(scenario_map_find["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in scenario_map_find["anchors"]],
            [("0x006A4D60", 105)],
        )

    def test_exact_tu_std_origin_manifests_are_pinned(self) -> None:
        paths = sorted((ROOT / "config").glob("vc8-generated-*-std-origin-anchors.toml"))
        self.assertEqual(len(paths), 32)
        target_sha = "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e"
        compiler_sha = "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c"
        rows = []
        for path in paths:
            with path.open("rb") as stream:
                manifest = tomllib.load(stream)
            self.assertEqual(manifest["target_sha256"], target_sha)
            self.assertEqual(manifest["compiler_sha256"], compiler_sha)
            self.assertEqual(manifest["min_nonreloc_coverage"], 0.70)
            self.assertEqual(manifest["min_nonreloc_bytes"], 24)
            self.assertIn(manifest["max_alignment_tail"], (0, 1))
            if manifest["max_alignment_tail"]:
                self.assertEqual(manifest["alignment_tail_hex"], "cc")
            self.assertTrue(manifest["source"].startswith("src/"))
            rows.extend(manifest["anchors"])
        self.assertEqual(len(rows), 280)
        self.assertEqual(len({row["address"] for row in rows}), 280)
        self.assertEqual(sum(row["size"] for row in rows), 38_208)

    def test_new_layout_probe_origin_manifests_are_pinned(self) -> None:
        expected = {
            "vc8-generated-spriteex-vector-origin-anchors.toml": (
                "scripts/probes/spriteex_vector_generated.cpp", False, 12, 829
            ),
            "vc8-generated-map-int-value16-origin-anchors.toml": (
                "scripts/probes/map_int_value16_generated.cpp", False, 7, 506
            ),
            "vc8-generated-map-int-value244-origin-anchors.toml": (
                "scripts/probes/map_int_value244_generated.cpp", False, 7, 576
            ),
            "vc8-generated-fighter-sequence-deque-origin-anchors.toml": (
                "scripts/probes/fighter_sequence_deque_generated.cpp", False, 3, 713
            ),
            "vc8-generated-phase-render-list-origin-anchors.toml": (
                "src/battle/FighterPhaseRenderState.cpp", True, 6, 825
            ),
            "vc8-generated-battle-render-request-list-origin-anchors.toml": (
                "src/battle/BattleObjectStage.cpp", False, 1, 59
            ),
            "vc8-generated-list-u32-origin-anchors.toml": (
                "scripts/probes/list_u32.cpp", False, 1, 184
            ),
            "vc8-generated-deque-u32-origin-anchors.toml": (
                "scripts/probes/deque_push_back_4byte.cpp", False, 2, 213
            ),
        }
        for filename, (source, enable_gs, count, byte_count) in expected.items():
            with (ROOT / "config" / filename).open("rb") as stream:
                manifest = tomllib.load(stream)
            self.assertEqual(manifest["target_sha256"], "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e")
            self.assertEqual(manifest["compiler_sha256"], "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c")
            self.assertEqual(manifest["source"], source)
            self.assertEqual(manifest["enable_gs"], enable_gs)
            self.assertEqual(len(manifest["anchors"]), count)
            self.assertEqual(sum(row["size"] for row in manifest["anchors"]), byte_count)

    def test_spell_tree_origin_manifest_is_expanded(self) -> None:
        path = ROOT / "config" / "vc8-generated-spell-tree-probe-origin-anchors.toml"
        with path.open("rb") as stream:
            manifest = tomllib.load(stream)
        self.assertEqual(manifest["source"], "scripts/probes/spell_tree.cpp")
        self.assertTrue(manifest["enable_gs"])
        self.assertEqual(len(manifest["anchors"]), 6)
        self.assertEqual(sum(row["size"] for row in manifest["anchors"]), 1_131)
        self.assertIn("0x0042CF20", {row["address"] for row in manifest["anchors"]})
        self.assertIn("0x0042E370", {row["address"] for row in manifest["anchors"]})

    def test_short_set_origin_manifest_is_pinned(self) -> None:
        path = ROOT / "config" / "vc8-generated-short-set-origin-anchors.toml"
        with path.open("rb") as stream:
            manifest = tomllib.load(stream)
        self.assertEqual(manifest["source"], "scripts/probes/short_set_generated.cpp")
        self.assertTrue(manifest["enable_gs"])
        self.assertEqual(
            [(row["address"], row["size"]) for row in manifest["anchors"]],
            [
                ("0x00432F90", 509),
                ("0x00433190", 695),
                ("0x00433450", 189),
                ("0x00432710", 28),
                ("0x00432730", 27),
                ("0x00432750", 99),
                ("0x00432900", 78),
                ("0x00432950", 82),
                ("0x00432A40", 137),
                ("0x00432AD0", 59),
                ("0x00432B50", 53),
            ],
        )

    def test_deque_short_erase_origin_manifest_is_pinned(self) -> None:
        path = ROOT / "config" / "vc8-generated-deque-short-erase-origin-anchors.toml"
        with path.open("rb") as stream:
            manifest = tomllib.load(stream)
        self.assertEqual(manifest["source"], "scripts/probes/DequeShortEraseOrigin.cpp")
        self.assertEqual([(row["address"], row["size"]) for row in manifest["anchors"]], [("0x004323B0", 108), ("0x00443A30", 108), ("0x0045DC20", 108), ("0x00617B50", 108)])
        self.assertTrue(all(row["equivalence_group"] == "deque-erase-108-clones" for row in manifest["anchors"]))

    def test_inventory_pagination_normalization(self) -> None:
        data, next_offset = self.inventory.normalize_page(
            {
                "data": [
                    {
                        "address": "0x401000",
                        "name": "sub_401000",
                        "size": "0x34",
                    }
                ],
                "next_offset": 1,
            }
        )
        self.assertEqual(len(data), 1)
        self.assertEqual(next_offset, 1)

    def test_attestation_byte_parser(self) -> None:
        self.assertEqual(
            self.ida_check.parse_ida_bytes("90 00 ff"), b"\x90\x00\xff"
        )

    def test_ida_mcp_runtime_is_pinned_and_project_independent(self) -> None:
        self.assertEqual(self.mcp_runtime.MCP_REQUIREMENT, "mcp==1.26.0")
        self.assertEqual(
            self.mcp_runtime.bootstrap_command(
                "/usr/bin/uv", ["scripts/check-ida-mcp.py"]
            ),
            [
                "/usr/bin/uv",
                "run",
                "--quiet",
                "--no-project",
                "--with",
                "mcp==1.26.0",
                "python3",
                "scripts/check-ida-mcp.py",
            ],
        )

    def test_ida_mcp_runtime_reports_missing_uv(self) -> None:
        with (
            mock.patch.object(
                self.mcp_runtime, "installed_mcp_version", return_value=None
            ),
            mock.patch.object(self.mcp_runtime.shutil, "which", return_value=None),
            mock.patch.dict(
                self.mcp_runtime.os.environ,
                {self.mcp_runtime.BOOTSTRAP_MARKER: ""},
            ),
        ):
            with self.assertRaisesRegex(RuntimeError, "install uv"):
                self.mcp_runtime.ensure_mcp_runtime()

    @unittest.skipUnless(
        (ROOT / "resources" / "th105.exe").is_file(), "private target is unavailable"
    )
    def test_typed_target_mapping_reads_exact_pe_bytes(self) -> None:
        data, _manifest = self.typed.verify_local_target()
        self.assertEqual(
            self.typed.target_bytes(data, 0x00401000, 8), data[0x1000:0x1008]
        )

    def test_first_mismatch_is_structured(self) -> None:
        mismatch = self.comparator.first_mismatch(
            b"\x90\x90\xc3", b"\x90\xcc\xc3", 0x401000
        )
        self.assertEqual(mismatch["offset"], 1)
        self.assertEqual(mismatch["address"], "0x00401001")

    def test_unknown_dir32_is_a_blocker(self) -> None:
        result, failure = self.comparator.failure_record(
            ValueError("unknown absolute data relocation: __ehhandler$probe")
        )
        self.assertEqual(result, "blocked")
        self.assertEqual(failure["category"], "relocation.dir32.unknown_symbol")

    def test_vc8_real_literal_symbol_contract(self) -> None:
        self.assertEqual(
            self.literals.real_literal_bytes(
                {"type": "DIR32", "symbol": "__real@3f800000"}
            ),
            bytes.fromhex("0000803f"),
        )
        self.assertEqual(
            self.literals.real_literal_bytes(
                {"type": "DIR32", "symbol": "__real@4060000000000000"}
            ),
            bytes.fromhex("0000000000006040"),
        )
        self.assertIsNone(
            self.literals.real_literal_bytes(
                {"type": "REL32", "symbol": "ordinary"}
            )
        )
        with self.assertRaisesRegex(ValueError, "must use DIR32"):
            self.literals.real_literal_bytes(
                {"type": "REL32", "symbol": "__real@3f800000"}
            )
        with self.assertRaisesRegex(ValueError, "zero addend"):
            self.literals.real_literal_bytes(
                {
                    "type": "DIR32",
                    "symbol": "__real@3f800000",
                    "addend": 4,
                }
            )
        with self.assertRaisesRegex(ValueError, "malformed __real"):
            self.literals.real_literal_bytes(
                {"type": "DIR32", "symbol": "__real@xyz"}
            )

    def test_real_literal_override_cannot_hide_value_mismatch(self) -> None:
        destination = {
            "coff_symbol": "_named_scalar",
            "address": "0x00600000",
            "data_hex": "0000000000006040",
            "addends": "0",
            "evidence": "test fixture",
            "validation": "address",
        }
        with self.assertRaisesRegex(ValueError, "source encodes .*destination declares"):
            self.literals.validate_real_literal_mapping(
                "__real@0000000000000000", "_named_scalar", destination
            )
        self.assertEqual(
            self.literals.validate_real_literal_mapping(
                "__real@4060000000000000", "_named_scalar", destination
            ),
            bytes.fromhex("0000000000006040"),
        )

    def test_repository_real_literal_mappings_are_consistent(self) -> None:
        with (ROOT / "config" / "reccmp-relocations.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            relocations = list(csv.DictReader(stream))
        with (ROOT / "config" / "match-units.toml").open("rb") as stream:
            manifest = tomllib.load(stream)
        counts = self.literals.audit_real_literals(relocations, manifest)
        self.assertEqual(counts["ledger_literals"], 306)
        self.assertEqual(counts["explicit_mappings"], 429)
        self.assertEqual(counts["target_checks"], 0)

    @unittest.skipUnless(
        (ROOT / "resources" / "th105.exe").is_file(), "private target is unavailable"
    )
    def test_repository_real_literals_match_target_bytes(self) -> None:
        counts = self.validator.validate_real_literal_relocations(
            self.manifest.load_manifest(), require_bytes=True
        )
        self.assertEqual(counts["target_checks"], 735)

    def test_rel32_accepts_only_supported_instruction_forms(self) -> None:
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\xe8\0\0\0\0", 1), "call"
        )
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\xe9\0\0\0\0", 1), "jmp"
        )
        self.assertEqual(
            self.comparator.rel32_operand_kind(b"\x0f\x84\0\0\0\0", 2), "jcc"
        )
        self.assertIsNone(
            self.comparator.rel32_operand_kind(b"\x90\0\0\0\0", 1)
        )


    def test_youmu_giant_owner_locality_checkpoint(self) -> None:
        source = (ROOT / "src" / "characters" / "YoumuActionState.cpp").read_text(
            encoding="utf-8"
        )
        self.assertIn(
            "*(_WORD *)(raw +  1900) = 0;\n*(_WORD *)(raw +  1898) = 1;",
            source,
        )
        self.assertNotIn("*(_DWORD *)(raw +  1898) = 1;", source)
        self.assertIn(
            "if ( !*(_WORD *)(raw +  322) && *(_WORD *)(raw +  320) == 5 )\n"
            "dispatch_indexed_event_member(0x1Du);",
            source,
        )
        self.assertIn(
            "case 0xD7:", source
        )
        self.assertEqual(source.count("if ( !*(_BYTE *)(raw +  1150) )"), 2)
        self.assertIn("if ( *(float *)(raw +  244) < v7 )", source)
        self.assertIn("if ( *(float *)(raw +  244) < v8 )", source)
        mid412 = source[source.index("case 0x19C:") : source.index("case 0x19E:")]
        self.assertLess(
            mid412.index("*(_BYTE *)(raw +  2021) = 1;"),
            mid412.index("*(_WORD *)(raw +  2022) = 3;"),
        )
        for expression in (
            "*(float *)(raw +  236) - 80 * (char)v174",
            "*(float *)(raw +  236) - 150 * (char)v67",
            "*(float *)(raw +  236) - 45 * (char)v69",
            "*(float *)(raw +  236) - 45 * (char)v70",
        ):
            self.assertIn(expression, source)
        self.assertNotIn("- (double)(45 * (char)v69)", source)
        units = self.manifest.load_manifest()["units"]
        unit = units["gpt-web-youmu-vslot28-full-root"]
        self.assertIn("20/98", unit["notes"])
        self.assertIn("51 -> 57", unit["notes"])
        self.assertIn("336 -> 320", unit["notes"])
        self.assertIn("+0x9334", unit["notes"])


if __name__ == "__main__":
    unittest.main()
