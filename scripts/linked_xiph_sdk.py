"""Pinned original Xiph static providers for authored CIL consumers."""
import hashlib
import io
from pathlib import Path
import zipfile

ARCHIVE_SHA256 = "fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc"
MEMBERS = {
    "vorbisfile": "deeda1a326333abf91e9912dd0b65e1e7d7a85070dbd167de720f4f39041575f",
    "vorbis": "f09d5d66d2f943e70964ae1e5449f1f0a4b420a4303db2e04f7b3c092b9d293a",
    "ogg": "f144c78498e6e263edd37e331a09cf1178b2ae945932a44280826f84f072214e",
}


def validate(unit):
    enabled = unit.get("link_xiph_sdk", False)
    if type(enabled) is not bool or enabled and unit.get("link_runtime") != "static":
        raise ValueError("Xiph providers require an explicit boolean and the pinned static CRT")


def verified_members(raw):
    if hashlib.sha256(raw).hexdigest() != ARCHIVE_SHA256:
        raise ValueError("Xiph SDK archive SHA-256 differs from the original pinned release")
    with zipfile.ZipFile(io.BytesIO(raw)) as archive:
        result = {}
        for name, digest in MEMBERS.items():
            member = "oggvorbis-win32sdk-1.0.1/lib/" + name + "_static.lib"
            if archive.namelist().count(member) != 1:
                raise ValueError("Xiph SDK static member is missing or duplicated")
            data = archive.read(member)
            if not data.startswith(b"!<arch>\n") or hashlib.sha256(data).hexdigest() != digest:
                raise ValueError("Xiph SDK static member SHA-256 or archive kind differs")
            result[name] = data
    return result


def inputs(unit, image, *, generate=False):
    import linked_pe as core
    validate(unit)
    if not unit.get("link_xiph_sdk"):
        return []
    cache = core.ROOT / ".tools/upstream/OggVorbis-win32sdk-1.0.1.zip"
    members = verified_members(cache.read_bytes())
    result = []
    for name, data in members.items():
        path = Path(image).with_suffix(".xiph-" + name + ".lib")
        if generate:
            path.write_bytes(data)
        if path.read_bytes() != data:
            raise ValueError("linked Xiph provider was modified after extraction")
        result.append({"family": name, "path": str(path.relative_to(core.ROOT)),
                       "sha256": MEMBERS[name], "archive_sha256": ARCHIVE_SHA256})
    return result
