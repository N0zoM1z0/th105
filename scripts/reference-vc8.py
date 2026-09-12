#!/usr/bin/env python3
"""Fetch, verify and read the pinned official VC8 manual; no game state writes."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import tomllib
import urllib.request

ROOT = Path(__file__).resolve().parent.parent


def digest(path: Path) -> str:
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def verify(pdf: Path, document: dict) -> None:
    if pdf.stat().st_size != document["size_bytes"] or digest(pdf) != document["sha256"]:
        raise ValueError(f"Document identity mismatch: {pdf}")


def topic_filename(topic: dict) -> str:
    slug = re.sub(r"[^a-z0-9]+", "-", topic["topic"].lower()).strip("-")
    return f'{topic["first_page"]}-{topic["last_page"]}-{slug}.md'


def extract_topics(text: Path, document: dict) -> None:
    pages = text.read_text(encoding="utf-8").split("\f")
    if pages and not pages[-1].strip():
        pages.pop()
    if len(pages) != document["pages"]:
        raise ValueError("Extracted page count differs from the pinned PDF")
    directory = text.parent / "topics"
    directory.mkdir(exist_ok=True)
    index = ["# VC8 official reference: local topic extracts", "",
             "Generated from the SHA-pinned Microsoft Visual Studio 2005 PDF.",
             "These are document excerpts, not TH105 target observations.", ""]
    for topic in document["topics"]:
        filename = topic_filename(topic)
        first, last = topic["first_page"], topic["last_page"]
        content = [f'# {topic["topic"]}', "", f'Source: {document["landing_url"]}',
                   f'Original PDF: {document["download_url"]}',
                   f'PDF SHA-256: `{document["sha256"]}`',
                   f'Physical PDF pages: {first}..{last} (one-based).',
                   "Microsoft documentation; original ownership and notices retained.",
                   "Text layout is extracted by Poppler; consult the PDF if a table is ambiguous.", ""]
        for page in range(first, last + 1):
            content += [f"## PDF page {page}", "", "```text", pages[page - 1].rstrip(), "```", ""]
        (directory / filename).write_text("\n".join(content), encoding="utf-8")
        (directory / filename).with_suffix(".json").write_text(json.dumps({
            "title": topic["topic"], "pdf_sha256": document["sha256"],
            "source_url": document["landing_url"],
            "pages": [{"number": page, "lines": pages[page - 1].splitlines()}
                      for page in range(first, last + 1)]}, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8")
        index.append(f'- [{topic["topic"]}](topics/{filename}) — PDF pages {first}..{last}')
    (text.parent / "INDEX.md").write_text("\n".join(index) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    actions = parser.add_mutually_exclusive_group(required=True)
    actions.add_argument("--fetch", action="store_true", help="download if absent, then verify")
    actions.add_argument("--verify", action="store_true")
    actions.add_argument("--extract-text", action="store_true", help="create searchable local text")
    actions.add_argument("--extract-topics", action="store_true", help="refresh Markdown/JSON from verified text")
    actions.add_argument("--topics", action="store_true", help="list reviewed PDF page ranges")
    actions.add_argument("--pages", metavar="FIRST:LAST", help="read at most 20 physical PDF pages")
    actions.add_argument("--search", metavar="TEXT", help="find text and report physical PDF pages")
    parser.add_argument("--limit", type=int, default=10, help="maximum search hits, 1..50")
    args = parser.parse_args()
    document = tomllib.loads((ROOT / "config/reference-documents.toml").read_text())["vc8_cpp"]
    pdf = ROOT / document["local_pdf"]
    text = ROOT / document["local_text"]
    provenance = text.with_suffix(".provenance.json")
    if args.topics:
        for topic in document["topics"]:
            print(f'{topic["first_page"]}:{topic["last_page"]}\t{topic["topic"]}'
                  f'\tbuild/references/vc8/topics/{topic_filename(topic)}')
        return 0
    if args.fetch and not pdf.exists():
        pdf.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.NamedTemporaryFile(dir=pdf.parent, suffix=".download", delete=False) as tmp:
            temporary = Path(tmp.name)
        try:
            with urllib.request.urlopen(document["download_url"], timeout=60) as response:
                with temporary.open("wb") as output:
                    received = 0
                    while chunk := response.read(1024 * 1024):
                        received += len(chunk)
                        if received > document["size_bytes"]:
                            raise ValueError("Download exceeds pinned document size")
                        output.write(chunk)
            verify(temporary, document)
            temporary.replace(pdf)
        finally:
            temporary.unlink(missing_ok=True)
    verify(pdf, document)
    if args.fetch or args.verify:
        print(f'Verified {pdf}\nSHA-256: {document["sha256"]}')
        return 0
    if args.pages:
        bounds = args.pages.split(":")
        first = int(bounds[0])
        last = int(bounds[1]) if len(bounds) == 2 else first
        if len(bounds) > 2 or not 1 <= first <= last <= document["pages"] or last - first >= 20:
            raise ValueError("Choose 1..20 pages inside the pinned document")
        subprocess.run(["pdftotext", "-layout", "-enc", "UTF-8", "-f", str(first),
                        "-l", str(last), str(pdf), "-"], check=True)
        return 0
    if args.extract_text:
        if not shutil.which("pdftotext"):
            raise ValueError("pdftotext is required (Poppler utilities)")
        subprocess.run(["pdftotext", "-layout", "-enc", "UTF-8", str(pdf), str(text)], check=True)
        provenance.write_text(json.dumps({"pdf_sha256": document["sha256"],
                                         "text_sha256": digest(text)}, indent=2) + "\n")
        extract_topics(text, document)
        print(f"Extracted {text}; recorded PDF/text hashes in {provenance}")
        print(f'Topic Markdown index: {text.parent / "INDEX.md"}')
        return 0
    record = json.loads(provenance.read_text())
    if record.get("pdf_sha256") != document["sha256"] or record.get("text_sha256") != digest(text):
        raise ValueError("Text cache provenance mismatch; run --extract-text")
    if args.extract_topics:
        extract_topics(text, document)
        print(f'Topic Markdown/JSON refreshed: {text.parent / "INDEX.md"}')
        return 0
    if not args.search.strip() or not 1 <= args.limit <= 50:
        raise ValueError("Supply a nonempty search and --limit 1..50")
    query = args.search.casefold()
    page = 1
    hits = 0
    with text.open(encoding="utf-8") as stream:
        for line in stream:
            parts = line.split("\f")
            for index, part in enumerate(parts):
                if index:
                    page += 1
                if query in part.casefold():
                    print(f"PDF page {page}: {part.strip()[:300]}")
                    hits += 1
                    if hits == args.limit:
                        return 0
    if not hits:
        print("No matches")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f"VC8 reference error: {error}", file=sys.stderr)
        raise SystemExit(1)
