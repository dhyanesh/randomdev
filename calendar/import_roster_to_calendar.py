import gspread
from google.oauth2.service_account import Credentials
from googleapiclient.discovery import build
from datetime import datetime, timedelta
import calendar
import argparse
from dataclasses import dataclass
from pathlib import Path

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

    def _authenticate(self, creds_file: str) -> Credentials:
        scopes = [
            'https://spreadsheets.google.com/feeds',
            'https://www.googleapis.com/auth/drive',
            'https://www.googleapis.com/auth/calendar'
        ]
        if not Path(creds_file).exists():
            raise FileNotFoundError(f"Service account file '{creds_file}' not found.")
        return Credentials.from_service_account_file(creds_file, scopes=scopes)

    def get_worksheet(self, title: str, worksheet_name: str) -> gspread.Worksheet:
        try:
            sheet = self.sheets_client.open(title)
            return sheet.worksheet(worksheet_name)
        except gspread.exceptions.SpreadsheetNotFound:
            raise ValueError(f"Spreadsheet with title '{title}' not found.")
        except gspread.exceptions.WorksheetNotFound:
            raise ValueError(f"Worksheet with name '{worksheet_name}' not found in spreadsheet '{title}'.")

    def list_calendar_events(self, calendar_id: str, start_time: str, end_time: str, query: str):
        events_result = self.calendar_service.events().list(
            calendarId=calendar_id,
            timeMin=start_time,
            timeMax=end_time,
            q=query,
            singleEvents=True,
            orderBy='startTime'
        ).execute()
        return events_result.get('items', [])

    def add_calendar_event(self, calendar_id: str, event_body: dict):
        self.calendar_service.events().insert(calendarId=calendar_id, body=event_body).execute()

    def update_calendar_event(self, calendar_id: str, event_id: str, event_body: dict):
        self.calendar_service.events().update(calendarId=calendar_id, eventId=event_id, body=event_body).execute()

class RosterImporter:
    """Handles the logic of reading the roster sheet and creating calendar events."""
    def __init__(self, google_service: GoogleServiceProvider, consultant_map: dict):
        self.google_service = google_service
        self.consultant_map = consultant_map

    def import_roster_to_calendar(self, year: int, month: int, sheet_name: str):
        sheet_title = f"Roster {calendar.month_name[month]} {year}"
        worksheet = self.google_service.get_worksheet(sheet_title, sheet_name)
        
        print(f"Reading data from worksheet '{sheet_name}' in spreadsheet '{sheet_title}'...")
        roster_data = worksheet.get_all_values()
        
        header_row_index = -1
        for i, row in enumerate(roster_data):
            if row and row[0] == 'Day':
                header_row_index = i
                break
        
        if header_row_index == -1:
            raise ValueError("Could not find header row in the worksheet.")

        roster_rows = roster_data[header_row_index + 1:]

        shift_times = {
            'Morning shift': {'start': 9, 'end': 18},
            'Afternoon shift': {'start': 12, 'end': 20},
            'Night shift': {'start': 18, 'end': 33}
        }

        days_of_week = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
        print("Importing events to Google Calendar...")
        for row in roster_rows:
            if not row or row[0] not in days_of_week:
                break
            if not row or not row[1]:
                continue
            
            try:
                date = datetime.strptime(row[1], '%d-%m-%Y')
            except ValueError:
                print(f"Skipping row with invalid date format: {row[1]}")
                continue

            self._create_events_for_shift(row[2], date, 'Morning shift', shift_times['Morning shift'])
            self._create_events_for_shift(row[3], date, 'Afternoon shift', shift_times['Afternoon shift'])
            self._create_events_for_shift(row[4], date, 'Night shift', shift_times['Night shift'])

        print("Calendar import complete.")

    def _create_events_for_shift(self, shift_cell: str, date: datetime, summary: str, hours: dict):
        consultant_initials = [c.strip() for c in shift_cell.split('/') if c.strip()]
        for initial in consultant_initials:
            if initial == 'BG':
                continue

            consultant = self._get_consultant_by_initial(initial)
            if consultant:
                self._create_or_update_calendar_event(consultant, summary, date, hours)
            else:
                print(f"Warning: Consultant with initial '{initial}' not found in the consultant map.")

    def _get_consultant_by_initial(self, initial: str) -> Consultant | None:
        for name, data in self.consultant_map.items():
            if data['initial'] == initial:
                return Consultant(name=name, **data)
        return None

    def _create_or_update_calendar_event(self, consultant: Consultant, summary: str, date: datetime, hours: dict):
        start_time = date + timedelta(hours=hours['start'])
        end_time = date + timedelta(hours=hours['end'])
        event_body = {
            'summary': summary,
            'start': {'dateTime': start_time.isoformat(), 'timeZone': 'Asia/Kolkata'},
            'end': {'dateTime': end_time.isoformat(), 'timeZone': 'Asia/Kolkata'}
        }

        existing_events = self.google_service.list_calendar_events(
            calendar_id=consultant.calendarId,
            start_time=(date + timedelta(hours=1)).isoformat() + 'Z',
            end_time=(date + timedelta(days=1)).isoformat() + 'Z',
            query=summary
        )

        if existing_events:
            event_id = existing_events[0]['id']
            print(f"Updating event for {consultant.name} ({summary}) on {date.strftime('%Y-%m-%d')}")
            self.google_service.update_calendar_event(consultant.calendarId, event_id, event_body)
        else:
            print(f"Creating event for {consultant.name} ({summary}) on {date.strftime('%Y-%m-%d')}")
            self.google_service.add_calendar_event(consultant.calendarId, event_body)

def main():
    """Main function to run the script."""
    consultant_map = {
        "Mittal": {"initial": "MT", "calendarId": 'primary', "sharees": ['dhyanesh.damania@gmail.com', 'gunsnroses128@gmail.com']},
        "Amirtha": {"initial": "AM", "calendarId": 'dd2a6c96f10e133dff18f3f7cb4994efd0068c472228d1247b5075ba1d6894c1@group.calendar.google.com', "sharees": ['dhyanesh.damania@gmail.com', 'amirthavarsheni@gmail.com']}
    }

    parser = argparse.ArgumentParser(description='Import roster from Google Sheet to Google Calendar.')
    parser.add_argument('-y', '--year', type=int, default=datetime.now().year, help='The year of the roster.')
    parser.add_argument('-m', '--month', type=int, default=datetime.now().month, help='The month of the roster.')
    parser.add_argument('--sheet-name', type=str, default='Sheet1', help='Name of the worksheet to import from.')
    args = parser.parse_args()

    try:
        google_service = GoogleServiceProvider('your_service_account_file.json')
        importer = RosterImporter(google_service, consultant_map)
        importer.import_roster_to_calendar(args.year, args.month, args.sheet_name)

    except (FileNotFoundError, ValueError) as e:
        print(f"Error: {e}")
        exit(1)

if __name__ == '__main__':
    main()