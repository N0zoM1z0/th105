"""The texture aggregate proof must not admit arbitrary startup or private ABI."""
from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_texture_lifecycle as texture


class TextureLifecycleTests(unittest.TestCase):
    def unit(self):
        return {
            texture.FLAG: True, "kind": "linked_candidate", "source": texture.SOURCE,
            "link_runtime": "static", "link_runtime_data": ["___security_cookie"],
            "enable_gs": True,
            "linked_coff_sources": ["src/library/UnsignedIntList.cpp", "src/library/UnsignedIntVector.cpp"],
            "functions": [
                {"address": "0x00404F00", "symbol_base": texture.CTOR, "private_texture_global": True,
                 "eh_cleanup": {"handler": "0x006BE461", "info": "0x006E4C94"}},
                {"address": "0x00404FD0", "symbol_base": texture.DTOR},
                {"address": "0x00405040", "symbol_base": texture.SCALAR, "vtable_entry": texture.VTABLE},
            ],
            "link_vtables": [
                {"symbol": texture.VTABLE, "target": "??_7TextureResourceHandleManager64@th105@@6B@",
                 "entry": texture.SCALAR + "=0x00405040", "target_type_name": ".?AV?$CHandleManager@PAUIDirect3DTexture9@@@@"},
                {"symbol": "??_7NetworkUdpPacketCriticalSectionView@th105@@6B@",
                 "target": "??_7CriticalSectionWrapper@th105@@6B@",
                 "entry": "??_GNetworkUdpPacketCriticalSectionView@th105@@UAEPAXI@Z=0x0040ABE0",
                 "target_type_name": ".?AVCCriticalSection@@"},
            ],
        }

    def validate(self, unit):
        texture.validate(unit, {texture.KEY})

    def test_inactive_contract_does_not_change_existing_units(self):
        texture.validate({}, set())
        texture.validate({"functions": None}, set())
        self.assertEqual(texture.layout_specs({}), [])
        with self.assertRaises(ValueError):
            texture.validate({"functions": [{"private_texture_global": True}]}, set())

    def test_actual_contract_and_native_layout_spec(self):
        self.validate(self.unit())
        self.assertEqual(texture.layout_specs(self.unit()), [
            {"symbol": texture.GLOBAL, "size": 0x84, "layout_source": texture.SOURCE}])

    def test_source_runtime_and_provider_changes_fail_closed(self):
        changes = [
            lambda u: u.update({texture.FLAG: 1}), lambda u: u.update({texture.FLAG: False}),
            lambda u: u.update(kind="probe"), lambda u: u.update(source="src/Other.cpp"),
            lambda u: u.update(link_runtime="import"), lambda u: u.update(link_runtime_data=[]),
            lambda u: u.update(enable_gs=False), lambda u: u.update(link_objects=[{}]),
            lambda u: u.update(preserve_public_members=[texture.CTOR]),
            lambda u: u.update(linked_coff_sources=[]),
        ]
        for change in changes:
            u = self.unit(); change(u)
            with self.subTest(unit=u), self.assertRaises(ValueError):
                self.validate(u)

    def test_no_absolute_provider_for_owned_storage(self):
        for mapping in (texture.GLOBAL + "=external", "external=" + texture.KEY):
            u = self.unit(); u["link_data_targets"] = [mapping]
            with self.assertRaises(ValueError):
                self.validate(u)

    def test_exact_entry_set_and_complete_eh_are_mandatory(self):
        changes = [
            lambda u: u["functions"].pop(),
            lambda u: u["functions"].append(dict(u["functions"][1])),
            lambda u: u["functions"][0].update(address="0x00401E40"),
            lambda u: u["functions"][0].update(symbol_base="??0Other@@QAE@XZ"),
            lambda u: u["functions"][0].update(private_texture_global=1),
            lambda u: u["functions"][0].pop("eh_cleanup"),
            lambda u: u["functions"][0]["eh_cleanup"].update(info="0x006E4680"),
            lambda u: u.update(functions=None),
        ]
        for change in changes:
            u = self.unit(); change(u)
            with self.subTest(unit=u), self.assertRaises(ValueError):
                self.validate(u)

    def test_no_export_or_other_private_path_substitution(self):
        for key, value in (("export_name", texture.CTOR), ("private_global", {}),
                           ("private_from", {}), ("private_static_leaf", True),
                           ("vtable_entry", texture.VTABLE)):
            u = self.unit(); u["functions"][0][key] = value
            with self.subTest(key=key), self.assertRaises(ValueError):
                self.validate(u)

    def test_scalar_and_both_rtti_contracts_are_mandatory(self):
        changes = [lambda u: u["functions"][2].pop("vtable_entry"),
                   lambda u: u["link_vtables"].pop(),
                   lambda u: u["link_vtables"][0].update(target_type_name=".?AVOther@@"),
                   lambda u: u["link_vtables"][0].update(entry=texture.SCALAR + "=0x00402090")]
        for change in changes:
            u = self.unit(); change(u)
            with self.assertRaises(ValueError):
                self.validate(u)

    def test_field_ledger_is_exact_not_a_widenable_zero_range(self):
        good = (texture.TARGET, bytes(4), texture.FIELDS, "address")
        self.assertEqual(texture.field_binding({texture.KEY: good}), texture.TARGET)
        for bad in ((texture.TARGET + 4, *good[1:]),
                    (texture.TARGET, b"\x01\x00\x00\x00", *good[2:]),
                    (texture.TARGET, bytes(4), texture.FIELDS | {4}, "address"),
                    (texture.TARGET, bytes(4), texture.FIELDS - {128}, "address"),
                    (texture.TARGET, bytes(4), texture.FIELDS, "literal"), None):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                texture.field_binding({texture.KEY: bad})

    def initializer(self):
        return texture.initializer_bytes(0x10008000, 0x10001000, 0x10008100, 0x10008200, 0x10009000)

    def test_initializer_includes_all_eight_cache_stores(self):
        raw = self.initializer()
        self.assertEqual(len(raw), 59)
        self.assertEqual(raw[5:8], b"\x33\xc0\x68")
        self.assertEqual(raw[-2:], b"\x59\xc3")
        for index, offset in enumerate(range(0x64, 0x84, 4)):
            pos = 12 + 5 * index
            self.assertEqual(raw[pos], 0xA3)
            self.assertEqual(struct.unpack_from("<I", raw, pos + 1)[0], 0x10009000 + offset)
        self.assertEqual(texture.INIT_RELOCS, (8, 13, 18, 23, 28, 33, 38, 43, 48))

    def test_every_initializer_byte_and_extent_is_checked(self):
        raw = self.initializer()
        texture.require_bytes(raw, raw, "initializer")
        for index in range(len(raw)):
            bad = bytearray(raw); bad[index] ^= 1
            with self.subTest(index=index), self.assertRaises(ValueError):
                texture.require_bytes(bytes(bad), raw, "initializer")
        for bad in (raw[:-1], raw + b"\x90", raw[:12] + raw[17:]):
            with self.assertRaises(ValueError):
                texture.require_bytes(bad, raw, "initializer")

    def test_callback_requires_full_ecx_receiver_and_destructor_tail(self):
        raw = texture.callback_bytes(0x10008100, 0x10002000, 0x10009000)
        self.assertEqual(len(raw), 10)
        self.assertEqual(raw[:5], b"\xb9" + struct.pack("<I", 0x10009000))
        self.assertEqual(raw[5], 0xE9)
        for index in range(len(raw)):
            bad = bytearray(raw); bad[index] ^= 1
            with self.assertRaises(ValueError):
                texture.require_bytes(bytes(bad), raw, "callback")
        with self.assertRaises(ValueError):
            texture.require_bytes(raw[5:], raw, "callback")

    def test_unique_real_crt_slot_rejects_extra_or_missing_initializers(self):
        entry = 0x10008000
        pack = lambda values: struct.pack("<" + "I" * len(values), *values)
        self.assertEqual(texture.table_slot(pack([0, entry, 0]), 0x10009000, entry), 0x10009004)
        for values in ([0, 0, 0], [0, entry, entry, 0], [0, entry, entry + 4, 0],
                       [1, entry, 0], [0, entry, 1], [0, entry]):
            with self.subTest(values=values), self.assertRaises(ValueError):
                texture.table_slot(pack(values), 0x10009000, entry)
        with self.assertRaises(ValueError):
            texture.table_slot(pack([0, entry, 0]), 0x10009001, entry)


if __name__ == "__main__":
    unittest.main()
