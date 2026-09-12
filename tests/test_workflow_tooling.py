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
        cls.roster_vtable_coverage = load_script("audit-roster-primary-vtable-coverage.py")
        cls.rdata_text_pointers = load_script("rank-unledgered-rdata-text-pointers.py")

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
        self.assertEqual(len(functions), 4023)
        matching = [row for row in functions if row["status"] == "matching"]
        self.assertEqual(len(matching), 1312)
        self.assertTrue(all(row["match_percent"] == "100.00" for row in matching))
        with (ROOT / "config" / "implemented.csv").open(
            newline="", encoding="utf-8"
        ) as stream:
            implemented = [row[0] for row in csv.reader(stream) if row]
        self.assertEqual(len(implemented), 1388)
        self.assertEqual(
            len(self.validator.rows(ROOT / "config" / "matches.csv")), 1312
        )

    def test_match_unit_graph_covers_current_exact_baseline(self) -> None:
        manifest = self.manifest.load_manifest()
        self.assertEqual(len(manifest["units"]), 492)
        self.assertEqual(
            sum(len(unit["functions"]) for unit in manifest["units"].values()),
            1393,
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
        self.assertEqual(len(accepted), 460)
        self.assertEqual(sum(map(len, accepted.values())), 1312)
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

    def test_natural_atan2_contract_has_one_dedicated_strict_unit(self) -> None:
        units = self.manifest.load_manifest()["units"]
        unit = units["gpt-web-angle-atan2-natural"]
        self.assertEqual(unit["profile"], "vc8-sp1-probe-o2-fp-strict")
        self.assertEqual(unit["source"], "src/engine/AngleAtan2.cpp")
        self.assertEqual([row["address"] for row in unit["functions"]], ["0x00406540"])
        self.assertEqual(unit["functions"][0]["symbol_base"], "?atan2_degrees@th105@@YAMMM@Z")
        source = (ROOT / unit["source"]).read_text(encoding="utf-8")
        self.assertIn("return atan2f(y, x) * 180.0f / 3.1415927f;", source)
        self.assertNotIn("volatile", source)
        self.assertNotIn("atan2_degrees", (ROOT / "src/engine/AngleLookup.cpp").read_text())
        for name in ("AliceObjectEffects", "CharacterObjectEffects", "CpuActionPolicies",
                     "AyaObjectActionEntry", "YoumuObjectActionEntry"):
            caller = (ROOT / "src/characters" / (name + ".cpp")).read_text()
            self.assertIn('#include "engine/AngleAtan2.hpp"', caller)
            self.assertNotIn("double __cdecl atan2_degrees", caller)
        for item in units.values():
            for function in item["functions"]:
                self.assertNotIn("?atan2_degrees@th105@@YANMM@Z=0x00406540",
                                 function.get("rel32_targets", []))

    def test_ida_missed_cscene_manager_virtual_and_raw_pointer_audits_are_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        scene = functions["0X0041E070"]
        self.assertEqual(scene["proposed_name"], "CSceneManager_initialize")
        self.assertEqual(scene["status"], "matching")
        self.assertEqual(scene["match_percent"], "100.00")
        self.assertEqual(scene["size"], "162")
        self.assertEqual(scene["source_file"], "src/engine/SceneManagerRuntime.cpp")
        self.assertEqual(origins["0X0041E070"]["origin"], "authored_game")
        self.assertEqual(origins["0X0041E070"]["disposition"], "authored")

        units = self.manifest.load_manifest()["units"]
        unit = units["gpt-web-scene-manager-initialize"]
        self.assertEqual(unit["source"], "src/engine/SceneManagerRuntime.cpp")
        self.assertEqual(unit["functions"][0]["address"].upper(), "0X0041E070")

    @unittest.skipUnless((ROOT / "resources" / "th105.exe").exists(), "private target is unavailable")
    def test_roster_vtable_and_rdata_census_against_target(self) -> None:
        vtable = self.roster_vtable_coverage.audit()
        surfaces = {surface["surface"]: surface for surface in vtable["surfaces"]}
        self.assertEqual(
            (surfaces["fighter"]["owner_count"], surfaces["fighter"]["slot_count"],
             surfaces["fighter"]["unique_pointer_count"]),
            (15, 360, 99),
        )
        self.assertEqual(surfaces["fighter"]["ledger_interior"], [])
        self.assertEqual(surfaces["fighter"]["unledgered"], [])
        self.assertEqual(
            (surfaces["object"]["owner_count"], surfaces["object"]["slot_count"],
             surfaces["object"]["unique_pointer_count"]),
            (15, 255, 59),
        )
        self.assertEqual(surfaces["object"]["ledger_interior"], [])
        self.assertEqual(surfaces["object"]["unledgered"], [])

        rdata = self.rdata_text_pointers.census()
        uncovered = {row["address"].upper() for row in rdata["uncovered"]}
        self.assertNotIn("0X0041E070", uncovered)
        self.assertIn("0X006BE770", uncovered)


    def test_ida_missed_ogg_callbacks_and_audio_runtime_are_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        callbacks = {
            "0X00418B40": ("read_ogg_data_source", "39"),
            "0X00418C70": ("seek_ogg_data_source", "81"),
            "0X00418CD0": ("close_ogg_data_source", "25"),
            "0X00418CF0": ("tell_ogg_data_source", "23"),
        }
        for address, (name, size) in callbacks.items():
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["size"], size)
            self.assertEqual(row["status"], "matching")
            self.assertEqual(row["match_percent"], "100.00")
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        for address, name, source in (
            ("0X00418A10", "OggDataSource_open", "src/audio/DirectSound.cpp"),
            ("0X00418B70", "fill_ogg_pcm_block", "src/audio/OggPcmRuntime.cpp"),
            ("0X00418D10", "load_sfl_loop_metadata", "src/audio/OggMetadata.cpp"),
        ):
            self.assertEqual(functions[address]["proposed_name"], name)
            self.assertEqual(functions[address]["status"], "implemented")
            self.assertEqual(functions[address]["source_file"], source)
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        scheduler = functions["0X00419100"]
        self.assertEqual(scheduler["proposed_name"], "AudioScheduler_thread_main")
        self.assertEqual(origins["0X00419100"]["origin"], "authored_game")
        self.assertEqual(origins["0X00419100"]["disposition"], "authored")
        for address in ("0X00689190", "0X006892B0"):
            self.assertEqual(origins[address]["origin"], "third_party")
            self.assertEqual(origins[address]["disposition"], "exclude")

        units = self.manifest.load_manifest()["units"]
        self.assertEqual(len(units["gpt-web-ogg-data-source-callbacks"]["functions"]), 4)
        self.assertEqual(units["gpt-web-ogg-data-source-open"]["source"], "src/audio/DirectSound.cpp")
        self.assertEqual(units["gpt-web-ogg-pcm-runtime"]["source"], "src/audio/OggPcmRuntime.cpp")
        self.assertTrue(units["gpt-web-ogg-metadata"]["enable_gs"])

    @unittest.skipUnless((ROOT / "resources" / "th105.exe").exists(), "private target is unavailable")
    def test_data_pointer_census_against_target(self) -> None:
        data_pointers = self.rdata_text_pointers.census(".data")
        self.assertEqual(data_pointers["source_section"], ".data")
        self.assertEqual(data_pointers["unique_text_pointer_count"], 49)
        self.assertEqual(data_pointers["uncovered_count"], 8)
        self.assertEqual(data_pointers["ignored_rtti_name_dword_count"], 81)
        uncovered = {row["address"].upper() for row in data_pointers["uncovered"]}
        for address in ("0X00418B40", "0X00418C70", "0X00418CD0", "0X00418CF0"):
            self.assertNotIn(address, uncovered)
        self.assertNotIn("0X00689190", uncovered)
        self.assertNotIn("0X006892B0", uncovered)

    def test_rtti_name_tail_is_not_a_code_pointer(self) -> None:
        blob = b"\0.?AVCSelectSV@@\0"
        offset = blob.index(b"V@@\0")
        self.assertEqual(int.from_bytes(blob[offset:offset + 4], "little"), 0x00404056)
        self.assertEqual(
            self.rdata_text_pointers.containing_msvc_rtti_name(blob, offset),
            (1, len(blob) - 1, ".?AVCSelectSV@@"),
        )
        for invalid, at in ((b"\0V@@\0", 1), (blob[:-1], offset), (blob, -1), (blob, len(blob))):
            self.assertIsNone(self.rdata_text_pointers.containing_msvc_rtti_name(invalid, at))

    def test_lifetime_checkpoint_ledgers_are_complete(self) -> None:
        functions = {
            row["address"]: row
            for row in self.validator.rows(ROOT / "config" / "functions.csv")
        }
        matches = {
            row["address"]: row
            for row in self.validator.rows(ROOT / "config" / "matches.csv")
        }
        mappings = self.validator.validate_reccmp_ledgers()
        implemented = self.validator.read_implemented(mappings)
        for address, size in (
            ("0x0040ADE0", 11), ("0x0040ADF0", 11), ("0x0040AE00", 11),
            ("0x0040AE10", 60), ("0x00412C80", 30), ("0x0044B320", 30),
        ):
            self.assertEqual(functions[address]["status"], "matching")
            self.assertEqual(int(matches[address]["size"]), size)
            self.assertEqual(matches[address]["name"], mappings[int(address, 0)]["name"])
            self.assertIn(matches[address]["name"], implemented)
        self.assertEqual(functions["0x0040ADB0"]["status"], "implemented")
        self.assertNotIn("0x0040ADB0", matches)
        self.assertIn("CNumber_dtor", implemented)

    def test_timer_import_contract_is_pinned(self) -> None:
        relocations = {
            row["coff_symbol"]: row
            for row in self.validator.rows(ROOT / "config" / "reccmp-relocations.csv")
        }
        for symbol, address, raw in (
            ("__imp__timeGetTime@0", "0x006C0258", "72542e00"),
            ("__imp__GetTickCount@0", "0x006C00E0", "ec592e00"),
        ):
            self.assertEqual(relocations[symbol]["address"], address)
            self.assertEqual(relocations[symbol]["data_hex"], raw)
        if (ROOT / "resources" / "th105.exe").exists():
            self.comparator.verify_target()
            self.assertEqual(self.comparator.target_bytes(0x006C0258, 4).hex(), "72542e00")
            self.assertEqual(self.comparator.target_bytes(0x006C00E0, 4).hex(), "ec592e00")
            self.assertEqual(self.comparator.target_bytes(0x006E5474, 12), b"timeGetTime\0")
            self.assertEqual(self.comparator.target_bytes(0x006E59EE, 13), b"GetTickCount\0")
            self.assertEqual(self.comparator.target_bytes(0x006E5492, 10), b"WINMM.dll\0")

    def test_audio_scheduler_boundary_and_cbitmap_exact_wave_are_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "reccmp-relocations.csv").open(newline="", encoding="utf-8") as stream:
            relocations = {row["coff_symbol"]: row for row in csv.DictReader(stream)}

        finalizer = functions["0X00419000"]
        self.assertEqual(finalizer["current_name"], "")
        self.assertEqual(finalizer["proposed_name"], "finalize_audio_scheduler_state")
        self.assertEqual(finalizer["status"], "implemented")
        self.assertEqual(finalizer["source_file"], "src/audio/AudioSchedulerFinalizer.cpp")
        self.assertIn("259/241", finalizer["evidence"])
        self.assertEqual(origins["0X00419000"]["origin"], "authored_game")
        self.assertEqual(origins["0X00419000"]["disposition"], "authored")

        listener_rows = {
            "0X00419350": ("create_audio_scheduler_listener_event", "166/169"),
            "0X00419400": ("remove_audio_scheduler_listener_event", "174/193"),
            "0X004194D0": ("wait_audio_scheduler_listener_event", "126/184"),
        }
        for address, (name, residual) in listener_rows.items():
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "implemented")
            self.assertEqual(row["source_file"], "src/audio/AudioSchedulerListeners.cpp")
            self.assertIn(residual, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        bitmap_rows = {
            "0X00419F80": ("CBitmapData_ctor", "23"),
            "0X00419FA0": ("CBitmapData_scalar_deleting_destructor", "47"),
            "0X00419FD0": ("CBitmapData_dtor", "21"),
            "0X0041ABD0": ("CBitmapData_copy_from", "196"),
            "0X0041A8E0": ("CBitmapData_png_read", "33"),
        }
        for address, (name, size) in bitmap_rows.items():
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["size"], size)
            self.assertEqual(row["status"], "matching")
            self.assertEqual(row["match_percent"], "100.00")
            self.assertEqual(row["source_file"], "src/assets/CBitmapDataRuntime.cpp")
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        vtable = relocations["??_7CBitmapData@th105@@6B@"]
        self.assertEqual(vtable["address"].upper(), "0X006D6E10")
        self.assertEqual(vtable["data_hex"], "a09f4100")
        version = relocations["??_C@_05OHLMCMDJ@1?45?42?$AA@"]
        self.assertEqual(version["address"].upper(), "0X006D6E04")
        self.assertEqual(bytes.fromhex(version["data_hex"]), b"1.5.2\0")
        callback_ptr = relocations["?CBitmapData_png_read@th105@@YAXPAUPngStruct@1@PAEK@Z"]
        self.assertEqual(callback_ptr["address"].upper(), "0X0041A8E0")

        slot1 = functions["0X00419FF0"]
        self.assertEqual(slot1["proposed_name"], "CBitmapData_load_bitmap")
        self.assertEqual(slot1["status"], "implemented")
        self.assertEqual(slot1["size"], "2230")
        self.assertEqual(slot1["source_file"], "src/assets/CBitmapDataRuntime.cpp")
        self.assertIn("2197/2230", slot1["evidence"])
        self.assertEqual(origins["0X00419FF0"]["origin"], "authored_game")
        self.assertEqual(origins["0X00419FF0"]["disposition"], "authored")

        for address, name, residual in (
            ("0X0041A910", "CBitmapData_load_png", "680/703"),
            ("0X0041ACA0", "CBitmapData_load_from_file", "440/448"),
        ):
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "implemented")
            self.assertEqual(row["source_file"], "src/assets/CBitmapDataRuntime.cpp")
            self.assertIn(residual, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        file_buffer = functions["0X00419860"]
        self.assertEqual(file_buffer["proposed_name"], "FileBufferView_load_plain")
        self.assertEqual(file_buffer["status"], "implemented")
        self.assertEqual(file_buffer["source_file"], "src/assets/FileBufferRuntime.cpp")
        self.assertIn("224/234", file_buffer["evidence"])
        self.assertEqual(origins["0X00419860"]["origin"], "authored_game")
        self.assertEqual(origins["0X00419860"]["disposition"], "authored")

        package_dtor = functions["0X0041B850"]
        self.assertEqual(package_dtor["proposed_name"], "PackageFileIndexNode_dtor")
        self.assertEqual(package_dtor["status"], "matching")
        self.assertEqual(package_dtor["match_percent"], "100.00")
        self.assertEqual(package_dtor["source_file"], "src/assets/PackageFileIndexRuntime.cpp")
        self.assertEqual(origins["0X0041B850"]["origin"], "authored_game")
        self.assertEqual(origins["0X0041B850"]["disposition"], "authored")
        self.assertEqual(relocations["__ehhandler$?load_plain@FileBufferView@th105@@QAE_NPBD@Z"]["address"].upper(), "0X006BDCC8")

        units = self.manifest.load_manifest()["units"]
        self.assertEqual(units["gpt-web-file-buffer-runtime"]["source"], "src/assets/FileBufferRuntime.cpp")
        self.assertTrue(units["gpt-web-file-buffer-runtime"]["enable_gs"])
        self.assertEqual(units["gpt-web-package-file-index-runtime"]["source"], "src/assets/PackageFileIndexRuntime.cpp")
        self.assertEqual(len(units["gpt-web-audio-scheduler-listeners"]["functions"]), 3)
        self.assertEqual(len(units["gpt-web-audio-scheduler-finalizer"]["functions"]), 1)
        bitmap = units["gpt-web-cbitmap-data-runtime"]
        self.assertEqual(bitmap["source"], "src/assets/CBitmapDataRuntime.cpp")
        self.assertEqual(len(bitmap["functions"]), 8)
        slot1_unit = next(row for row in bitmap["functions"] if row["address"].upper() == "0X00419FF0")
        self.assertEqual(slot1_unit["symbol_base"], "?load_bitmap@CBitmapData@th105@@UAE_NPBD@Z")
        self.assertTrue(bitmap["enable_gs"])

    def test_palette_and_effect_object_hierarchy_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        for address, name, residual in (
            ("0X00419A60", "PaletteDataView_load_bmp_palette", "1007/1047"),
            ("0X00419E80", "PaletteDataView_load_raw_palette", "247/243"),
            ("0X00422140", "CSelectObject_ctor", "59/59"),
            ("0X0046F150", "InfoEffectObject_ctor", "59/59"),
        ):
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "implemented")
            self.assertIn(residual, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        exact = {
            "0X00422190": ("AnimationObject_scalar_deleting_destructor", "73"),
            "0X00422180": ("EffectObjectBase_update_slot_28", "5"),
        }
        for address, (name, size) in exact.items():
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["size"], size)
            self.assertEqual(row["status"], "matching")
            self.assertEqual(row["match_percent"], "100.00")
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        units = self.manifest.load_manifest()["units"]
        palette = units["gpt-web-palette-data-runtime"]
        self.assertEqual(palette["source"], "src/assets/PaletteDataRuntime.cpp")
        self.assertTrue(palette["enable_gs"])
        hierarchy = units["gpt-web-effect-object-hierarchy-lifetime"]
        self.assertEqual(hierarchy["source"], "src/battle/EffectHandlePoolAcquire.cpp")
        update = next(row for row in hierarchy["functions"] if row["address"].upper() == "0X00422180")
        self.assertEqual(update["symbol_base"], "?update_slot_28@EffectObjectBase@@UAEXXZ")
        self.assertEqual(update["rel32_targets"], ["?advance_frame_and_dispatch@CharacterObjectRuntime@th105@@QAEEXZ=0x004351C0"])

    def test_profile_editor_wave_and_network_packet_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        editor = functions["0X00428000"]
        self.assertEqual(editor["proposed_name"], "ProfileEditor168_ctor")
        self.assertEqual(editor["status"], "matching")
        self.assertEqual(editor["match_percent"], "100.00")
        self.assertIn("33/33", editor["evidence"])

        for address, name, residual in (
            ("0X00419590", "load_cv3_wave_data", "250/247"),
            ("0X00419690", "load_wave_data", "439/459"),
            ("0X00419950", "FileBufferEncodedView_load_encoded", "275/267"),
            ("0X0044DAC0", "NetworkAckInfoPacket40_ctor", "43/41"),
            ("0X0044E050", "InputPacket24_parse", "78/78"),
        ):
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "implemented")
            self.assertIn(residual, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        for address in ("0X00428A90", "0X00448DE0"):
            self.assertEqual(origins[address]["origin"], "compiler_generated")
            self.assertEqual(origins[address]["disposition"], "exclude")

        units = self.manifest.load_manifest()["units"]
        editor_unit = units["gpt-web-profile-editor-constructor"]
        self.assertEqual(editor_unit["source"], "src/ui/ProfileEditorConstructor.cpp")
        self.assertEqual(editor_unit["functions"][0]["address"].upper(), "0X00428000")
        wave = units["gpt-web-wave-data-runtime"]
        self.assertEqual(wave["source"], "src/audio/WaveDataRuntime.cpp")
        self.assertTrue(wave["enable_gs"])
        encoded = units["gpt-web-file-buffer-encoded-runtime"]
        self.assertEqual(encoded["source"], "src/assets/FileBufferEncodedRuntime.cpp")
        self.assertTrue(encoded["enable_gs"])

    def test_battle_setup_slot_coupled_exact_checkpoint(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "matches.csv").open(newline="", encoding="utf-8") as stream:
            matches = {row["address"].upper(): row for row in csv.DictReader(stream)}

        saved = functions["0X0042B9B0"]
        self.assertEqual(saved["proposed_name"], "BattleInputGate_save_battle_setup_slot")
        self.assertEqual(saved["status"], "matching")
        self.assertEqual(saved["match_percent"], "100.00")
        self.assertEqual(saved["source_file"], "src/battle/BattleSetupSlots.cpp")
        self.assertEqual(origins["0X0042B9B0"]["origin"], "authored_game")
        self.assertEqual(origins["0X0042B9B0"]["disposition"], "authored")
        self.assertEqual(origins["0X0042B9B0"]["evidence_id"], "canonical-exact-authored")
        self.assertEqual(matches["0X0042B9B0"]["unit"], "cross-v106a-fixed-slot-select")

        loaded = functions["0X0042BAF0"]
        self.assertEqual(loaded["status"], "implemented")
        self.assertNotIn("0X0042BAF0", matches)
        self.assertIn("+0x92", loaded["evidence"])

        unit = self.manifest.load_manifest()["units"]["cross-v106a-fixed-slot-select"]
        self.assertEqual(
            {row["address"].upper() for row in unit["functions"]},
            {"0X004284C0", "0X0042B9B0", "0X0042BAF0"},
        )
        self.assertIn("305/305", unit["notes"])
        self.assertIn("+0x92", unit["notes"])

        source = (ROOT / "src" / "battle" / "BattleSetupSlots.cpp").read_text(encoding="utf-8")
        self.assertIn("typedef std::vector<FixedSlotEnvelopeView> FixedSlotVectorView;", source)
        self.assertIn("slot > owner->maximum_saved_slot_140", source)
        self.assertNotIn("int side_bit = 1 << side;", source)

    def test_service_and_battle_readiness_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        authored = {
            "0X00403840": ("BgmService_schedule_or_start", "142/143"),
            "0X004038D0": ("BgmService_stop", "96/98"),
            "0X00403940": ("BgmService_fade", "76/70"),
            "0X00403990": ("BgmService_set_level", "70/69"),
            "0X004056C0": ("CScript_clear_commands", "296/170"),
            "0X0040BFE0": ("ProfileRenderListView_set_color", "74/81"),
            "0X00414CB0": ("D3DBackend_register_reset_listener", "134/157"),
            "0X00417FF0": ("BattleBaseEffect_initialize", "71/71"),
            "0X0046F9F0": ("BattleInfoRecord_emit_group_effect", "66/85"),
        }
        for address, (name, residual) in authored.items():
            self.assertEqual(functions[address]["proposed_name"], name)
            self.assertEqual(functions[address]["status"], "implemented")
            self.assertIn(residual, functions[address]["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")

        ready = functions["0X004712B0"]
        self.assertEqual(ready["proposed_name"], "BattleInputGate_is_synchronized_input_ready")
        self.assertEqual(ready["status"], "matching")
        self.assertEqual(ready["match_percent"], "100.00")
        self.assertIn("129/129", ready["evidence"])
        self.assertEqual(origins["0X004712B0"]["evidence_id"], "canonical-exact-authored")

        for address in (
            "0X00405770", "0X004061F0", "0X0040C270", "0X00424E20",
            "0X0040A790", "0X00455160", "0X0040CDA0",
        ):
            self.assertEqual(origins[address]["origin"], "compiler_generated")
            self.assertEqual(origins[address]["disposition"], "exclude")

        units = self.manifest.load_manifest()["units"]
        self.assertEqual(
            units["gpt-web-battle-input-ready"]["functions"][0]["address"].upper(),
            "0X004712B0",
        )
        self.assertEqual(
            units["gpt-web-profile-render-list-color-runtime"]["source"],
            "src/ui/ProfileRenderListColorRuntime.cpp",
        )
        bgm = units["gpt-web-bgm-service-runtime"]
        self.assertTrue(any(row["address"].upper() == "0X00403840" for row in bgm["functions"]))
        bgm_source = (ROOT / "src" / "audio" / "BgmServiceRuntime.cpp").read_text(encoding="utf-8")
        self.assertIn("timeGetTime()", bgm_source)
        self.assertNotIn("GetTickCount()", bgm_source)

        source = (ROOT / "src" / "battle" / "BattleInputReady.cpp").read_text(encoding="utf-8")
        self.assertIn("published_140 == consumed_141", source)
        self.assertIn("input_104->is_input_available_427680()", source)
        self.assertNotIn("unsigned char available =", source)

    def test_attack_character_object_lifetime_exact_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "reccmp-relocations.csv").open(newline="", encoding="utf-8") as stream:
            relocations = {row["coff_symbol"]: row for row in csv.DictReader(stream)}

        for address, name, exact_size, source_file in (
            ("0X0045F8E0", "AttackObject_dtor", "78/78", "src/battle/AttackObjectLifetime.cpp"),
            ("0X0045F930", "AttackObject_scalar_deleting_destructor", "30/30", "src/battle/AttackObjectLifetime.cpp"),
            ("0X00492ED0", "CharacterObject_dtor", "145/145", "src/characters/CharacterObject.cpp"),
        ):
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "matching")
            self.assertEqual(row["match_percent"], "100.00")
            self.assertEqual(row["source_file"], source_file)
            self.assertIn(exact_size, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["disposition"], "authored")
            self.assertEqual(origins[address]["evidence_id"], "canonical-exact-authored")

        units = self.manifest.load_manifest()["units"]
        attack = units["gpt-web-attack-object-lifetime"]
        self.assertEqual(attack["source"], "src/battle/AttackObjectLifetime.cpp")
        self.assertEqual(
            {row["address"].upper() for row in attack["functions"]},
            {"0X0045F8E0", "0X0045F930"},
        )
        character = units["cross-v106a-character-object-ctor"]
        self.assertTrue(character["enable_gs"])
        self.assertEqual(
            {row["address"].upper() for row in character["functions"]},
            {"0X00492F90", "0X00492ED0", "0X00492F70"},
        )

        attack_header = (ROOT / "src" / "battle" / "AttackObject.hpp").read_text(encoding="utf-8")
        self.assertIn("virtual ~AnimationObject() throw()", attack_header)
        self.assertIn("virtual ~AttackObject() throw();", attack_header)
        character_source = (ROOT / "src" / "characters" / "CharacterObject.cpp").read_text(encoding="utf-8")
        self.assertIn("CharacterObject::~CharacterObject()", character_source)
        self.assertIn("free(copied_words_340)", character_source)
        self.assertIn("SecondaryAnimationRenderRuntimeView", character_source)
        self.assertEqual(
            relocations["__ehhandler$??1CharacterObject@@UAE@XZ"]["address"].upper(),
            "0X006BBAE8",
        )

    def test_battle_info_gauge_runtime_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "reccmp-relocations.csv").open(newline="", encoding="utf-8") as stream:
            relocations = {row["coff_symbol"]: row for row in csv.DictReader(stream)}

        for address, name, size in (
            ("0X0046FA50", "TGageValue_int_ptr_value", "20/20"),
            ("0X0046FA70", "TGageValue_short_ptr_value", "27/27"),
        ):
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "matching")
            self.assertEqual(row["match_percent"], "100.00")
            self.assertEqual(row["source_file"], "src/battle/BattleInfoGaugeRuntime.cpp")
            self.assertIn(size, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["evidence_id"], "canonical-exact-authored")

        bind = functions["0X0046FA90"]
        self.assertEqual(bind["proposed_name"], "BattleInfoRecordF8_bind_fighter")
        self.assertEqual(bind["status"], "implemented")
        self.assertIn("655/648", bind["evidence"])
        self.assertIn("+0x02", bind["evidence"])
        self.assertEqual(origins["0X0046FA90"]["origin"], "authored_game")
        self.assertEqual(origins["0X0046FA90"]["evidence_id"], "battle-info-gauge-runtime-authored-106a")

        self.assertEqual(relocations["??_7?$TGageValue@PAH@th105@@6B@"]["address"].upper(), "0X006C3890")
        self.assertEqual(relocations["??_7?$TGageValue@PAF@th105@@6B@"]["address"].upper(), "0X006C3898")
        self.assertEqual(relocations["__real@40b2c00000000000"]["address"].upper(), "0X006C38A8")

        unit = self.manifest.load_manifest()["units"]["gpt-web-battle-info-gauge-runtime"]
        self.assertEqual(unit["source"], "src/battle/BattleInfoGaugeRuntime.cpp")
        self.assertEqual(
            {row["address"].upper() for row in unit["functions"]},
            {"0X0046FA50", "0X0046FA70", "0X0046FA90"},
        )
        source = (ROOT / "src" / "battle" / "BattleInfoGaugeRuntime.cpp").read_text(encoding="utf-8")
        self.assertIn("span_0c(span - start)", source)
        self.assertIn("start + 200.0f", source)
        self.assertNotIn("volatile", source)

    def test_csv_reader_family_wave_is_pinned(self) -> None:
        with (ROOT / "config" / "functions.csv").open(newline="", encoding="utf-8") as stream:
            functions = {row["address"].upper(): row for row in csv.DictReader(stream)}
        with (ROOT / "config" / "function-origins.csv").open(newline="", encoding="utf-8") as stream:
            origins = {row["address"].upper(): row for row in csv.DictReader(stream)}

        checks = (
            ("0X0040F580", "CsvReader_next_string", "245/245", "+0x2B"),
            ("0X0040F680", "CsvReader_advance_row", "169/167", "+0x02"),
            ("0X0040FDB0", "CsvReader_clear_rows", "5/125", "+0x00"),
        )
        for address, name, residual, mismatch in checks:
            row = functions[address]
            self.assertEqual(row["proposed_name"], name)
            self.assertEqual(row["status"], "implemented")
            self.assertEqual(row["source_file"], "src/assets/CsvReaderRuntime.cpp")
            self.assertIn(residual, row["evidence"])
            self.assertIn(mismatch, row["evidence"])
            self.assertEqual(origins[address]["origin"], "authored_game")
            self.assertEqual(origins[address]["evidence_id"], "csv-reader-public-methods-authored-106a")

        dtor = functions["0X0042E980"]
        self.assertEqual(dtor["proposed_name"], "CsvReader_dtor")
        self.assertEqual(dtor["status"], "matching")
        self.assertEqual(dtor["match_percent"], "100.00")
        self.assertIn("5/5", dtor["evidence"])
        self.assertEqual(origins["0X0042E980"]["evidence_id"], "canonical-exact-authored")

        for address in ("0X0040F730", "0X0040F7D0", "0X0040F840", "0X0040F8E0"):
            self.assertEqual(origins[address]["origin"], "compiler_generated")
            self.assertEqual(origins[address]["disposition"], "exclude")
            self.assertEqual(origins[address]["evidence_id"], "csv-reader-private-load-helpers-generated-106a")

        units = self.manifest.load_manifest()["units"]
        core = units["gpt-web-csv-reader-next-int"]
        self.assertEqual(core["source"], "src/assets/CsvReaderRuntime.cpp")
        self.assertEqual(
            {row["address"].upper() for row in core["functions"]},
            {"0X0040F480", "0X0040F580", "0X0040F680", "0X0040FDB0"},
        )
        life = units["gpt-web-csv-reader-lifetime"]
        self.assertEqual(life["source"], "src/assets/CsvReaderLifetime.cpp")
        self.assertEqual(life["functions"][0]["address"].upper(), "0X0042E980")

        source = (ROOT / "src" / "assets" / "CsvReaderRuntime.cpp").read_text(encoding="utf-8")
        self.assertIn("std::string *next_string_40f580(std::string *out)", source)
        self.assertIn("rows_00.clear();", source)
        self.assertNotIn("volatile", source)

    def test_progress_reports_current_exact_baseline(self) -> None:
        markdown = self.progress.render()
        self.assertIn("Tracked 1.06a function candidates | 4,023", markdown)
        self.assertIn("Confirmed authored functions | 1,476", markdown)
        self.assertIn("Confirmed authored code bytes | 2,088,147", markdown)
        self.assertIn("Classified exclusions | 1,308", markdown)
        self.assertIn("Origin/boundary review pending | 1,239", markdown)
        self.assertIn("Canonical exact functions | 1,312", markdown)
        self.assertIn("Canonical exact authored bytes | 217,279", markdown)
        self.assertIn("Source-present authored mappings | 1,388", markdown)
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
        self.assertEqual(text.count("if ( selector_random_roll(0x64u) <= 0xAu )"), 2)
        self.assertIn(
            "case 1:\nv101 = *(__int16 *)CPU_FIELD(1896) <= 0;\n"
            "*(_DWORD *)CPU_FIELD(1716) = 1;\nif ( v101 )\n{\n"
            "*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) <= 0xAu )\n"
            "*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);\n}\n"
            "return;",
            text,
        )
        self.assertIn(
            "LABEL_994:\n*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) <= 0xAu )\n"
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
            "if ( selector_random_roll(0x64u) > 0x64u )\nreturn;\n"
            "goto LABEL_1025;\nLABEL_1025:\n"
            "*(_WORD *)CPU_FIELD(1896) = selector_random_roll(0x3Cu);",
            text,
        )
        self.assertIn(
            "case 0x64:\nv110 = *(_BYTE *)CPU_FIELD(260);", text
        )
        self.assertIn(
            "if ( v101 )\n{\n*(_WORD *)CPU_FIELD(1894) = 0;\n"
            "if ( selector_random_roll(0x64u) <= 0x64u )\n"
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
        self.assertEqual(len(rows), 158)
        self.assertEqual(len({row["address"] for row in rows}), 158)
        self.assertEqual(sum(row["size"] for row in rows), 57799)
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
        self.assertEqual(counts["ledger_literals"], 308)
        self.assertEqual(counts["explicit_mappings"], 435)
        self.assertEqual(counts["target_checks"], 0)

    @unittest.skipUnless(
        (ROOT / "resources" / "th105.exe").is_file(), "private target is unavailable"
    )
    def test_repository_real_literals_match_target_bytes(self) -> None:
        counts = self.validator.validate_real_literal_relocations(
            self.manifest.load_manifest(), require_bytes=True
        )
        self.assertEqual(counts["target_checks"], 743)

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
        for machine_temp in (
            "void (__thiscall *v14)(void *, int);",
            "void (__thiscall *v16)(void *, int);",
            "void (__thiscall *v19)(void *, int);",
            "void (__thiscall *v20)(void *, int);",
        ):
            self.assertNotIn(machine_temp, source)
        self.assertNotIn("LABEL_173", source)
        self.assertEqual(
            source.count(
                "if ( *(float *)(raw +  236) > (double)*(float *)(*(_DWORD *)(raw +  368) + 236) )"
            ),
            3,
        )
        self.assertEqual(
            source.count(
                "if ( *(float *)(raw +  236) < (double)*(float *)(*(_DWORD *)(raw +  368) + 236) )"
            ),
            3,
        )
        c6 = source[source.index("case 0xC6:") : source.index("case 0xC7:")]
        call700 = c6.index(")(*(_DWORD *)raw +  8))(raw, 700);")
        self.assertLess(c6.index("return;", call700), c6.index("else", call700))
        self.assertIn("if ( *(__int16 *)(raw +  320) <= 3 )", source)
        self.assertIn(
            "reinterpret_cast<CharacterObjectRuntime *>(raw + 4)->set_oriented_components_f0_f4",
            source,
        )
        self.assertIn("int facing_600 = *(unsigned __int8 *)(raw +  260);", source)
        self.assertIn("int facing = *(unsigned __int8 *)(raw +  260);", source)
        units = self.manifest.load_manifest()["units"]
        unit = units["gpt-web-youmu-vslot28-full-root"]
        self.assertIn("24/98", unit["notes"])
        self.assertIn("57 -> 60", unit["notes"])
        self.assertIn("320 -> 298", unit["notes"])
        self.assertIn("+0x9354", unit["notes"])
        self.assertIn("target 0x64, candidate 0x79", unit["notes"])


if __name__ == "__main__":
    unittest.main()
