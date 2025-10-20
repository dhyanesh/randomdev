"""
This script generates a monthly duty roster for a team of consultants using the Google OR-Tools CP-SAT solver.

The script takes into account a set of hard and soft constraints to create a fair and balanced roster.

**Technologies:**
- Google OR-Tools CP-SAT Solver: For solving the constraint satisfaction problem.
- Python: The programming language used.

**Hard Constraints:**
1.  A consultant can work at most one shift per day.
2.  Morning shifts have 3 people, afternoon shifts have 1 person (on weekdays), and night shifts have 2 people.
3.  Specific consultants (AM and SJ) are exempt from afternoon shifts.
4.  Night shifts must have at least one senior consultant.
5.  A consultant cannot have a morning or afternoon shift the day after a night shift.
6.  Consultants' vacation requests are respected.
7.  One consultant (MH) has a fixed quota of 4 night shifts per month.
8.  Other consultants have a night shift quota of 5 to 7 nights per month.
9.  Consultants cannot have more than 4 consecutive days off.
10. Total monthly working hours for each consultant should be within 16 hours of their target (192, reduced by 8 hours for each day of CL).

**Soft Constraints (Objectives to Minimize):**
1.  **Weekend Fairness:** Minimize the difference in the number of weekend shifts worked among all consultants.
2.  **Working Hours Target:** Try to keep each consultant's total hours close to their target (192 adjusted for CL).
3.  **Night Shift Fairness:** Minimize the difference in the number of night shifts worked among consultants (excluding MH).

**Usage:**
The script is run from the command line with the year and month.

**Command:**
```bash
python roster_generator_cp.py -y <year> -m <month> [options]
```

**Arguments:**
- `-y`, `--year`: The year for the roster (e.g., 2025).
- `-m`, `--month`: The month for the roster (e.g., 9).
- `--export-gsheet`: Export the generated roster to a Google Sheet.
- `--share-email <email>`: Email address to share the Google Sheet with.
- `--force-regenerate`: Force regeneration of the roster, ignoring any cached version.

**Features:**
- **October 2025 Requests:** Specific leave and shift preferences for October 2025 are hardcoded.
- **Google Sheets Export:** Can create or update a Google Sheet with the roster and statistics.
- **Local Caching:** Caches the generated roster locally to speed up subsequent runs.
"""
from __future__ import print_function
from ortools.sat.python import cp_model
import calendar
from collections import namedtuple
import datetime
import argparse
import json
import gspread
from google.oauth2.service_account import Credentials
from pathlib import Path
from monthly_constraints.base import MonthlyConstraints
from monthly_constraints.october_2025 import October2025Constraints
from google.cloud import storage


def download_json_from_gcs(bucket_name, blob_name):
    """Downloads a JSON file from GCS and returns it as a dictionary."""
    try:
        storage_client = storage.Client()
        bucket = storage_client.bucket(bucket_name)
        blob = bucket.blob(blob_name)
        data = blob.download_as_text()
        return json.loads(data)
    except Exception as e:
        print(f"Error downloading JSON from GCS (gs://{bucket_name}/{blob_name}): {e}")
        return None

def upload_json_to_gcs(bucket_name, blob_name, data):
    """Uploads a dictionary as a JSON file to GCS."""
    try:
        storage_client = storage.Client()
        bucket = storage_client.bucket(bucket_name)
        blob = bucket.blob(blob_name)
        blob.upload_from_string(json.dumps(data, indent=4), content_type='application/json')
        print(f"Successfully uploaded to gs://{bucket_name}/{blob_name}")
    except Exception as e:
        print(f"Error uploading JSON to GCS: {e}")


# Based on the provided PDF and constraints.
Consultant = namedtuple('Consultant', ['name', 'initial', 'is_senior', 'gender'])

