"""A global constructor is a private caller only through complete current proofs."""
import copy
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import linked_global_caller as global_caller


class GlobalCallerTests(unittest.TestCase):
    def fixture(self, template=False):
        owner = "?$Member@PAUPayload@game@@@game" if template else "Member@game"
        table = "??_7" + owner + "@@6B@"
        child = dict(address="0x00402000", symbol_base="??0" + owner + "@@QAE@XZ",
                     private_from=dict(caller="0x00401000", site="0x00401020",
                                       through_exact_caller=True),
                     eh_cleanup=dict(handler="0x00602000", info="0x00603000"))
        parent = dict(address="0x00401000", symbol_base="??0Global@game@@QAE@XZ",
                      private_global=dict(object="?global", role="constructor"),
                      eh_cleanup=dict(handler="0x00601000", info="0x00601040"))
        obj = dict(symbol="?global", size=64, initializer="0x00604000",
                   initializer_table="0x00605000", destructor_callback="0x00606000")
        unit = dict(link_objects=[obj], link_vtables=[dict(symbol=table)])
        def region(kind, size, target=0):
            return dict(kind=kind, size=size, target_address=target,
                        canonical_sha256="a" * 64, target_sha256="a" * 64)
        proof = dict(symbol="?global", size=64, target_initializer=0x604000,
                     target_initializer_slot=0x605000, target_callback=0x606000,
                     source_address=0x10003000, target_address=0x703000,
                     regions=[region("initializer", 17), region("atexit callback", 5)])
        report = dict(global_lifecycle_witness=copy.deepcopy(proof),
                      validated_cleanup_eh=[region("cleanup handler", 27, 0x601000),
                          region("cleanup funclet 0", 11, 0x600FF0),
                          region("FuncInfo", 36, 0x601040), region("unwind map", 8, 0x601038)])
        return child, parent, unit, report, {"?global": proof}

    def test_named_and_pointer_template_members_are_supported(self):
        for template in (False, True):
            f, p, u, report, fresh = self.fixture(template)
            self.assertEqual(global_caller.validate(f, p, u), u["link_objects"][0])
            witness = global_caller.observe(f, p, u, report, fresh)
            self.assertEqual(witness["global_lifecycle_witness"], fresh["?global"])
            self.assertEqual(len(witness["validated_cleanup_eh"]), 4)

    def test_only_default_polymorphic_constructor_entries(self):
        good = "??0Member@game@@QAE@XZ"
        self.assertEqual(global_caller.constructor_vtable(good), "??_7Member@game@@6B@")
        for bad in [None, "??1Member@game@@UAE@XZ", "?method@Member@@QAEXXZ",
                    "??0Member@game@@QAE@I@Z", good + "junk",
                    "??0?$Member@H@game@@QAE@XZ"]:
            self.assertIsNone(global_caller.constructor_vtable(bad))

    def test_source_only_indirect_cleanup_and_extra_flags_are_rejected(self):
        changes = [lambda f, p, u: f["private_from"].update(through_exact_caller=False),
                   lambda f, p, u: f["private_from"].update(source_only_caller=True),
                   lambda f, p, u: f["private_from"].update(cleanup=0),
                   lambda f, p, u: f["private_from"].update(sites=["0x00401020"]),
                   lambda f, p, u: f["private_from"].update(caller="0x00403000"),
                   lambda f, p, u: f["private_from"].update(site="bad"),
                   lambda f, p, u: f.update(export_name="_forced"),
                   lambda f, p, u: f["private_from"].update(through_exact_caller=1),
                   lambda f, p, u: f.update(eh_cleanup={}),
                   lambda f, p, u: p.update(eh_cleanup={"handler": "bad", "info": "0x00600000"}),
                   lambda f, p, u: f.pop("eh_cleanup"),
                   lambda f, p, u: p.pop("eh_cleanup"),
                   lambda f, p, u: p["private_global"].update(role="destructor"),
                   lambda f, p, u: p.update(private_from={}),
                   lambda f, p, u: u.update(link_vtables=[]),
                   lambda f, p, u: u.update(link_objects=[])]
        for change in changes:
            f, p, u, _, _ = self.fixture(); change(f, p, u)
            with self.subTest(change=change), self.assertRaises(ValueError):
                global_caller.validate(f, p, u)

    def test_fresh_global_identity_cannot_be_reused_or_omitted(self):
        for change in [lambda r, g: r.pop("global_lifecycle_witness"),
                       lambda r, g: g.clear(),
                       lambda r, g: r["global_lifecycle_witness"].update(source_address=0x10003004),
                       lambda r, g: g["?global"].update(target_initializer=0x604010),
                       lambda r, g: g["?global"].update(size=68)]:
            f, p, u, report, fresh = self.fixture(); change(report, fresh)
            with self.subTest(change=change), self.assertRaises(ValueError):
                global_caller.observe(f, p, u, report, fresh)

    def test_complete_startup_regions_must_match(self):
        changes = [lambda proof: proof.update(regions=[]),
                   lambda proof: proof["regions"][0].update(size=16),
                   lambda proof: proof["regions"][0].update(canonical_sha256=""),
                   lambda proof: proof["regions"][1].update(target_sha256="b" * 64),
                   lambda proof: proof.update(regions=[None, None])]
        for change in changes:
            f, p, u, report, fresh = self.fixture()
            change(fresh["?global"]); report["global_lifecycle_witness"] = copy.deepcopy(fresh["?global"])
            with self.subTest(change=change), self.assertRaises(ValueError):
                global_caller.observe(f, p, u, report, fresh)

    def test_complete_parent_eh_must_be_retained(self):
        changes = [lambda r: r.update(validated_cleanup_eh=[]),
                   lambda r: r["validated_cleanup_eh"].pop(1),
                   lambda r: r["validated_cleanup_eh"][0].update(target_address=0x601010),
                   lambda r: r["validated_cleanup_eh"][-2].update(size=32),
                   lambda r: r["validated_cleanup_eh"][-1].update(size=16),
                   lambda r: r["validated_cleanup_eh"][1].update(target_sha256="b" * 64),
                   lambda r: r["validated_cleanup_eh"].append(None)]
        for change in changes:
            f, p, u, report, fresh = self.fixture(); change(report)
            with self.subTest(change=change), self.assertRaises(ValueError):
                global_caller.observe(f, p, u, report, fresh)
