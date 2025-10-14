import datetime
from monthly_constraints.base import MonthlyConstraints

class October2025Constraints(MonthlyConstraints):
    """
    Applies the specific requests for October 2025.
    """

    def get_cl_days(self):
        return {'PK': 4, 'MT': 2, 'AM': 2}

    def get_special_night_consultants(self):
        return ['MT', 'AM']

    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        # Apply general hard constraints
        super().apply_one_shift_per_day_constraint(model, shifts, consultants, all_days, all_shifts)
        super().apply_shift_size_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        super().apply_night_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        super().apply_post_night_duty_constraints(model, shifts, consultants, all_days, all_shifts)
        super().apply_leave_constraints(model, shifts, consultants, all_days, all_shifts)

        # Apply October-specific hard constraints
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

        # SK needs leave on 20
        for s in all_shifts:
            model.Add(shifts[(sk_idx, 20, s)] == 0)

        # PK needs leave on 20, 25, 26
        for d in [20, 25, 26]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)

        # PK needs 4 days CL from Oct 2-5
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

        # MT needs to be off Oct 1, 2, 3
        for d in [1, 2, 3]:
            for s in all_shifts:
                model.Add(shifts[(mt_idx, d, s)] == 0)
        
        # MT No morning shift on Oct 14th
        model.Add(shifts[(mt_idx, 14, 0)] == 0)

        # MT No morning shift on Oct 7th
        model.Add(shifts[(mt_idx, 7, 0)] == 0)

        # MT No night shift on Oct 26th
        model.Add(shifts[(mt_idx, 26, 2)] == 0)

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
        model.Add(sum(shifts[(mt_idx, d, 2)] for d in all_days) <= 6)
        model.Add(sum(shifts[(am_idx, d, 2)] for d in all_days) <= 6)

        # Mohan no afternoon shifts
        model.Add(sum(shifts[(mh_idx, d, 1)] for d in all_days) == 0)

        # Mohan needs vacation from 24 to 26th
        for d in [24, 25, 26]:
            for s in all_shifts:
                model.Add(shifts[(mh_idx, d, s)] == 0)

        # Mittal: After the 27th, only two consecutive night duties are allowed.
        days_after_27 = range(27, 32)
        model.Add(sum(shifts[(mt_idx, d, s)] for d in days_after_27 for s in all_shifts) == 2)
        model.Add(sum(shifts[(mt_idx, d, 2)] for d in days_after_27) == 2)
        consecutive_nights_vars = []
        for d in range(27, 31):
            v = model.NewBoolVar(f'mt_consecutive_nights_{d}')
            model.AddBoolAnd([shifts[(mt_idx, d, 2)], shifts[(mt_idx, d + 1, 2)]]).OnlyEnforceIf(v)
            model.AddBoolOr([shifts[(mt_idx, d, 2)].Not(), shifts[(mt_idx, d + 1, 2)].Not()]).OnlyEnforceIf(v.Not())
            consecutive_nights_vars.append(v)
        model.Add(sum(consecutive_nights_vars) == 1)

        # Mohan: Put nights on 7th and 12th. Remove 19th and 25th night. Instead of 18th morning put 6th morning.
        model.Add(shifts[(mh_idx, 7, 2)] == 1)
        model.Add(shifts[(mh_idx, 12, 2)] == 1)
        model.Add(shifts[(mh_idx, 19, 2)] == 0)
        model.Add(shifts[(mh_idx, 25, 2)] == 0)
        model.Add(shifts[(mh_idx, 18, 0)] == 0)
        model.Add(shifts[(mh_idx, 6, 0)] == 1)

    def apply_soft_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
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

        positive_preferences = []
        negative_preferences = []

        # PS
        positive_preferences.extend([shifts[(ps_idx, d, 2)] for d in [7, 10, 11, 13, 18, 25, 31]])
        positive_preferences.extend([shifts[(ps_idx, d, s)] for d in [3, 6, 9, 15, 21, 27, 30] for s in [0, 1]])
        positive_preferences.extend([shifts[(ps_idx, d, 0)] for d in [17, 23]])

        # MH
        positive_preferences.extend([shifts[(mh_idx, d, 2)] for d in [2, 21]])
        positive_preferences.extend([shifts[(mh_idx, d, 0)] for d in [5, 9, 10, 14, 15, 16, 17, 20, 23, 27, 28, 29, 30]])

        # SK
        saturdays = [d for d in all_days if datetime.date(year, month, d).weekday() == 5]
        sundays = [d for d in all_days if datetime.date(year, month, d).weekday() == 6]
        weekdays = [d for d in all_days if datetime.date(year, month, d).weekday() < 5]
        weekends = saturdays + sundays
        positive_preferences.extend([shifts[(sk_idx, d, 0)] for d in weekends])
        positive_preferences.extend([shifts[(sk_idx, d, 1)] for d in weekdays])
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
        positive_preferences.append(shifts[(sj_idx, 20, 0)])

        preference_score = model.NewIntVar(-500, 500, 'preference_score')
        model.Add(preference_score == sum(positive_preferences) - sum(negative_preferences))

        return preference_score