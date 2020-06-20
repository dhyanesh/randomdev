#!/usr/local/bin/python3

from __future__ import print_function
from ortools.sat.python import cp_model
import csv
import calendar

doctors = [
"Dr. Mohan",
"Dr. Chaitra",
"Dr. Deepti",
"Dr. Sangeet",
"Dr. Sunil",
"Dr. Nazreen",
"Dr. Neelima",
"Dr. Nitya",
"Dr. Owais",
"Dr. Sarath",
"Dr. Shivanvesh",
"Dr. Vikram",
"Dr. Vishnu",
"Dr. Abhiram",
"Dr. Pallavi",
"Dr. Amla",
"Dr. Mittal"]

def PrettyPrintDoctor(doctor):
    return doctors[doctor]

def PrettyPrintShift(shift):
    if shift == 0:
        return 'Morning'
    elif shift == 1:
        return 'Night'
    elif shift == 2:
        return 'MMH'
    else:
        return 'UNKNOWN'

def PrettyPrintZone(zone):
    if zone == 0:
        return '1/2'
    elif zone == 1:
        return '3'
    elif zone == 2:
        return '4'
    else:
        return 'UNKNOWN'

def AddConsecutiveShiftConstraint(model, shifts, doc, day, shift1, shift2):
    all_zones = range(3)
    model.Add(sum((shifts[(doc, day, shift1, zone)] + shifts[(doc, day + 1, shift2, zone)]) for zone in all_zones) <= 1)


