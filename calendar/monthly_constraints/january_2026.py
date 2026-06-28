import datetime
from monthly_constraints.base import MonthlyConstraints

class January2026Constraints(MonthlyConstraints):
    """
    Applies the specific requests for January 2026.
    """

    def get_cl_days(self):
        return {'MNS': 24}

    def get_special_night_consultants(self):
        return ['MNS']

    def apply_shift_size_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        for d in all_days:
            date = datetime.date(year, month, d)
            # Relaxed shift size for 10, 11 (Weekend/Conf) and 13-16 (Heavy Leave Requests)
            if date.weekday() == 6 or d in [1, 5, 6, 10, 11, 13, 14, 15, 16]:
                model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) == 2)
            else:
                model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) == 3)
            
            if date.weekday() == 6 and d != 4:
                 model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) == 1)
            else:
                 model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) == 0)
            
            model.Add(sum(shifts[(c, d, 2)] for c in range(len(consultants))) == 2)

    def apply_night_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        senior_indices = [i for i, c in enumerate(consultants) if c.is_senior]
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        sj_index = next(i for i, c in enumerate(consultants) if c.initial == 'SJ')
        mh_index = next(i for i, c in enumerate(consultants) if c.initial == 'MH')
        ps_index = next(i for i, c in enumerate(consultants) if c.initial == 'PS')

        for d in all_days:
            if d != 4:
                model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)
            model.Add(shifts[(am_index, d, 2)] + shifts[(sj_index, d, 2)] <= 1)
            model.Add(shifts[(am_index, d, 2)] + shifts[(mh_index, d, 2)] <= 1)
            if d < len(all_days):
                for c_idx, c in enumerate(consultants):
                    if c.initial != 'MH':
                        model.Add(shifts[(c_idx, d, 2)] + shifts[(c_idx, d + 1, 2)] <= 1)
        model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)
        for c_idx, c in enumerate(consultants):
            if c.initial in ['MNS', 'MH', 'PS']: continue
            num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
            model.Add(num_nights >= 5)
            model.Add(num_nights <= 8)

    def apply_consultant_specific_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        sj_index = next(i for i, c in enumerate(consultants) if c.initial == 'SJ')
        mittal_index = next(i for i, c in enumerate(consultants) if c.initial == 'MT')
        for d in all_days:
            model.Add(shifts[(am_index, d, 1)] == 0)
            model.Add(shifts[(sj_index, d, 1)] == 0)
            am_day_side = shifts[(am_index, d, 0)] + shifts[(am_index, d, 1)]
            mt_day_side = shifts[(mittal_index, d, 0)] + shifts[(mittal_index, d, 1)]
            model.Add(am_day_side + mt_day_side <= 1)
            model.Add(shifts[(am_index, d, 2)] + shifts[(mittal_index, d, 2)] <= 1)
            date = datetime.date(year, month, d)
            if date.weekday() == 0 or date.weekday() == 2: model.Add(shifts[(mittal_index, d, 2)] == 0)
            if date.weekday() == 6: model.Add(shifts[(mittal_index, d, 0)] == 0)

    def apply_post_night_duty_constraints(self, model, shifts, consultants, all_days, all_shifts, previous_month_roster=None):
        for c in range(len(consultants)):
            for d in all_days[:-1]:
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        exceptions = ['MT', 'MNS', 'AM', 'SB', 'PK', 'PS', 'MH']
        exception_indices = [i for i, c in enumerate(consultants) if c.initial in exceptions]
        for c in range(len(consultants)):
            if c in exception_indices: continue
            for d in range(1, len(all_days) - 3):
                model.Add(sum(shifts[(c, i, s)] for i in range(d, d + 5) for s in all_shifts) >= 1)


    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster=None, cl_days=None):
        self.apply_one_shift_per_day_constraint(model, shifts, consultants, all_days, all_shifts)
        self.apply_shift_size_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_consultant_specific_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_night_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_post_night_duty_constraints(model, shifts, consultants, all_days, all_shifts, None)
        self.apply_leave_constraints(model, shifts, consultants, all_days, all_shifts)
        self.apply_working_hours_constraints(model, shifts, consultants, all_days, all_shifts, cl_days)
        
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        mns_idx = consultant_map['MNS']; mh_idx = consultant_map['MH']; ps_idx = consultant_map['PS']
        sj_idx = consultant_map['SJ']; sk_idx = consultant_map['SK']; pk_idx = consultant_map['PK']
        mj_idx = consultant_map['MJ']; sb_idx = consultant_map['SB']; am_idx = consultant_map['AM']

        for d in all_days:
            for s in all_shifts: model.Add(shifts[(mns_idx, d, s)] == 0)
        
        for d in [10, 11, 24, 25]: model.Add(shifts[(mh_idx, d, 2)] == 1)
        for d in [2, 5, 6, 7, 9, 16, 19, 20, 21, 23, 27, 28, 29, 31]: model.Add(shifts[(mh_idx, d, 0)] == 1)
        for d in [17, 19, 23, 26, 31]: model.Add(shifts[(ps_idx, d, 2)] == 1)
        for d in [10, 13, 16, 22, 25, 29, 30]: model.Add(shifts[(ps_idx, d, 0)] == 1)
        
        # --- Leave requests ---
        def add_leave(c_idx, days):
             for d in days:
                 if d <= 7: continue
                 for s in all_shifts: model.Add(shifts[(c_idx, d, s)] == 0)

        add_leave(sj_idx, [1, 10, 11, 23, 24])
        add_leave(sk_idx, [1, 2, 3, 9, 22, 23])
        add_leave(pk_idx, [6, 7, 17, 18, 26, 27])
        # add_leave(mj_idx, [13, 14, 15])
        add_leave(sb_idx, [1, 13, 14, 15, 16])
        add_leave(am_idx, [4, 5, 6, 7, 20, 21, 25, 26, 27])

    def calculate_preference_score(self, model, shifts, consultants, all_days, all_shifts, year, month):
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        sj_idx = consultant_map['SJ']; sb_idx = consultant_map['SB']; am_idx = consultant_map['AM']; sk_idx = consultant_map['SK']
        pk_idx = consultant_map['PK']; mj_idx = consultant_map['MJ']
        pos_pref = []
        pos_pref.append(shifts[(sj_idx, 22, 0)])
        pos_pref.append(shifts[(sb_idx, 11, 2)] * 10)
        pos_pref.append(shifts[(am_idx, 3, 0)] * 10)
        pos_pref.append(shifts[(am_idx, 24, 0)] * 10)
        pos_pref.append(shifts[(am_idx, 18, 2)] * 10)
        for d in [11, 18, 25]: pos_pref.append(shifts[(sk_idx, d, 0)] * 100)


        for d in all_days:
            m3 = model.NewBoolVar(f'm3_{d}')
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) == 3).OnlyEnforceIf(m3)
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) != 3).OnlyEnforceIf(m3.Not())
            pos_pref.append(m3 * 500)
            
        # for c_idx, c in enumerate(consultants):
        #     if c.initial in ['MH', 'MNS']: continue
        #     h6 = model.NewBoolVar(f'h6_{c.initial}')
        #     num_n = sum(shifts[(c_idx, d, 2)] for d in all_days)
        #     model.Add(num_n >= 6).OnlyEnforceIf(h6)
        #     model.Add(num_n < 6).OnlyEnforceIf(h6.Not())
        #     pos_pref.append(h6 * 5000)
            
        pref_score = model.NewIntVar(-100000, 100000, 'pref_score')
        model.Add(pref_score == sum(pos_pref))
        return pref_score