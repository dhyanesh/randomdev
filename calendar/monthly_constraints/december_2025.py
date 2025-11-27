import datetime
from monthly_constraints.base import MonthlyConstraints

class December2025Constraints(MonthlyConstraints):
    """
    Applies the specific requests for December 2025.
    """

    def get_cl_days(self):
        return {
            'MT': 24,
            'MNS': 10
        }

    def get_special_night_consultants(self):
        return ['MT', 'MNS']

    def apply_leave_constraints(self, model, shifts, consultants, all_days, all_shifts):
        pass
    
    # Re-enabling this as it wasn't the cause of strict infeasibility (math was)
    # def apply_simmy_consecutive_shifts_constraint(self, model, shifts, consultants, all_days):
    #    pass

    def apply_night_shift_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        # Override base class to handle capacity issues (MT off, MNS no nights)
        senior_indices = [i for i, c in enumerate(consultants) if c.is_senior]
        female_indices = [i for i, c in enumerate(consultants) if c.gender == 'Female']
        am_index = next(i for i, c in enumerate(consultants) if c.initial == 'AM')
        mh_index = next(i for i, c in enumerate(consultants) if c.initial == 'MH')
        
        # Relaxed Night constraints logic...
        for d in all_days:
             model.Add(sum(shifts[(c, d, 2)] for c in senior_indices) >= 1)
             model.Add(sum(shifts[(c, d, 2)] for c in female_indices) <= 1)
             model.Add(shifts[(am_index, d, 2)] + shifts[(mh_index, d, 2)] <= 1)

        model.Add(sum(shifts[(mh_index, d, 2)] for d in all_days) == 4)

        special_night_consultants = self.get_special_night_consultants()
        for c_idx, c in enumerate(consultants):
            if c.initial != 'MH' and c.initial not in special_night_consultants:
                num_nights = sum(shifts[(c_idx, d, 2)] for d in all_days)
                model.Add(num_nights >= 6) 
                model.Add(num_nights <= 10) # Relaxed to 10

    def apply_shift_size_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        for d in all_days:
            # Morning: At least 2 people (plus BG who is added manually)
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) >= 2)
            model.Add(sum(shifts[(c, d, 0)] for c in range(len(consultants))) <= 3) # Keep upper bound
            
            # Afternoon: 0 consultants
            model.Add(sum(shifts[(c, d, 1)] for c in range(len(consultants))) == 0)
            
            # Night: Strictly 2 people
            model.Add(sum(shifts[(c, d, 2)] for c in range(len(consultants))) == 2)

    def apply_hard_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster=None):
        super().apply_hard_constraints(model, shifts, consultants, all_days, all_shifts, year, month, previous_month_roster)

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

        # --- PS (Praveen Sr) ---
        # CL from 4th to 8th
        for d in range(4, 9): # 4, 5, 6, 7, 8
            for s in all_shifts:
                model.Add(shifts[(ps_idx, d, s)] == 0)

        # --- MJ (Manju Jr) ---
        # CL on 9, 10 and 19, 20, 21
        for d in [9, 10, 19, 20, 21]:
            for s in all_shifts:
                model.Add(shifts[(mj_idx, d, s)] == 0)

        # --- PK (Praveen Jr) ---
        # Negative dates (Leave): 8, 9, 16
        for d in [8, 9, 16]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)
        # CL for 3 days: 23 to 25th
        for d in [23, 24, 25]:
            for s in all_shifts:
                model.Add(shifts[(pk_idx, d, s)] == 0)

        # --- SK (Santosh) ---
        # Leave request: 1st-3rd & 28-31st
        for d in [1, 2, 3, 28, 29, 30, 31]:
            for s in all_shifts:
                model.Add(shifts[(sk_idx, d, s)] == 0)

        # --- SJ (Simmy) ---
        # Leave requests - 6, 21-27 and on 31st
        leaves_sj = [6, 21, 22, 23, 24, 25, 26, 27, 31]
        for d in leaves_sj:
            for s in all_shifts:
                model.Add(shifts[(sj_idx, d, s)] == 0)

        # --- AM (Amirtha) ---
        # Leave needed on 1, 2 , 3 , 7 ,14, 15,16, 17 , 30, 31
        leaves_am = [1, 2, 3, 7, 14, 15, 16, 17, 30, 31]
        for d in leaves_am:
            for s in all_shifts:
                model.Add(shifts[(am_idx, d, s)] == 0)
        
        # Avoid night duty on 6th, 13th (Hard - Negative)
        for d in [6, 13]:
            model.Add(shifts[(am_idx, d, 2)] == 0)

        # --- MH (Mohan) ---
        # No afternoon shifts pls.. (Hard)
        for d in all_days:
            model.Add(shifts[(mh_idx, d, 1)] == 0)

        # --- MNS (Manjunath Sr) ---
        # No duties before 11th (1-10)
        for d in range(1, 11):
            for s in all_shifts:
                model.Add(shifts[(mns_idx, d, s)] == 0)
        
        # Only morning/afternoon shifts after that (No nights)
        for d in range(11, 32): # Dec has 31 days
            model.Add(shifts[(mns_idx, d, 2)] == 0)
        
        # --- MT (Mittal) ---
        # Off for the entire month
        for d in all_days:
            for s in all_shifts:
                model.Add(shifts[(mt_idx, d, s)] == 0)

    def apply_soft_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        consultant_map = {c.initial: i for i, c in enumerate(consultants)}
        sj_idx = consultant_map['SJ']
        ps_idx = consultant_map['PS']
        mh_idx = consultant_map['MH']
        sb_idx = consultant_map['SB']
        am_idx = consultant_map['AM']
        
        positive_preferences = []
        negative_preferences = []

        # SJ: Preferably morning shift on 5, 20 and 30.
        for d in [5, 20, 30]:
             positive_preferences.append(shifts[(sj_idx, d, 0)])
        
        # PS: Day duty preferences: 2, 12, 14, 17, 27
        for d in [2, 12, 14, 17, 27]:
            positive_preferences.append(shifts[(ps_idx, d, 0)])
        # PS: Night preferences
        for d in [9, 10, 18, 20, 24, 29, 30]:
            positive_preferences.append(shifts[(ps_idx, d, 2)])

        # MH: D (Day) preferences
        for d in [1, 2, 3, 5, 8, 10, 12, 15, 16, 17, 19, 22, 23, 31]:
            positive_preferences.append(shifts[(mh_idx, d, 0)])
        # MH: Night preferences
        for d in [6, 7, 28, 29]:
            positive_preferences.append(shifts[(mh_idx, d, 2)])
            
        # SB: Night on 8th
        positive_preferences.append(shifts[(sb_idx, 8, 2)])
        # SB: Day on 4th, 5th
        positive_preferences.append(shifts[(sb_idx, 4, 0)])
        positive_preferences.append(shifts[(sb_idx, 5, 0)])
        
        # AM: Night on 21, 23
        positive_preferences.append(shifts[(am_idx, 21, 2)])
        positive_preferences.append(shifts[(am_idx, 23, 2)])

        preference_score = model.NewIntVar(-500, 500, 'preference_score')
        model.Add(preference_score == sum(positive_preferences) - sum(negative_preferences))

        return preference_score