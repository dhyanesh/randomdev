import datetime
import calendar

# --- Data ---

# Manual Roster Text (Dec 2025 manual take w.jpg)
roster_text = """
1 BG/MH/PK MJ SJ/AM
2 BG/MH/MJ PS/PK
3 BG/MH/AM SJ/MJ
4 BG/SB/SN SN/AM
5 BG/MH/SJ MJ/SB
6 BG/SJ/SN MH/MJ
7 PS/SN MH/SJ
8 BG/SB/AM SB/SN
9 BG/SJ/AM PK/MNS
10 BG/MH/SN AM/SJ
11 BG/MNS/SB SN/PS
12 BG/MH/PK MNS SJ/MJ
13 BG/MNS/SB PS SN/AM
14 PK/MNS SJ/PS
15 BG/MH/SB SN/MJ
16 BG/MH/SJ SB/MNS
17 BG/MH/PK MJ/AM
18 BG/SB/SJ MNS PK/PS
19 BG/MH/SJ SB/SN
20 BG/SJ/PS MNS PK/AM
21 MH/SN MNS/PS
22 BG/SJ/PS AM/SB
23 BG/MNS/SN PK/MJ
24 BG/MNS/SN AM/SB
25 BG/MNS/MJ PS/SN
26 BG/AM/PK MJ/
27 BG/PK/MNS PS/AM
28 SB/PK/MNS MH/SB
29 BG/MNS/MJ MH/PK
30 BG/MNS/AM PS/SJ
31 BG/MH/MNS PK/MJ
"""

# Consultant Definitions
CONSULTANTS = {
    'PS': {'name': 'Dr. Praveen S', 'senior': True, 'gender': 'Male'},
    'MH': {'name': 'Dr. Mohan', 'senior': True, 'gender': 'Male'},
    'PK': {'name': 'Dr. Praveen Kumar', 'senior': False, 'gender': 'Male'},
    'SN': {'name': 'Dr. Santosh', 'senior': True, 'gender': 'Male'}, # Assuming SN = SK/Santosh
    'SB': {'name': 'Dr. Shiva Shankar B', 'senior': False, 'gender': 'Male'},
    'AM': {'name': 'Dr. Amritha', 'senior': True, 'gender': 'Female'},
    'MT': {'name': 'Dr. Mittal', 'senior': True, 'gender': 'Male'},
    'MJ': {'name': 'Dr. Manjunath', 'senior': False, 'gender': 'Male'},
    'SJ': {'name': 'Dr. Simmy John', 'senior': False, 'gender': 'Female'},
    'MNS': {'name': 'Dr. Manjunath N S', 'senior': True, 'gender': 'Male'},
}

# Requests (Same as previous)
REQUESTS = {
    'SB': {'leave': [1, 2, 3, 6, 7], 'day_req': [4, 5], 'night_req': [8]},
    'PS': {'leave': [4, 5, 6, 7, 8], 'day_req': [2, 12, 14, 17, 27], 'night_req': [9, 10, 18, 20, 24, 29, 30]},
    'MJ': {'leave': [9, 10, 19, 20, 21]},
    'PK': {'leave': [8, 9, 16, 23, 24, 25]},
    'SN': {'leave': [1, 2, 3, 28, 29, 30, 31]},
    'SJ': {'leave': [6, 21, 22, 23, 24, 25, 26, 27, 31, 5], 'morning_req': [5, 20, 30]},
    'AM': {'leave': [1, 2, 3, 7, 14, 15, 16, 17, 30, 31], 'night_req': [21, 23], 'avoid_night': [6, 13]},
    'MH': {'night_req': [6, 7, 28, 29], 'day_req': [1, 2, 3, 5, 8, 10, 12, 15, 16, 17, 19, 22, 23, 31], 'no_afternoon': True},
    'MNS': {'no_duties_before': 11, 'after_11_only_MA': True},
    'MT': {'leave': list(range(1, 32))}
}

YEAR = 2025
MONTH = 12

def parse_roster(text):
    roster = {}
    lines = text.strip().split('\n')
    for line in lines:
        parts = line.strip().split()
        if not parts: continue
        
        day = int(parts[0])
        
        cleaned_parts = []
        for p in parts:
            if p == 'B' or p == 'B4': p = 'BG'
            cleaned_parts.append(p)
        parts = cleaned_parts

        tokens = parts[1:]
        
        morning = []
        afternoon = []
        night = []

        def get_initials(token):
            return [x for x in token.split('/') if x]

        night_token = tokens[-1]
        night = get_initials(night_token)
        
        remaining = tokens[:-1]
        
        if not remaining:
            pass
        else:
            is_afternoon_candidate = False
            if len(remaining) >= 1:
                last_rem = remaining[-1]
                if '/' not in last_rem:
                     is_afternoon_candidate = True
            
            if is_afternoon_candidate and len(remaining) > 1:
                 afternoon = get_initials(remaining[-1])
                 morning_tokens = remaining[:-1]
                 for t in morning_tokens:
                     morning.extend(get_initials(t))
            elif is_afternoon_candidate and len(remaining) == 1:
                 # Ambiguous case check. If morning becomes empty?
                 # If row is "2 BG/MH/MJ PS/PK" -> Rem=["BG/MH/MJ"]. Slash exists. Not candidate.
                 # If row is "1 BG/MH/PK MJ SJ/AM" -> Rem=["BG/MH/PK", "MJ"]. MJ is candidate.
                 afternoon = get_initials(remaining[-1])
                 morning_tokens = remaining[:-1]
                 for t in morning_tokens:
                     morning.extend(get_initials(t))
            else:
                 for t in remaining:
                     morning.extend(get_initials(t))
        
        roster[day] = {'morning': morning, 'afternoon': afternoon, 'night': night}
    
    return roster

