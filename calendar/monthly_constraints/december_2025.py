import datetime
from monthly_constraints.base import MonthlyConstraints

class December2025Constraints(MonthlyConstraints):
    """
    Applies the specific requests for December 2025.
    """

    def get_cl_days(self):
        # Specific CL requests
        return {
            'PK': 3, 
            'MJ': 5,
            'PS': 4,
            'SK': 4, 
            'SJ': 5,
            'AM': 2,
            # MT is off, giving him CLs to reduce target to 0 so lower bound check passes
            'MT': 24, 
            # MNS: 0 (User instruction)
            # SB: 0 (Only asked for leaves, not CL)
        }

    def get_special_night_consultants(self):
        return ['MT']

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        # Override to allow long leaves
        pass

    def apply_simmy_consecutive_shifts_constraint(self, model, shifts, consultants, all_days):
        # Override to disable Simmy's consecutive shift constraint if it's causing issues
        pass

    def apply_shift_size_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        for d in all_days:
            # Morning: Exactly 3 people
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) == 3)
            
            # Afternoon: 0 people every day (User request)
            model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) == 0)
            
            # Night: Exactly 2 people
            model.Add(sum(shifts[(c, d, 2)] for c in range(len(consultants))) == 2)

    def apply_night_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        senior_indices = [i for i, c in enumerate(consultants) if c.is_senior]
        female_indices = [i for i, c in enumerate(consultants) if c.gender == 'Female']
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        mh_index = next(i for i, c in enumerate(consultants) if c.initial == 'MH')

        for d in all_days:
            # model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)
            # model.Add(sum(shifts[(c, d, 2)] for c in female_indices) <= 1)
            model.Add(shifts[(am_index, d, 2)] + shifts[(mh_index, d, 2)] <= 1)

        # Relaxed MH constraint - Max 4 nights (Hard constraint)
        # model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) >= 0) # Implicit
        model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) <= 4)

        special_night_consultants = self.get_special_night_consultants()
        for c_idx, c in enumerate(consultants):
            if c.initial != 'MH' and c.initial not in special_night_consultants:
                num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
                
                # Specific exception for Santosh (SK) and Amirtha (AM)
                if c.initial == 'SK' or c.initial == 'AM':
                    model.Add(num_nights == 7)
                else:
                    model.Add(num_nights >= 7)
                    model.Add(num_nights <= 8)

    def apply_working_hours_constraints(self, model, shifts, consultants, all_days, all_shifts, cl_days):
        for c_idx, c in enumerate(consultants):
            consultant_cl_days = cl_days.get(c.initial, 0)
            target_hours = 192 - (consultant_cl_days * 8)
            total_hours_expr = sum(shifts[(c_idx, d, 0)] * 9 + shifts[(c_idx, d, 1)] * 8 + shifts[(c_idx, d, 2)] * 15 for d in all_days)
            
            # Hard cap at 192 hours as requested (Absolute Maximum)
            model.Add(total_hours_expr <= 192)
            
            # Lower bound flexibility
            # Relaxed to -50 because total available roster hours are less than sum of targets
            model.Add(total_hours_expr >= target_hours - 50)

    def apply_post_night_duty_constraints(self, model, shifts, consultants, all_days, all_shifts, previous_month_roster=None):
        # Standard post-night duty constraint: No morning/afternoon shift after a night shift
        for c in range(len(consultants)):
            for d in all_days[:-1]:
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 0)] <= 1)
                model.Add(shifts[(c, d, 2)] + shifts[(c, d + 1, 1)] <= 1)

        if previous_month_roster:
            last_day_of_previous_month = max([int(k) for k in previous_month_roster.keys()])
            last_day_str = str(last_day_of_previous_month)
            
            for c_idx, c in enumerate(consultants):
                # Check if 'night' key exists and consultant is in it
                if 'night' in previous_month_roster[last_day_str] and \
                   c.initial in previous_month_roster[last_day_str]['night']:
                    # Standard: No morning/afternoon on 1st if worked night on last day of prev month
                    model.Add(shifts[(c_idx, 1, 0)] == 0)
                    model.Add(shifts[(c_idx, 1, 1)] == 0)
                    
                    # Extra: No night shift on 1st if worked night on last day of prev month (Consecutive Night Check)
                    model.Add(shifts[(c_idx, 1, 2)] == 0)

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

        # --- SB (Shiva) ---
        # Leave requests on 1, 2, 3, 6, 7
        for d in [1, 2, 3, 6, 7]:
            for s in all_shifts:
                model.Add(shifts[(sb_idx, d, s)] == 0)
        # Day duty on 5th (Hard request)
        model.Add(shifts[(sb_idx, 5, 0)] == 1)

        # --- PK (Praveen Jr) ---
        # Leave on 1st
        for s in all_shifts:
            model.Add(shifts[(pk_idx, 1, s)] == 0)
        # Negative dates (Leave): 8, 9, 16
        for d in [8, 9, 16]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)
        # CL for 3 days: 23 to 25th
        for d in [23, 24, 25]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)

        # --- MJ (Manju Jr) ---
        # CL on 9, 10 and 19, 20, 21
        for d in [9, 10, 19, 20, 21]:
            for s in all_shifts:
                model.Add(shifts[(mj_idx, d, s)] == 0)

        # --- PS (Praveen Sr) ---
        # CL from 4th to 8th
        for d in range(4, 9): # 4, 5, 6, 7, 8
            for s in all_shifts:
                model.Add(shifts[(ps_idx, d, s)] == 0)

        # --- SK (Santosh) ---
        # Leave request/CL request 1st-3rd & 28-31st
        for d in [1, 2, 3, 28, 29, 30, 31]:
            for s in all_shifts:
                model.Add(shifts[(sk_idx, d, s)] == 0)

        # --- SJ (Simmy) ---
        # Leave requests - 6, 21-27 and on 31st.
        leaves_sj = [6, 21, 22, 23, 24, 25, 26, 27, 31]
        for d in leaves_sj:
            for s in all_shifts:
                model.Add(shifts[(sj_idx, d, s)] == 0)
        # CL - 5
        for d in [5]:
            for s in all_shifts:
                model.Add(shifts[(sj_idx, d, s)] == 0)

        # --- AM (Amirtha) ---
        # Leave needed on 7, 14, 21 (Updated Request)
        leaves_am = [7, 14, 21]
        for d in leaves_am:
            for s in all_shifts:
                model.Add(shifts[(am_idx, d, s)] == 0)
        
        # Avoid night duty on 6th, 13th (Hard Request)
        for d in [6, 13]:
            model.Add(shifts[(am_idx, d, 2)] == 0)

        # --- MH (Mohan) ---
        # No afternoon shifts pls.. (Hard)
        for d in all_days:
            model.Add(shifts[(mh_idx, d, 1)] == 0)

        # Specific Hard Preferences (User Request)
        # N - 6, 7, 28, 29
        for d in [6, 7, 28, 29]:
             model.Add(shifts[(mh_idx, d, 2)] == 1)
             
        # D - 2, 3, 5, 10, 12, 15, 16, 17, 19, 22, 23, 31 (1st and 8th excluded)
        for d in [2, 3, 5, 10, 12, 15, 16, 17, 19, 22, 23, 31]:
             model.Add(shifts[(mh_idx, d, 0)] == 1)

        # --- MNS (Manjunath Sr) ---
        # No duties before 11th (1-10)
        for d in range(1, 11):
            for s in all_shifts:
                model.Add(shifts[(mns_idx, d, s)] == 0)
        
        # Only morning/afternoon shifts after that (Nights allowed now)
        # for d in range(11, 32):
        #     model.Add(shifts[(mns_idx, d, 2)] == 0)
        
        # --- MT (Mittal) ---
        # Dr. Mittal is off for the entire month.
        for d in all_days:
            for s in all_shifts:
                model.Add(shifts[(mt_idx, d, s)] == 0)

        # Prevent 3 consecutive night shifts for all consultants (Max 2 allowed)
        for c_idx in range(len(consultants)):
            for d in range(1, len(all_days) - 1):
                model.Add(shifts[(c_idx, d, 2)] + shifts[(c_idx, d + 1, 2)] + shifts[(c_idx, d + 2, 2)] <= 2)

    def calculate_preference_score(self, model, shifts, consultants, all_days, all_shifts, year, month):
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        sb_idx = consultant_map['SB']
        pk_idx = consultant_map['PK']
        ps_idx = consultant_map['PS']
        sj_idx = consultant_map['SJ']
        am_idx = consultant_map['AM']
        mh_idx = consultant_map['MH']
        
        positive_preferences = []
        negative_preferences = []

        # SB (Shiva)
        # Day duty on 4th and 5th
        positive_preferences.append(shifts[(sb_idx, 4, 0)])
        positive_preferences.append(shifts[(sb_idx, 5, 0)])
        # Night duty on 8th
        positive_preferences.append(shifts[(sb_idx, 8, 2)])

        # PK (Praveen Jr)
        # No specific positive shift preferences mentioned

        # PS (Praveen Sr)
        # Day duty on 2 12 14 17 27
        for d in [2, 12, 14, 17, 27]:
            positive_preferences.append(shifts[(ps_idx, d, 0)])
        # Night on 9 10 18 20 24 29 30
        for d in [9, 10, 18, 20, 24, 29, 30]:
            positive_preferences.append(shifts[(ps_idx, d, 2)])
        
        # SJ (Simmy)
        # Preferably morning shift on 5, 20 and 30.
        for d in [20, 30]:
            positive_preferences.append(shifts[(sj_idx, d, 0)])

        # AM (Amirtha)
        # Will do night duty on 23rd (21st removed as it's a leave now)
        positive_preferences.append(shifts[(am_idx, 23, 2)])

        # AM Soft Leave Preferences (Avoid any shift)
        # 1, 2, 3, 15, 16, 17, 30, 31
        for d in [1, 2, 3, 15, 16, 17, 30, 31]:
            for s in all_shifts:
                negative_preferences.append(shifts[(am_idx, d, s)])

        # MH (Mohan)
        # N -6, 7, 28, 29
        for d in [6, 7, 28, 29]:
            positive_preferences.append(shifts[(mh_idx, d, 2)])
        # D- 1, 2, 3, 5, 8, 10, 12, 15, 16, 17, 19, 22, 23, 31.
        for d in [1, 2, 3, 5, 8, 10, 12, 15, 16, 17, 19, 22, 23, 31]:
            positive_preferences.append(shifts[(mh_idx, d, 0)])

        preference_score = model.NewIntVar(-1000, 1000, 'preference_score')
        model.Add(preference_score == sum(positive_preferences) - sum(negative_preferences))

        return preference_score