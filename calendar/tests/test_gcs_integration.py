import unittest
from unittest.mock import patch, call
from roster_generator_cp import main

class TestGCSIntegration(unittest.TestCase):

    @patch('roster_generator_cp.generate_roster_cp')
    @patch('roster_generator_cp.download_json_from_gcs')
    def test_load_from_cache(self, mock_download, mock_generate):
        """Test that the script loads a cached roster from GCS and doesn't generate a new one."""
        mock_download.return_value = {'1': {'morning': ['PK'], 'afternoon': [], 'night': []}}
        
        main(['-y', '2025', '-m', '10'])

        mock_download.assert_called_once_with('trilife-duty-roster-files', '2025/10/roster.json')
        mock_generate.assert_not_called()

    @patch('roster_generator_cp.upload_json_to_gcs')
    @patch('roster_generator_cp.generate_roster_cp')
    @patch('roster_generator_cp.download_json_from_gcs')
    def test_save_to_cache(self, mock_download, mock_generate, mock_upload):
        """Test that the script generates a new roster and saves it to GCS when no cache is found."""
        mock_download.return_value = None
        mock_generate.return_value = ({1: {'morning': ['PK'], 'afternoon': [], 'night': []}}, {'PK': 0})

        main(['-y', '2025', '-m', '10'])

        mock_download.assert_called_once_with('trilife-duty-roster-files', '2025/10/roster.json')
        mock_generate.assert_called_once()
        mock_upload.assert_called_once_with('trilife-duty-roster-files', '2025/10/roster.json', {1: {'morning': ['PK'], 'afternoon': [], 'night': []}})

    @patch('roster_generator_cp.upload_json_to_gcs')
    @patch('roster_generator_cp.generate_roster_cp')
    @patch('roster_generator_cp.download_json_from_gcs')
    def test_load_fixed_roster(self, mock_download, mock_generate, mock_upload):
        """Test that the script loads a fixed roster from GCS."""
        fixed_roster_data = {'1': {'morning': ['AM'], 'afternoon': [], 'night': []}}
        mock_download.side_effect = [None, fixed_roster_data] # First call for cache (None), second for fixed roster
        mock_generate.return_value = ({}, {})

        main(['-y', '2025', '-m', '10', '--fixed-roster', '2025/10/fixed_roster.json'])

        self.assertEqual(mock_download.call_count, 2)
        mock_download.assert_has_calls([
            call('trilife-duty-roster-files', '2025/10/roster.json'),
            call('trilife-duty-roster-files', '2025/10/fixed_roster.json')
        ])
        mock_generate.assert_called_once_with(2025, 10, fixed_roster_data)

if __name__ == '__main__':
    unittest.main()