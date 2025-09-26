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

**Soft Constraints (Objectives to Minimize):**
1.  **Weekend Fairness:** Minimize the difference in the number of weekend shifts worked among all consultants.
2.  **Working Hours Fairness:** Minimize the difference in total monthly working hours among all consultants.
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

def apply_october_2025_requests(model, shifts, consultants, all_days, all_shifts, year, month):
    """
    Applies the specific requests for October 2025.
    """
    if year != 2025 or month != 10:
        return {c.initial: 0 for c in consultants}, model.NewIntVar(0, 0, 'empty_pref')

    consultant_map = {c.initial: i for i, c in enumerate(consultants)}
    ps_idx = consultant_map['PS']
    mh_idx = consultant_map['MH']
    pk_idx = consultant_map['PK']
    sk_idx = consultant_map['SK']
    sb_idx = consultant_map['SB']
    am_idx = consultant_map['AM']
    mt_idx = consultant_map['MT']
    mj_idx = consultant_map['MJ']
    sj_idx = consultant_map['SJ']

    cl_days_per_consultant = {c.initial: 0 for c in consultants}
    
    # --- Hard Constraints ("need") ---

    # PK needs leave on 20, 25, 26
    for d in [20, 25, 26]:
        for s in all_shifts:
            model.Add(shifts[(pk_idx, d, s)] == 0)

    # PK needs 4 days CL from Oct 2-5
    cl_days_per_consultant['PK'] = 4
    for d in [2, 3, 4, 5]:
        for s in all_shifts:
            model.Add(shifts[(pk_idx, d, s)] == 0)

    # SB needs leave on 1, 2, 3, 25, 26
    for d in [1, 2, 3, 25, 26]:
        for s in all_shifts:
            model.Add(shifts[(sb_idx, d, s)] == 0)

    # AM needs leave on 1, 2, 3, 6, 7, 8, 13, 14, 15, 27, 28, 29
    for d in [1, 2, 3, 6, 7, 8, 13, 14, 15, 27, 28, 29]:
        for s in all_shifts:
            model.Add(shifts[(am_idx, d, s)] == 0)

    # MT needs to be off Oct 1, 2, 3. Taking 2 CLs.
    cl_days_per_consultant['MT'] = 2
    for d in [1, 2, 3]:
        for s in all_shifts:
            model.Add(shifts[(mt_idx, d, s)] == 0)
    
    # MT No morning shift on Oct 14th
    model.Add(shifts[(mt_idx, 14, 0)] == 0)

    # MJ needs leave on 20, 21, 22, 23
    for d in [20, 21, 22, 23]:
        for s in all_shifts:
            model.Add(shifts[(mj_idx, d, s)] == 0)

    # SJ needs leave on 11, 12, 13
    for d in [11, 12, 13]:
        for s in all_shifts:
            model.Add(shifts[(sj_idx, d, s)] == 0)

    # SJ can do two noon shifts.
    model.Add(sum(shifts[(sj_idx, d, 1)] for d in all_days) <= 2)

    # Mittal and Amritha nights constraint
    model.Add(sum(shifts[(mt_idx, d, 2)] for d in all_days) == 6)
    model.Add(sum(shifts[(am_idx, d, 2)] for d in all_days) == 6)

    # Mohan no afternoon shifts
    model.Add(sum(shifts[(mh_idx, d, 1)] for d in all_days) == 0)

    # --- Soft Constraints ("prefer") ---
    positive_preferences = []
    negative_preferences = []

    # PS
    positive_preferences.extend([shifts[(ps_idx, d, 2)] for d in [7, 10, 11, 13, 18, 25, 31]])
    positive_preferences.extend([shifts[(ps_idx, d, s)] for d in [3, 6, 9, 15, 21, 27, 30] for s in [0, 1]])
    positive_preferences.extend([shifts[(ps_idx, d, 0)] for d in [17, 23]])

    # MH
    positive_preferences.extend([shifts[(mh_idx, d, 2)] for d in [2, 7, 12, 21]])
    positive_preferences.extend([shifts[(mh_idx, d, 0)] for d in [5, 6, 9, 10, 14, 15, 16, 17, 20, 23, 27, 28, 29, 30]])

    # SK
    saturdays = [d for d in all_days if datetime.date(year, month, d).weekday() == 5]
    sundays = [d for d in all_days if datetime.date(year, month, d).weekday() == 6]
    weekdays = [d for d in all_days if datetime.date(year, month, d).weekday() < 5]
    weekends = saturdays + sundays
    # Prefer morning shifts on weekends
    positive_preferences.extend([shifts[(sk_idx, d, 0)] for d in weekends])
    # Prefer afternoon shifts on weekdays
    positive_preferences.extend([shifts[(sk_idx, d, 1)] for d in weekdays])
    # Avoid night shifts on weekends
    negative_preferences.extend([shifts[(sk_idx, d, 2)] for d in weekends])

    # SB
    positive_preferences.append(shifts[(sb_idx, 29, 0)])
    positive_preferences.append(shifts[(sb_idx, 30, 0)])

    # AM
    positive_preferences.extend([shifts[(am_idx, d, 0)] for d in [4, 19, 20]])
    positive_preferences.extend([shifts[(am_idx, d, 2)] for d in [5, 12]])

    # MJ
    negative_preferences.extend([shifts[(mj_idx, 1, s)] for s in all_shifts])
    negative_preferences.extend([shifts[(mj_idx, 4, s)] for s in all_shifts])
    negative_preferences.extend([shifts[(mj_idx, 5, s)] for s in all_shifts])

    # SJ
    # Preference for 4 consecutive morning shifts removed for performance.
    positive_preferences.append(shifts[(sj_idx, 20, 0)])

    preference_score = model.NewIntVar(-500, 500, 'preference_score')
    model.Add(preference_score == sum(positive_preferences) - sum(negative_preferences))

    return cl_days_per_consultant, preference_score

