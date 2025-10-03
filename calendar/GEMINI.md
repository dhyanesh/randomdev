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

**Environment Setup:**

Before running any scripts, activate the Python virtual environment:

```bash
source venv/bin/activate
```

**1. Roster Generation:**

The `roster_generator_cp.py` script generates a duty roster.

**Prerequisites:**

*   Python 3
*   OR-Tools library (`pip install ortools`)
*   For Google Sheets export:
    *   `gspread` and `google-auth-oauthlib` libraries (`pip install gspread google-auth-oauthlib`)
    *   A `your_service_account_file.json` file with Google Cloud service account credentials.

**Running the script:**

```bash
python roster_generator_cp.py -y <year> -m <month> --vacations-file vacations.json
```

*   `<year>`: The year for the roster (e.g., 2025).
*   `<month>`: The month for the roster (e.g., 9).

**Options:**
*   `--export-gsheet`: Export the generated roster to a Google Sheet.
*   `--share-email <email>`: Email address to share the Google Sheet with.
*   `--force-regenerate`: Force regeneration of the roster, ignoring any cached version.
*   `--fixed-roster <file_path>`: Path to a JSON file with a fixed partial roster.

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
*   **Configuration:** `roster_generator_cp.py` has hardcoded requests for October 2025 and uses a local JSON file for caching (`roster_<year>_<month>.json`). The `trilife_shifts.py` script uses a hardcoded dictionary for consultant information.
*   **Dependencies:** The required Python libraries are listed in the "Building and Running" section. A `requirements.txt` file would be a good addition to the project.

### Key Files

*   `roster_generator_cp.py`: The main script for generating the duty roster using OR-Tools. It supports caching and exporting to Google Sheets.
*   `trilife_shifts.py`: A script to parse a PDF roster and create a schedule in Google Sheets and Calendar.
*   `shifts.py`: A simpler, interactive script for creating shift schedules.
*   `test_roster_generator.py`: Unit tests for the roster generator.
*   `test_trilife_shifts.py`: Unit tests for the Trilife shift scheduler.
*   `fixed_roster_2025_10.json`: A JSON file that defines a fixed partial roster for October 2025. This is used with the `--fixed-roster` argument in `roster_generator_cp.py` to ensure that the specified shifts are not changed during roster generation.