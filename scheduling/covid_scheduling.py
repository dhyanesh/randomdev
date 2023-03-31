#!/usr/local/bin/python3

from __future__ import print_function
from ortools.sat.python import cp_model
import csv
import calendar

class Doctor:
    def __init__(self, n, v=[], nsm=True, ms=16, se={}, de=[], miws=0, mws=5, ze=[], minc=0):
        self.name = n
        self.vacations = v
        self.nsm_duty = nsm;
        self.max_shifts = ms
        self.shift_exclusions = se
        self.doctor_exclusions = de
        self.min_week_shifts = miws
        self.max_week_shifts = mws
        self.zone_exclusions = ze
        self.min_consecutive = minc

ZONE_12 = 0
ZONE_34 = 1
NSM_ZONE = 0

MORN_SHIFT = 0
NIGHT_SHIFT = 1
NSM_SHIFT = 2

doctors = [
Doctor("Dr. Mohan", v=[17,18,19], se={NIGHT_SHIFT: [16]}),
Doctor("Dr. Deepti", [1, 2, 3], se={MORN_SHIFT: [4]}),
Doctor("Dr. Sunil", [1, 2, 14, 15, 16, 17]),
Doctor("Dr. Sangeet", [1, 9, 23, 24, 25, 26, 27, 28, 29, 30], nsm=False, ms=11),
 Doctor("Dr. Vishnu", [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 18], nsm=False, ms=8),
Doctor("Dr. Nazreen", se={MORN_SHIFT: [1], NSM_SHIFT: [1]}, minc=2),
Doctor("Dr. Neelima", [17, 18, 19], False),
Doctor("Dr. Nitya", v=[16, 17], se={MORN_SHIFT: [1], NSM_SHIFT: [1], NIGHT_SHIFT: [1]}),
Doctor("Dr. Owais"),
Doctor("Dr. Sarath", v=[2, 7, 19, 20, 30], se={NIGHT_SHIFT: [1]}),
Doctor("Dr. Shivanvesh", [17, 18, 19, 26, 27, 28, 29, 30], se={MORN_SHIFT: [1], NSM_SHIFT: [1]}, mws=5),
Doctor("Dr. Vikram", v=[17, 18, 19, 27, 28, 29], se={MORN_SHIFT: [1], NSM_SHIFT: [1], NIGHT_SHIFT: [1]}),
Doctor("Dr. Pallavi", v=[14, 15, 16], se={MORN_SHIFT: [1], NSM_SHIFT: [1]}, minc=2),
Doctor("Dr. Mittal", [14, 15, 16, 23], de=["Dr. Naveen", "Dr. Mohan"]),
Doctor("Dr. Naveen", v=[1, 2, 17, 18], se={NIGHT_SHIFT: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]}, ze=[ZONE_12], miws=2),
Doctor("Dr. Anand", [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22], False, ms=5, miws=0, mws=5, se={NIGHT_SHIFT: [17, 18, 19, 20, 21, 22]}, de=["Dr. Naveen"]),
Doctor("Dr. Priyam", [1, 2, 3, 4, 5, 6, 7], mws=5, se={MORN_SHIFT: [16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]}),
Doctor("Dr. Amla", v=[2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 24], nsm=False, se={NIGHT_SHIFT: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]}, ms=8, mws=5)
]

