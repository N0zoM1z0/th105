"""Fail-closed raw target checks distinguishing PNG and zlib version roles."""
import json
import struct



def _call(read, site, expected):
    raw = read(site, 5)
    if len(raw) != 5 or raw[0] != 0xE8 or site + 5 + struct.unpack('<i', raw[1:])[0] != expected:
        raise ValueError('version-path call differs at 0x%08X' % site)


def audit(read):
    # The game passes the same string returned by the native PNG getter.
    if read(0x66BF00, 6) != b'\xB8\x04\x6E\x6D\x00\xC3' or read(0x6D6E04, 6) != b'1.5.2\0':
        raise ValueError('native PNG version getter differs')
    if read(0x41A97E, 5) != b'\x68\x04\x6E\x6D\x00':
        raise ValueError('game PNG version argument differs')
    _call(read, 0x41A983, 0x66FD60)
    _call(read, 0x66CF02, 0x66BF00)
    if read(0x66CF10, 3) != b'\x3A\x14\x30':
        raise ValueError('native PNG version-byte comparison differs')
    # This other literal is passed to the zlib inflate-init wrapper, not PNG.
    if read(0x66D037, 6) != b'\x68\xF0\xB0\x6C\x00\x50' or read(0x6CB0F0, 6) != b'1.2.5\0':
        raise ValueError('native zlib version argument differs')
    _call(read, 0x66D03D, 0x6679C0)
    return {'native_png_header': '1.5.2', 'native_zlib_header_argument': '1.2.5',
            'comparison_libpng': '1.2.5',
            'scope': 'target version roles only; native release and runtime provider equivalence unproved'}


if __name__ == '__main__':
    import linked_pe
    comparator = linked_pe.comparator()
    sha = comparator.verify_target()
    print(json.dumps({'result': 'verified', 'target_sha256': sha, **audit(comparator.target_bytes)}, indent=2))
