#!/usr/bin/env python3
"""Run exact-acceptance tooling checks; optional diagnostics use --all-tests."""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import subprocess
import sys


ROOT = Path(__file__).resolve().parents[1]

# Reconstruction experiments are optional. The routine gate protects strict
# comparison, relocation/extent ownership, the environment and exact accounting.
EXACT_TEST_MODULES = (
    "test_workflow_tooling",
    "test_compare_unit_object",
    "test_coff_switch_payload",
    "test_owned_extent_comparison",
    "test_linked_pe",
    "test_linked_cleanup_caller",
    "test_linked_member_leaf",
    "test_linked_stdcall_graph",
    "test_linked_generated_origins",
    "test_linked_checked_iterator_origins",
    "test_linked_original_boost_origins",
    "test_linked_logic_error_origins",
    "test_linked_bad_alloc_origins",
    "test_linked_exception_members",
    "test_linked_boost_small_origins",
    "test_linked_clone_copy_origins",
    "test_linked_list_node_origins",
    "test_vc8_float_sine_origins",
    "test_linked_byte_allocator_origins",
    "test_linked_gamepad_allocator_origins",
    "test_linked_endpoint_allocator_origins",
    "test_linked_peer_allocator_origins",
    "test_linked_network_tree_erase_origins",
    "test_linked_resource_deque_tidy_origins",
    "test_linked_script_map_tidy_origins",
    "test_linked_package_map_tidy_origins",
    "test_linked_bgm_list_growth_origins",
    "test_linked_unsigned_list_growth_origins",
    "test_linked_packet_deque_back_origins",
    "test_linked_csv_deque_copy_origins",
    "test_linked_wave_pointer_back_origins",
    "test_origin_source_line_endings",
    "test_linked_vector_xlen_origins",
    "test_linked_bad_exception_origins",
    "test_boost_public_exception_copies",
    "test_boost_public_regex_exception",
    "test_boost_matcher_leaf_origins",
    "test_boost_matcher_stack_origins",
    "test_boost_default_error_origins",
    "test_boost_default_syntax_origins",
    "test_xiph_packet_wrapper_origins",
    "test_vc8_invalid_copy_origins",
    "test_vc8_typeinfo_dtor_origins",
    "test_vc8_typeinfo_delete_origins",
    "test_vc8_exception_delete_origins",
    "test_vc8_sqrt_shared_origins",
    "test_vc8_sin_shared_origins",
    "test_vc8_cos_shared_origins",
    "test_vc8_log10_shared_origins",
    "test_vc8_pow_shared_origins",
    "test_sprite_default_origins",
    "test_csprite_lifetime_origins",
    "test_network_base_constructor_eh",
    "test_network_packet_vtables",
    "test_network_base_destructor_eh",
    "test_timeline_texture_receiver",
    "test_boost_matcher_lifetimes",
    "test_boost_recursion_cleanup_origins",
    "test_select_render_audit",
    "test_native_callbacks",
    "test_select_character_audit",
    "test_select_eh_aliases",
    "test_score_observations_audit",
    "test_ctile_real_owner",
    "test_select_owner_layout",
    "test_design_color_owner",
    "test_client_ack_tail",
    "test_profile_character_preview",
    "test_sprite_texture_options",
    "test_server_input_publish",
    "test_sprite_callback_origins",
    "test_input_base_cleanup_origins",
    "test_replay_member_cleanup_origins",
    "test_score_vector_default_origins",
    "test_deque_popback_origins",
    "test_unsigned_deque_popback_origins",
    "test_vc8_public_wrapper_origins",
    "test_vc8_data_accessor_origins",
    "test_vc8_control_entry_origins",
    "test_vc8_validation_leaf_origins",
    "test_vc8_atan2_entry_origins",
    "test_vc8_pointer_policy_origins",
    "test_vc8_member_call_bridge_origins",
    "test_xiph_table_getter_origins",
    "test_xiph_invsq_origins",
    "test_xiph_staticbook_destroy_origins",
    "test_legacy_real_literals",
    "test_linked_string_range_origins",
    "test_scalar_wrapper_origins",
    "test_implicit_lifetime_origins",
    "test_xiph_owned_switch_origins",
    "test_linked_png_sdk",
    "test_linked_wave_callbacks",
    "test_linked_global_caller",
    "test_linked_texture_lifecycle",
    "test_linked_lifecycle",
    "test_linked_noreturn",
    "test_linked_switch_replay",
    "test_select_constructor_audit",
    "test_repo_python",
    "test_upstream_boost",
    "test_upstream_boost_sources",
    "test_boost_collation_origins",
    "test_upstream_vc8_runtime",
    "test_msvc_runtime_assembly",
    "test_progress_svg",
)


def tracked(pattern: str) -> list[str]:
    output = subprocess.run(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z", pattern],
        cwd=ROOT,
        check=True,
        stdout=subprocess.PIPE,
    ).stdout
    return [
        entry
        for raw in output.split(b"\0")
        if raw
        for entry in [raw.decode()]
        if (ROOT / entry).is_file()
    ]


def run(label: str, command: list[str], *, cwd: Path = ROOT) -> None:
    print(f"\n==> {label}", flush=True)
    environment = os.environ.copy()
    environment["PYTHONPYCACHEPREFIX"] = str(ROOT / "build" / "pycache")
    subprocess.run(command, cwd=cwd, env=environment, check=True)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--all-tests", action="store_true",
        help="also run optional analysis/probe tests (no native corpus rebuild)",
    )
    args = parser.parse_args()
    try:
        run("Check repository Python environment", [sys.executable, "scripts/repo_python_env.py"])
        python_files = sorted(
            set(
                tracked("scripts/*.py")
                + tracked("scripts/ida/*.py")
                + tracked("tests/*.py")
            )
        )
        run("Compile tracked Python", [sys.executable, "-m", "py_compile", *python_files])
        shell_files = tracked("scripts/*.sh") + tracked("scripts/repo-python")
        if shell_files:
            run("Check shell syntax", ["bash", "-n", *shell_files])
        run(
            "Audit floating relocation mappings",
            [sys.executable, "scripts/check-match-literals.py", "--skip-target-bytes"],
        )
        run(
            "Validate reconstruction ledgers",
            [sys.executable, "scripts/validate-tracking.py", "--skip-target-bytes"],
        )
        run("Validate match-unit graph", [sys.executable, "scripts/build.py", "--check"])
        if args.all_tests:
            run(
                "Run all tooling and analysis tests",
                [sys.executable, "-m", "unittest", "discover", "-s", "tests", "-v"],
            )
        else:
            run(
                "Run exact-acceptance tooling tests",
                [sys.executable, "-m", "unittest", "-v", *EXACT_TEST_MODULES],
                cwd=ROOT / "tests",
            )
        run("Check generated progress", [sys.executable, "scripts/progress.py", "--check"])
        if os.environ.get("CI"):
            run(
                "Check generated progress is committed",
                [
                    "git",
                    "diff",
                    "--exit-code",
                    "--",
                    "docs/PROGRESS.md",
                    "resources/progress.svg",
                ],
            )
        run(
            "Smoke-test status report",
            [sys.executable, "scripts/report-reconstruction-status.py", "--summary"],
        )
        run("Check whitespace", ["git", "diff", "--check"])
    except (OSError, subprocess.CalledProcessError) as exc:
        print(f"error: CI validation failed: {exc}")
        return 1
    print("\nTH105 target-independent CI checks passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
