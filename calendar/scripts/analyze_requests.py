
import json
import re

# Load roster
with open('data/roster_2026_01.json', 'r') as f:
    roster = json.load(f)

# Consultant mapping
CONSULTANT_MAP = {
    'DR. PRAVEEN. S': 'PS',
    'DR. MOHAN': 'MH',
    'DR. PRAVEEN KUMAR': 'PK',
    'DR. SANTOSH': 'SK',
    'DR. SHIVA SHANKAR.B': 'SB',
    'DR. AMRITHA': 'AM',
    'DR. MITTAL': 'MT',
    'DR. MANJUNATH': 'MJ',
    'DR. SIMMY JOHN': 'SJ',
    'DR. MANJUNATH N S': 'MNS'
}

def parse_requests(filename):
    requests = {}
    current_consultant = None
    
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            
            if line.startswith('Consultant:'):
                name = line.split('Consultant:')[1].strip()
                if name in CONSULTANT_MAP:
                    current_consultant = CONSULTANT_MAP[name]
                    requests[current_consultant] = []
                else:
                    print(f"Warning: Unknown consultant {name}")
                    current_consultant = None
            elif line.startswith('Request:') and current_consultant:
                req_text = line.split('Request:')[1].strip().lower()
                
                # Parse days
                days = [int(d) for d in re.findall(r'\b\d{1,2}\b', req_text)]
                
                req_type = 'unknown'
                if 'night' in req_text:
                    req_type = 'night'
                elif 'day' in req_text or 'morning' in req_text: # Treating prefer morning as day for now, specific logic can be added
                     req_type = 'day'
                elif 'leave' in req_text or 'off' in req_text:
                    req_type = 'leave'
                
                if req_type != 'unknown':
                    if 'entire month' in req_text:
                         requests[current_consultant].append({'type': 'entire_month_off', 'days': []})
                    else:
                        requests[current_consultant].append({'type': req_type, 'days': days, 'original': line})

    return requests

def check_requests(roster, requests):
    unmet = {}
    
    for consultant, consult_requests in requests.items():
        unmet[consultant] = []
        for req in consult_requests:
            if req['type'] == 'entire_month_off':
                # Check if consultant appears anywhere
                found = False
                for d in roster:
                    for shift_type in roster[d]:
                        if consultant in roster[d][shift_type]:
                            unmet[consultant].append(f"Request: Off entire month. Found in {d} {shift_type}")
                            found = True
                            break
                    if found: break
            else:
                for day in req['days']:
                    day_str = str(day)
                    if day_str not in roster:
                        continue # Should not happen for 1-31
                    
                    shifts = roster[day_str]
                    in_morning = consultant in shifts.get('morning', [])
                    in_afternoon = consultant in shifts.get('afternoon', [])
                    in_night = consultant in shifts.get('night', [])
                    
                    if req['type'] == 'leave':
                        if in_morning or in_afternoon or in_night:
                            found_shift = 'Morning' if in_morning else ('Afternoon' if in_afternoon else 'Night')
                            unmet[consultant].append(f"Request: Leave on {day}. Got {found_shift}.")
                    
                    elif req['type'] == 'day':
                        # Met if in morning or afternoon
                        if not (in_morning or in_afternoon):
                            if in_night:
                                unmet[consultant].append(f"Request: Day shift on {day}. Got Night.")
                            else:
                                unmet[consultant].append(f"Request: Day shift on {day}. Got Off.")
                                
                    elif req['type'] == 'night':
                        if not in_night:
                            if in_morning or in_afternoon:
                                found_shift = 'Morning' if in_morning else 'Afternoon'
                                unmet[consultant].append(f"Request: Night shift on {day}. Got {found_shift}.")
                            else:
                                unmet[consultant].append(f"Request: Night shift on {day}. Got Off.")

    return unmet

requests = parse_requests('data/consultant_requests_2026_01.txt')
unmet_summary = check_requests(roster, requests)

print("--- Unmet Requests Summary ---")
for consultant, issues in unmet_summary.items():
    # Find full name
    full_name = next((name for name, code in CONSULTANT_MAP.items() if code == consultant), consultant)
    if issues:
        print(f"\n{full_name} ({len(issues)} unmet):")
        for issue in issues:
            print(f"  - {issue}")
    else:
        print(f"\n{full_name}: All requests met.")
