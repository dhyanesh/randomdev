import dateutil.parser
import gspread
from google.oauth2.service_account import Credentials
from datetime import datetime, timedelta
from googleapiclient.discovery import build
import calendar
import pandas as pd
import camelot
from pathlib import Path
import argparse

# --- Data Models ---

class Consultant:
    """Represents a consultant with their name, calendar details, and sharing preferences."""
    def __init__(self, name, calendarId, sharees):
        self.name = name
        self.calendarId = calendarId
        self.sharees = sharees

# --- Core Functions ---

def read_roster_from_pdf(pdf_path):
    """
    Reads shift data from all pages of a PDF file using Camelot and returns a consolidated DataFrame.
    
    Args:
        pdf_path (str): The file path to the roster PDF.
        
    Returns:
        pandas.DataFrame: A DataFrame containing the cleaned roster data.
    """
    if not Path(pdf_path).exists():
        print(f"Error: PDF file not found at '{pdf_path}'")
        exit()
        
    print(f"Reading PDF: {pdf_path}...")
    tables = camelot.read_pdf(pdf_path, pages='all', flavor='stream')

    if not tables:
        print("Error: No tables found in the PDF.")
        exit()

    roster_df = pd.concat([table.df for table in tables], ignore_index=True)
    roster_df_trimmed = roster_df.iloc[:, :4]

    roster_df_trimmed.columns = range(roster_df_trimmed.shape[1])
    roster_df_trimmed = roster_df_trimmed.reset_index(drop=True)

    print("Successfully processed the PDF roster.")
    return roster_df_trimmed

def create_shift_schedule_from_pdf(client, creds, consultant, year, roster_df, consultant_initial):
    """
    Creates a Google Sheet schedule from a roster DataFrame.

    Args:
        client: Authenticated gspread client.
        creds: Authenticated credentials.
        consultant (Consultant): The consultant for whom to generate the schedule.
        year (int): The roster year, used for date parsing.
        roster_df (pd.DataFrame): The DataFrame containing roster information.
        consultant_initial (str): The initial representing the consultant in the roster (e.g., 'MT').
        
    Returns:
        gspread.Worksheet: The newly created worksheet with the schedule.
    """
    month = None
    for date_str in roster_df.iloc[:, 0]:
        if date_str:
            try:
                month = dateutil.parser.parse(date_str).month
                break
            except (dateutil.parser.ParserError, TypeError):
                continue
    
    if month is None:
        print("Error: Could not determine the month from the roster.")
        exit()

    sheet_title = f'Shift Schedule for {consultant.name} {calendar.month_name[month]} {year}'
    print(f"Creating Google Sheet: '{sheet_title}'...")
    sheet = client.create(sheet_title)
    worksheet = sheet.sheet1

    worksheet.append_row(['Date', 'Morning Shift', 'Afternoon Shift', 'Night Shift'])

    for _, row in roster_df.iterrows():
        if not row.iloc[0]:
            continue
        
        try:
            date = dateutil.parser.parse(row.iloc[0], default=datetime(year, 1, 1))
        except (dateutil.parser.ParserError, TypeError):
            print(f"Warning: Skipping row with unparsable date '{row.iloc[0]}'")
            continue
        
        formatted_date = date.strftime('%Y-%m-%d')

        morning_shift = 'y' if consultant_initial in str(row.iloc[1]) else 'n'
        afternoon_shift = 'y' if consultant_initial in str(row.iloc[2]) else 'n'
        night_shift = 'y' if consultant_initial in str(row.iloc[3]) else 'n'
        
        if 'y' in [morning_shift, afternoon_shift, night_shift]:
            worksheet.append_row([formatted_date, morning_shift, afternoon_shift, night_shift])

    drive_service = build('drive', 'v3', credentials=creds)
    user_email = "dhyanesh.damania@gmail.com"
    permission = {'type': 'user', 'role': 'writer', 'emailAddress': user_email}
    drive_service.permissions().create(fileId=sheet.id, body=permission, fields='id').execute()

    print(f"Access granted to {user_email} for spreadsheet {sheet.id}")
    return worksheet