CONSULTANTS = [
    Consultant('DR. PRAVEEN. S', 'PS', True, 'Male'),
    Consultant('DR. MOHAN', 'MH', True, 'Male'),
    Consultant('DR. PRAVEEN KUMAR', 'PK', False, 'Male'),
    Consultant('DR. SANTOSH', 'SK', True, 'Male'),
    Consultant('DR. SHIVA SHANKAR.B', 'SB', False, 'Male'),
    Consultant('DR. AMRITHA', 'AM', True, 'Female'),
    Consultant('DR. MITTAL', 'MT', True, 'Male'),
    Consultant('DR. MANJUNATH', 'MJ', False, 'Male'),
    Consultant('DR. SIMMY JOHN', 'SJ', False, 'Female'),
    Consultant('DR. MANJUNATH N S', 'MNS', True, 'Male'),
]

def get_constraints_handler(year, month):
    if year == 2025 and month == 10:
        return October2025Constraints()
    return MonthlyConstraints()

def generate_roster_cp(year, month, fixed_roster=None):
    """
    Generates a duty roster for the given year and month using the CP-SAT solver.
    """
    num_days = calendar.monthrange(year, month)[1]
    all_days = range(1, num_days + 1)
    all_consultants = range(len(CONSULTANTS))
    all_shifts = range(3) # 0: Morning, 1: Afternoon, 2: Night

    model = cp_model.CpModel()

    # --- Create variables ---
    shifts = {}
    for c in all_consultants:
        for d in all_days:
            for s in all_shifts:
                shifts[(c, d, s)] = model.NewBoolVar(f'shift_c{c}_d{d}_s{s}')

    # --- Apply fixed roster constraints ---
    if fixed_roster:
        for day, day_shifts in fixed_roster.items():
            d = int(day)
            for shift_name, consultants in day_shifts.items():
                s = ['morning', 'afternoon', 'night'].index(shift_name)
                for consultant_initial in consultants:
                    c_idx = [i for i, c in enumerate(CONSULTANTS) if c.initial == consultant_initial][0]
                    model.Add(shifts[(c_idx, d, s)] == 1)

    # --- Apply constraints ---
    constraints_handler = get_constraints_handler(year, month)
    cl_days_per_consultant, preference_score = constraints_handler.apply_all_constraints(
        model, shifts, CONSULTANTS, all_days, all_shifts, year, month
    )

    # --- Define Soft Constraints (Objectives) ---

    # 1. Weekend Distribution Preference
    weekend_days = [d for d in all_days if datetime.date(year, month, d).weekday() >= 5]
    weekend_shifts_per_consultant = [sum(shifts[(c, d, s)] for d in weekend_days for s in all_shifts) for c in all_consultants]
    min_weekend_shifts = model.NewIntVar(0, num_days, 'min_weekend_shifts')
    max_weekend_shifts = model.NewIntVar(0, num_days, 'max_weekend_shifts')
    model.AddMinEquality(min_weekend_shifts, weekend_shifts_per_consultant)
    model.AddMaxEquality(max_weekend_shifts, weekend_shifts_per_consultant)
    weekend_fairness_diff = max_weekend_shifts - min_weekend_shifts

    # 2. Working Hours Target
    total_hours_deviations = []
    for c_idx, c in enumerate(CONSULTANTS):
        consultant_initial = CONSULTANTS[c_idx].initial
        cl_days = cl_days_per_consultant.get(consultant_initial, 0)
        target_hours = 192 - (cl_days * 8)

        total_hours_expr = sum(shifts[(c_idx, d, 0)] * 9 + shifts[(c_idx, d, 1)] * 8 + shifts[(c_idx, d, 2)] * 15 for d in all_days)
        model.Add(total_hours_expr <= target_hours) # Hard constraint
        model.Add(total_hours_expr >= target_hours - 16) # Hard constraint with wider window
        
        # Soft constraint to be close to target
        deviation = model.NewIntVar(0, 100, f'deviation_c{c_idx}')
        model.AddAbsEquality(deviation, total_hours_expr - target_hours)
        total_hours_deviations.append(deviation)

    total_hours_deviation = model.NewIntVar(0, 1000, 'total_hours_deviation')
    model.Add(total_hours_deviation == sum(total_hours_deviations))

    # 3. Night Shift Fairness Preference
    fair_night_consultants = [i for i, c in enumerate(CONSULTANTS) if c.initial != 'MH']
    night_shifts_per_consultant = [sum(shifts[(c, d, 2)] for d in all_days) for c in fair_night_consultants]
    min_night_shifts = model.NewIntVar(0, num_days, 'min_night_shifts')
    max_night_shifts = model.NewIntVar(0, num_days, 'max_night_shifts')
    model.AddMinEquality(min_night_shifts, night_shifts_per_consultant)
    model.AddMaxEquality(max_night_shifts, night_shifts_per_consultant)
    nights_fairness_diff = max_night_shifts - min_night_shifts

    # 4. Consecutive Night Shift Preference
    consecutive_night_vars = []
    for c in all_consultants:
        for d in all_days[:-1]:
            lit1 = shifts[(c, d, 2)]
            lit2 = shifts[(c, d + 1, 2)]
            consecutive = model.NewBoolVar(f'consecutive_c{c}_d{d}')
            model.AddBoolAnd([lit1, lit2]).OnlyEnforceIf(consecutive)
            model.AddBoolOr([lit1.Not(), lit2.Not()]).OnlyEnforceIf(consecutive.Not())
            consecutive_night_vars.append(consecutive)

    # --- Set Objective Function ---
    model.Minimize(weekend_fairness_diff * 4 + total_hours_deviation + nights_fairness_diff * 4 - preference_score + sum(consecutive_night_vars) * 10)

    # --- Solve the model ---
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        roster = {day: {'morning': [], 'afternoon': [], 'night': []} for day in all_days}
        for d in all_days:
            for c_idx, c in enumerate(CONSULTANTS):
                if solver.Value(shifts[(c_idx, d, 0)]) == 1:
                    roster[d]['morning'].append(c.initial)
                if solver.Value(shifts[(c_idx, d, 1)]) == 1:
                    roster[d]['afternoon'].append(c.initial)
                if solver.Value(shifts[(c_idx, d, 2)]) == 1:
                    roster[d]['night'].append(c.initial)
        return roster, cl_days_per_consultant
    else:
        return None, None