shifts_done = {
1:["Dr. Mohan,Dr. Sarath","Dr. Nazreen, Dr. Pallavi","Dr. Owais,Dr. Amla","Dr. Shivanvesh, Dr. Mittal"],
2:["Dr. Neelima,Dr. Nitya","Dr. Shivanvesh,Dr. Pallavi","Dr. Sangeet,Dr. Owais","Dr. Vikram,Dr. Mittal"],
3:["Dr. Mohan,Dr. Naveen","Dr. Nitya,Dr. Sarath","Dr. Sangeet,Dr. Owais","Dr. Sunil,Dr. Vikram"],
4:["Dr. Mohan,Dr. Naveen","Dr. Neelima,Dr. Sarath","Dr. Nazreen,Dr. Mittal","Dr. Deepti,Dr. Owais"],
5:["Dr. Shivanvesh,Dr. Mohan","Dr. Neelima,Dr. Pallavi","Dr. Sunil,Dr. Nazreen","Dr. Sangeet,Dr. Vikram"],
6:["Dr. Naveen,Dr. Shivanvesh","Dr. Neelima,Dr. Nitya","Dr. Deepti,Dr. Sunil","Dr. Vikram,Dr. Mittal"],
7:["Dr. Shivanvesh,Dr. Naveen","Dr. Nitya,Dr. Pallavi","Dr. Deepti,Dr. Sunil","Dr. Sangeet,Dr. Nazreen"],
8:["Dr. Mohan,Dr. Naveen","Dr. Sunil,Dr. Nazreen","Dr. Vikram,Dr. Mittal","Dr. Sarath,Dr. Shivanvesh"],
9:["Dr. Neelima,Dr. Priyam","Dr. Mohan,Dr. Owais","Dr. Deepti,Dr. Mittal","Dr. Nitya,Dr. Shivanvesh"],
10:["Dr. Sangeet,Dr. Priyam","Dr. Mohan,Dr. Sunil","Dr. Pallavi,Dr. Naveen","Dr. Deepti,Dr. Nitya"],
11:["Dr. Sangeet,Dr. Owais","Dr. Sunil,Dr. Neelima","Dr. Pallavi,Dr. Mittal","Dr. Shivanvesh,Dr. Vikram"],
12:["Dr. Nazreen,Dr. Priyam","Dr. Sangeet,Dr. Neelima","Dr. Pallavi,Dr. Naveen","Dr. Sarath,Dr. Shivanvesh"],
13:["Dr. Sunil,Dr. Nazreen","Dr. Mohan,Dr. Owais","Dr. Vikram,Dr. Naveen","Dr. Nitya,Dr. Pallavi"],
14:["Dr. Neelima,Dr. Priyam","Dr. Sangeet,Dr. Nazreen","Dr. Deepti,Dr. Vikram","Dr. Nitya,Dr. Sarath"],
15:["Dr. Owais,Dr. Shivanvesh","Dr. Deepti,Dr. Vikram","Dr. Naveen,Dr. Priyam","Dr. Mohan,Dr. Sarath"],
16:["Dr. Vishnu,Dr. Owais","Dr. Deepti,Dr. Nazreen","Dr. Neelima,Dr. Naveen","Dr. Sangeet,Dr. Priyam"],
17:["Dr. Sarath,Dr. Mittal","Dr. Nazreen,Dr. Owais","Dr. Pallavi,Dr. Amla","Dr. Sangeet,Dr. Priyam"],
18:["Dr. Sarath,Dr. Mittal","Dr. Deepti,Dr. Owais","Dr. Nitya,Dr. Amla","Dr. Sunil,Dr. Pallavi"],
19:["Dr. Nazreen,Dr. Mittal","Dr. Deepti,Dr. Vishnu","Dr. Sangeet,Dr. Nitya","Dr. Pallavi,Dr. Priyam"],
20:["Dr. Owais,Dr. Vikram","Dr. Shivanvesh,Dr. Mittal","Dr. Mohan,Dr. Neelima","Dr. Sunil,Dr. Priyam"],
21:["Dr. Vishnu,Dr. Vikram","Dr. Sarath,Dr. Shivanvesh","Dr. Neelima,Dr. Nitya","Dr. Mohan,Dr. Sunil"],
22:["Dr. Vikram,Dr. Vishnu","Dr. Neelima,Dr. Deepti","Dr. Naveen,Dr. Amla","Dr. Mohan,Dr. Priyam"],
}

def IndexOfDoctorName(doctor_name):
    index = 0
    for doc in doctors:
        if doc.name == doctor_name:
            return index
        index += 1
    return -1

def PrettyPrintDoctor(doctor):
    return doctors[doctor].name

def PrettyPrintShift(shift):
    if shift == 0:
        return 'Morning'
    elif shift == 1:
        return 'Night'
    elif shift == 2:
        return 'NSM'
    else:
        return 'UNKNOWN'

def PrettyPrintZone(zone):
    if zone == 0:
        return '1/2'
    elif zone == 1:
        return '3/4'
    else:
        return 'UNKNOWN'