def main():
    year = 2020
    month = 7
    num_days = calendar.monthrange(year, month)[1]
    cal = calendar.Calendar()
    all_days = []
    all_day_weekday = []
    for day, weekday in cal.itermonthdays2(year, month):
        if day == 0:
            continue
        all_days.append(day)
        all_day_weekday.append((day, weekday))
    num_doctors = len(doctors)
    num_shifts = 3
    num_zones = 3

    num_morn_doctors = 3
    num_night_doctors = 5
    num_mmh_doctors = 1

    min_mmh_shifts = 0
    max_mmh_shifts = 3

    max_morn_shifts = 9
    max_night_shifts = 10
    max_total_shifts = 19
    min_morn_shifts = max_morn_shifts - 4
    min_night_shifts = max_night_shifts - 2
    min_total_shifts = max_total_shifts - 2

    all_doctors = range(num_doctors)
    all_shifts = range(num_shifts)
    all_zones = range(num_zones)

    MORN_SHIFT = 0
    NIGHT_SHIFT = 1
    MMH_SHIFT = 2

    ZONE_12 = 0
    ZONE_3 = 1
    ZONE_4 = 2

    shift_exclusions = {MMH_SHIFT: [13, 14, 15]}
    zone_exclusions = {ZONE_3: [13, 14], ZONE_4: [13, 14]}

    min_zone3_shifts = (num_days * 2) // (num_doctors - len(zone_exclusions[ZONE_3]))
    max_zone3_shifts = min_zone3_shifts + 1

    min_zone4_shifts = (num_days * 2) // (num_doctors - len(zone_exclusions[ZONE_4]))
    max_zone4_shifts = min_zone4_shifts + 1

    shift_requests = []
    # shift_requests = [[[0, 0, 1], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 1],
    #                    [0, 1, 0], [0, 0, 1]],
    #                   [[0, 0, 0], [0, 0, 0], [0, 1, 0], [0, 1, 0], [1, 0, 0],
    #                    [0, 0, 0], [0, 0, 1]],
    #                   [[0, 1, 0], [0, 1, 0], [0, 0, 0], [1, 0, 0], [0, 0, 0],
    #                    [0, 1, 0], [0, 0, 0]],
    #                   [[0, 0, 1], [0, 0, 0], [1, 0, 0], [0, 1, 0], [0, 0, 0],
    #                    [1, 0, 0], [0, 0, 0]],
    #                   [[0, 0, 0], [0, 0, 1], [0, 1, 0], [0, 0, 0], [1, 0, 0],
    #                    [0, 1, 0], [0, 0, 0]]]
    # Creates the model.
    model = cp_model.CpModel()

    # Creates shift variables.
    # shifts[(doc, day, shift, zone)]:
    shifts = {}
    for doc in all_doctors:
        for day in all_days:
            for shift in all_shifts:
                for zone in all_zones:
                    shifts[(doc, day, shift, zone)] = model.NewBoolVar('shift_doc%iday%ishift%izone%i' % (doc, day, shift, zone))

    sundays = [5, 12, 19, 26]
    # Set the number of day and night doctors according to the zone.
    for day, weekday in all_day_weekday:
        if weekday == calendar.SUNDAY:
            model.Add(sum(shifts[(doc, day, MORN_SHIFT, ZONE_12)] for doc in all_doctors) == num_morn_doctors - 2 + 1)
        else:
            model.Add(sum(shifts[(doc, day, MORN_SHIFT, ZONE_12)] for doc in all_doctors) == num_morn_doctors - 2)
        model.Add(sum(shifts[(doc, day, NIGHT_SHIFT, ZONE_12)] for doc in all_doctors) == num_night_doctors - 2)
        model.Add(sum(shifts[(doc, day, MORN_SHIFT, ZONE_3)] for doc in all_doctors) == 1)
        model.Add(sum(shifts[(doc, day, MORN_SHIFT, ZONE_4)] for doc in all_doctors) == 1)
        model.Add(sum(shifts[(doc, day, NIGHT_SHIFT, ZONE_3)] for doc in all_doctors) == 1)
        model.Add(sum(shifts[(doc, day, NIGHT_SHIFT, ZONE_4)] for doc in all_doctors) == 1)
        model.Add(sum(shifts[(doc, day, MMH_SHIFT, zone)] for doc in all_doctors for zone in all_zones) == num_mmh_doctors)

    # Each doctor works at most one shift per day.
    for doc in all_doctors:
        for day in all_days:
            model.Add(sum(shifts[(doc, day, shift, zone)] for shift in all_shifts for zone in all_zones) <= 1)

    for doc in all_doctors:
        for day in all_days[:-1]:
            AddConsecutiveShiftConstraint(model, shifts, doc, day, NIGHT_SHIFT, MORN_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, NIGHT_SHIFT, NIGHT_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, NIGHT_SHIFT, MMH_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, MMH_SHIFT, MORN_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, MMH_SHIFT, NIGHT_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, MMH_SHIFT, MMH_SHIFT)

    for doc in all_doctors:
        num_morn_shifts_worked = sum(
            shifts[(doc, day, MORN_SHIFT, zone)] for day in all_days for zone in all_zones)
        model.Add(num_morn_shifts_worked <= max_morn_shifts)
        model.Add(num_morn_shifts_worked >= min_morn_shifts)
        num_night_shifts_worked = sum(
            shifts[(doc, day, NIGHT_SHIFT, zone)] for day in all_days for zone in all_zones)
        model.Add(num_night_shifts_worked <= max_night_shifts)
        model.Add(num_night_shifts_worked >= min_night_shifts)
        num_mmh_shifts_worked = 2 * sum(
            shifts[(doc, day, MMH_SHIFT, zone)] for day in all_days for zone in all_zones)
        model.Add(num_morn_shifts_worked + num_night_shifts_worked + num_mmh_shifts_worked <= max_total_shifts)
        model.Add(num_morn_shifts_worked + num_night_shifts_worked + num_mmh_shifts_worked >= min_total_shifts)
        if doc not in shift_exclusions[MMH_SHIFT]:
            model.Add(num_mmh_shifts_worked >= min_mmh_shifts * 2)
            model.Add(num_mmh_shifts_worked <= max_mmh_shifts * 2)
        if doc not in zone_exclusions[ZONE_3]:
            num_zone_3_shifts_worked  = sum(
                    shifts[(doc, day, shift, ZONE_3)] for day in all_days for shift in all_shifts)
            model.Add(num_zone_3_shifts_worked >= min_zone3_shifts)
            model.Add(num_zone_3_shifts_worked <= max_zone3_shifts)
        if doc not in zone_exclusions[ZONE_4]:
            num_zone_4_shifts_worked  = sum(
                    shifts[(doc, day, shift, ZONE_4)] for day in all_days for shift in all_shifts)
            model.Add(num_zone_4_shifts_worked >= min_zone4_shifts)
            model.Add(num_zone_4_shifts_worked <= max_zone4_shifts)


    for shift, doc_list in shift_exclusions.items():
        for doc in doc_list:
            model.Add(sum(shifts[(doc, day, shift, zone)] for day in all_days for zone in all_zones) == 0)

    for zone, doc_list in zone_exclusions.items():
        for doc in doc_list:
            model.Add(sum(shifts[(doc, day, shift, zone)] for day in all_days for shift in all_shifts) == 0)

    # model.Maximize(
    #     sum(shift_requests[n][d][s] * shifts[(n, d, s)] for n in all_doctors
    #         for d in all_days for s in all_shifts))
    # Creates the solver and solve.
    solver = cp_model.CpSolver()
    if solver.Solve(model) == cp_model.INFEASIBLE:
        print('No solution found')
        exit()

    print('Solution found')
    sum_shifts = {}
    for doc in all_doctors:
        for shift in all_shifts:
            for zone in all_zones:
                sum_shifts[(doc, shift, zone)] = 0

    with open('%s_%d.csv' % (calendar.month_name[month], year), 'w', newline='') as csvfile:
        fieldnames = ['Day', 'Date', 'Morning zone 1/2', 'Morning zone 3', 'Morning zone 4',
                'Morning total', 'Night zone 1/2', 'Night zone 3', 'Night zone 4', 'Night total', 'MMH', 'Total']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        for day, weekday in all_day_weekday:
            print('Day', day)
            row = {'Day': calendar.day_abbr[weekday], 'Date': day}
            for shift in all_shifts:
                per_shift_doctors = []
                for zone in all_zones:
                    per_zone_doctors = []
                    for doc in all_doctors:
                        if solver.Value(shifts[(doc, day, shift, zone)]) == 1:
                            per_zone_doctors.append(PrettyPrintDoctor(doc))
                            sum_shifts[(doc, shift, zone)] += 1
                            if shift != MMH_SHIFT:
                                print(PrettyPrintDoctor(doc), 'works the ', PrettyPrintShift(shift), ' shift in zone ', PrettyPrintZone(zone))
                            else:
                                print(PrettyPrintDoctor(doc), 'works the ', PrettyPrintShift(shift), ' shift.')
                    if shift != MMH_SHIFT:
                        row[PrettyPrintShift(shift) + ' zone ' + PrettyPrintZone(zone)] = ','.join(per_zone_doctors)
                    else:
                        per_shift_doctors.extend(per_zone_doctors)
                if shift == MMH_SHIFT:
                    row[PrettyPrintShift(shift)] = ','.join((per_shift_doctors))
            writer.writerow(row)

        # Statistics.
        print()
        writer.writerow({})
        writer.writerow({'Night zone 1/2': 'Duty Totals'})
        intermediate_headers = {}
        for field in fieldnames:
            if field=='Day':
                intermediate_headers[field] = 'Doctor'
            else:
                intermediate_headers[field] = field
        writer.writerow(intermediate_headers)
        print('Statistics')
        for doc in all_doctors:
            total = 0
            row = {'Day': PrettyPrintDoctor(doc)}
            for shift in all_shifts:
                shift_total = 0
                for zone in all_zones:
                    doc_shifts = sum_shifts[(doc, shift, zone)]
                    shift_total += doc_shifts
                    if shift == MMH_SHIFT:
                        doc_shifts *= 2
                    else:
                        row[PrettyPrintShift(shift) + ' zone ' + PrettyPrintZone(zone)] = doc_shifts
                        print(PrettyPrintDoctor(doc), 'has ', doc_shifts, ' ', PrettyPrintShift(shift), 'shifts in zone ', PrettyPrintZone(zone))
                    total += doc_shifts
                print(PrettyPrintDoctor(doc), 'has ', shift_total, ' ', PrettyPrintShift(shift), 'shifts.')
                if shift == MMH_SHIFT:
                    row[PrettyPrintShift(shift)] = shift_total
                else:
                    row[PrettyPrintShift(shift) + ' total'] = shift_total
            print('Total shifts: ', total)
            row['Total'] = total
            writer.writerow(row)
    # print('  - Number of shift requests met = %i' % solver.ObjectiveValue(),
    #       '(out of', num_doctors * min_shifts_per_doctor, ')')
    print('  - wall time       : %f s' % solver.WallTime())


if __name__ == '__main__':
    main()
