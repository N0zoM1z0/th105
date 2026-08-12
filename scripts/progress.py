#!/usr/bin/env python3
"""Generate lightweight Markdown/SVG progress from config/functions.csv."""

from __future__ import annotations

from collections import Counter
import csv
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"
ORIGINS = ROOT / "config" / "function-origins.csv"
MARKDOWN = ROOT / "docs" / "PROGRESS.md"
SVG = ROOT / "resources" / "progress.svg"
ORDER = [
    "unclassified",
    "identified",
    "decompiled",
    "implemented",
    "compiles",
    "matching",
    "library",
    "blocked",
]


def render() -> tuple[str, str]:
    with FUNCTIONS.open(newline="", encoding="utf-8") as stream:
        rows = list(csv.DictReader(stream))

    with ORIGINS.open(newline="", encoding="utf-8") as stream:
        origin_rows = list(csv.DictReader(stream))
    origins = {row["address"]: row for row in origin_rows}
    if [row["address"] for row in rows] != [row["address"] for row in origin_rows]:
        raise RuntimeError("config/function-origins.csv is stale or out of ledger order")

    authored = [row for row in rows if row["status"] != "library"]
    library = [row for row in rows if row["status"] == "library"]
    exact_library = [row for row in library if row["match_percent"] == "100.00"]
    third_party = [
        row for row in rows if origins[row["address"]]["origin"] == "third_party"
    ]
    exact_third_party = [
        row
        for row in third_party
        if row["status"] == "library" and row["match_percent"] == "100.00"
    ]
    total_bytes = sum(int(row["size"]) for row in authored)
    library_bytes = sum(int(row["size"]) for row in library)
    exact_library_bytes = sum(int(row["size"]) for row in exact_library)
    third_party_bytes = sum(int(row["size"]) for row in third_party)
    exact_third_party_bytes = sum(int(row["size"]) for row in exact_third_party)
    all_bytes = sum(int(row["size"]) for row in rows)
    matching = [row for row in authored if row["status"] == "matching"]
    matching_bytes = sum(int(row["size"]) for row in matching)
    function_pct = 100 * len(matching) / len(authored) if authored else 0.0
    byte_pct = 100 * matching_bytes / total_bytes if total_bytes else 0.0
    library_function_pct = (
        100 * len(exact_library) / len(library) if library else 0.0
    )
    library_byte_pct = (
        100 * exact_library_bytes / library_bytes if library_bytes else 0.0
    )
    third_party_function_pct = (
        100 * len(exact_third_party) / len(third_party) if third_party else 0.0
    )
    third_party_byte_pct = (
        100 * exact_third_party_bytes / third_party_bytes if third_party_bytes else 0.0
    )
    combined_functions = len(matching) + len(exact_library)
    combined_bytes = matching_bytes + exact_library_bytes
    combined_function_pct = 100 * combined_functions / len(rows) if rows else 0.0
    combined_byte_pct = 100 * combined_bytes / all_bytes if all_bytes else 0.0
    counts = Counter(row["status"] for row in rows)
    origin_counts = Counter(row["origin"] for row in origin_rows)
    disposition_counts = Counter(row["disposition"] for row in origin_rows)
    audited_authored = [
        row for row in rows if origins[row["address"]]["disposition"] == "include_authored"
    ]
    audited_matching = [row for row in audited_authored if row["status"] == "matching"]
    audited_bytes = sum(int(row["size"]) for row in audited_authored)
    audited_matching_bytes = sum(int(row["size"]) for row in audited_matching)
    audited_function_pct = (
        100 * len(audited_matching) / len(audited_authored) if audited_authored else 0.0
    )
    audited_byte_pct = (
        100 * audited_matching_bytes / audited_bytes if audited_bytes else 0.0
    )

    lines = [
        "# Reconstruction progress",
        "",
        "Generated from `config/functions.csv` and `config/function-origins.csv`.",
        "Only functions with a verified 100% comparison are counted as reconstructed.",
        "Authored-game and external/library results are shown separately and combined.",
        "",
        f"- Matching functions: **{len(matching)} / {len(authored)} ({function_pct:.2f}%)**",
        f"- Matching function bytes: **{matching_bytes:,} / {total_bytes:,} ({byte_pct:.2f}%)**",
        f"- Reproducible library functions: **{len(exact_library)} / "
        f"{len(library)} ({library_function_pct:.2f}%)**",
        f"- Reproducible library bytes: **{exact_library_bytes:,} / "
        f"{library_bytes:,} ({library_byte_pct:.2f}%)**",
        f"- Reproducible third-party functions: **{len(exact_third_party)} / "
        f"{len(third_party)} ({third_party_function_pct:.2f}%)**",
        f"- Reproducible third-party bytes: **{exact_third_party_bytes:,} / "
        f"{third_party_bytes:,} ({third_party_byte_pct:.2f}%)**",
        f"- Combined exact reconstruction: **{combined_functions} / {len(rows)} "
        f"({combined_function_pct:.2f}%) functions**, **{combined_bytes:,} / "
        f"{all_bytes:,} ({combined_byte_pct:.2f}%) bytes**",
        f"- Ghidra internal `.text` inventory: **{len(rows):,} functions**",
        f"- Origin census: **{disposition_counts['exclude_authored']:,} excluded**, "
        f"**{disposition_counts['include_authored']:,} confirmed authored**, "
        f"**{disposition_counts['review']:,} awaiting origin review**",
        f"- Exact within confirmed-authored census: **{len(audited_matching)} / "
        f"{len(audited_authored)} ({audited_function_pct:.2f}%) functions**, "
        f"**{audited_matching_bytes:,} / {audited_bytes:,} "
        f"({audited_byte_pct:.2f}%) bytes**",
        "",
        "| Status | Functions |",
        "| --- | ---: |",
    ]
    lines.extend(f"| `{status}` | {counts[status]:,} |" for status in ORDER)
    lines.extend(
        [
            "",
            "| Origin | Functions |",
            "| --- | ---: |",
        ]
    )
    lines.extend(
        f"| `{origin}` | {origin_counts[origin]:,} |"
        for origin in (
            "authored_game",
            "compiler_generated",
            "vc8_runtime",
            "third_party",
            "import_thunk",
            "unknown",
        )
    )
    lines.extend(
        [
            "",
            "The legacy authored denominator is every non-`library` ledger row. The",
            "confirmed-authored census is evidence-backed but deliberately incomplete;",
            "`review` rows are not silently counted as either authored or library. Exact",
            "library rows remain excluded from authored-game matching, but are included",
            "in the separately visible library, third-party, and combined reconstruction",
            "metrics.",
            "",
            "Run `python3 scripts/function-origins.py --write` and then",
            "`python3 scripts/progress.py` after changing origin or ledger evidence.",
            "",
        ]
    )

    bar_width = 440
    filled = bar_width * combined_byte_pct / 100
    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="560" height="138" role="img" aria-label="TH10.5 combined reconstruction progress {combined_byte_pct:.2f}% by bytes">
  <rect width="560" height="138" rx="8" fill="#1f2335"/>
  <text x="24" y="32" fill="#f4f4f5" font-family="sans-serif" font-size="16" font-weight="600">TH10.5 complete reconstruction</text>
  <text x="536" y="32" fill="#f4f4f5" text-anchor="end" font-family="monospace" font-size="14">{combined_byte_pct:.2f}% all bytes</text>
  <rect x="24" y="48" width="440" height="14" rx="7" fill="#3b4058"/>
  <rect x="24" y="48" width="{filled:.2f}" height="14" rx="7" fill="#e46c8c"/>
  <text x="24" y="88" fill="#c8cad2" font-family="sans-serif" font-size="13">Combined: {combined_functions:,} / {len(rows):,} functions · {combined_bytes:,} / {all_bytes:,} bytes</text>
  <text x="24" y="110" fill="#c8cad2" font-family="sans-serif" font-size="13">Authored exact: {len(matching):,} functions · {matching_bytes:,} bytes</text>
  <text x="24" y="130" fill="#c8cad2" font-family="sans-serif" font-size="13">Library exact: {len(exact_library):,} functions · {exact_library_bytes:,} bytes</text>
</svg>
'''
    return "\n".join(lines), svg


def main() -> int:
    markdown, svg = render()
    check = "--check" in sys.argv
    if check:
        stale = []
        if not MARKDOWN.exists() or MARKDOWN.read_text(encoding="utf-8") != markdown:
            stale.append(str(MARKDOWN.relative_to(ROOT)))
        if not SVG.exists() or SVG.read_text(encoding="utf-8") != svg:
            stale.append(str(SVG.relative_to(ROOT)))
        if stale:
            print("stale generated progress: " + ", ".join(stale))
            return 1
        print("progress artifacts are current")
        return 0

    MARKDOWN.write_text(markdown, encoding="utf-8")
    SVG.write_text(svg, encoding="utf-8")
    print(f"updated {MARKDOWN.relative_to(ROOT)} and {SVG.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
