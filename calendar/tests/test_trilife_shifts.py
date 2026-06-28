import unittest
from unittest.mock import patch, MagicMock, mock_open
import pandas as pd
from datetime import datetime

# Mock the external libraries before they are imported by the script
import sys
mock_gspread = MagicMock()
mock_googleapiclient = MagicMock()
mock_google_oauth2 = MagicMock()
mock_camelot = MagicMock()

sys.modules['gspread'] = mock_gspread
sys.modules['googleapiclient'] = mock_googleapiclient
sys.modules['googleapiclient.discovery'] = mock_googleapiclient.discovery
sys.modules['google.oauth2'] = mock_google_oauth2
sys.modules['google.oauth2.service_account'] = mock_google_oauth2.service_account
sys.modules['camelot'] = mock_camelot

from trilife_shifts import Consultant, GoogleServiceProvider, ShiftScheduler

class TestShiftScheduler(unittest.TestCase):

    def setUp(self):
        self.mock_google_service = MagicMock(spec=GoogleServiceProvider)
        self.scheduler = ShiftScheduler(self.mock_google_service)

    @patch('camelot.read_pdf')
    @patch('pathlib.Path.exists')
    def test_read_roster_from_pdf_success(self, mock_exists, mock_read_pdf):
        # Arrange
        mock_exists.return_value = True
        mock_table = MagicMock()
        mock_table.df = pd.DataFrame({
            0: ['DATE', '01-08-25', '02-08-25'],
            1: ['MORNING', 'MT', 'AM'],
            2: ['AFTERNOON', 'SK', 'PS'],
            3: ['NIGHT', 'SJ', 'MT']
        })
        mock_read_pdf.return_value = [mock_table]

        # Act
        df = self.scheduler.read_roster_from_pdf('dummy.pdf')

        # Assert
        self.assertIsInstance(df, pd.DataFrame)
        self.assertEqual(df.shape, (3, 4))
        self.assertEqual(df.iloc[1, 1], 'MT')

    @patch('pathlib.Path.exists')
    def test_read_roster_from_pdf_file_not_found(self, mock_exists):
        # Arrange
        mock_exists.return_value = False

        # Act & Assert
        with self.assertRaises(FileNotFoundError):
            self.scheduler.read_roster_from_pdf('non_existent.pdf')

    def test_get_year_month_from_roster_success(self):
        # Arrange
        roster_df = pd.DataFrame({0: ['01-08-2025', '02-08-2025']})

        # Act
        year, month = self.scheduler._get_year_month_from_roster(roster_df)

        # Assert
        self.assertEqual(year, 2025)
        self.assertEqual(month, 8)

    def test_get_year_month_from_roster_different_months(self):
        # Arrange
        roster_df = pd.DataFrame({0: ['01-08-2025', '02-09-2025']})

        # Act & Assert
        with self.assertRaises(ValueError) as context:
            self.scheduler._get_year_month_from_roster(roster_df)
        self.assertEqual(str(context.exception), "All dates in the roster must be for the same month.")

    def test_get_year_month_from_roster_no_valid_date(self):
        # Arrange
        roster_df = pd.DataFrame({0: ['Invalid Date', None]})

        # Act & Assert
        with self.assertRaises(ValueError):
            self.scheduler._get_year_month_from_roster(roster_df)

    @patch('trilife_shifts.datetime')
    def test_create_schedule_sheet_warning_for_wrong_month(self, mock_datetime):
        # Arrange
        mock_datetime.now.return_value = datetime(2025, 1, 1)
        consultant = Consultant(name='Test', initial='TT', calendarId='test_cal', sharees=['test@test.com'])
        roster_df = pd.DataFrame({
            0: ['01-08-2025', '02-08-2025'],
            1: ['TT', 'AM'],
            2: ['SK', 'PS'],
            3: ['SJ', 'TT']
        })
        mock_worksheet = MagicMock()
        mock_worksheet.spreadsheet.id = 'test_sheet_id'
        self.mock_google_service.create_sheet.return_value = mock_worksheet

        with patch('builtins.print') as mock_print:
            # Act
            self.scheduler.create_schedule_sheet(consultant, roster_df)

            # Assert
            mock_print.assert_called_with("Warning: The roster month (August 2025) is not the current or next month.")

    def test_get_shifts(self):
        # Arrange
        row = pd.Series(['01-08-25', 'MT', 'SK', 'SJ'])
        initial = 'MT'

        # Act
        shifts = self.scheduler._get_shifts(row, initial)

        # Assert
        self.assertEqual(shifts, ['y', 'n', 'n'])

    @patch('trilife_shifts.dateutil.parser.parse')
    def test_create_schedule_sheet(self, mock_parse):
        # Arrange
        mock_parse.return_value = datetime(2025, 8, 1)
        consultant = Consultant(name='Test', initial='TT', calendarId='test_cal', sharees=['test@test.com'])
        roster_df = pd.DataFrame({
            0: ['01-08-25', '02-08-25'],
            1: ['TT', 'AM'],
            2: ['SK', 'PS'],
            3: ['SJ', 'TT']
        })
        mock_worksheet = MagicMock()
        mock_worksheet.spreadsheet.id = 'test_sheet_id'
        self.mock_google_service.create_sheet.return_value = mock_worksheet
        self.scheduler._get_year_month_from_roster = MagicMock(return_value=(2025, 8))

        # Act
        worksheet = self.scheduler.create_schedule_sheet(consultant, roster_df)

        # Assert
        self.mock_google_service.create_sheet.assert_called_once_with('Shift Schedule for Test August 2025')
        self.assertEqual(worksheet.append_row.call_count, 3) # Header + 2 shifts
        self.mock_google_service.share_file.assert_called_once_with('test_sheet_id', 'dhyanesh.damania@gmail.com')

    def test_import_shifts_to_calendar(self):
        # Arrange
        consultant = Consultant(name='Test', initial='TT', calendarId='test_cal', sharees=['test@test.com'])
        mock_worksheet = MagicMock()
        mock_worksheet.get_all_values.return_value = [
            ['Date', 'Morning Shift', 'Afternoon Shift', 'Night Shift'],
            ['2025-08-01', 'y', 'n', 'n'],
            ['2025-08-02', 'n', 'y', 'y']
        ]
        self.scheduler._create_calendar_event = MagicMock()

        # Act
        self.scheduler.import_shifts_to_calendar(consultant, mock_worksheet)

        # Assert
        self.assertEqual(self.scheduler._create_calendar_event.call_count, 3)

