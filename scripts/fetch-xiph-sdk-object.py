#!/usr/bin/env python3
"""Fetch one COFF object from the archived official Ogg/Vorbis 1.0.1 SDK."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path
import struct
import tempfile
import urllib.request
import zipfile


ROOT = Path(__file__).resolve().parents[1]
ARCHIVE_URL = (
    "https://web.archive.org/web/20041104173806id_/"
    "http://www.vorbis.com/files/1.0.1/windows/"
    "OggVorbis-win32sdk-1.0.1.zip"
)
ARCHIVE_SHA256 = "fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc"
ARCHIVE_MEMBER = {
    "ogg": "oggvorbis-win32sdk-1.0.1/lib/ogg_static.lib",
    "vorbis": "oggvorbis-win32sdk-1.0.1/lib/vorbis_static.lib",
    "vorbisfile": "oggvorbis-win32sdk-1.0.1/lib/vorbisfile_static.lib",
}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def download_archive(cache: Path) -> bytes:
    if cache.is_file():
        data = cache.read_bytes()
        if sha256(data) == ARCHIVE_SHA256:
            return data
        raise ValueError(f"cached Xiph SDK has the wrong SHA-256: {cache}")

    cache.parent.mkdir(parents=True, exist_ok=True)
    with urllib.request.urlopen(ARCHIVE_URL, timeout=120) as response:
        data = response.read()
    actual = sha256(data)
    if actual != ARCHIVE_SHA256:
        raise ValueError(
            f"downloaded Xiph SDK SHA-256 mismatch: got {actual}, "
            f"expected {ARCHIVE_SHA256}"
        )
    with tempfile.NamedTemporaryFile(dir=cache.parent, delete=False) as stream:
        stream.write(data)
        temporary = Path(stream.name)
    temporary.replace(cache)
    return data


def archive_members(library: bytes) -> list[tuple[str, bytes]]:
    if not library.startswith(b"!<arch>\n"):
        raise ValueError("Xiph SDK library is not a COFF archive")
    members: list[tuple[str, bytes]] = []
    long_names = b""
    offset = 8
    while offset + 60 <= len(library):
        header = library[offset : offset + 60]
        if header[58:60] != b"`\n":
            raise ValueError("malformed COFF archive member header")
        try:
            size = int(header[48:58].decode("ascii").strip())
        except ValueError as error:
            raise ValueError("malformed COFF archive member size") from error
        body_start = offset + 60
        body_end = body_start + size
        if body_end > len(library):
            raise ValueError("truncated COFF archive member")
        raw_name = header[:16].decode("ascii", errors="replace").rstrip()
        body = library[body_start:body_end]
        if raw_name == "//":
            long_names = body
        elif raw_name.startswith("/") and raw_name[1:].isdigit():
            name_offset = int(raw_name[1:])
            # Microsoft's archive long-name table uses NUL terminators. GNU
            # archives commonly use ``/\n``; accepting both keeps the parser
            # explicit without depending on an external archiver.
            endings = [
                end
                for end in (
                    long_names.find(b"\0", name_offset),
                    long_names.find(b"/\n", name_offset),
                )
                if end >= 0
            ]
            name_end = min(endings) if endings else -1
            if name_end < 0:
                raise ValueError("invalid COFF archive long-name reference")
            name = long_names[name_offset:name_end].decode("ascii", errors="replace")
            members.append((name, body))
        elif raw_name not in {"/", "//"}:
            members.append((raw_name.removesuffix("/"), body))
        offset = body_end + (size & 1)
    return members


def extract_object(sdk: bytes, component: str, object_name: str) -> bytes:
    import io

    with zipfile.ZipFile(io.BytesIO(sdk)) as archive:
        library = archive.read(ARCHIVE_MEMBER[component])
    matches = [
        body
        for name, body in archive_members(library)
        if name.replace("\\", "/").rsplit("/", 1)[-1].lower()
        == object_name.lower()
    ]
    if len(matches) != 1:
        raise ValueError(
            f"expected one {component}/{object_name} SDK member, got {len(matches)}"
        )
    if len(matches[0]) < 2 or struct.unpack_from("<H", matches[0], 0)[0] != 0x014C:
        raise ValueError("selected SDK member is not an i386 COFF object")
    return matches[0]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--component", choices=sorted(ARCHIVE_MEMBER), required=True)
    parser.add_argument("--object", dest="object_name", required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument(
        "--cache",
        type=Path,
        default=ROOT / ".tools" / "upstream" / "OggVorbis-win32sdk-1.0.1.zip",
    )
    args = parser.parse_args()

    sdk = download_archive(args.cache.resolve())
    obj = extract_object(sdk, args.component, args.object_name)
    output = args.output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(obj)
    print(
        f"Xiph SDK {args.component}/{args.object_name}: {len(obj)} bytes, "
        f"sha256={sha256(obj)}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
