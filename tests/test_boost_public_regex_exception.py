import copy
from pathlib import Path
import sys
import tempfile
import tomllib
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import boost_public_regex_exception as g

class PublicRegexExceptionTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address='0x006B5350',size='46')],g.load_manifest()['units']
    def test_original_public_and_provider_units(self):
        s,r,u=self.fixture();a,unit,provider=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(a['size'],46);self.assertEqual(provider['boost_regex_source_tu'],'regex.cpp')
    def test_wrong_extent_mask_or_nominal_type_rejected(self):
        for k,v in [('size',45),('mask',[9]),('symbol',g.COPY.replace('regex_error','runtime_error'))]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_profile_and_verified_header_contract(self):
        for k,v in [('enable_gs',False),('profile','vc8-sp1-probe-o2-ob1'),('boost_regex_headers',False)]:
            s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_provider_cannot_be_a_replacement_body(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.PROVIDER]['source']='scripts/probes/Invented.cpp'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_formal_vtable_binding_cannot_change(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['dir32_targets']=[]
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_probe_cannot_disable_original_header_verification(self):
        with self.assertRaises(ValueError):g.upstream.validate(dict(source=g.upstream.REGEX_EXCEPTION_PROBE,boost_regex_headers=False))
    def probe_root(self,raw):
        temp=tempfile.TemporaryDirectory();root=Path(temp.name);p=root/g.upstream.REGEX_EXCEPTION_PROBE;p.parent.mkdir(parents=True);p.write_bytes(raw);return temp,root
    def test_original_declaration_accepts_git_newlines(self):
        raw=(g.ROOT/g.upstream.REGEX_EXCEPTION_PROBE).read_bytes().replace(b'\r\n',b'\n')
        for data in [raw,raw.replace(b'\n',b'\r\n')]:
            temp,root=self.probe_root(data)
            with temp:self.assertEqual(g.upstream.verified_regex_exception_instantiation(root),root/g.upstream.REGEX_EXCEPTION_PROBE)
    def test_attribute_removal_or_extra_code_rejected(self):
        raw=(g.ROOT/g.upstream.REGEX_EXCEPTION_PROBE).read_bytes()
        for data in [raw.replace(b'BOOST_ATTRIBUTE_NORETURN ',b''),raw+b'\nvoid invented() {}\n']:
            temp,root=self.probe_root(data)
            with temp:
                with self.assertRaises(ValueError):g.upstream.verified_regex_exception_instantiation(root)

if __name__=='__main__':unittest.main()