class TestGoogleServiceProvider(unittest.TestCase):

    @patch('trilife_shifts.build')
    @patch('trilife_shifts.gspread.authorize')
    @patch('trilife_shifts.Credentials.from_service_account_file')
    @patch('trilife_shifts.Path.exists', return_value=True)
    def test_authentication_success(self, mock_exists, mock_creds, mock_authorize, mock_build):
        # Act
        GoogleServiceProvider('test_creds.json')
        # Assert
        mock_creds.assert_called_once()
        mock_authorize.assert_called_once()
        self.assertEqual(mock_build.call_count, 2)

    @patch('trilife_shifts.Path.exists', return_value=False)
    def test_authentication_file_not_found(self, mock_exists):
        with self.assertRaises(FileNotFoundError):
            GoogleServiceProvider('non_existent.json')

    @patch('trilife_shifts.build')
    @patch('trilife_shifts.gspread.authorize')
    @patch('trilife_shifts.Credentials.from_service_account_file')
    @patch('trilife_shifts.Path.exists', return_value=True)
    def test_create_sheet(self, mock_exists, mock_creds, mock_authorize, mock_build):
        # Arrange
        google_service = GoogleServiceProvider('dummy_creds.json')
        # Act
        google_service.create_sheet('Test Sheet')
        # Assert
        google_service.sheets_client.create.assert_called_once_with('Test Sheet')

    @patch('trilife_shifts.build')
    @patch('trilife_shifts.gspread.authorize')
    @patch('trilife_shifts.Credentials.from_service_account_file')
    @patch('trilife_shifts.Path.exists', return_value=True)
    def test_share_file(self, mock_exists, mock_creds, mock_authorize, mock_build):
        # Arrange
        google_service = GoogleServiceProvider('dummy_creds.json')
        # Act
        google_service.share_file('test_id', 'test@test.com')
        # Assert
        google_service.drive_service.permissions().create.assert_called_once()

if __name__ == '__main__':
    unittest.main(argv=['first-arg-is-ignored'], exit=False)
