import json
import argparse
from datetime import datetime, timedelta
from pathlib import Path
from google.oauth2.service_account import Credentials
from googleapiclient.discovery import build

class GoogleCalendarService:
    def __init__(self, creds_file: str):
        scopes = ['https://www.googleapis.com/auth/calendar']
        if not Path(creds_file).exists():
            raise FileNotFoundError(f"Service account file '{creds_file}' not found.")
        self.creds = Credentials.from_service_account_file(creds_file, scopes=scopes)
        self.service = build('calendar', 'v3', credentials=self.creds)

    def add_event(self, calendar_id: str, summary: str, start_dt: datetime, end_dt: datetime):
        event = {
            'summary': summary,
            'start': {'dateTime': start_dt.isoformat(), 'timeZone': 'Asia/Kolkata'},
            'end': {'dateTime': end_dt.isoformat(), 'timeZone': 'Asia/Kolkata'}
        }
        print(f"Creating event: {summary} on {start_dt.strftime('%Y-%m-%d %H:%M')}")
        try:
            self.service.events().insert(calendarId=calendar_id, body=event).execute()
        except Exception as e:
            print(f"Failed to create event: {e}")

def import_roster(year: int, month: int, consultant: str, calendar_id: str):
    creds_file = 'your_service_account_file.json'
    roster_file = f'data/roster_{year}_{month:02d}.json'
    initial = consultant

    try:
        if not Path(roster_file).exists():
            raise FileNotFoundError(f"Roster file '{roster_file}' not found.")

        with open(roster_file, 'r') as f:
            roster_data = json.load(f)
        
        cal_service = GoogleCalendarService(creds_file)
        
        # Shift times
        # Morning: 9am-5pm
        # Afternoon: 12pm-8pm 
        # Night: 7pm to 9am next day
        
        for entry in roster_data:
            date_obj = datetime.strptime(entry['date'], '%Y-%m-%d')
            
            # Check Morning Shift
            if initial in entry['morning'].split('/'):
                start = date_obj.replace(hour=9, minute=0)
                end = date_obj.replace(hour=17, minute=0)
                cal_service.add_event(calendar_id, "Morning Shift", start, end)
            
            # Check Afternoon (Noon) Shift
            if initial in entry['afternoon'].split('/'):
                start = date_obj.replace(hour=12, minute=0)
                end = date_obj.replace(hour=20, minute=0)
                cal_service.add_event(calendar_id, "Afternoon Shift", start, end)
                
            # Check Night Shift
            if initial in entry['night'].split('/'):
                start = date_obj.replace(hour=19, minute=0)
                end = (date_obj + timedelta(days=1)).replace(hour=9, minute=0)
                cal_service.add_event(calendar_id, "Night Shift", start, end)

        print(f"Import for {consultant} for {year}-{month:02d} complete.")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Import manual roster from JSON to Google Calendar")
    parser.add_argument("-y", "--year", type=int, required=True, help="Year of the roster")
    parser.add_argument("-m", "--month", type=int, required=True, help="Month of the roster")
    parser.add_argument("-c", "--consultant", type=str, default="MT", help="Consultant initials (default: MT)")
    parser.add_argument("--calendar-id", type=str, default="primary", help="Google Calendar ID (default: primary)")
    
    args = parser.parse_args()
    import_roster(args.year, args.month, args.consultant, args.calendar_id)
