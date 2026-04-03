import unittest
from ortools.sat.python import cp_model
from monthly_constraints.base import MonthlyConstraints
from monthly_constraints.october_2025 import October2025Constraints
from monthly_constraints.november_2025 import November2025Constraints
from roster_generator_cp import CONSULTANTS
import calendar

class TestMonthlyConstraints(unittest.TestCase):
    def setUp(self):
        self.model = cp_model.CpModel()
        self.year = 2025
        self.month = 10
        self.num_days = calendar.monthrange(self.year, self.month)[1]
        self.all_days = range(1, self.num_days + 1)
        self.all_consultants = range(len(CONSULTANTS))
        self.all_shifts = range(3)
        
        self.shifts = {}
        for c in self.all_consultants:
            for d in self.all_days:
                for s in self.all_shifts:
                    self.shifts[(c, d, s)] = self.model.NewBoolVar(f'shift_c{c}_d{d}_s{s}')

    def test_base_constraints_structure(self):
        handler = MonthlyConstraints()
        # Test that methods exist and run
        cl_days = handler.get_cl_days()
        self.assertIsInstance(cl_days, dict)
        
        # Test objective expression generation
        obj_expr = handler.get_objective_expression(
            self.model, self.shifts, CONSULTANTS, self.all_days, self.all_shifts, self.year, self.month
        )
        self.assertIsNotNone(obj_expr)

    def test_october_constraints_structure(self):
        handler = October2025Constraints()
        cl_days = handler.get_cl_days()
        self.assertEqual(cl_days['PK'], 4)
        
        obj_expr = handler.get_objective_expression(
            self.model, self.shifts, CONSULTANTS, self.all_days, self.all_shifts, self.year, self.month
        )
        self.assertIsNotNone(obj_expr)

    def test_november_constraints_structure(self):
        handler = November2025Constraints()
        cl_days = handler.get_cl_days()
        self.assertEqual(cl_days['AM'], 1)
        
        # November has 30 days
        num_days_nov = 30
        all_days_nov = range(1, num_days_nov + 1)
        
        # We need shifts for November days too if they are not in self.shifts (which is for 31 days)
        # But self.shifts covers 31 days, so it covers 30 days.
        # However, we must pass all_days_nov to get_objective_expression so it iterates correctly.
        
        obj_expr = handler.get_objective_expression(
            self.model, self.shifts, CONSULTANTS, all_days_nov, self.all_shifts, self.year, 11
        )
        self.assertIsNotNone(obj_expr)

if __name__ == '__main__':
    unittest.main()
