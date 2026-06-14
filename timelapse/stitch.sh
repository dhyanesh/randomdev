#!/usr/bin/env bash

# This script concatenates all .mp4 files in the current directory into a single timelapse video.

echo "Finding all .mp4 files..."

# Create a temporary file safely using mktemp and ensure it's deleted on exit
TMPFILE=$(mktemp)
trap 'rm -f "$TMPFILE"' EXIT

for f in *.mp4; do
    # Skip the output file if it already exists
    if [ "$f" != "final_timelapse.mp4" ]; then
        echo "file '$PWD/$f'" >> "$TMPFILE"
    fi
done

COUNT=$(wc -l < "$TMPFILE" | tr -d ' ')
if [ "$COUNT" -eq 0 ]; then
    echo "No .mp4 files found in the current directory!"
    exit 1
fi

echo "Found $COUNT videos. Stitching them together..."

# Use ffmpeg concat demuxer to losslessly stitch them together
ffmpeg -f concat -safe 0 -i "$TMPFILE" -c copy final_timelapse.mp4

echo ""
echo "Done! Your stitched video is saved as: final_timelapse.mp4"
