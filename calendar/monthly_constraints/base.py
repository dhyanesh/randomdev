import datetime

class MonthlyConstraints:
    """
    Base class for applying constraints to the roster model.
    """

    def apply_all_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        self.apply_hard_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        cl_days = self.get_cl_days()
        preference_score = self.apply_soft_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        return cl_days, preference_score

    def get_cl_days(self):
        return {}

    def get_special_night_consultants(self):
        return []

    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        self.apply_one_shift_per_day_constraint(model, shifts, consultants, all_days, all_shifts)
        self.apply_shift_size_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_consultant_specific_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_night_shift_constraints(model, shifts, consultants, all_days, all_shifts, year, month)
        self.apply_post_night_duty_constraints(model, shifts, consultants, all_days, all_shifts)
        self.apply_leave_constraints(model, shifts, consultants, all_days, all_shifts)

    def apply_soft_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        return model.NewIntVar(0, 0, 'preference_score')

    def apply_one_shift_per_day_constraint(self, model, shifts, consultants, all_days, all_shifts):
        for c in range(len(consultants)):
            for d in all_days:
                model.Add(sum(shifts[(c, d, s)] for s in all_shifts) <= 1)

    def apply_shift_size_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        for d in all_days:
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) >= 2)
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) <= 3)
            date = datetime.date(year, month, d)
            if date.weekday() < 6:
                model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) == 1)
            else:
                model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) == 0)
            model.Add(sum(shifts[(c, d, 2)] for c in range(len(consultants))) == 2)

    def apply_consultant_specific_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        sj_index = next(i for i, c in enumerate(consultants) if c.initial == 'SJ')
        mittal_index = next(i for i, c in enumerate(consultants) if c.initial == 'MT')

        for d in all_days:
            model.Add(shifts[(am_index, d, 1)] == 0)
            model.Add(shifts[(sj_index, d, 1)] == 0)

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

        model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)

        special_night_consultants = self.get_special_night_consultants()
        for c_idx, c in enumerate(consultants):
            if c.initial != 'MH' and c.initial not in special_night_consultants:
                num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
                model.Add(num_nights >= 5)
                model.Add(num_nights <= 7)

    def apply_post_night_duty_constraints(self, model, shifts, consultants, all_days, all_shifts):
        for c in range(len(consultants)):
            for d in all_days[:-1]:
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        for c in range(len(consultants)):
            for d in range(1, len(all_days) - 3):
                model.Add(sum(shifts[(c, i, s)] for i in range(d, d + 5) for s in all_shifts) >= 1)