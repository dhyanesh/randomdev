This is a Python project for generating and managing duty rosters for a group of consultants. The project consists of two main parts: a roster generator and a shift scheduler that integrates with Google Calendar.

### Project Overview

The project automates the creation of monthly duty rosters for a team of consultants, taking into account various constraints like shift types, vacations, and fairness. It can also parse a PDF roster and create a schedule in Google Sheets, which can then be imported into Google Calendar.

**Key Technologies:**

*   **Python:** The primary programming language.
*   **OR-Tools:** A library from Google for combinatorial optimization, used for roster generation.
*   **gspread & google-api-python-client:** Libraries for interacting with Google Sheets and Google Calendar APIs.
*   **Camelot & pandas:** Used for parsing PDF files and data manipulation.
*   **unittest:** For testing the project's functionality.

### Building and Running

**1. Roster Generation:**

The `roster_generator_cp.py` script generates a duty roster.

**Prerequisites:**

*   Python 3
*   OR-Tools library (`pip install ortools`)

**Running the script:**

```bash
python roster_generator_cp.py -y <year> -m <month> --vacations-file vacations.json
```

*   `<year>`: The year for the roster (e.g., 2025).
*   `<month>`: The month for the roster (e.g., 9).
*   `--vacations-file`: Path to the JSON file containing vacation data.

**2. Trilife Shift Scheduler:**

The `trilife_shifts.py` script parses a PDF roster and creates a schedule in Google Sheets and Calendar.

**Prerequisites:**

*   Python 3
*   Required libraries: `gspread`, `google-api-python-client`, `pandas`, `camelot-py[cv]`, `python-dateutil`
*   A `your_service_account_file.json` file with Google Cloud service account credentials.

**Running the script:**

```bash
python trilife_shifts.py <consultant_name> <pdf_path> --create-sheet --import-calendar
```

*   `<consultant_name>`: The name of the consultant (e.g., "Mittal").
*   `<pdf_path>`: The path to the roster PDF file.
*   `--create-sheet`: Creates a new Google Sheet.
*   `--import-calendar`: Imports the schedule into Google Calendar.

### Development Conventions

*   **Testing:** The project uses the `unittest` framework for testing. Test files are `test_roster_generator.py` and `test_trilife_shifts.py`.
*   **Code Style:** The code is generally well-structured, with classes and functions for different functionalities. The `trilife_shifts.py` script follows a more object-oriented approach.
*   **Configuration:** The `roster_generator_cp.py` script uses a JSON file for vacation data. The `trilife_shifts.py` script uses a hardcoded dictionary for consultant information.
*   **Dependencies:** The required Python libraries are listed in the "Building and Running" section. A `requirements.txt` file would be a good addition to the project.

### Key Files

*   `roster_generator_cp.py`: The main script for generating the duty roster using OR-Tools.
*   `trilife_shifts.py`: A script to parse a PDF roster and create a schedule in Google Sheets and Calendar.
*   `shifts.py`: A simpler, interactive script for creating shift schedules.
*   `test_roster_generator.py`: Unit tests for the roster generator.
*   `test_trilife_shifts.py`: Unit tests for the Trilife shift scheduler.
*   `vacations.json`: A JSON file containing vacation requests for the consultants.
