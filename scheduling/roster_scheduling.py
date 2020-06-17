#!/usr/local/bin/python3

from __future__ import print_function
from ortools.sat.python import cp_model
import csv

def PrettyPrintDoctor(doctor):
    return 'Doctor %i' % doctor

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
    num_doctors = 18
    num_shifts = 3
    num_days = 30
    num_zones = 3

    num_morn_doctors = 3
    num_night_doctors = 5
    num_mmh_doctors = 1

    min_zone3_shifts = (num_days * 2) // num_doctors
    max_zone3_shifts = min_zone3_shifts + 1

    min_zone4_shifts = (num_days * 2) // num_doctors
    max_zone4_shifts = min_zone4_shifts + 1

    min_mmh_shifts = 0
    max_mmh_shifts = 2

    max_morn_shifts = 9
    max_night_shifts = 9
    max_total_shifts = 18
    min_total_shifts = max_total_shifts - 2

    all_doctors = range(num_doctors)
    all_shifts = range(num_shifts)
    all_days = range(num_days)
    all_zones = range(num_zones)

    MORN_SHIFT = 0
    NIGHT_SHIFT = 1
    MMH_SHIFT = 2

    ZONE_12 = 0
    ZONE_3 = 1
    ZONE_4 = 2

    shift_exclusions = {MMH_SHIFT: [10, 15]}
    zone_exclusions = {ZONE_3: [10, 15], ZONE_4: [10, 15]}

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

    # Set the number of day and night doctors according to the zone.
    for day in all_days:
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
        for day in range(num_days - 1):
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
        num_night_shifts_worked = sum(
            shifts[(doc, day, NIGHT_SHIFT, zone)] for day in all_days for zone in all_zones)
        model.Add(num_night_shifts_worked <= max_night_shifts)
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
    sum_shifts = {}
    for doc in all_doctors:
        for shift in all_shifts:
            for zone in all_zones:
                sum_shifts[(doc, shift, zone)] = 0

    with open('output.csv', 'w', newline='') as csvfile:
        fieldnames = ['Day', 'Morning zone 1/2', 'Morning zone 3', 'Morning zone 4',
                '', 'Night zone 1/2', 'Night zone 3', 'Night zone 4', '', 'MMH', 'Total']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        for day in all_days:
            print('Day', day)
            row = {'Day': day + 1}
            for shift in all_shifts:
                per_shift_doctors = []
                for zone in all_zones:
                    per_zone_doctors = []
                    for doc in all_doctors:
                        if solver.Value(shifts[(doc, day, shift, zone)]) == 1:
                            per_zone_doctors.append(PrettyPrintDoctor(doc))
                            sum_shifts[(doc, shift, zone)] += 1
                            if shift != MMH_SHIFT:
                                print('Doctor', doc, 'works the ', PrettyPrintShift(shift), ' shift in zone ', PrettyPrintZone(zone))
                            else:
                                print('Doctor', doc, 'works the ', PrettyPrintShift(shift), ' shift.')
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
                        print('Doctor', doc, 'has ', doc_shifts, ' ', PrettyPrintShift(shift), 'shifts in zone ', PrettyPrintZone(zone))
                    total += doc_shifts
                print('Doctor', doc, 'has ', shift_total, ' ', PrettyPrintShift(shift), 'shifts.')
                if shift == MMH_SHIFT:
                    row[PrettyPrintShift(shift)] = shift_total
            print('Total shifts: ', total)
            row['Total'] = total
            writer.writerow(row)
    # print('  - Number of shift requests met = %i' % solver.ObjectiveValue(),
    #       '(out of', num_doctors * min_shifts_per_doctor, ')')
    print('  - wall time       : %f s' % solver.WallTime())


if __name__ == '__main__':
    main()