def print_roster(roster, year, month):
    if roster is None:
        print("No solution found for the given constraints.")
        return

    print("DAY        | DATE       | GENERAL (9am-6pm)   | AFTERNOON (12pm-8pm) | NIGHT (6pm-9am)")
    print("-" * 82)
    for day, shifts in roster.items():
        date = datetime.date(year, month, day)
        day_name = date.strftime('%a')
        
        morning_shifts = shifts['morning'][:] # Make a copy
        if date.weekday() < 6: # Not Sunday
            morning_shifts.insert(0, 'BG')

        date_str = f"{day}-{month}-{year}"
        morning_str = '/'.join(morning_shifts)
        afternoon_str = '/'.join(shifts['afternoon'])
        night_str = '/'.join(shifts['night'])
        print(f"{day_name:<10} | {date_str:<10} | {morning_str:<19} | {afternoon_str:<20} | {night_str}")

def get_statistics(roster, year, month, cl_days_per_consultant):
    """Calculates shift statistics and returns them as a list of lists."""
    if roster is None:
        return None

    stats_header = [ 'Consultant', 'General', 'Afternoon', 'Night', 'Total Hours']
    stats_rows = [stats_header]

    for consultant in CONSULTANTS:
        general_shifts = 0
        afternoon_shifts = 0
        night_shifts = 0

        for day_roster in roster.values():
            if consultant.initial in day_roster['morning']:
                general_shifts += 1
            if consultant.initial in day_roster['afternoon']:
                afternoon_shifts += 1
            if consultant.initial in day_roster['night']:
                night_shifts += 1
        
        total_hours = (general_shifts * 9) + (afternoon_shifts * 8) + (night_shifts * 15)
        
        cl_days = cl_days_per_consultant.get(consultant.initial, 0)
        hours_str = f"{total_hours}"
        if cl_days > 0:
            hours_str += f" ({cl_days} CL)"
            
        stats_rows.append([consultant.name, general_shifts, afternoon_shifts, night_shifts, hours_str])
    
    # Add HOD stats
    num_days = calendar.monthrange(year, month)[1]
    hod_mornings = sum(1 for i in range(1, num_days + 1) if datetime.date(year, month, i).weekday() < 6)
    hod_hours = hod_mornings * 5
    stats_rows.append(['Dr. BHARGAVA', hod_mornings, 0, 0, hod_hours])
    
    return stats_rows

