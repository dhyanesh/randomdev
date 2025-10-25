import datetime
from monthly_constraints.base import MonthlyConstraints

class November2025Constraints(MonthlyConstraints):
    """
    Applies the specific requests for November 2025.
    """

    def get_cl_days(self):
        return {'AM': 1, 'SJ': 2, 'MJ': 5}

    def get_special_night_consultants(self):
        return []

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        pass

    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster=None):
        super().apply_hard_constraints(model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster)

        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        pk_idx = consultant_map['PK']
        sk_idx = consultant_map['SK']
        sb_idx = consultant_map['SB']
        am_idx = consultant_map['AM']
        mt_idx = consultant_map['MT']
        mj_idx = consultant_map['MJ']
        sj_idx = consultant_map['SJ']
        mns_idx = consultant_map['MNS']
        mh_idx = consultant_map['MH']

        # PK leave
        for d in [12, 13, 25, 26]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)

        # SK leave
        for d in [1, 2, 15, 16]:
            for s in all_shifts:
                model.Add(shifts[(sk_idx, d, s)] == 0)

        # SK 2 Sunday mornings
        sundays = [d for d in all_days if datetime.date(year, month, d).weekday() == 6]
        model.Add(sum(shifts[(sk_idx, d, 0)] for d in sundays) == 2)

        # SB leave
        for d in [8, 9, 10]:
            for s in all_shifts:
                model.Add(shifts[(sb_idx, d, s)] == 0)
        model.Add(shifts[(sb_idx, 6, 2)] == 1)

        # AM leave
        for d in [1, 3, 4, 5, 17, 18, 19, 24, 25, 26]:
            for s in all_shifts:
                model.Add(shifts[(am_idx, d, s)] == 0)
        model.Add(shifts[(am_idx, 23, 2)] == 1)
        model.Add(shifts[(am_idx, 30, 2)] == 1)

        # MT leave
        for d in [1, 2]:
            for s in all_shifts:
                model.Add(shifts[(mt_idx, d, s)] == 0)
        for d in range(3, 7):
            model.Add(shifts[(mt_idx, d, 1)] == 0)
            model.Add(shifts[(mt_idx, d, 2)] == 0)

        # MNS leave
        for d in range(1, 6):
            for s in all_shifts:
                model.Add(shifts[(mns_idx, d, s)] == 0)

        # SJ leave
        for d in [9, 14, 15, 16, 19, 20]:
            for s in all_shifts:
                model.Add(shifts[(sj_idx, d, s)] == 0)
        
        # MJ leave
        for d in [4, 5, 6, 28, 29, 30]:
            for s in all_shifts:
                model.Add(shifts[(mj_idx, d, s)] == 0)

        # MH night preferences
        for d in [1, 2, 8, 9]:
            model.Add(shifts[(mh_idx, d, 2)] == 1)

        # Mohan vacation on 21 and 26
        for d in [21, 26]:
            for s in all_shifts:
                model.Add(shifts[(mh_idx, d, s)] == 0)

        # Amirtha holiday on 16th night
        model.Add(shifts[(am_idx, 16, 2)] == 0)

        # PK holiday on 10th
        for s in all_shifts:
            model.Add(shifts[(pk_idx, 10, s)] == 0)

        # PK can only do morning shift on 1st
        model.Add(shifts[(pk_idx, 1, 1)] == 0)
        model.Add(shifts[(pk_idx, 1, 2)] == 0)

        # Mittal holidays on 29th and 30th
        for d in [29, 30]:
            for s in all_shifts:
                model.Add(shifts[(mt_idx, d, s)] == 0)

        # Mittal 6 nights
        model.Add(sum(shifts[(mt_idx, d, 2)] for d in all_days) == 6)

    def apply_soft_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        ps_idx = consultant_map['PS']
        mh_idx = consultant_map['MH']
        sk_idx = consultant_map['SK']

        positive_preferences = []
        negative_preferences = []

        # PS preferences
        positive_preferences.extend([shifts[(ps_idx, d, s)] for d in [11, 14, 15, 20, 23, 26, 28] for s in [0, 1]])
        positive_preferences.extend([shifts[(ps_idx, d, 2)] for d in [3, 4, 6, 9, 12, 18, 24, 30]])

        # MH preferences
        positive_preferences.extend([shifts[(mh_idx, d, 0)] for d in [4, 5, 6, 7, 11, 12, 13, 14, 17, 18, 19, 27, 28, 29]])

        # SK preferences
        saturdays = [d for d in all_days if datetime.date(year, month, d).weekday() == 5]
        positive_preferences.extend([shifts[(sk_idx, d, 0)] for d in saturdays])
        weekdays = [d for d in all_days if datetime.date(year, month, d).weekday() < 5]
        weekends = [d for d in all_days if datetime.date(year, month, d).weekday() >= 5]
        positive_preferences.extend([shifts[(sk_idx, d, 1)] for d in weekdays])
        negative_preferences.extend([shifts[(sk_idx, d, 2)] for d in weekends])

        preference_score = model.NewIntVar(-500, 500, 'preference_score')
        model.Add(preference_score == sum(positive_preferences) - sum(negative_preferences))

        return preference_score
