import dateutil.parser
import gspread
from google.oauth2.service_account import Credentials
from googleapiclient.discovery import build
from datetime import datetime, timedelta
import calendar
import pandas as pd
import camelot
from pathlib import Path
import argparse
from dataclasses import dataclass

@dataclass
class Consultant:
    """Represents a consultant with their name, calendar details, and sharing preferences."""
    name: str
    initial: str
    calendarId: str
    sharees: list[str]

class GoogleServiceProvider:
    """Handles all interactions with Google APIs (Sheets, Calendar, Drive)."""
    def __init__(self, creds_file: str):
        self.creds = self._authenticate(creds_file)
        self.sheets_client = gspread.authorize(self.creds)
        self.calendar_service = build('calendar', 'v3', credentials=self.creds)
        self.drive_service = build('drive', 'v3', credentials=self.creds)

    def _authenticate(self, creds_file: str) -> Credentials:
        scopes = [
            'https://spreadsheets.google.com/feeds',
            'https://www.googleapis.com/auth/drive',
            'https://www.googleapis.com/auth/calendar'
        ]
        if not Path(creds_file).exists():
            raise FileNotFoundError(f"Service account file '{creds_file}' not found.")
        return Credentials.from_service_account_file(creds_file, scopes=scopes)

    def create_sheet(self, title: str) -> gspread.Worksheet:
        print(f"Creating Google Sheet: '{title}'...")
        sheet = self.sheets_client.create(title)
        return sheet.sheet1

    def share_file(self, file_id: str, email: str):
        permission = {'type': 'user', 'role': 'writer', 'emailAddress': email}
        self.drive_service.permissions().create(fileId=file_id, body=permission, fields='id').execute()
        print(f"Access granted to {email} for spreadsheet {file_id}")

    def get_worksheet_from_key(self, key: str) -> gspread.Worksheet:
        try:
            sheet = self.sheets_client.open_by_key(key)
            return sheet.sheet1
        except gspread.exceptions.SpreadsheetNotFound:
            raise ValueError("Spreadsheet not found. Please check the key.")

    def add_calendar_event(self, calendar_id: str, event_body: dict):
        self.calendar_service.events().insert(calendarId=calendar_id, body=event_body).execute()

    def share_calendar(self, calendar_id: str, email: str):
        rule = {'scope': {'type': 'user', 'value': email}, 'role': 'owner'}
        self.calendar_service.acl().insert(calendarId=calendar_id, body=rule).execute()
        print(f"-> Shared calendar '{calendar_id}' with {email} as owner.")

