import datetime
from monthly_constraints.base import MonthlyConstraints

class October2025Constraints(MonthlyConstraints):
    """
    Applies the specific requests for October 2025.
    """
    def apply_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
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
