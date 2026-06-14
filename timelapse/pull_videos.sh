#!/usr/bin/env bash

# This script pulls all .mp4 timelapse videos from your Pixel's Camera folder
# within a specific sequential time range.

START_PREFIX=$1
END_PREFIX=$2

if [ -z "$START_PREFIX" ] || [ -z "$END_PREFIX" ]; then
    echo "Usage: $0 <start_timestamp_prefix> <end_timestamp_prefix>"
    echo "Example: $0 20260613_22 20260614_04"
    exit 1
fi

echo "Connecting to Pixel via ADB..."
adb devices | grep -q "device$" || { echo "Device not found. Please connect your phone."; exit 1; }

echo "Targeting videos from $START_PREFIX to $END_PREFIX..."
mkdir -p data

# We use adb shell to list the files, then pull them one by one
adb shell 'ls /sdcard/DCIM/Camera/*.mp4 2>/dev/null' | tr -d '\r' | while read -r file; do
    filename=$(basename "$file")
    
    # Extract the timestamp (YYYYMMDD_HHMMSS) from standard Android filenames
    timestamp=$(echo "$filename" | grep -oE '[0-9]{8}_[0-9]{6}')
    
    if [ -n "$timestamp" ]; then
        # Lexicographical string comparison
        # Includes files >= START_PREFIX and strictly < END_PREFIX
        if [[ "$timestamp" > "$START_PREFIX" || "$timestamp" == "$START_PREFIX"* ]] && [[ "$timestamp" < "$END_PREFIX" ]]; then
            echo "Downloading: $filename"
            adb pull "$file" ./data/
        fi
    fi
done

echo ""
echo "Transfer complete! Videos in the specified range are in the ./data/ folder."
