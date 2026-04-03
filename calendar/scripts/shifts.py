#!/opt/homebrew/bin/python3

import gspread
from google.oauth2.service_account import Credentials
from datetime import datetime, timedelta
from googleapiclient.discovery import build
import calendar

class Consultant:
    def __init__(self, name, calendarId, sharees):
        self.name = name
        self.calendarId = calendarId
        self.sharees = sharees

def share_calendar(calendar_service, calendar_id, email_addresses):
    """Shares the calendar with the specified email addresses.

    Args:
        calendar_service: The Calendar API service object.
        calendar_id: The ID of the calendar.
        email_addresses: A list of email addresses to share with.
    """
    for email in email_addresses:
        rule = {
            'scope': {
                'type': 'user',
                'value': email,
            },
            'role': 'owner'
        }
        created_rule = calendar_service.acl().insert(
            calendarId=calendar_id, body=rule
        ).execute()
        print(f"Calendar shared with {email} (Rule ID: {created_rule.get('id')})")

def create_shift_schedule(client, consultant, month, year):
    # Create a new Google Sheet
    sheet = client.create('Shift Schedule for %s %s %d' % (consultant.name, calendar.month_name[month], year))
    worksheet = sheet.sheet1

    # Header row
    worksheet.append_row(['Date', 'Morning Shift', 'Evening Shift', 'Night Shift'])

    # Populate the schedule
    first_day = datetime(year, month, 1)
    last_day = datetime(year, month, calendar.monthrange(year, month)[1])
    for day in range(1, (last_day - first_day).days + 2):
        date = first_day + timedelta(days=day-1)
        formatted_date = date.strftime('%Y-%m-%d')

        all_shifts = input(f"Enter shifts on {formatted_date}? (M/E/N/X): ")
        shifts = all_shifts.split(',')

        # Append the row to the sheet
        morning_shift = 'y' if "M" in shifts else 'n'
        evening_shift = 'y' if "E" in shifts else 'n'
        night_shift = 'y' if "N" in shifts else 'n'
        worksheet.append_row([formatted_date, morning_shift, evening_shift, night_shift])

    drive_service = build('drive', 'v3', credentials=creds)
    user_email = "dhyanesh.damania@gmail.com"
    permission = {
        'type': 'user',
        'role': 'writer',
        'emailAddress': user_email
    }

    # Create the permission using the Drive API
    request = drive_service.permissions().create(
        fileId=sheet.id,
        body=permission,
        fields='id'
    )
    response = request.execute()

    print(f"Access granted to {user_email} for spreadsheet {sheet.id} (Permission ID: {response.get('id')})")
    return worksheet

def import_to_calendar(calendar_service, consultant, worksheet):
    for row in worksheet.get_all_values()[1:]:
        date = datetime.strptime(row[0], '%Y-%m-%d')
        if row[1] == 'y':
            event = {
                'summary': 'Morning Shift',
                'start': {
                    'dateTime': (date + timedelta(hours=8)).strftime('%Y-%m-%dT%H:%M:%S%z'),
                    'timeZone': 'Asia/Kolkata'  # Replace with your timezone
                },
                'end': {
                    'dateTime': (date + timedelta(hours=16)).strftime('%Y-%m-%dT%H:%M:%S%z'),
                    'timeZone': 'Asia/Kolkata'
                }
            }
            calendar_service.events().insert(calendarId=consultant.calendarId, body=event).execute()
        if row[2] == 'y':
            event = {
                'summary': 'Evening Shift',
                'start': {
                    'dateTime': (date + timedelta(hours=14)).strftime('%Y-%m-%dT%H:%M:%S%z'),
                    'timeZone': 'Asia/Kolkata'  # Replace with your timezone
                },
                'end': {
                    'dateTime': (date + timedelta(hours=21)).strftime('%Y-%m-%dT%H:%M:%S%z'),
                    'timeZone': 'Asia/Kolkata'
                }
            }
            calendar_service.events().insert(calendarId=consultant.calendarId, body=event).execute()
        if row[3] == 'y':
            event = {
                'summary': 'Night Shift',
                'start': {
                    'dateTime': (date + timedelta(hours=20)).strftime('%Y-%m-%dT%H:%M:%S%z'),
                    'timeZone': 'Asia/Kolkata'  # Replace with your timezone
                },
                'end': {
                    'dateTime': (date + timedelta(hours=32)).strftime('%Y-%m-%dT%H:%M:%S%z'),
                    'timeZone': 'Asia/Kolkata'
                }
            }
            calendar_service.events().insert(calendarId=consultant.calendarId, body=event).execute()


# Get user input for month and year
consultant_name = input("Enter consultant name: ")
if consultant_name == "Mittal":
    consultant = Consultant(name="Mittal", calendarId='primary', sharees=['dhyanesh.damania@gmail.com', 'gunsnroses128@gmail.com'])
elif consultant_name == "Amirtha":
    consultant = Consultant(name="Amirtha", calendarId='dd2a6c96f10e133dff18f3f7cb4994efd0068c472228d1247b5075ba1d6894c1@group.calendar.google.com', sharees=['dhyanesh.damania@gmail.com', 'amirthavarsheni@gmail.com'])
else:
    exit()
month = int(input("Enter the month: "))
year = int(input("Enter the year: "))

creds = Credentials.from_service_account_file('your_service_account_file.json',
                                              scopes=['https://spreadsheets.google.com/feeds',
                                                      'https://www.googleapis.com/auth/drive',
                                                      'https://www.googleapis.com/auth/calendar'])
client = gspread.authorize(creds)

create = input("Do you want to create the schedule? (y/n): ")
if create == 'y':
    worksheet = create_shift_schedule(client, consultant, month, year)

# Authenticate to Google Calendar API
calendar_service = build('calendar', 'v3', credentials=creds)

should_import = input("Do you want to import these events to Google Calendar? (y/n): ")
if should_import == 'y':
    if create != 'y':
        key = input("Enter spreadsheet key: ")
        sheet = client.open_by_key(key)
        worksheet = sheet.sheet1
    import_to_calendar(calendar_service, consultant, worksheet)

share = input("Do you want to share the calendar? (y/n): ")
if share == 'y':
    share_calendar(calendar_service, consultant.calendarId, consultant.sharees)
