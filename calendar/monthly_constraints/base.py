import datetime

class MonthlyConstraints:
    """
    Base class for applying constraints to the roster model.
    """

    def apply_all_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster=None):
        cl_days = self.get_cl_days()
        self.apply_hard_constraints(model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster, cl_days)
        return cl_days

    def get_cl_days(self):
        return {}

    def get_special_night_consultants(self):
        return []

    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster=None, cl_days=None):
        if cl_days is None:
            cl_days = {}
        self.apply_one_shift_per_day_constraint(model, shifts, consultants, all_days, all_shifts)
        self.apply_shift_size_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_consultant_specific_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_night_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_post_night_duty_constraints(model, shifts, consultants, all_days, all_shifts, previous_month_roster)
        self.apply_leave_constraints(model, shifts, consultants, all_days, all_shifts)
        self.apply_simmy_consecutive_shifts_constraint(model, shifts, consultants, all_days)
        self.apply_working_hours_constraints(model, shifts, consultants, all_days, all_shifts, cl_days)

    def calculate_preference_score(self, model, shifts, consultants, all_days, all_shifts, year, month):
        return model.NewIntVar(0, 0, 'preference_score')

    def get_objective_expression(self, model, shifts, consultants, all_days, all_shifts, year, month):
        general_cost = self.calculate_general_soft_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        preference_score = self.calculate_preference_score(model, shifts, consultants, all_days, all_shifts, year, month)
        return general_cost - preference_score

    def apply_working_hours_constraints(self, model, shifts, consultants, all_days, all_shifts, cl_days):
        for c_idx, c in enumerate(consultants):
            consultant_cl_days = cl_days.get(c.initial, 0)
            target_hours = 192 - (consultant_cl_days * 8)
            total_hours_expr = sum(shifts[(c_idx, d, 0)] * 9 + shifts[(c_idx, d, 1)] * 8 + shifts[(c_idx, d, 2)] * 15 for d in all_days)
            model.Add(total_hours_expr <= 200) # Hard constraint
            model.Add(total_hours_expr >= target_hours - 32) # Hard constraint with wider window

    def calculate_general_soft_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        num_days = len(all_days)
        all_consultants = range(len(consultants))

        # 1. Weekend Fairness
        weekend_days = [d for d in all_days if datetime.date(year, month, d).weekday() >= 5]
        weekend_shifts_per_consultant = [sum(shifts[(c, d, s)] for d in weekend_days for s in all_shifts) for c in all_consultants]
        min_weekend_shifts = model.NewIntVar(0, num_days, 'min_weekend_shifts')
        max_weekend_shifts = model.NewIntVar(0, num_days, 'max_weekend_shifts')
        model.AddMinEquality(min_weekend_shifts, weekend_shifts_per_consultant)
        model.AddMaxEquality(max_weekend_shifts, weekend_shifts_per_consultant)
        weekend_fairness_diff = max_weekend_shifts - min_weekend_shifts

        # 2. Working Hours Target (Soft)
        cl_days = self.get_cl_days()
        total_hours_deviations = []
        for c_idx, c in enumerate(consultants):
            consultant_cl_days = cl_days.get(c.initial, 0)
            target_hours = 192 - (consultant_cl_days * 8)
            total_hours_expr = sum(shifts[(c_idx, d, 0)] * 9 + shifts[(c_idx, d, 1)] * 8 + shifts[(c_idx, d, 2)] * 15 for d in all_days)
            deviation = model.NewIntVar(0, 100, f'deviation_c{c_idx}')
            model.AddAbsEquality(deviation, total_hours_expr - target_hours)
            total_hours_deviations.append(deviation)
        
        total_hours_deviation = model.NewIntVar(0, 1000, 'total_hours_deviation')
        model.Add(total_hours_deviation == sum(total_hours_deviations))

        # 3. Night Shift Fairness Preference
        fair_night_consultants = [i for i, c in enumerate(consultants) if c.initial != 'MH']
        night_shifts_per_consultant = [sum(shifts[(c, d, 2)] for d in all_days) for c in fair_night_consultants]
        min_night_shifts = model.NewIntVar(0, num_days, 'min_night_shifts')
        max_night_shifts = model.NewIntVar(0, num_days, 'max_night_shifts')
        model.AddMinEquality(min_night_shifts, night_shifts_per_consultant)
        model.AddMaxEquality(max_night_shifts, night_shifts_per_consultant)
        nights_fairness_diff = max_night_shifts - min_night_shifts

        # 4. Consecutive Night Shift Preference
        consecutive_night_vars = []
        for c in all_consultants:
            for d in all_days[:-1]:
                lit1 = shifts[(c, d, 2)]
                lit2 = shifts[(c, d + 1, 2)]
                consecutive = model.NewBoolVar(f'consecutive_c{c}_d{d}')
                model.AddBoolAnd([lit1, lit2]).OnlyEnforceIf(consecutive)
                model.AddBoolOr([lit1.Not(), lit2.Not()]).OnlyEnforceIf(consecutive.Not())
                consecutive_night_vars.append(consecutive)
        
        return weekend_fairness_diff * 4 + total_hours_deviation + nights_fairness_diff * 4 + sum(consecutive_night_vars) * 10

    def apply_one_shift_per_day_constraint(self, model, shifts, consultants, all_days, all_shifts):
        for c in range(len(consultants)):
            for d in all_days:
                model.Add(sum(shifts[(c, d, s)] for s in all_shifts) <= 1)

    def apply_shift_size_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        for d in all_days:
            # Morning: Exactly 3 people
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) == 3)
            
            date = datetime.date(year, month, d)
            # Afternoon: Optional (0 or 1) on all days
            model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) <= 1)
            model.Add(sum(shifts[(c, d, 2)] for c in range(len(consultants))) == 2)

    def apply_consultant_specific_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        sj_index = next(i for i, c in enumerate(consultants) if c.initial == 'SJ')
        mittal_index = next(i for i, c in enumerate(consultants) if c.initial == 'MT')

        for d in all_days:
            model.Add(shifts[(am_index, d, 1)] == 0)
            model.Add(shifts[(sj_index, d, 1)] == 0)

            # Prevent AM and MT from working on the same shift "side" (Day/Afternoon vs Night)
            # They CAN work on the same day if one is Day/Afternoon and the other is Night.
            
            # 1. Cannot both be on Morning/Afternoon side
            am_day_side = shifts[(am_index, d, 0)] + shifts[(am_index, d, 1)]
            mt_day_side = shifts[(mittal_index, d, 0)] + shifts[(mittal_index, d, 1)]
            model.Add(am_day_side + mt_day_side <= 1)
            
            # 2. Cannot both be on Night side
            model.Add(shifts[(am_index, d, 2)] + shifts[(mittal_index, d, 2)] <= 1)

            date = datetime.date(year, month, d)
            if date.weekday() == 0 or date.weekday() == 2:
                model.Add(shifts[(mittal_index, d, 2)] == 0)
            if date.weekday() == 6:
                model.Add(shifts[(mittal_index, d, 0)] == 0)

    def apply_night_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        senior_indices = [i for i, c in enumerate(consultants) if c.is_senior]
        female_indices = [i for i, c in enumerate(consultants) if c.gender == 'Female']
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        mh_index = next(i for i, c in enumerate(consultants) if c.initial == 'MH')

        for d in all_days:
            model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)
            model.Add(sum(shifts[(c, d, 2)] for c in female_indices) <= 1)
            model.Add(shifts[(am_index, d, 2)] + shifts[(mh_index, d, 2)] <= 1)
            
            # No back-to-back night shifts
            if d < len(all_days):
                for c_idx, c in enumerate(consultants):
                    if c.initial != 'MH':
                        model.Add(shifts[(c_idx, d, 2)] + shifts[(c_idx, d + 1, 2)] <= 1)

        model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)

        special_night_consultants = self.get_special_night_consultants()
        for c_idx, c in enumerate(consultants):
            if c.initial != 'MH' and c.initial not in special_night_consultants:
                num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
                model.Add(num_nights >= 6)
                model.Add(num_nights <= 7)

    def apply_post_night_duty_constraints(self, model, shifts, consultants, all_days, all_shifts, previous_month_roster=None):
        for c in range(len(consultants)):
            for d in all_days[:-1]:
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

        if previous_month_roster:
            last_day_of_previous_month = max(previous_month_roster.keys())
            for c_idx, c in enumerate(consultants):
                if c.initial in previous_month_roster[last_day_of_previous_month]['night']:
                    model.Add(shifts[(c_idx, 1, 0)] == 0)
                    model.Add(shifts[(c_idx, 1, 1)] == 0)
                    model.Add(shifts[(c_idx, 1, 2)] == 0)

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        for c in range(len(consultants)):
            for d in range(1, len(all_days) - 3):
                model.Add(sum(shifts[(c, i, s)] for i in range(d, d + 5) for s in all_shifts) >= 1)

    def apply_simmy_consecutive_shifts_constraint(self, model, shifts, consultants, all_days):
        sj_index = next(i for i, c in enumerate(consultants) if c.initial == 'SJ')
        consecutive_shifts_vars = []
        for d in range(1, len(all_days) - 2):
            v = model.NewBoolVar(f'sj_consecutive_shifts_{d}')
            model.Add(sum(shifts[(sj_index, i, 0)] for i in range(d, d + 4)) == 4).OnlyEnforceIf(v)
            model.Add(sum(shifts[(sj_index, i, 0)] for i in range(d, d + 4)) != 4).OnlyEnforceIf(v.Not())
            consecutive_shifts_vars.append(v)
        model.Add(sum(consecutive_shifts_vars) >= 1)