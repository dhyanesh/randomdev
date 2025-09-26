from abc import ABC, abstractmethod

class MonthlyConstraints(ABC):
    """
    Abstract base class for applying month-specific constraints to the roster model.
    """
    @abstractmethod
    def apply_constraints(self, model, shifts, consultants, all_days, all_shifts, year, month):
        """
        Applies month-specific constraints to the CP-SAT model.

        Args:
            model: The cp_model.CpModel() instance.
            shifts: The dictionary of shift variables.
            consultants: The list of Consultant namedtuples.
            all_days: A range object for the days of the month.
            all_shifts: A range object for the shifts.
            year: The year of the roster.
            month: The month of the roster.

        Returns:
            A tuple containing:
            - cl_days_per_consultant: A dictionary mapping consultant initials to the number of CL days.
            - preference_score: A model variable representing the score of fulfilled preferences.
        """
        pass
