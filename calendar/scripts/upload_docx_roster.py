import sys
import re
from html.parser import HTMLParser
from datetime import datetime
import gspread
from import_roster_to_calendar import GoogleServiceProvider, RosterImporter

class RosterHTMLParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.in_table = False
        self.in_row = False
        self.in_cell = False
        self.rows = []
        self.current_row = []
        self.current_cell_text = []
        self.table_count = 0

    def handle_starttag(self, tag, attrs):
        if tag == 'table':
            self.table_count += 1
            if self.table_count == 1: # Assuming the first table is the roster
                self.in_table = True
        elif tag == 'tr' and self.in_table:
            self.in_row = True
            self.current_row = []
        elif tag == 'td' and self.in_row:
            self.in_cell = True
            self.current_cell_text = []

    def handle_endtag(self, tag):
        if tag == 'table':
            self.in_table = False
        elif tag == 'tr' and self.in_table:
            self.in_row = False
            if self.current_row:
                self.rows.append(self.current_row)
        elif tag == 'td' and self.in_row:
            self.in_cell = False
            self.current_row.append(" ".join(self.current_cell_text).strip())

    def handle_data(self, data):
        if self.in_cell:
            self.current_cell_text.append(data.strip())

def parse_html_roster(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        html_content = f.read()

    parser = RosterHTMLParser()
    parser.feed(html_content)
    
    # Filter out empty rows or header rows if needed
    # The first row in HTML is DATE, MORNING, NOON, NIGHT
    # We want to skip it or verify it.
    
    parsed_data = []
    
    for row in parser.rows:
        if not row: continue
        if "DATE" in row[0].upper(): continue # Skip header
        
        # Row format: [Date+Day, Morning, Noon, Night]
        # Example cell 0: "01/02/2026 Sunday"
        
        date_day_cell = row[0]
        # Extract date and day
        # Pattern: DD/MM/YYYY or DD/MM
        
        date_match = re.search(r'(\d{1,2}/\d{1,2}(?:/\d{4})?)', date_day_cell)
        if not date_match:
            continue
            
        date_str = date_match.group(1)
        
        # Clean up date string
        if date_str.count('/') == 1:
             # append year if missing. Assuming 2026 based on filename/context or current year
             date_str += "/2026"
             
        try:
            date_obj = datetime.strptime(date_str, "%d/%m/%Y")
            formatted_date = date_obj.strftime("%d-%m-%Y")
            day_str = date_obj.strftime("%a") # Mon, Tue, etc.
        except ValueError:
            print(f"Skipping invalid date: {date_str}")
            continue

        # Clean up shifts
        # Replace newlines or spaces with '/' if needed, but the HTML parser joins with space
        # The input seems to be like "MH/PK/SB" already.
        # But sometimes "BG/MH/MNS/SJ"
        
        morning = row[1].replace('\n', '').strip()
        noon = row[2].replace('\n', '').strip()
        night = row[3].replace('\n', '').strip()
        
        parsed_data.append([day_str, formatted_date, morning, noon, night])
        
    return parsed_data

def upload_and_sync(html_file, year, month):
    print(f"Parsing {html_file}...")
    roster_data = parse_html_roster(html_file)
    
    if not roster_data:
        print("No roster data found.")
        return

    print(f"Found {len(roster_data)} shifts.")

    # Authenticate
    google_service = GoogleServiceProvider('your_service_account_file.json')
    
    sheet_title = f"Roster {datetime(year, month, 1).strftime('%B %Y')}"
    
    # Check if sheet exists, if not create
    try:
        sheet = google_service.sheets_client.open(sheet_title)
        print(f"Opened existing spreadsheet: {sheet_title}")
    except gspread.exceptions.SpreadsheetNotFound:
        print(f"Creating new spreadsheet: {sheet_title}")
        sheet = google_service.sheets_client.create(sheet_title)
        # Share with user
        google_service.drive_service.permissions().create(
            fileId=sheet.id,
            body={'type': 'user', 'role': 'writer', 'emailAddress': 'dhyanesh.damania@gmail.com'},
            fields='id'
        ).execute()

    # Get or create worksheet
    worksheet_name = "Sheet1"
    try:
        worksheet = sheet.worksheet(worksheet_name)
        worksheet.clear()
    except gspread.exceptions.WorksheetNotFound:
        worksheet = sheet.add_worksheet(title=worksheet_name, rows=100, cols=10)

    # Write header and data
    header = ['Day', 'Date', 'Morning shift', 'Afternoon shift', 'Night shift']
    worksheet.append_row(header)
    for row in roster_data:
        worksheet.append_row(row)
        
    print("Uploaded to Google Sheets.")
    
    # Sync to Calendar
    # Re-using the logic from import_roster_to_calendar
    # We need to reconstruct the consultant map as it's defined in main() of import_roster_to_calendar
    # Ideally we should extract it or redefine it.
    
    consultant_map = {
        "Mittal": {"initial": "MT", "calendarId": 'primary', "sharees": ['dhyanesh.damania@gmail.com', 'gunsnroses128@gmail.com']},
        # "Amirtha": {"initial": "AM", "calendarId": 'dd2a6c96f10e133dff18f3f7cb4994efd0068c472228d1247b5075ba1d6894c1@group.calendar.google.com', "sharees": ['dhyanesh.damania@gmail.com', 'amirthavarsheni@gmail.com']},
        # Add others if known or parsing will skip them (warning will be shown)
        # Based on initials in HTML: MH, PK, SB, SJ, SK, MJ, MNS, BG, PN
        # We only have mapping for MT and AM in the provided script.
        # I will use the map from import_roster_to_calendar.py
    }
    
    importer = RosterImporter(google_service, consultant_map)
    # We can pass the already modified worksheet? 
    # The importer method takes sheet name.
    
    importer.import_roster_to_calendar(year, month, worksheet_name)

if __name__ == "__main__":
    upload_and_sync("FEB 2026.html", 2026, 2)
