"""Original-source integrity and scoped header-input tracking, without networking."""
import hashlib
import io
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
import upstream_boost as boost
import workflow_manifest as workflow


def fixture(root):
    entries = []
    for name, raw in [('boost/version.hpp', b'#define BOOST_VERSION 104000\n'),
                      ('LICENSE_1_0.txt', b'fixture license\n')]:
        path = root / boost.FOLDER / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(raw)
        entries.append(dict(path=name, repository='https://github.com/boostorg/config',
                            commit='a' * 40, source_path=name if name == 'LICENSE_1_0.txt' else 'include/' + name,
                            git_blob_sha1=hashlib.sha1(b'blob ' + str(len(raw)).encode() + b'\0' + raw).hexdigest(),
                            size=len(raw), sha256=hashlib.sha256(raw).hexdigest()))
    return dict(schema_version=1, release='boost-1.40.0', superproject='https://github.com/boostorg/boost',
                superproject_commit=boost.SUPERPROJECT, files=entries)


class UpstreamBoostTests(unittest.TestCase):
    def test_selection_is_explicit_and_scoped(self):
        self.assertEqual(boost.inputs({}), [])
        boost.validate(dict(kind='probe', boost_regex_headers=True, include_dirs=[boost.FOLDER]))
        for unit in [dict(boost_regex_headers='true'),
                     dict(kind='probe', boost_regex_headers=True, include_dirs=[]),
                     dict(kind='probe', boost_regex_headers=True, include_dirs=[boost.FOLDER, 'other'])]:
            with self.assertRaises(ValueError):
                boost.validate(unit)

    def test_instance_source_requires_the_original_wrapper_and_headers(self):
        unit = dict(kind='probe', boost_regex_headers=True, boost_regex_instances=True,
                    source=boost.INSTANCE_PROBE, include_dirs=[boost.FOLDER])
        boost.validate(unit)
        for changes in [dict(boost_regex_headers=False), dict(source='arbitrary.cpp'),
                        dict(boost_regex_instances='true')]:
            with self.assertRaises(ValueError):
                boost.validate(dict(unit, **changes))

    def test_release_wrapper_retains_original_instance_verification(self):
        unit = dict(kind='probe', boost_regex_headers=True, boost_regex_instances=True,
                    source=boost.RELEASE_INSTANCE_PROBE, include_dirs=[boost.FOLDER])
        boost.validate(unit)
        with self.assertRaises(ValueError):
            boost.validate(dict(unit, boost_regex_headers=False))
        root = Path('/original-source-fixture')
        original = root / boost.INSTANCE_PATH
        with mock.patch.object(boost, 'load_lock', return_value={}), \
                mock.patch.object(boost, 'verified_sources', return_value=[]), \
                mock.patch.object(boost, 'verified_instance', return_value=original) as verify:
            paths = boost.inputs(unit, root)
        verify.assert_called_once_with(root)
        self.assertIn(original, paths)

    def test_instance_bytes_are_checked_without_a_compiler(self):
        raw = b'original source fixture\n'
        entry = dict(path='instances.cpp', size=len(raw),
                     git_blob_sha1=hashlib.sha1(b'blob ' + str(len(raw)).encode() + b'\0' + raw).hexdigest(),
                     sha256=hashlib.sha256(raw).hexdigest())
        with tempfile.TemporaryDirectory() as tmp, mock.patch.object(boost, 'INSTANCE', entry):
            root = Path(tmp)
            path = root / boost.INSTANCE_PATH
            path.parent.mkdir(parents=True)
            path.write_bytes(raw)
            self.assertEqual(boost.verified_instance(root), path)
            path.write_bytes(raw + b'changed')
            with self.assertRaises(ValueError):
                boost.verified_instance(root)

    def test_original_files_and_tamper_are_checked(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            manifest = fixture(root)
            self.assertEqual(len(boost.verified_sources(root, manifest)), 2)
            path = root / boost.FOLDER / 'boost/version.hpp'
            path.write_bytes(path.read_bytes() + b' ')
            with self.assertRaises(ValueError):
                boost.verified_sources(root, manifest)

    def test_extra_headers_and_traversal_are_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            manifest = fixture(root)
            (root / boost.FOLDER / 'boost/extra.hpp').write_text('')
            with self.assertRaises(ValueError):
                boost.verified_sources(root, manifest)
            manifest['files'][0]['path'] = 'boost/../../outside.hpp'
            with self.assertRaises(ValueError):
                boost.records(manifest)

    def test_byte_encoding_cannot_change_original_identity(self):
        raw = b'// author \xf8\n'
        record = dict(path='boost/example.hpp', size=len(raw),
                      git_blob_sha1=hashlib.sha1(b'blob ' + str(len(raw)).encode() + b'\0' + raw).hexdigest(),
                      sha256=hashlib.sha256(raw).hexdigest())
        boost.verify_bytes(raw, record)
        with self.assertRaises(ValueError):
            boost.verify_bytes(raw.decode('latin-1').encode('utf-8'), record)

    def test_fetch_checks_before_writing_and_uses_immutable_official_url(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            manifest = fixture(root)
            path = root / boost.FOLDER / 'boost/version.hpp'
            raw = path.read_bytes()
            path.unlink()
            with mock.patch.object(boost.urllib.request, 'urlopen', return_value=io.BytesIO(b'wrong')):
                with self.assertRaises(ValueError):
                    boost.fetch_missing(root, manifest)
            self.assertFalse(path.exists())
            with mock.patch.object(boost.urllib.request, 'urlopen', return_value=io.BytesIO(raw)) as get:
                boost.fetch_missing(root, manifest)
            self.assertEqual(path.read_bytes(), raw)
            self.assertEqual(get.call_args.args[0],
                             'https://raw.githubusercontent.com/boostorg/config/' + 'a' * 40 + '/include/boost/version.hpp')

    def test_fetch_does_not_overwrite_an_altered_existing_header(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            manifest = fixture(root)
            (root / boost.FOLDER / 'boost/version.hpp').write_bytes(b'changed')
            with mock.patch.object(boost.urllib.request, 'urlopen') as get:
                with self.assertRaises(ValueError):
                    boost.fetch_missing(root, manifest)
            get.assert_not_called()

    def test_missing_sdk_is_deferred_only_for_metadata_not_native_inputs(self):
        unit = dict(kind='probe', boost_regex_headers=True, include_dirs=[boost.FOLDER])
        self.assertTrue(workflow.deferred_upstream_include(unit, boost.FOLDER))
        self.assertFalse(workflow.deferred_upstream_include(unit, 'unrelated'))
        self.assertFalse(workflow.deferred_upstream_include({}, boost.FOLDER))
        zlib = dict(kind='linked_candidate', link_png_sdk=True)
        self.assertTrue(workflow.deferred_upstream_include(zlib, '.tools/upstream/zlib-1.2.3'))
        self.assertFalse(workflow.deferred_upstream_include(zlib, '.tools/other'))
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaises(OSError):
                boost.inputs(unit, Path(tmp))

    def test_changed_lock_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'config').mkdir()
            (root / boost.LOCK).write_text('{}')
            with self.assertRaises(ValueError):
                boost.load_lock(root)

    def test_external_hpp_is_part_of_input_digest(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            names = ['src/probe.cpp', 'config/match-units.toml', 'config/target.toml',
                     'config/known-symbols.csv', 'config/reccmp-relocations.csv',
                     'scripts/build.py', 'scripts/compare-function.py', 'scripts/compile-unit.sh',
                     'scripts/fetch-xiph-sdk-object.py', 'scripts/extract-msvc-library-object.py',
                     'scripts/match_literals.py', 'scripts/workflow_manifest.py', 'vendor/header.hpp']
            for name in names:
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text('fixture\n')
            unit = dict(kind='probe', source='src/probe.cpp', profile='vc8-sp1-probe-o2',
                        enable_gs=False, include_dirs=['vendor'], functions=[])
            with mock.patch.multiple(workflow, ROOT=root, MANIFEST=root / 'config/match-units.toml',
                                     TARGET_CONFIG=root / 'config/target.toml'), \
                    mock.patch.object(workflow, 'compiler_sha256', return_value='0' * 64):
                before, paths = workflow.unit_input_digest('fixture', unit)
                (root / 'vendor/header.hpp').write_text('changed\n')
                after, _ = workflow.unit_input_digest('fixture', unit)
            self.assertIn('vendor/header.hpp', paths)
            self.assertNotEqual(before, after)



class PublicSearchInstantiationTests(unittest.TestCase):
    def test_exact_original_public_instantiation_is_pinned(self):
        self.assertEqual(boost.verified_search_instantiation(boost.ROOT), (boost.ROOT/boost.SEARCH_PROBE).resolve())

    def test_extra_source_or_compiler_control_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp);p=root/boost.SEARCH_PROBE;p.parent.mkdir(parents=True)
            p.write_bytes((boost.ROOT/boost.SEARCH_PROBE).read_bytes()+b'\n#pragma optimize("", off)\n')
            with self.assertRaises(ValueError):boost.verified_search_instantiation(root)

    def test_source_cannot_skip_original_header_verification(self):
        with self.assertRaises(ValueError):boost.validate(dict(kind='probe',source=boost.SEARCH_PROBE))

    def test_changed_release_configuration_is_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp);p=root/boost.SEARCH_PROBE;p.parent.mkdir(parents=True)
            p.write_bytes((boost.ROOT/boost.SEARCH_PROBE).read_bytes().replace(b'#define NDEBUG',b'// removed release macro'))
            with self.assertRaises(ValueError):boost.verified_search_instantiation(root)


    def test_repository_crlf_checkout_preserves_source_pin(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp);p=root/boost.SEARCH_PROBE;p.parent.mkdir(parents=True)
            raw=(boost.ROOT/boost.SEARCH_PROBE).read_bytes().replace(b'\r\n',b'\n')
            for content in (raw,raw.replace(b'\n',b'\r\n')):
                p.write_bytes(content)
                self.assertEqual(boost.verified_search_instantiation(root),p.resolve())

if __name__ == '__main__':
    unittest.main()
