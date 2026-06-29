# Pixel Astrophotography Timelapse Toolkit

This repository contains a set of scripts designed to automate the process of taking multi-hour Astrophotography timelapses on a Google Pixel (or any Android device) using a Mac, pulling the files based on accurate file modification times, and losslessly stitching them into a final video.

## Prerequisites

Ensure you have the following installed on your Mac:
1. **ADB (Android Debug Bridge)**: To communicate with the phone.
2. **FFmpeg**: To losslessly stitch the videos together.
3. **Python 3**: To run the intervalometer script.

### Phone Setup
1. Mount your phone on a sturdy tripod.
2. Go to **Settings > System > Developer Options**.
3. Enable **USB Debugging** (or Wireless Debugging).
4. Connect the phone to your Mac via a data-capable USB cable.
5. Accept the "Allow USB debugging" prompt on your phone screen.
6. Open the Google Camera app and swipe to **Night Sight / Astrophotography mode**.

---

## The Scripts

### 1. `timelapse.py` (The Intervalometer)
Because Android restricts accessibility services for automated tapping, this script uses ADB to simulate pressing the Volume Up button (which triggers the camera shutter).

**Usage:**
```bash
caffeinate -i ./timelapse.py --count <number_of_shots> --interval <seconds> --delay <initial_delay>
```

**CRITICAL TIP (`caffeinate`):**
Always prefix the command with `caffeinate -i`. This built-in macOS command prevents your Mac from going to sleep while the script is running. If your Mac goes to sleep during a 6-hour timelapse, the script will stop running!

**Example (6.5 hours of Astrophotography):**
```bash
caffeinate -i ./timelapse.py --count 90 --interval 255 --delay 20
```
*Note: A 255-second interval is roughly 4.25 minutes, matching the time it takes the Pixel to compute a full astrophotography shot. The 20-second delay gives you time to step away before the first shot.*

### 2. `pull_videos.sh` (The File Transfer)
This script uses Android's `stat` command to pull files based on their true modification time (Epoch time), bypassing any time-zone glitches that might occur in the Google Camera file naming system.

**Usage:**
```bash
./pull_videos.sh <START_TIME> <END_TIME> <DESTINATION_DIRECTORY>
```
*Format must be `YYYYMMDD_HHMM` (Local Mac Time).*

**Example:**
```bash
./pull_videos.sh 20260614_2200 20260615_0445 ./data/2026-06-15
```
This will pull all `.mp4` videos created between 10:00 PM and 4:45 AM and place them in the `./data/2026-06-15` folder.

### 3. `stitch.sh` (The Video Merger)
This script uses `ffmpeg` to losslessly merge all the 1-second interim astrophotography videos into a single, smooth master timelapse.

**Usage:**
1. Navigate into the directory where you downloaded the videos:
   ```bash
   cd ./data/2026-06-15
   ```
2. Run the stitch script:
   ```bash
   ../../stitch.sh
   ```

The script will safely create a temporary manifest file using `mktemp`, automatically overwrite any old output, and generate a `final_timelapse.mp4` video in that directory.

---

## Astrophotography Tips
*   **Power:** Your phone's screen will be on and processing heavily for hours. It is highly recommended to use a USB hub or a wireless charger to keep the phone battery topped up if your Mac isn't supplying enough power.
*   **Focus:** Before starting the script, tap on a bright star in the viewfinder to ensure the focus is locked to "Infinity".