class ShiftScheduler:
    """Handles the business logic of parsing the roster and creating the schedule."""
    def __init__(self, google_service: GoogleServiceProvider):
        self.google_service = google_service

    def read_roster_from_pdf(self, pdf_path: str) -> pd.DataFrame:
        if not Path(pdf_path).exists():
            raise FileNotFoundError(f"PDF file not found at '{pdf_path}'")
        
        print(f"Reading PDF: {pdf_path}...")
        tables = camelot.read_pdf(pdf_path, pages='all', flavor='stream')

        if not tables:
            raise ValueError("No tables found in the PDF.")

        roster_df = pd.concat([table.df for table in tables], ignore_index=True)
        roster_df_trimmed = roster_df.iloc[:, :4]
        roster_df_trimmed.columns = range(roster_df_trimmed.shape[1])
        return roster_df_trimmed.reset_index(drop=True)

    def create_schedule_sheet(self, consultant: Consultant, roster_df: pd.DataFrame) -> gspread.Worksheet:
        year, month = self._get_year_month_from_roster(roster_df)
        
        current_date = datetime.now()
        current_month = current_date.month
        current_year = current_date.year
        
        next_month = current_month + 1 if current_month < 12 else 1
        next_year = current_year if current_month < 12 else current_year + 1
        
        if not (year == current_year and month == current_month) and not (year == next_year and month == next_month):
            print(f"Warning: The roster month ({calendar.month_name[month]} {year}) is not the current or next month.")

        sheet_title = f'Shift Schedule for {consultant.name} {calendar.month_name[month]} {year}'
        worksheet = self.google_service.create_sheet(sheet_title)
        worksheet.append_row(['Date', 'Morning Shift', 'Afternoon Shift', 'Night Shift'])

        for _, row in roster_df.iterrows():
            if not row.iloc[0]:
                continue
            
            try:
                date = dateutil.parser.parse(row.iloc[0], default=datetime(year, month, 1), dayfirst=True)
            except (dateutil.parser.ParserError, TypeError):
                print(f"Warning: Skipping row with unparsable date '{row.iloc[0]}'")
                continue
            
            formatted_date = date.strftime('%Y-%m-%d')
            shifts = self._get_shifts(row, consultant.initial)

            if 'y' in shifts:
                worksheet.append_row([formatted_date] + shifts)
        
        self.google_service.share_file(worksheet.spreadsheet.id, "dhyanesh.damania@gmail.com")
        return worksheet

    def import_shifts_to_calendar(self, consultant: Consultant, worksheet: gspread.Worksheet):
        print("Importing events to Google Calendar...")
        shift_times = {
            'Morning Shift': {'start': 8, 'end': 17},
            'Afternoon Shift': {'start': 12, 'end': 20},
            'Night Shift': {'start': 17, 'end': 32}
        }

        for row in worksheet.get_all_values()[1:]:
            date = datetime.strptime(row[0], '%Y-%m-%d')
            if row[1] == 'y':
                self._create_calendar_event('Morning Shift', date, shift_times['Morning Shift'], consultant.calendarId)
            if row[2] == 'y':
                self._create_calendar_event('Afternoon Shift', date, shift_times['Afternoon Shift'], consultant.calendarId)
            if row[3] == 'y':
                self._create_calendar_event('Night Shift', date, shift_times['Night Shift'], consultant.calendarId)
        print("Calendar import complete.")

    def _get_year_month_from_roster(self, roster_df: pd.DataFrame) -> tuple[int, int]:
        dates = []
        for date_str in roster_df.iloc[:, 0]:
            if date_str:
                try:
                    dates.append(dateutil.parser.parse(date_str, dayfirst=True))
                except (dateutil.parser.ParserError, TypeError):
                    continue
        
        if not dates:
            raise ValueError("Could not determine the month from the roster.")

        if not all(d.month == dates[0].month for d in dates):
            raise ValueError("All dates in the roster must be for the same month.")

        return dates[0].year, dates[0].month

    def _get_shifts(self, row: pd.Series, initial: str) -> list[str]:
        return ['y' if initial in str(row.iloc[i]) else 'n' for i in range(1, 4)]

    def _create_calendar_event(self, summary: str, date: datetime, hours: dict, calendar_id: str):
        event_body = {
            'summary': summary,
            'start': {'dateTime': (date + timedelta(hours=hours['start'])).isoformat(), 'timeZone': 'Asia/Kolkata'},
            'end': {'dateTime': (date + timedelta(hours=hours['end'])).isoformat(), 'timeZone': 'Asia/Kolkata'}
        }
        self.google_service.add_calendar_event(calendar_id, event_body)

def main():
    """Main function to run the script."""
    consultant_map = {
        "Mittal": {"initial": "MT", "calendarId": 'primary', "sharees": ['dhyanesh.damania@gmail.com', 'gunsnroses128@gmail.com']},
        "Amirtha": {"initial": "AM", "calendarId": 'dd2a6c96f10e133dff18f3f7cb4994efd0068c472228d1247b5075ba1d6894c1@group.calendar.google.com', "sharees": ['dhyanesh.damania@gmail.com', 'amirthavarsheni@gmail.com']}
    }

    parser = argparse.ArgumentParser(description='Automate Trilife shift scheduling.')
    parser.add_argument('consultant', choices=consultant_map.keys(), help='Consultant name')
    parser.add_argument('pdf_path', help='Path to the roster PDF file')
    parser.add_argument('--create-sheet', action='store_true', help='Create a new Google Sheet from the PDF')
    parser.add_argument('--import-calendar', action='store_true', help='Import events to Google Calendar')
    parser.add_argument('--sheet-key', help='Google Sheet key (if not creating a new sheet)')
    parser.add_argument('--share-calendar', action='store_true', help='Share the Google Calendar')
    args = parser.parse_args()

    try:
        google_service = GoogleServiceProvider('your_service_account_file.json')
        scheduler = ShiftScheduler(google_service)
        
        consultant_config = consultant_map[args.consultant]
        consultant = Consultant(name=args.consultant, **consultant_config)

        roster_df = scheduler.read_roster_from_pdf(args.pdf_path.strip())
        
        worksheet = None
        if args.create_sheet:
            worksheet = scheduler.create_schedule_sheet(consultant, roster_df)
        
        if args.import_calendar:
            if not worksheet:
                if not args.sheet_key:
                    raise ValueError("--sheet-key is required when not creating a new sheet.")
                worksheet = google_service.get_worksheet_from_key(args.sheet_key)
            scheduler.import_shifts_to_calendar(consultant, worksheet)

        if args.share_calendar:
            for email in consultant.sharees:
                google_service.share_calendar(consultant.calendarId, email)

    except (FileNotFoundError, ValueError) as e:
        print(f"Error: {e}")
        exit()

if __name__ == '__main__':
    main()