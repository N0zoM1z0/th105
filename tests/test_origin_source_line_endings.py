"""Origin source byte pins must survive the configured Git checkout EOL."""
import hashlib
from pathlib import Path
import subprocess
import tomllib
import unittest

ROOT=Path(__file__).resolve().parents[1]

class OriginSourceLineEndingsTests(unittest.TestCase):
    def test_source_pins_match_bytes_and_checkout_attributes(self):
        pins={}
        for anchor in sorted((ROOT/'config').glob('*origin*anchors.toml')):
            data=tomllib.loads(anchor.read_text(encoding='utf-8'))
            for name,digest in data.get('source_pins',{}).items():
                if not name.startswith('src/'):
                    continue
                self.assertEqual(pins.setdefault(name,digest),digest, f'conflicting source pin: {name}')
        self.assertTrue(pins)
        names=sorted(pins)
        result=subprocess.run(['git','check-attr','-z','eol','--',*names],cwd=ROOT,check=True,stdout=subprocess.PIPE).stdout.split(b'\0')
        attrs={result[i].decode():result[i+2].decode() for i in range(0,len(result)-1,3)}
        for name in names:
            raw=(ROOT/name).read_bytes()
            self.assertEqual(hashlib.sha256(raw).hexdigest(),pins[name],f'source pin mismatch: {name}')
            lf=raw.replace(b'\r\n',b'\n')
            self.assertNotIn(b'\r',lf,f'mixed or unsupported line ending: {name}')
            style=attrs[name]
            self.assertIn(style,('lf','crlf'),f'checkout EOL not pinned: {name}')
            checkout=lf if style=='lf' else lf.replace(b'\n',b'\r\n')
            self.assertEqual(hashlib.sha256(checkout).hexdigest(),pins[name],f'checkout changes pinned bytes: {name}')

if __name__=='__main__':unittest.main()