def import_to_calendar(calendar_service, consultant, worksheet):
    """Imports shifts from a Google Sheet to Google Calendar."""
    print("Importing events to Google Calendar...")
    for row in worksheet.get_all_values()[1:]:
        date = datetime.strptime(row[0], '%Y-%m-%d')
        
        shift_times = {
            'Morning Shift': {'start': 8, 'end': 17},
            'Afternoon Shift': {'start': 12, 'end': 20},
            'Night Shift': {'start': 17, 'end': 32}
        }
        
        if row[1] == 'y':
            event_body = _create_event_body('Morning Shift', date, shift_times['Morning Shift'])
            calendar_service.events().insert(calendarId=consultant.calendarId, body=event_body).execute()
        if row[2] == 'y':
            event_body = _create_event_body('Afternoon Shift', date, shift_times['Afternoon Shift'])
            calendar_service.events().insert(calendarId=consultant.calendarId, body=event_body).execute()
        if row[3] == 'y':
            event_body = _create_event_body('Night Shift', date, shift_times['Night Shift'])
            calendar_service.events().insert(calendarId=consultant.calendarId, body=event_body).execute()
    print("Calendar import complete.")

def _create_event_body(summary, date, hours):
    """Helper function to create a Google Calendar event dictionary."""
    return {
        'summary': summary,
        'start': {
            'dateTime': (date + timedelta(hours=hours['start'])).isoformat(),
            'timeZone': 'Asia/Kolkata'
        },
        'end': {
            'dateTime': (date + timedelta(hours=hours['end'])).isoformat(),
            'timeZone': 'Asia/Kolkata'
        }
    }

def share_calendar(calendar_service, calendar_id, email_addresses):
    """Shares the calendar with specified email addresses."""
    print(f"Sharing calendar '{calendar_id}'...")
    for email in email_addresses:
        rule = {'scope': {'type': 'user', 'value': email}, 'role': 'owner'}
        calendar_service.acl().insert(calendarId=calendar_id, body=rule).execute()
        print(f"-> Shared with {email} as owner.")

# --- Main Execution ---

def main():
    """Main function to run the script."""
    
    consultant_map = {
        "Mittal": {
            "initial": "MT", 
            "calendarId": 'primary', 
            "sharees": ['dhyanesh.damania@gmail.com', 'gunsnroses128@gmail.com']
        },
        "Amirtha": {
            "initial": "AM", 
            "calendarId": 'dd2a6c96f10e133dff18f3f7cb4994efd0068c472228d1247b5075ba1d6894c1@group.calendar.google.com', 
            "sharees": ['dhyanesh.damania@gmail.com', 'amirthavarsheni@gmail.com']
        }
    }

    parser = argparse.ArgumentParser(description='Automate Trilife shift scheduling.')
    parser.add_argument('consultant', choices=consultant_map.keys(), help='Consultant name')
    parser.add_argument('year', type=int, help='Roster year (e.g., 2025)')
    parser.add_argument('pdf_path', help='Path to the roster PDF file')
    parser.add_argument('--create-sheet', action='store_true', help='Create a new Google Sheet from the PDF')
    parser.add_argument('--import-calendar', action='store_true', help='Import events to Google Calendar')
    parser.add_argument('--sheet-key', help='Google Sheet key (if not creating a new sheet)')
    parser.add_argument('--share-calendar', action='store_true', help='Share the Google Calendar')
    args = parser.parse_args()

    config = consultant_map[args.consultant]
    consultant = Consultant(name=args.consultant, calendarId=config['calendarId'], sharees=config['sharees'])
    
    creds_file = 'your_service_account_file.json'
    scopes = [
        'https://spreadsheets.google.com/feeds',
        'https://www.googleapis.com/auth/drive',
        'https://www.googleapis.com/auth/calendar'
    ]
    if not Path(creds_file).exists():
        print(f"Error: Service account file '{creds_file}' not found.")
        exit()
        
    creds = Credentials.from_service_account_file(creds_file, scopes=scopes)
    client = gspread.authorize(creds)
    calendar_service = build('calendar', 'v3', credentials=creds)

    roster_df = read_roster_from_pdf(args.pdf_path.strip())
    
    worksheet = None
    if args.create_sheet:
        worksheet = create_shift_schedule_from_pdf(client, creds, consultant, args.year, roster_df, config['initial'])
    
    if args.import_calendar:
        if not worksheet:
            if not args.sheet_key:
                print("Error: --sheet-key is required when not creating a new sheet.")
                exit()
            try:
                sheet = client.open_by_key(args.sheet_key)
                worksheet = sheet.sheet1
            except gspread.exceptions.SpreadsheetNotFound:
                print("Error: Spreadsheet not found. Please check the key.")
                exit()
        import_to_calendar(calendar_service, consultant, worksheet)

    if args.share_calendar:
        share_calendar(calendar_service, consultant.calendarId, consultant.sharees)

if __name__ == '__main__':
    main()