def generate_roster_cp(year, month):
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

    # --- Define Hard Constraints ---

    # Each consultant works at most one shift per day
    for c in all_consultants:
        for d in all_days:
            model.Add(sum(shifts[(c, d, s)] for s in all_shifts) <= 1)

    cl_days_per_consultant = {c.initial: 0 for c in CONSULTANTS}
    preference_score = model.NewIntVar(0, 0, 'preference_score') # Default empty score

    if year == 2025 and month == 10:
        cl_days_per_consultant, preference_score = apply_october_2025_requests(model, shifts, CONSULTANTS, all_days, all_shifts, year, month)

    # Shift size constraints
    for d in all_days:
        model.Add(sum(shifts[(c, d, 0)] for c in all_consultants) == 3) # Morning shift is 3 people
        date = datetime.date(year, month, d)
        if date.weekday() < 6:
            model.Add(sum(shifts[(c, d, 1)] for c in all_consultants) == 1) # Afternoon
        else:
            model.Add(sum(shifts[(c, d, 1)] for c in all_consultants) == 0)
        model.Add(sum(shifts[(c, d, 2)] for c in all_consultants) == 2) # Night

    # No afternoon shifts for AM and SJ
    am_index = [i for i, c in enumerate(CONSULTANTS) if c.initial == 'AM'][0]
    sj_index = [i for i, c in enumerate(CONSULTANTS) if c.initial == 'SJ'][0]
    for d in all_days:
        model.Add(shifts[(am_index, d, 1)] == 0)
        if not (year == 2025 and month == 10):
            model.Add(shifts[(sj_index, d, 1)] == 0)

    # At least one senior on night shift
    senior_indices = [i for i, c in enumerate(CONSULTANTS) if c.is_senior]
    for d in all_days:
        model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)

    # No two female consultants on night shift
    female_indices = [i for i, c in enumerate(CONSULTANTS) if c.gender == 'Female']
    for d in all_days:
        model.Add(sum(shifts[(c, d, 2)] for c in female_indices) <= 1)

    # Mittal cannot do Monday and Wednesday night duties
    mittal_index = [i for i, c in enumerate(CONSULTANTS) if c.initial == 'MT'][0]
    for d in all_days:
        date = datetime.date(year, month, d)
        if date.weekday() == 0 or date.weekday() == 2: # Monday or Wednesday
            model.Add(shifts[(mittal_index, d, 2)] == 0)

    # Post-night duty
    for c in all_consultants:
        for d in all_days[:-1]:
            model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
            model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

    # Night shift constraints
    mh_index = [i for i, c in enumerate(CONSULTANTS) if c.initial == 'MH'][0]
    model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)

    oct_2025_special_nights = []
    if year == 2025 and month == 10:
        oct_2025_special_nights = ['MT', 'AM']

    for c_idx, c in enumerate(CONSULTANTS):
        if c.initial != 'MH' and c.initial not in oct_2025_special_nights:
            num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
            model.Add(num_nights >= 5)
            model.Add(num_nights <= 7)

    # No more than 4 consecutive leaves
    for c in all_consultants:
        for d in range(1, num_days - 3):
            model.Add(sum(shifts[(c, i, s)] for i in range(d, d + 5) for s in all_shifts) >= 1)

    # --- Define Soft Constraints (Objectives) ---

    # 1. Weekend Distribution Preference
    weekend_days = [d for d in all_days if datetime.date(year, month, d).weekday() >= 5]
    weekend_shifts_per_consultant = [sum(shifts[(c, d, s)] for d in weekend_days for s in all_shifts) for c in all_consultants]
    min_weekend_shifts = model.NewIntVar(0, num_days, 'min_weekend_shifts')
    max_weekend_shifts = model.NewIntVar(0, num_days, 'max_weekend_shifts')
    model.AddMinEquality(min_weekend_shifts, weekend_shifts_per_consultant)
    model.AddMaxEquality(max_weekend_shifts, weekend_shifts_per_consultant)
    weekend_fairness_diff = max_weekend_shifts - min_weekend_shifts

    # 2. Working Hours Fairness Preference
    all_total_hours = []
    for c_idx, c in enumerate(CONSULTANTS):
        total_hours = model.NewIntVar(0, 300, f'total_hours_c{c_idx}')
        model.Add(total_hours == sum(shifts[(c_idx, d, 0)] * 9 + shifts[(c_idx, d, 1)] * 8 + shifts[(c_idx, d, 2)] * 15 for d in all_days))
        all_total_hours.append(total_hours)

    min_total_hours = model.NewIntVar(0, 300, 'min_total_hours')
    max_total_hours = model.NewIntVar(0, 300, 'max_total_hours')
    model.AddMinEquality(min_total_hours, all_total_hours)
    model.AddMaxEquality(max_total_hours, all_total_hours)
    hours_fairness_diff = max_total_hours - min_total_hours

    # 3. Night Shift Fairness Preference
    fair_night_consultants = [i for i, c in enumerate(CONSULTANTS) if c.initial != 'MH']
    night_shifts_per_consultant = [sum(shifts[(c, d, 2)] for d in all_days) for c in fair_night_consultants]
    min_night_shifts = model.NewIntVar(0, num_days, 'min_night_shifts')
    max_night_shifts = model.NewIntVar(0, num_days, 'max_night_shifts')
    model.AddMinEquality(min_night_shifts, night_shifts_per_consultant)
    model.AddMaxEquality(max_night_shifts, night_shifts_per_consultant)
    nights_fairness_diff = max_night_shifts - min_night_shifts

    # --- Set Objective Function ---
    model.Minimize(weekend_fairness_diff * 2 + hours_fairness_diff + nights_fairness_diff * 4 - preference_score)

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
        return roster
    else:
        return None

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

