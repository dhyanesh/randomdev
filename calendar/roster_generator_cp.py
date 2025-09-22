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
The script is run from the command line with the year, month, and a path to a JSON file containing vacation data.

**Command:**
```bash
python roster_generator_cp.py -y <year> -m <month> --vacations-file <path_to_vacations.json>
```

**Arguments:**
- `-y`, `--year`: The year for the roster (e.g., 2025).
- `-m`, `--month`: The month for the roster (e.g., 9).
- `--vacations-file`: The path to the JSON file with vacation data.

**Vacation File Format (`vacations.json`):**
The JSON file should contain a list of vacation requests, where each request specifies the consultant's initial and a list of dates they will be unavailable.

**Example `vacations.json`:**
```json
{
  "requests": [
    {
      "consultant_initial": "PK",
      "dates": ["2025-09-05", "2025-09-06"]
    },
    {
      "consultant_initial": "MNS",
      "dates": ["2025-09-10"]
    }
  ]
}
```
"""
from __future__ import print_function
from ortools.sat.python import cp_model
import calendar
from collections import namedtuple
import datetime
import argparse
import json

# Based on the provided PDF and constraints.
Consultant = namedtuple('Consultant', ['name', 'initial', 'is_senior'])

CONSULTANTS = [
    Consultant('DR. PRAVEEN. S', 'PS', True),
    Consultant('DR. MOHAN', 'MH', True),
    Consultant('DR. PRAVEEN KUMAR', 'PK', False),
    Consultant('DR. SANTOSH', 'SK', True),
    Consultant('DR. SHIVA SHANKAR.B', 'SB', False),
    Consultant('DR. AMRITHA', 'AM', True),
    Consultant('DR. MITTAL', 'MT', True),
    Consultant('DR. MANJUNATH', 'MJ', False),
    Consultant('DR. SIMMY JOHN', 'SJ', False),
    Consultant('DR. MANJUNATH N S', 'MNS', True),
]


def generate_roster_cp(year, month, vacations):
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
        model.Add(shifts[(sj_index, d, 1)] == 0)

    # At least one senior on night shift
    senior_indices = [i for i, c in enumerate(CONSULTANTS) if c.is_senior]
    for d in all_days:
        model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)

    # Post-night duty
    for c in all_consultants:
        for d in all_days[:-1]:
            model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
            model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

    # Vacations
    for c_idx, c in enumerate(CONSULTANTS):
        for d in all_days:
            date = datetime.date(year, month, d)
            if date in vacations.get(c.initial, []):
                for s in all_shifts:
                    model.Add(shifts[(c_idx, d, s)] == 0)

    # Night shift constraints
    mh_index = [i for i, c in enumerate(CONSULTANTS) if c.initial == 'MH'][0]
    model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)

    for c_idx, c in enumerate(CONSULTANTS):
        if c.initial != 'MH':
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
    model.Minimize(weekend_fairness_diff * 2 + hours_fairness_diff + nights_fairness_diff * 4)

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

    print("DATE       | GENERAL (9am-6pm)   | AFTERNOON (12pm-8pm) | NIGHT (6pm-9am)")
    print("-" * 70)
    for day, shifts in roster.items():
        date = datetime.date(year, month, day)
        if date.weekday() < 6: # Not Sunday
            shifts['morning'].insert(0, 'BG')

        date_str = f"{day}-{month}-{year}"
        morning_str = '/'.join(shifts['morning'])
        afternoon_str = '/'.join(shifts['afternoon'])
        night_str = '/'.join(shifts['night'])
        print(f"{date_str:<10} | {morning_str:<19} | {afternoon_str:<20} | {night_str}")

import argparse

def print_statistics(roster, year, month):
    if roster is None:
        return

    print("\n--- Shift Statistics ---")
    print(f"{ 'Consultant':<20} | { 'General':<10} | { 'Afternoon':<10} | { 'Night':<10} | { 'Total Hours':<10}")
    print("-" * 75)

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

        print(f"{consultant.name:<20} | {general_shifts:<10} | {afternoon_shifts:<10} | {night_shifts:<10} | {total_hours:<10}")
    
    # Add HOD stats
    num_days = calendar.monthrange(year, month)[1]
    hod_mornings = sum(1 for i in range(1, num_days + 1) if datetime.date(year, month, i).weekday() < 6)
    hod_hours = hod_mornings * 9
    print(f"{ 'Dr. BHARGAVA':<20} | {hod_mornings:<10} | {0:<10} | {0:<10} | {hod_hours:<10}")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate a duty roster for consultants.')
    parser.add_argument('-y', '--year', type=int, default=datetime.datetime.now().year, help='The year for the roster.')
    parser.add_argument('-m', '--month', type=int, default=datetime.datetime.now().month, help='The month for the roster.')
    parser.add_argument('--vacations-file', type=str, required=True, help='Path to the vacation data file (JSON format).')
    args = parser.parse_args()

    # Read and parse the vacation file
    with open(args.vacations_file, 'r') as f:
        vacation_data = json.load(f)

    # Convert JSON data to the dictionary format expected by the solver
    vacations_dict = {}
    for req in vacation_data['requests']:
        vacations_dict[req['consultant_initial']] = [
            datetime.datetime.strptime(d, '%Y-%m-%d').date() for d in req['dates']
        ]

    roster = generate_roster_cp(args.year, args.month, vacations_dict)
    print_roster(roster, args.year, args.month)
    print_statistics(roster, args.year, args.month)