def print_statistics_from_data(stats_data):
    """Prints statistics from a data structure."""
    if not stats_data:
        return
    
    print("\n--- Shift Statistics ---")
    header = stats_data[0]
    rows = stats_data[1:]
    
    print(f"{header[0]:<20} | {header[1]:<10} | {header[2]:<10} | {header[3]:<10} | {header[4]:<10}")
    print("-" * 75)
    for row in rows:
        print(f"{str(row[0]):<20} | {str(row[1]):<10} | {str(row[2]):<10} | {str(row[3]):<10} | {str(row[4]):<10}")

def export_to_gsheet(roster, stats_data, year, month, service_account_file='your_service_account_file.json', share_email=None, worksheet_name='Sheet1'):
    """Exports the roster and statistics to a Google Sheet."""
    
    print("\nConnecting to Google Sheets...")
    
    # 1. Authentication
    scopes = [
        'https://spreadsheets.google.com/feeds',
        'https://www.googleapis.com/auth/drive'
    ]
    try:
        creds = Credentials.from_service_account_file(service_account_file, scopes=scopes)
        client = gspread.authorize(creds)
    except FileNotFoundError:
        print(f"Error: Service account file '{service_account_file}' not found.")
        print("Please make sure the file exists and is in the correct path.")
        return
    except Exception as e:
        print(f"An error occurred during authentication: {e}")
        return

    # 2. Open or Create Spreadsheet
    sheet_title = f"Roster {calendar.month_name[month]} {year}"
    try:
        spreadsheet = client.open(sheet_title)
        print(f"Found existing spreadsheet: '{sheet_title}'")
    except gspread.exceptions.SpreadsheetNotFound:
        print(f"Creating new spreadsheet: '{sheet_title}'")
        spreadsheet = client.create(sheet_title)
        if share_email:
            print(f"Sharing sheet with {share_email}...")
            spreadsheet.share(share_email, perm_type='user', role='writer')

    try:
        worksheet = spreadsheet.worksheet(worksheet_name)
        worksheet.clear()
        print(f"Found existing worksheet: '{worksheet_name}'. Clearing its content.")
    except gspread.exceptions.WorksheetNotFound:
        worksheet = spreadsheet.add_worksheet(title=worksheet_name, rows="100", cols="20")
        print(f"Created new worksheet: '{worksheet_name}'.")

    # 3. Format and Write Roster Data
    print("Formatting and writing roster data...")
    roster_header = ["Day", "Date", "General (9am-6pm)", "Afternoon (12pm-8pm)", "Night (6pm-9am)"]
    roster_rows = [roster_header]
    
    for day, shifts in roster.items():
        date = datetime.date(year, month, day)
        day_name = date.strftime('%a')
        date_str = f"{day}-{month}-{year}"
        
        morning_shifts = shifts['morning'][:] # Make a copy
        if date.weekday() < 6: # Not Sunday
            morning_shifts.insert(0, 'BG')

        morning_str = '/'.join(morning_shifts)
        afternoon_str = '/'.join(shifts['afternoon'])
        night_str = '/'.join(shifts['night'])
        roster_rows.append([day_name, date_str, morning_str, afternoon_str, night_str])
    
    worksheet.update(roster_rows, 'A1')
    worksheet.format('A1:E1', {'textFormat': {'bold': True}})

    # 4. Add statistics
    if stats_data:
        print("Formatting and writing statistics data...")
        stats_start_row = len(roster_rows) + 2 # Leave one blank row
        worksheet.update(stats_data, f'A{stats_start_row}')
        worksheet.format(f'A{stats_start_row}:E{stats_start_row}', {'textFormat': {'bold': True}})

    
    print("-" * 30)
    print("Export to Google Sheets successful!")
    print(f"Sheet URL: {spreadsheet.url}")
    print("-" * 30)