def get_statistics(roster, year, month):
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
        stats_rows.append([consultant.name, general_shifts, afternoon_shifts, night_shifts, total_hours])
    
    # Add HOD stats
    num_days = calendar.monthrange(year, month)[1]
    hod_mornings = sum(1 for i in range(1, num_days + 1) if datetime.date(year, month, i).weekday() < 6)
    hod_hours = hod_mornings * 9
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

def export_to_gsheet(roster, stats_data, year, month, service_account_file='your_service_account_file.json', share_email=None):
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

    worksheet = spreadsheet.sheet1
    worksheet.clear()

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

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate a duty roster for consultants.')
    parser.add_argument('-y', '--year', type=int, default=datetime.datetime.now().year, help='The year for the roster.')
    parser.add_argument('-m', '--month', type=int, default=datetime.datetime.now().month, help='The month for the roster.')
    parser.add_argument('--export-gsheet', action='store_true', help='Export the roster to Google Sheets.')
    parser.add_argument('--share-email', type=str, help='Email address to share the Google Sheet with.')
    parser.add_argument('--force-regenerate', action='store_true', help='Force regeneration of the roster, ignoring any cached version.')
    args = parser.parse_args()

    cache_filename = f"roster_{args.year}_{args.month}.json"
    roster = None

    if not args.force_regenerate:
        try:
            with open(cache_filename, 'r') as f:
                print(f"Loading roster from cache file: {cache_filename}")
                cached_roster = json.load(f)
                roster = {int(k): v for k, v in cached_roster.items()}
        except FileNotFoundError:
            print("No cache file found.")

    if roster is None:
        print("Generating new roster...")
        roster = generate_roster_cp(args.year, args.month)
        
        if roster:
            print(f"Saving roster to cache file: {cache_filename}")
            with open(cache_filename, 'w') as f:
                json.dump(roster, f, indent=4)

    if roster:
        print_roster(roster, args.year, args.month)
        print() # Add a blank line
        stats_data = get_statistics(roster, args.year, args.month)
        print_statistics_from_data(stats_data)

        if args.export_gsheet:
            print("\nExporting to Google Sheets...")
            print("Please ensure 'your_service_account_file.json' is in the same directory.")
            export_to_gsheet(roster, stats_data, args.year, args.month, 
                             service_account_file='your_service_account_file.json', 
                             share_email=args.share_email)
    else:
        print("Could not generate or load a roster.")