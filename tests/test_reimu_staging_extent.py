import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
from reimu_staging_extent import staging_execution_extent


class StagingExtentTests(unittest.TestCase):
    def test_existing_small_text(self):
        self.assertEqual(staging_execution_extent(79980, 81550), 79980)

    def test_extension_requires_opt_in(self):
        with self.assertRaises(ValueError):
            staging_execution_extent(81652, 81550, metadata_start=80344, metadata_limit=82924)

    def test_switch_data_stays_outside_execution(self):
        self.assertEqual(staging_execution_extent(81652, 81550, allow_switch_metadata=True,
                         metadata_start=80344, metadata_limit=82924), 80344)

    def test_code_overflow_is_rejected(self):
        with self.assertRaises(ValueError):
            staging_execution_extent(81652, 81550, allow_switch_metadata=True,
                                     metadata_start=81551, metadata_limit=82924)

    def test_data_overflow_is_rejected(self):
        with self.assertRaises(ValueError):
            staging_execution_extent(82925, 81550, allow_switch_metadata=True,
                                     metadata_start=80344, metadata_limit=82924)

    def test_unmapped_metadata_is_rejected(self):
        with self.assertRaises(ValueError):
            staging_execution_extent(81652, 81550, allow_switch_metadata=True,
                                     metadata_limit=82924)

    def test_empty_text_is_rejected(self):
        with self.assertRaises(ValueError):
            staging_execution_extent(0, 81550)


if __name__ == "__main__":
    unittest.main()