def AddConsecutiveShiftConstraint(model, shifts, doc, day, shift1, shift2):
    all_zones = range(2)
    model.Add(sum((shifts[(doc, day, shift1, zone)] + shifts[(doc, day + 1, shift2, zone)]) for zone in all_zones) <= 1)

def NumDaysInWeek(week_start):
    return min(7, num_days - week_start + 1)

def WeekDayList(week_start, num_days):
    return range(week_start, min(week_start + 7, num_days))

def main():
    year = 2020
    month = 11
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
    num_zones = 2

    num_morn_doctors = 2
    num_night_doctors = 2

    nsm_shifts_per_week = 4
    max_nsm_shifts = 7
    max_consecutive_morn_shifts = 3
    max_consecutive_night_shifts = 2

    all_doctors = range(num_doctors)
    all_shifts = range(num_shifts)
    all_zones = range(num_zones)

    # Creates the model.
    model = cp_model.CpModel()

    week_starts = range(2, num_days, 7)

    # Creates shift variables.
    # shifts[(doc, day, shift, zone)]:
    shifts = {}
    for doc in all_doctors:
        for day in all_days:
            for shift in all_shifts:
                for zone in all_zones:
                    shifts[(doc, day, shift, zone)] = model.NewBoolVar('shift_doc%iday%ishift%izone%i' % (doc, day, shift, zone))

    doc_zones = {}
    for doc in all_doctors:
        for week_start in week_starts:
            for zone in all_zones:
                doc_zones[(doc, week_start, zone)] = model.NewBoolVar('doc_zones_doc%iweek_start%izone%i' % (doc, week_start, zone))

    # Set the number of day and night doctors according to the zone.
    for day in all_days:
        for zone in all_zones:
            model.Add(sum(shifts[(doc, day, MORN_SHIFT, zone)] for doc in all_doctors) == num_morn_doctors)
            model.Add(sum(shifts[(doc, day, NIGHT_SHIFT, zone)] for doc in all_doctors) == num_night_doctors)
            model.Add(sum(shifts[(doc, day, NSM_SHIFT, NSM_ZONE)] for doc in all_doctors) == 0)

    # Each doctor works at most one shift per day.
    for doc in all_doctors:
        for day in all_days:
            model.Add(sum(shifts[(doc, day, shift, zone)] for shift in all_shifts for zone in all_zones) <= 1)

    # Each doctor works in at most one zone in a week.
    for doc in all_doctors:
        if doctors[doc].name != "Dr. Naveen":
            for week_start in week_starts:
                if week_start >= 22:
                    model.Add(sum(doc_zones[(doc, week_start, zone)] for zone in all_zones) <= 1)
                    for day in WeekDayList(week_start, num_days):
                        for zone in all_zones:
                            for shift in [MORN_SHIFT, NIGHT_SHIFT]:
                                model.AddImplication(shifts[(doc, day, shift, zone)], doc_zones[(doc, week_start, zone)])

    for doc in all_doctors:
        for day in all_days[:-1]:
            AddConsecutiveShiftConstraint(model, shifts, doc, day, NIGHT_SHIFT, MORN_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, NIGHT_SHIFT, NSM_SHIFT)
            AddConsecutiveShiftConstraint(model, shifts, doc, day, NSM_SHIFT, MORN_SHIFT)
        for day in all_days[:-max_consecutive_morn_shifts]:
            if day >= 22:
                model.Add(sum(shifts[(doc, day + diff, MORN_SHIFT, zone)] for zone in all_zones for diff in range(max_consecutive_morn_shifts + 1)) <= max_consecutive_morn_shifts)
        for day in all_days[:-max_consecutive_night_shifts]:
            if day >= 22:
                model.Add(sum(shifts[(doc, day + diff, NIGHT_SHIFT, zone)] for zone in all_zones for diff in range(max_consecutive_night_shifts + 1)) <= max_consecutive_night_shifts)
        # for shift in all_shifts:
        #     for day in all_days[:-doctors[doc].min_consecutive]:
        #         if day >= 16:
        #             model.Add(sum(shifts[(doc, day + diff, shift, zone)] for zone in all_zones for diff in range(doctors[doc].min_consecutive + 1)) >= doctors[doc].min_consecutive)
        for week_start in [1,7,13,19,25]:
            diff = min(week_start + 6, 31) - week_start
            model.AddLinearExpressionInDomain(sum(shifts[(doc, day, NSM_SHIFT, NSM_ZONE)] for day in range(week_start, week_start + diff)), cp_model.Domain.FromValues([0, diff]))
        for week_start in week_starts:
            if week_start >= 22:
                model.Add(sum(shifts[(doc, day, shift, zone)] for shift in [MORN_SHIFT, NIGHT_SHIFT] for zone in all_zones for day in WeekDayList(week_start, num_days)) <= doctors[doc].max_week_shifts)
                if doctors[doc].name != "Dr. Shivanvesh" and week_start != 29 and week_start >= 22:
                    model.Add(sum(shifts[(doc, day, shift, zone)] for shift in [MORN_SHIFT, NIGHT_SHIFT] for zone in all_zones for day in WeekDayList(week_start, num_days)) >= doctors[doc].min_week_shifts)
    for day, shift_list in shifts_done.items():
        shift_index = 0
        for shift in shift_list:
            doc_names = shift.split(",")
            for doc_name in doc_names:
                doc = IndexOfDoctorName(doc_name.strip())
                assert doc != -1, "'" + doc_name + "'"
                model.Add(shifts[(doc, day, shift_index % 2, shift_index // 2)] == True)
            shift_index += 1

    for doc in all_doctors:
        doc_obj = doctors[doc]
        num_morn_12_shifts_worked = sum(
            shifts[(doc, day, MORN_SHIFT, ZONE_12)] for day in all_days)
        num_morn_34_shifts_worked = sum(
            shifts[(doc, day, MORN_SHIFT, ZONE_34)] for day in all_days)
        num_morn_shifts_worked = sum(
            shifts[(doc, day, MORN_SHIFT, zone)] for day in all_days for zone in all_zones)
        num_total_shifts_worked = 7 * num_morn_shifts_worked
        if doctors[doc].name != "Dr. Amla" and doctors[doc].name != "Dr. Anand" and doctors[doc].name != "Dr. Naveen":
            model.Add(num_morn_shifts_worked <= doc_obj.max_shifts // 2 + 1)
            model.Add(num_morn_12_shifts_worked <= doc_obj.max_shifts // 4 + 1)
            if doctors[doc].name != "Dr. Priyam":
                model.Add(num_morn_12_shifts_worked >= doc_obj.max_shifts // 4 - 1)
        # model.Add(num_morn_shifts_worked >= doc_obj.max_shifts // 2)
        num_night_12_shifts_worked = sum(
            shifts[(doc, day, NIGHT_SHIFT, ZONE_12)] for day in all_days)
        num_night_34_shifts_worked = sum(
            shifts[(doc, day, NIGHT_SHIFT, ZONE_34)] for day in all_days)
        num_night_shifts_worked = sum(
            shifts[(doc, day, NIGHT_SHIFT, zone)] for day in all_days for zone in all_zones)
        num_total_shifts_worked += 7 * num_night_shifts_worked
        if doctors[doc].name != "Dr. Priyam":
            model.Add(num_night_shifts_worked <= doc_obj.max_shifts // 2 + 1)
        if doctors[doc].name != "Dr. Amla" and doctors[doc].name != "Dr. Anand" and doctors[doc].name != "Dr. Naveen":
            model.Add(num_night_shifts_worked >= doc_obj.max_shifts // 2)
            # if doc_obj.name != "Dr. Priyam" and doc_obj.name != "Dr. Sangeet":
            #     model.Add(num_night_12_shifts_worked <= doc_obj.max_shifts // 4 + 1)
            model.Add(num_night_12_shifts_worked >= doc_obj.max_shifts // 4 - 1)
        num_nsm_shifts_worked = sum(
            shifts[(doc, day, NSM_SHIFT, NSM_ZONE)] for day in all_days)
        model.Add(num_nsm_shifts_worked <= max_nsm_shifts)
        num_total_shifts_worked += nsm_shifts_per_week * num_nsm_shifts_worked
        model.Add(num_total_shifts_worked <= (doc_obj.max_shifts - 0) * 7)
        if doc_obj.name != "Dr. Neelima":
            model.Add(sum(shifts[(doc, day, shift, ZONE_12)] for day in all_days for shift in all_shifts) <= doc_obj.max_shifts // 2)
        else:
            model.Add(sum(shifts[(doc, day, shift, ZONE_12)] for day in all_days for shift in all_shifts) <= doc_obj.max_shifts // 2 + 1)
        if doc_obj.name == "Dr. Vishnu" or doc_obj.name == "Dr. Anand" or doc_obj.name == "Dr. Amla":
            model.Add(num_total_shifts_worked >= (doc_obj.max_shifts) * 7)
        elif doc_obj.name == "Dr. Priyam" or doc_obj.name == "Dr. Naveen":
            model.Add(num_total_shifts_worked >= (doc_obj.max_shifts - 2) * 7)
        else:
            model.Add(num_total_shifts_worked >= (doc_obj.max_shifts - 1) * 7)

    for doc in all_doctors:
        for shift, days in doctors[doc].shift_exclusions.items():
            for day in days:
                model.Add(sum(shifts[(doc, day, shift, zone)] for zone in all_zones) == 0)

    for doc in all_doctors:
        for zone in doctors[doc].zone_exclusions:
            model.Add(sum(shifts[(doc, day, shift, zone)] for shift in all_shifts for day in all_days[22:]) == 0)

    for doc in all_doctors:
        for de in doctors[doc].doctor_exclusions:
            de_index = IndexOfDoctorName(de)
            assert de_index != -1
            for zone in all_zones:
                for day in all_days:
                    for shift in all_shifts:
                        model.Add(shifts[(doc, day, shift, zone)] + shifts[(de_index, day, shift, zone)] <= 1)
                    model.Add(shifts[(doc, day, MORN_SHIFT, zone)] + shifts[(de_index, day, NIGHT_SHIFT, zone)] <= 1)
                    model.Add(shifts[(de_index, day, MORN_SHIFT, zone)] + shifts[(doc, day, NIGHT_SHIFT, zone)] <= 1)
                for day in all_days[:-1]:
                    model.Add(shifts[(doc, day, NIGHT_SHIFT, zone)] + shifts[(de_index, day + 1, MORN_SHIFT, zone)] <= 1)
                    model.Add(shifts[(de_index, day, NIGHT_SHIFT, zone)] + shifts[(doc, day + 1, MORN_SHIFT, zone)] <= 1)

    for doc in all_doctors:
        if not doctors[doc].nsm_duty:
            model.Add(sum(shifts[(doc, day, NSM_SHIFT, NSM_ZONE)] for day in all_days) == 0)

    for doc in all_doctors:
        for day in doctors[doc].vacations:
            model.Add(sum(shifts[(doc, day, shift, zone)] for shift in all_shifts for zone in all_zones) == 0)
            if day >= 22:
                model.Add(sum(shifts[(doc, day - 1, NIGHT_SHIFT, zone)] for zone in all_zones) == 0)

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
        fieldnames = ['Day', 'Date', 'Morning zone 1/2', 'Night zone 1/2', 'Morning zone 3/4',
                'Night zone 3/4', 'NSM', 'Morning total', 'Night total', 'Total']
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
                            if shift != NSM_SHIFT:
                                print(PrettyPrintDoctor(doc), 'works the ', PrettyPrintShift(shift), ' shift in zone ', PrettyPrintZone(zone))
                            else:
                                print(PrettyPrintDoctor(doc), 'works the ', PrettyPrintShift(shift), ' shift.')
                    if shift != NSM_SHIFT:
                        row[PrettyPrintShift(shift) + ' zone ' + PrettyPrintZone(zone)] = ','.join(per_zone_doctors)
                    else:
                        per_shift_doctors.extend(per_zone_doctors)
                if shift == NSM_SHIFT:
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
                    if shift == NSM_SHIFT:
                        doc_shifts *= nsm_shifts_per_week / 7
                    else:
                        row[PrettyPrintShift(shift) + ' zone ' + PrettyPrintZone(zone)] = doc_shifts
                        print(PrettyPrintDoctor(doc), 'has ', doc_shifts, ' ', PrettyPrintShift(shift), 'shifts in zone ', PrettyPrintZone(zone))
                    total += doc_shifts
                print(PrettyPrintDoctor(doc), 'has ', shift_total, ' ', PrettyPrintShift(shift), 'shifts.')
                if shift == NSM_SHIFT:
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
