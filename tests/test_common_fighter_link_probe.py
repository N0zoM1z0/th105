"""Fail closed on source partitions, linker identities and executable bindings."""
import importlib.util
from pathlib import Path
import sys
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "common_fighter_link_test", ROOT / "scripts/probe-common-fighter-ltcg.py")
probe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(probe)
inspector = probe.load_inspector()


class CommonFighterLinkTests(unittest.TestCase):
    def test_source_partition_keeps_complete_body_types_and_storage(self):
        source = ('struct Actor { void keep(); void discard(); };\nint storage;\n'
                  'void Actor::keep() { const char *s = "}"; if (storage) { ++storage; } }\n'
                  'void Actor::discard() { /* { */ --storage; }\n')
        selected = probe.select_methods(source, {"keep"}, {"discard"})
        self.assertIn('void Actor::keep() { const char *s = "}";', selected)
        self.assertIn("if (storage) { ++storage; }", selected)
        self.assertIn("struct Actor { void keep(); void discard(); };", selected)
        self.assertIn("int storage;", selected)
        self.assertNotIn("Actor::discard", selected)
        self.assertNotIn("--storage", selected)

    def test_changed_or_unbalanced_source_partition_is_rejected(self):
        for source in ("void Actor::keep() {}\nvoid Actor::extra() {}\n",
                       "void Actor::keep() {\n", "void Actor::other() {}\n"):
            with self.subTest(source=source), self.assertRaises(ValueError):
                probe.select_methods(source, {"keep"}, set())

    def test_alias_requires_definition_at_same_address_and_in_same_object(self):
        aliases = {"view": "actual"}
        good = {0x10001000: [("view", "body.obj"), ("actual", "body.obj")]}
        self.assertEqual(inspector.normalize_map_aliases(good, aliases),
                         {0x10001000: [("actual", "body.obj")]})
        for bad in ({0x10001000: [("view", "body.obj")],
                     0x10002000: [("actual", "body.obj")]},
                    {0x10001000: [("view", "body.obj"), ("actual", "other.obj")]}):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                inspector.normalize_map_aliases(bad, aliases)

    def test_undeclared_coincident_map_names_remain_ambiguous(self):
        names = {0x10001000: [("first", "body.obj"), ("second", "body.obj")]}
        self.assertEqual(inspector.normalize_map_aliases(names, {}), names)

    def test_linker_diagnostic_preserves_decorated_identity(self):
        log = ('a.obj : error LNK2001: unresolved external symbol '
               '"public: void __thiscall View::method(void)" (?method@View@@QAEXXZ)\n'
               'a.obj : error LNK2019: unresolved external symbol _plain@4 referenced in function _caller\n')
        self.assertEqual(probe.unresolved_names(log), ["?method@View@@QAEXXZ", "_plain@4"])
        with self.assertRaises(ValueError):
            probe.unresolved_names('error LNK2001: unresolved external symbol "demangled only"')

    def test_abs_binding_rejects_code_unmapped_storage_and_changed_bytes(self):
        canonical = SimpleNamespace(
            known_data_targets=lambda: {"key": (0x500000, b"\0\0\0\0", (0,), None)},
            target_bytes=lambda address, count: b"\0" * count)
        section = SimpleNamespace(Characteristics=0x40000040, contains_rva=lambda rva: True)
        pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000),
                             get_section_by_rva=lambda rva: section)
        self.assertEqual(probe.attest_data(canonical, pe, "storage", "key")["address"], 0x500000)
        with self.assertRaises(ValueError):
            probe.attest_data(canonical, pe, "__imp__function@4", "key")
        section.Characteristics |= 0x20000000
        with self.assertRaises(ValueError):
            probe.attest_data(canonical, pe, "storage", "key")
        section.Characteristics &= ~0x20000000
        section.contains_rva = lambda rva: False
        with self.assertRaises(ValueError):
            probe.attest_data(canonical, pe, "storage", "key")
        section.contains_rva = lambda rva: True
        canonical.target_bytes = lambda address, count: b"\xff" * count
        with self.assertRaises(ValueError):
            probe.attest_data(canonical, pe, "storage", "key")


if __name__ == "__main__":
    unittest.main()
