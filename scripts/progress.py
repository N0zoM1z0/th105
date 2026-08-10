#!/usr/bin/env python3
"""Generate lightweight Markdown/SVG progress from config/functions.csv."""

from __future__ import annotations

from collections import Counter
import csv
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "config" / "functions.csv"
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

    authored = [row for row in rows if row["status"] != "library"]
    total_bytes = sum(int(row["size"]) for row in authored)
    matching = [row for row in authored if row["status"] == "matching"]
    matching_bytes = sum(int(row["size"]) for row in matching)
    function_pct = 100 * len(matching) / len(authored) if authored else 0.0
    byte_pct = 100 * matching_bytes / total_bytes if total_bytes else 0.0
    counts = Counter(row["status"] for row in rows)

    lines = [
        "# Reconstruction progress",
        "",
        "Generated from `config/functions.csv`. Only functions with a verified",
        "100% comparison are counted as reconstructed.",
        "",
        f"- Matching functions: **{len(matching)} / {len(authored)} ({function_pct:.2f}%)**",
        f"- Matching function bytes: **{matching_bytes:,} / {total_bytes:,} ({byte_pct:.2f}%)**",
        f"- Ghidra internal `.text` inventory: **{len(rows):,} functions**",
        "",
        "| Status | Functions |",
        "| --- | ---: |",
    ]
    lines.extend(f"| `{status}` | {counts[status]:,} |" for status in ORDER)
    lines.extend(
        [
            "",
            "Run `python3 scripts/progress.py` after changing the ledger.",
            "",
        ]
    )

    bar_width = 440
    filled = bar_width * byte_pct / 100
    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="560" height="112" role="img" aria-label="TH10.5 reconstruction progress {byte_pct:.2f}% by bytes">
  <rect width="560" height="112" rx="8" fill="#1f2335"/>
  <text x="24" y="32" fill="#f4f4f5" font-family="sans-serif" font-size="16" font-weight="600">TH10.5 reconstruction</text>
  <text x="536" y="32" fill="#f4f4f5" text-anchor="end" font-family="monospace" font-size="14">{byte_pct:.2f}% bytes</text>
  <rect x="24" y="48" width="440" height="14" rx="7" fill="#3b4058"/>
  <rect x="24" y="48" width="{filled:.2f}" height="14" rx="7" fill="#e46c8c"/>
  <text x="24" y="88" fill="#c8cad2" font-family="sans-serif" font-size="13">{len(matching):,} / {len(authored):,} functions · {matching_bytes:,} / {total_bytes:,} function bytes</text>
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
