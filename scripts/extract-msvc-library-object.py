#!/usr/bin/env python3
"""Extract one i386 COFF object from an explicitly selected pinned VC8 runtime set."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path
import struct


ROOT = Path(__file__).resolve().parents[1]
LIBRARIES = {
    "libcmt": (
        "libcmt.lib",
        "3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3",
    ),
    "libcpmt": (
        "libcpmt.lib",
        "e1b17cb213bfcf77e3c0988f8cb33ec8be143872d1c52de62c5da07ea1eb8031",
    ),
}


def archive_configuration(archive_set: str = "vc8-sp1", root: Path = ROOT):
    if archive_set == "vc8-sp1":
        return root / ".tools/msvc80-sp1/lib", LIBRARIES
    if archive_set == "vc8-kb971090":
        from upstream_vc8_runtime import FOLDER, LIBRARIES as patched_libraries, within
        return within(root, FOLDER), patched_libraries
    raise ValueError(f"unknown pinned runtime archive set: {archive_set}")


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def archive_members(library: bytes) -> list[tuple[str, bytes]]:
    if not library.startswith(b"!<arch>\n"):
        raise ValueError("VC8 runtime library is not a COFF archive")
    members: list[tuple[str, bytes]] = []
    long_names = b""
    offset = 8
    while offset + 60 <= len(library):
        header = library[offset : offset + 60]
        if header[58:60] != b"`\n":
            raise ValueError("malformed COFF archive member header")
        size = int(header[48:58].decode("ascii").strip())
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
            endings = [
                end
                for end in (
                    long_names.find(b"\0", name_offset),
                    long_names.find(b"/\n", name_offset),
                )
                if end >= 0
            ]
            if not endings:
                raise ValueError("invalid COFF archive long-name reference")
            name = long_names[name_offset : min(endings)].decode(
                "ascii", errors="replace"
            )
            members.append((name.replace("\\", "/"), body))
        elif raw_name not in {"/", "//"}:
            members.append((raw_name.removesuffix("/"), body))
        offset = body_end + (size & 1)
    return members


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", choices=sorted(LIBRARIES), required=True)
    parser.add_argument(
        "--object",
        dest="object_name",
        required=True,
        help="full archive member path, or a unique object basename",
    )
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--toolchain-root", type=Path)
    parser.add_argument("--archive-set", choices=("vc8-sp1", "vc8-kb971090"), default="vc8-sp1")
    args = parser.parse_args()

    archive_root, libraries = archive_configuration(args.archive_set)
    if args.toolchain_root:
        if args.archive_set != "vc8-sp1":
            raise ValueError("a toolchain-root override cannot replace the isolated pinned runtime set")
        archive_root = args.toolchain_root.resolve() / "lib"
    filename, expected_hash = libraries[args.library]
    archive_path = archive_root / filename
    library = archive_path.read_bytes()
    actual_hash = sha256(library)
    if actual_hash != expected_hash:
        raise ValueError(
            f"{filename} SHA-256 mismatch: got {actual_hash}, expected {expected_hash}"
        )

    wanted = args.object_name.replace("\\", "/").lower()
    members = archive_members(library)
    matches = [
        (name, body)
        for name, body in members
        if name.lower() == wanted
        or ("/" not in wanted and name.rsplit("/", 1)[-1].lower() == wanted)
    ]
    if len(matches) != 1:
        names = ", ".join(name for name, _ in matches[:8])
        raise ValueError(
            f"expected one {args.library}/{args.object_name} member, "
            f"got {len(matches)}: {names}"
        )
    member_name, obj = matches[0]
    if len(obj) < 2 or struct.unpack_from("<H", obj, 0)[0] != 0x014C:
        raise ValueError("selected VC8 runtime member is not an i386 COFF object")

    output = args.output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(obj)
    print(
        f"{args.archive_set} {args.library}/{member_name}: {len(obj)} bytes, "
        f"sha256={sha256(obj)}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
