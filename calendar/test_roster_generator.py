import unittest
import datetime
import calendar
from roster_generator_cp import generate_roster_cp, CONSULTANTS

class TestRosterConstraints(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        """Generate a roster once for all tests to use."""
        cls.year = 2025
        cls.month = 9
        cls.vacations = {
            'PK': [datetime.date(cls.year, 9, 5), datetime.date(cls.year, 9, 6)],
            'MNS': [datetime.date(cls.year, 9, 10)],
        }
        cls.roster = generate_roster_cp(cls.year, cls.month, cls.vacations)
        
        # Manually add HOD for testing purposes, mimicking the post-processing step
        for day, shifts in cls.roster.items():
            date = datetime.date(cls.year, cls.month, day)
            if date.weekday() < 6: # Not Sunday
                shifts['morning'].insert(0, 'BG')

    def test_shift_sizes_and_composition(self):
        """Tests constraints 1, 9, 10, 11."""
        senior_initials = {c.initial for c in CONSULTANTS if c.is_senior}
        for day, shifts in self.roster.items():
            date = datetime.date(self.year, self.month, day)
            if date.weekday() < 6: # Weekday
                self.assertEqual(len(shifts['morning']), 4, f"Day {day}: Morning shift size should be 4")
                self.assertEqual(len(shifts['afternoon']), 1, f"Day {day}: Afternoon shift size should be 1")
            else: # Sunday
                self.assertEqual(len(shifts['morning']), 3, f"Day {day}: Sunday Morning shift size should be 3")
                self.assertEqual(len(shifts['afternoon']), 0, f"Day {day}: Sunday Afternoon shift should be empty")
            
            self.assertEqual(len(shifts['night']), 2, f"Day {day}: Night shift size should be 2")
            self.assertTrue(any(c in senior_initials for c in shifts['night']), f"Day {day}: Night shift needs at least one senior")

    def test_night_shift_quotas(self):
        """Tests constraint 2."""
        night_counts = {c.initial: 0 for c in CONSULTANTS}
        for shifts in self.roster.values():
            for consultant in shifts['night']:
                night_counts[consultant] += 1
        
        self.assertEqual(night_counts['MH'], 4, "Mohan should have exactly 4 nights")
        for initial, count in night_counts.items():
            if initial != 'MH':
                self.assertTrue(5 <= count <= 7, f"{initial} should have between 5 and 7 nights, but has {count}")

    def test_consecutive_leaves(self):
        """Tests constraint 4."""
        for consultant in CONSULTANTS:
            consecutive_off_days = 0
            for day in sorted(self.roster.keys()):
                is_working = False
                for shift in self.roster[day].values():
                    if consultant.initial in shift:
                        is_working = True
                        break
                if is_working:
                    consecutive_off_days = 0
                else:
                    consecutive_off_days += 1
                self.assertLessEqual(consecutive_off_days, 4, f"{consultant.initial} has more than 4 consecutive leaves")

    def test_post_night_duty(self):
        """Tests constraint 5."""
        for day in range(1, len(self.roster)):
            for consultant in self.roster[day]['night']:
                self.assertNotIn(consultant, self.roster[day + 1]['morning'], f"{consultant} has morning shift after night duty on day {day}")
                self.assertNotIn(consultant, self.roster[day + 1]['afternoon'], f"{consultant} has afternoon shift after night duty on day {day}")

    def test_vacations(self):
        """Tests constraint 6."""
        for initial, dates in self.vacations.items():
            for date_obj in dates:
                day = date_obj.day
                for shift_type, consultants in self.roster[day].items():
                    self.assertNotIn(initial, consultants, f"{initial} is scheduled for {shift_type} on vacation day {date_obj}")

    def test_hod_schedule(self):
        """Tests constraint 8."""
        for day, shifts in self.roster.items():
            date = datetime.date(self.year, self.month, day)
            if date.weekday() < 6: # Weekday
                self.assertIn('BG', shifts['morning'], f"HOD not in morning shift on weekday {day}")
            else: # Sunday
                self.assertNotIn('BG', shifts['morning'], f"HOD scheduled on a Sunday {day}")

    def test_am_sj_no_afternoon(self):
        """Tests constraint 12."""
        for day, shifts in self.roster.items():
            self.assertNotIn('AM', shifts['afternoon'], f"AM scheduled for afternoon on day {day}")
            self.assertNotIn('SJ', shifts['afternoon'], f"SJ scheduled for afternoon on day {day}")

if __name__ == '__main__':
    unittest.main()