def main(argv=None):
    parser = argparse.ArgumentParser(description='Generate a duty roster for consultants.')
    parser.add_argument('-y', '--year', type=int, default=datetime.datetime.now().year, help='The year for the roster.')
    parser.add_argument('-m', '--month', type=int, default=datetime.datetime.now().month, help='The month for the roster.')
    parser.add_argument('--export-gsheet', action='store_true', help='Export the roster to Google Sheets.')
    parser.add_argument('--share-email', type=str, help='Email address to share the Google Sheet with.')
    parser.add_argument('--force-regenerate', action='store_true', help='Force regeneration of the roster, ignoring any cached version.')
    parser.add_argument('--fixed-roster', type=str, help='GCS blob name for a JSON file with a fixed partial roster.')
    parser.add_argument('--sheet-name', type=str, default='Sheet1', help='Name of the worksheet to export to (e.g., Proposed).')
    args = parser.parse_args(argv)

    bucket_name = "trilife-duty-roster-files"
    cache_blob_name = f"{args.year}/{args.month}/roster.json"
    roster = None
    cl_days_per_consultant = {}

    if not args.force_regenerate:
        print(f"Loading roster from GCS: gs://{bucket_name}/{cache_blob_name}")
        cached_roster = download_json_from_gcs(bucket_name, cache_blob_name)
        if cached_roster:
            roster = {int(k): v for k, v in cached_roster.items()}
            # We need to get the cl_days from the handler
            constraints_handler = get_constraints_handler(args.year, args.month)
            cl_days_per_consultant = constraints_handler.get_cl_days()
        else:
            print("No cache file found in GCS.")

    if roster is None:
        print("Generating new roster...")
        fixed_roster_data = None
        if args.fixed_roster:
            fixed_roster_blob_name = f"{args.year}/{args.month}/fixed_roster.json"
            print(f"Loading fixed roster from GCS: gs://{bucket_name}/{fixed_roster_blob_name}")
            fixed_roster_data = download_json_from_gcs(bucket_name, fixed_roster_blob_name)

        roster, cl_days_per_consultant = generate_roster_cp(args.year, args.month, fixed_roster_data)
        
        if roster:
            print(f"Saving roster to GCS: gs://{bucket_name}/{cache_blob_name}")
            upload_json_to_gcs(bucket_name, cache_blob_name, roster)

    if roster:
        print_roster(roster, args.year, args.month)
        print() # Add a blank line
        stats_data = get_statistics(roster, args.year, args.month, cl_days_per_consultant)
        print_statistics_from_data(stats_data)

        if args.export_gsheet:
            print("\nExporting to Google Sheets...")
            print("Please ensure 'your_service_account_file.json' is in the same directory.")
            export_to_gsheet(roster, stats_data, args.year, args.month, 
                             service_account_file='your_service_account_file.json', 
                             share_email=args.share_email, 
                             worksheet_name=args.sheet_name)
    else:
        print("Could not generate or load a roster.")

if __name__ == '__main__':
    main()