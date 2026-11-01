import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import upstream_boost as base
import upstream_boost_sources as extra
import workflow_manifest as workflow

class BoostExtraSourceTests(unittest.TestCase):
    def unit(self):
        name='regex.cpp'
        return dict(kind='probe',source=extra.PROBES[name],boost_regex_headers=True,
                    boost_regex_source_tu=name,include_dirs=[base.FOLDER,extra.INCLUDE])
    def fixture(self,root):
        paths=['src/'+n for n in extra.PROBES]+[extra.HEADER,'LICENSE_1_0.txt'];entries=[]
        for name in paths:
            b=('original fixture '+name+'\n').encode();p=root/extra.FOLDER/name;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(b);lic=name=='LICENSE_1_0.txt'
            entries.append(dict(path=name,source_path=name,repository='https://github.com/boostorg/'+('boost'if lic else'regex'),commit=base.SUPERPROJECT if lic else extra.COMMIT,size=len(b),sha256=hashlib.sha256(b).hexdigest(),git_blob_sha1=hashlib.sha1(b'blob '+str(len(b)).encode()+b'\0'+b).hexdigest()))
        manifest=dict(schema_version=1,release='boost-1.40.0',regex_commit=extra.COMMIT,files=entries);p=root/extra.LOCK;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(manifest));u=self.unit();w=root/u['source'];w.parent.mkdir(parents=True,exist_ok=True);w.write_text('#define NDEBUG\n#include "../../'+extra.FOLDER+'/src/regex.cpp"\n');return hashlib.sha256(p.read_bytes()).hexdigest()
    def test_source_selection_requires_known_original_wrapper(self):
        u=self.unit();base.validate(u)
        for change in [dict(source='arbitrary.cpp'),dict(boost_regex_headers=False),dict(boost_regex_source_tu='../file.cpp'),dict(boost_regex_source_tu=True),dict(boost_regex_instances=True),dict(include_dirs=[base.FOLDER])]:
            with self.assertRaises(ValueError):base.validate(dict(u,**change))
    def test_existing_header_only_rule_stays_strict(self):
        base.validate(dict(kind='probe',boost_regex_headers=True,include_dirs=[base.FOLDER]))
        with self.assertRaises(ValueError):base.validate(dict(kind='probe',boost_regex_headers=True,include_dirs=[base.FOLDER,extra.INCLUDE]))
    def test_complete_package_and_inputs(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);sha=self.fixture(root)
            with patch.object(extra,'LOCK_SHA256',sha):
                self.assertEqual(len(extra.verified_sources(root)),8)
                paths=extra.inputs(self.unit(),root);self.assertIn(root/extra.LOCK,paths);self.assertIn(root/extra.FOLDER/extra.HEADER,paths)
    def test_tampered_original_source_fails(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);sha=self.fixture(root);(root/extra.FOLDER/'src/regex.cpp').write_text('changed')
            with patch.object(extra,'LOCK_SHA256',sha),self.assertRaises(ValueError):extra.verified_sources(root)
    def test_extra_source_is_not_silently_used(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);sha=self.fixture(root);(root/extra.FOLDER/'unexpected.hpp').write_text('extra')
            with patch.object(extra,'LOCK_SHA256',sha),self.assertRaises(ValueError):extra.verified_sources(root)
    def test_wrapper_cannot_add_macro_or_code(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);sha=self.fixture(root);u=self.unit();p=root/u['source'];p.write_text(p.read_text()+'#define BOOST_REGEX_NO_W32\n')
            with patch.object(extra,'LOCK_SHA256',sha),self.assertRaisesRegex(ValueError,'wrapper'):extra.inputs(u,root)
    def test_lock_tamper_and_escaped_path_fail(self):
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);sha=self.fixture(root)
            with self.assertRaises(ValueError):extra.load_records(root)
            with self.assertRaises(ValueError):extra.path_for(root,'../../../../outside')
    def test_metadata_can_defer_only_the_selected_extra_include(self):
        self.assertTrue(workflow.deferred_upstream_include(self.unit(),extra.INCLUDE))
        self.assertFalse(workflow.deferred_upstream_include({},extra.INCLUDE))
        self.assertFalse(workflow.deferred_upstream_include(self.unit(),'.tools/other'))
    def test_old_package_still_rejects_extra_headers(self):
        from test_upstream_boost import fixture
        with tempfile.TemporaryDirectory()as tmp:
            root=Path(tmp);manifest=fixture(root);(root/base.FOLDER/'unreviewed.hpp').write_text('')
            with self.assertRaises(ValueError):base.verified_sources(root,manifest)
