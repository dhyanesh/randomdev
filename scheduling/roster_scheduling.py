from __future__ import print_function
from ortools.sat.python import cp_model


def main():
    num_doctors = 18
    num_shifts = 2
    num_days = 7
    num_day_doctors = 3
    num_night_doctors = 5
    all_doctors = range(num_doctors)
    all_shifts = range(num_shifts)
    all_days = range(num_days)
    MORN_SHIFT = 0
    NIGHT_SHIFT = 1
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
    # shifts[(doc, day, shift)]:
    shifts = {}
    for doc in all_doctors:
        for day in all_days:
            for shift in all_shifts:
                shifts[(doc, day, shift)] = model.NewBoolVar('shift_doc%iday%ishift%i' % (doc, day, shift))

    # Set the number of day and night doctors.
    for day in all_days:
        model.Add(sum(shifts[(doc, day, MORN_SHIFT)] for doc in all_doctors) == num_day_doctors)
        model.Add(sum(shifts[(doc, day, NIGHT_SHIFT)] for doc in all_doctors) == num_night_doctors)

    # Each doctor works at most one shift per day.
    for doc in all_doctors:
        for day in all_days:
            model.Add(sum(shifts[(doc, day, shift)] for shift in all_shifts) <= 1)

    # No doctor works two consecutive night shifts.
    for doc in all_doctors:
        for day in range(num_days - 1):
            model.Add(shifts[(doc, day, NIGHT_SHIFT)] + shifts[(doc, day + 1, NIGHT_SHIFT)] <= 1)

    # No doctor works night then day.
    for doc in all_doctors:
        for day in range(num_days - 1):
            model.Add(shifts[(doc, day, NIGHT_SHIFT)] + shifts[(doc, day + 1, MORN_SHIFT)] <= 1)

    # # min_shifts_assigned is the largest integer such that every doctor can be
    # # assigned at least that number of shifts.
    # min_shifts_per_doctor = (num_shifts * num_days) // num_doctors
    # max_shifts_per_doctor = min_shifts_per_doctor + 1
    # for n in all_doctors:
    #     num_shifts_worked = sum(
    #         shifts[(n, d, s)] for d in all_days for s in all_shifts)
    #     model.Add(min_shifts_per_doctor <= num_shifts_worked)
    #     model.Add(num_shifts_worked <= max_shifts_per_doctor)

    # model.Maximize(
    #     sum(shift_requests[n][d][s] * shifts[(n, d, s)] for n in all_doctors
    #         for d in all_days for s in all_shifts))
    # Creates the solver and solve.
    solver = cp_model.CpSolver()
    solver.Solve(model)
    # sum_shifts = [][]
    for day in all_days:
        print('Day', day)
        for shift in all_shifts:
            for doc in all_doctors:
                if solver.Value(shifts[(doc, day, shift)]) == 1:
                    # sum_shifts[doc][shift] += 1
                    print('Doctor', doc, 'works shift', shift)
                    # if shift_requests[n][d][s] == 1:
                    #     print('Doctor', n, 'works shift', s, '(requested).')
                    # else:
                    #     print('Doctor', n, 'works shift', s, '(not requested).')
        print()

    # Statistics.
    print()
    print('Statistics')
    # for doc in all_doctors:
    #     print('Doctor', doc, 'has ', sum_shifts[doc][MORN_SHIFT], ' morning shifts.')
    #     print('Doctor', doc, 'has ', sum_shifts[doc][NIGHT_SHIFT], ' night shifts.')
    # print('  - Number of shift requests met = %i' % solver.ObjectiveValue(),
    #       '(out of', num_doctors * min_shifts_per_doctor, ')')
    print('  - wall time       : %f s' % solver.WallTime())


if __name__ == '__main__':
    main()