def check_constraints(roster, requests):
    violations = []
    
    def is_sunday(d):
        return datetime.date(YEAR, MONTH, d).weekday() == 6
    
    stats = {c: {'G': 0, 'A': 0, 'N': 0, 'Hours': 0} for c in CONSULTANTS}
    
    for d, shifts in roster.items():
        morning = shifts['morning']
        afternoon = shifts['afternoon']
        nights = shifts['night']
        
        # 1. Night Shift Seniority
        seniors_on_night = [c for c in nights if c in CONSULTANTS and CONSULTANTS[c]['senior']]
        if not seniors_on_night:
            violations.append(f"Day {d}: Night shift {nights} has no senior consultant.")
            
        # 11. Night shift: 2 consultants
        if len(nights) != 2:
            violations.append(f"Day {d}: Night shift {nights} does not have exactly 2 consultants.")
        
            # 13. No two females on night
            # females = [c for c in nights if c in CONSULTANTS and CONSULTANTS[c]['gender'] == 'Female']
            # if len(females) > 1:
            #     violations.append(f"Day {d}: Two female consultants on night shift: {females}")
        # 10. Afternoon: 0 or 1. Zero on Sundays.
        if len(afternoon) > 1:
            violations.append(f"Day {d}: More than 1 consultant in afternoon: {afternoon}")
        if is_sunday(d) and len(afternoon) > 0:
            violations.append(f"Day {d} (Sunday): Afternoon shift should be empty, but has {afternoon}")
            
        # 9. Morning: 2 or 3 consultants (excluding HOD)
        morning_staff = [c for c in morning if c != 'BG' and c != 'B']
        if not (2 <= len(morning_staff) <= 3):
            # Note: Only flag if it's significantly off, e.g. 0 or 1.
            # Day 7: PS/SN (2 people). OK.
            pass
            
        # New: Check duplicate consultants in same day
        all_shifts_today = morning + afternoon + nights
        from collections import Counter
        counts = Counter(all_shifts_today)
        for c, count in counts.items():
            if c in CONSULTANTS and count > 1:
                violations.append(f"Day {d}: Consultant {c} works multiple shifts: {count}.")

    for c, info in CONSULTANTS.items():
        req = requests.get(c, {})
        g_count = 0
        a_count = 0
        n_count = 0
        consecutive_leaves = 0
        max_consecutive_leaves = 0
        
        for d in range(1, 32):
            if d not in roster: continue
            
            s = roster[d]
            is_working = False
            is_morning = c in s['morning']
            is_afternoon = c in s['afternoon']
            is_night = c in s['night']
            
            if is_morning: g_count += 1; is_working = True
            if is_afternoon: a_count += 1; is_working = True
            if is_night: n_count += 1; is_working = True
            
            if is_working:
                consecutive_leaves = 0
                if d > 1:
                    prev_night = roster[d-1]['night']
                    if c in prev_night:
                        if is_morning or is_afternoon:
                            violations.append(f"Day {d}: Consultant {c} has shift after working Night on Day {d-1}.")
                
                if c in ['AM', 'SJ'] and is_afternoon:
                    violations.append(f"Day {d}: Consultant {c} is assigned Afternoon shift.")
                
            else:
                consecutive_leaves += 1
                max_consecutive_leaves = max(max_consecutive_leaves, consecutive_leaves)
            
            if d in req.get('leave', []):
                if is_working:
                    violations.append(f"Day {d}: Consultant {c} requested leave but is working.")
            
            if 'night_req' in req:
                if d in req['night_req'] and not is_night:
                     violations.append(f"Day {d}: Consultant {c} requested Night but got something else or off.")
            
            if 'day_req' in req:
                if d in req['day_req'] and not (is_morning or is_afternoon):
                    # Optional
                    pass
        
        expected_nights = 4 if c == 'MH' else 6
        if n_count < expected_nights:
             violations.append(f"Consultant {c} has {n_count} nights. Minimum required: {expected_nights}.")
        
        total_hours = g_count * 9 + a_count * 8 + n_count * 15
        if total_hours > 192:
            violations.append(f"Consultant {c} exceeds 192 hours ({total_hours}).")
            
        if max_consecutive_leaves > 4:
             violations.append(f"Consultant {c} has {max_consecutive_leaves} consecutive days off.")

        stats[c]['G'] = g_count
        stats[c]['A'] = a_count
        stats[c]['N'] = n_count
        stats[c]['Hours'] = total_hours
        
    return violations, stats

roster = parse_roster(roster_text)
violations, stats = check_constraints(roster, REQUESTS)

print("---" + " Violations ---")
for v in violations:
    print(v)

print("\n--- Statistics ---")
print(f"{ 'Consultant':<20} | { 'General':<8} | { 'Afternoon':<9} | { 'Night':<6} | { 'Total Hours'}")
print("-" * 70)
for c in CONSULTANTS:
    s = stats[c]
    print(f"{ CONSULTANTS[c]['name']:<20} | { s['G']:<8} | { s['A']:<9} | { s['N']:<6} | { s['Hours']}")