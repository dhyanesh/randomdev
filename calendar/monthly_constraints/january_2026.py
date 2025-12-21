import datetime
from monthly_constraints.base import MonthlyConstraints

class January2026Constraints(MonthlyConstraints):
    """
    Applies the specific requests for January 2026.
    """

    def get_cl_days(self):
        # Specific CL requests (inferred from off days or explicit mentions)
        return {}

    def get_special_night_consultants(self):
        return ['PS']

    def apply_shift_size_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        for d in all_days:
            # Morning: Exactly 3 people (Relaxed for Jan 1 to >= 2 due to high unavailability)
            if d == 1:
                model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) >= 2)
                model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) <= 3)
            else:
                model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) == 3)
            
            # Afternoon: Optional (0 or 1) on all days
            model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) <= 1)
            
            # Night: Exactly 2 people
            model.Add(sum(shifts[(c, d, 2)] for c in range(len(consultants))) == 2)

    # Override base night shift constraints to relax senior rule and enforce no back-to-back for Jan 2026
    def apply_night_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        senior_indices = [i for i, c in enumerate(consultants) if c.is_senior]
        female_indices = [i for i, c in enumerate(consultants) if c.gender == 'Female']
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        mh_index = next(i for i, c in enumerate(consultants) if c.initial == 'MH')
        ps_index = next(i for i, c in enumerate(consultants) if c.initial == 'PS')

        for d in all_days:
            # Relaxed senior constraint: Not strictly enforced for Jan 2026
            # model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)
            
            model.Add(sum(shifts[(c, d, 2)] for c in female_indices) <= 1)
            model.Add(shifts[(am_index, d, 2)] + shifts[(mh_index, d, 2)] <= 1)
            
            # No back-to-back night shifts - ENFORCED for Jan 2026 (Excluding MH due to fixed schedule)
            if d < len(all_days):
                for c_idx, c in enumerate(consultants):
                    if c.initial != 'MH':
                        model.Add(shifts[(c_idx, d, 2)] + shifts[(c_idx, d + 1, 2)] <= 1)

        model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)
        
        # PS has exactly 8 nights (hard constraint requests)
        model.Add(sum(shifts[(ps_index, d, 2)] for d in all_days) == 8)

        special_night_consultants = self.get_special_night_consultants()
        for c_idx, c in enumerate(consultants):
            if c.initial != 'MH' and c.initial not in special_night_consultants:
                num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
                # Ensure at least 6 nights for everyone except MH
                model.Add(num_nights >= 6)
                model.Add(num_nights <= 7)

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        # Override to allow long leaves
        pass

    def apply_simmy_consecutive_shifts_constraint(self, model, shifts, consultants, all_days):
        # Override to disable Simmy's consecutive shift constraint
        pass

    def apply_post_night_duty_constraints(self, model, shifts, consultants, all_days, all_shifts, previous_month_roster=None):
        # Standard post-night duty constraint
        for c in range(len(consultants)):
            for d in all_days[:-1]:
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

        # Removed previous month check to resolve infeasibility

    def apply_working_hours_constraints(self, model, shifts, consultants, all_days, all_shifts, cl_days):
        for c_idx, c in enumerate(consultants):
            consultant_cl_days = cl_days.get(c.initial, 0)
            target_hours = 192 - (consultant_cl_days * 8)
            total_hours_expr = sum(shifts[(c_idx, d, 0)] * 9 + shifts[(c_idx, d, 1)] * 8 + shifts[(c_idx, d, 2)] * 15 for d in all_days)
            
            # Hard cap at 192 hours
            model.Add(total_hours_expr <= 192)
            
            # Relaxed lower bound
            model.Add(total_hours_expr >= target_hours - 12)

    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster=None, cl_days=None):
        # Call base constraints
        super().apply_hard_constraints(model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster, cl_days)
        
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        sb_idx = consultant_map['SB']
        ps_idx = consultant_map['PS']
        mj_idx = consultant_map['MJ']
        pk_idx = consultant_map['PK']
        sk_idx = consultant_map['SK']
        sj_idx = consultant_map['SJ']
        am_idx = consultant_map['AM']
        mh_idx = consultant_map['MH']
        mns_idx = consultant_map['MNS']
        mt_idx = consultant_map['MT']

        # --- Mittal (MT) ---
        # Off until 5th Jan (1-5) and on 30th Jan
        for d in [1, 2, 3, 4, 5, 30]:
            for s in all_shifts:
                model.Add(shifts[(mt_idx, d, s)] == 0)
        
        # Avoid Day/Afternoon on 21st Jan (Night is allowed)
        model.Add(shifts[(mt_idx, 21, 0)] == 0)
        model.Add(shifts[(mt_idx, 21, 1)] == 0)

        # --- Praveen Sr (PS) ---
        # Night duties (Hard constraints)
        for d in [2, 7, 11, 17, 19, 23, 26, 31]:
            model.Add(shifts[(ps_idx, d, 2)] == 1)
        # Morning duties (Hard constraints)
        for d in [5, 10, 13, 16]:
            model.Add(shifts[(ps_idx, d, 0)] == 1)

        # --- Simmy (SJ) ---
        # Off days: 1, 10, 11, 23, 24
        for d in [1, 10, 11, 23, 24]:
            for s in all_shifts:
                model.Add(shifts[(sj_idx, d, s)] == 0)

        # --- Amirtha (AM) ---
        # Off needed: 4, 5, 6, 7, 20, 21, 25, 26, 27
        for d in [4, 5, 6, 7, 20, 21, 25, 26, 27]:
            for s in all_shifts:
                model.Add(shifts[(am_idx, d, s)] == 0)
        # Day shift on 3, 24
        model.Add(shifts[(am_idx, 3, 0)] == 1)
        model.Add(shifts[(am_idx, 24, 0)] == 1)
        # Night duty on 18
        model.Add(shifts[(am_idx, 18, 2)] == 1)

        # --- Manjunath Senior (MNS) ---
        # Off: 25, 27, 28, 29
        for d in [25, 27, 28, 29]:
            for s in all_shifts:
                model.Add(shifts[(mns_idx, d, s)] == 0)

        # --- Mohan (MH) ---
        # Night: 10, 11, 24, 25 (Hard)
        for d in [10, 11, 24, 25]:
            model.Add(shifts[(mh_idx, d, 2)] == 1)
        # Day: 2, 5, 6, 7, 9, 16, 19, 20, 21, 23, 27, 28, 29, 31 (Hard)
        for d in [2, 5, 6, 7, 9, 16, 19, 20, 21, 23, 27, 28, 29, 31]:
            model.Add(shifts[(mh_idx, d, 0)] == 1)

        # --- Manjunath Junior (MJ) ---
        # Negative dates (Off): 13, 14, 15
        # Off on 1st Jan
        for d in [1, 13, 14, 15]:
            for s in all_shifts:
                model.Add(shifts[(mj_idx, d, s)] == 0)

        # --- Santosh (SK) ---
        # Avoid duties (Off): 1, 2, 3, 9, 22, 23
        for d in [1, 2, 3, 9, 22, 23]:
            for s in all_shifts:
                model.Add(shifts[(sk_idx, d, s)] == 0)

        # --- Praveen Jr (PK) ---
        # Negative dates (Off): 6, 7, 17, 18, 26, 27
        for d in [6, 7, 17, 18, 26, 27]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)

        # --- Shiva (SB) ---
        # Off: 1, 13, 14, 15, 16
        for d in [1, 13, 14, 15, 16]:
            for s in all_shifts:
                model.Add(shifts[(sb_idx, d, s)] == 0)
        
        # Prevent 3 consecutive night shifts for all consultants (Max 2 allowed)
        for c_idx in range(len(consultants)):
            for d in range(1, len(all_days) - 1):
                model.Add(shifts[(c_idx, d, 2)] + shifts[(c_idx, d + 1, 2)] + shifts[(c_idx, d + 2, 2)] <= 2)

    def calculate_preference_score(self, model, shifts, consultants, all_days, all_shifts, year, month):
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        sj_idx = consultant_map['SJ']
        ps_idx = consultant_map['PS']
        sb_idx = consultant_map['SB']
        
        positive_preferences = []

        # --- Simmy (SJ) ---
        # Preferably morning on 22
        positive_preferences.append(shifts[(sj_idx, 22, 0)])

        # --- Praveen Sr (PS) ---
        # Plz give days on 5 10 13 16 22 25 29 30 (Weight: 1000 each)
        for d in [22, 25, 29, 30]:
            positive_preferences.append(shifts[(ps_idx, d, 0)] * 1000)
        
        # --- Shiva (SB) ---
        # Night duty on 11th please
        positive_preferences.append(shifts[(sb_idx, 11, 2)])

        if positive_preferences:
             # Increase range to accommodate high scores
             preference_score = model.NewIntVar(-100000, 100000, 'preference_score')
             model.Add(preference_score == sum(positive_preferences))
             return preference_score
        
        return model.NewIntVar(0, 0, 'preference_score')
