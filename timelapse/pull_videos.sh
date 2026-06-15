#!/usr/bin/env bash

# This script pulls .mp4 videos based on file modification time, ignoring filenames.

START_TIME=$1
END_TIME=$2
DEST_DIR=${3:-./data}

if [ -z "$START_TIME" ] || [ -z "$END_TIME" ]; then
    echo "Usage: $0 <start_time> <end_time> [dest_dir]"
    echo "Format: YYYYMMDD_HHMM"
    echo "Example: $0 20260613_2200 20260614_0445 ./data/2026-06-14"
    exit 1
fi

# Convert human-readable times to Unix Epoch (seconds) on macOS
START_EPOCH=$(date -j -f "%Y%m%d_%H%M" "$START_TIME" "+%s" 2>/dev/null)
END_EPOCH=$(date -j -f "%Y%m%d_%H%M" "$END_TIME" "+%s" 2>/dev/null)

if [ -z "$START_EPOCH" ] || [ -z "$END_EPOCH" ]; then
    echo "Error parsing dates. Please ensure they are in YYYYMMDD_HHMM format."
    exit 1
fi

echo "Connecting to Pixel via ADB..."
adb devices | grep -q "device$" || { echo "Device not found. Please connect your phone."; exit 1; }

echo "Targeting videos created between $START_TIME and $END_TIME..."
mkdir -p "$DEST_DIR"

# Fetch file modification times and paths from Android, compare against epochs
adb shell 'stat -c "%Y %n" /sdcard/DCIM/Camera/*.mp4 2>/dev/null' | tr -d '\r' | while read -r line; do
    # Extract epoch (everything before the first space) and filepath (everything after)
    file_epoch="${line%% *}"
    filepath="${line#* }"
    
    if [ -n "$file_epoch" ] && [ "$file_epoch" -ge "$START_EPOCH" ] 2>/dev/null && [ "$file_epoch" -lt "$END_EPOCH" ] 2>/dev/null; then
        filename=$(basename "$filepath")
        echo "Downloading: $filename"
        adb pull "$filepath" "$DEST_DIR/"
    fi
done

echo ""
echo "Transfer complete! Videos in the specified time range are in the $DEST_DIR folder."
