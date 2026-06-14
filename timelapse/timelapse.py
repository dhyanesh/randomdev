#!/usr/bin/env python3

import argparse
import subprocess
import time
import sys
import datetime

def check_adb():
    """Verify ADB is installed and a device is connected."""
    try:
        # Check if adb exists
        subprocess.run(["adb", "version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
    except FileNotFoundError:
        print("Error: 'adb' command not found. Please ensure Android Platform Tools are installed and in your PATH.")
        sys.exit(1)
        
    # Check for connected devices
    result = subprocess.run(["adb", "devices"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    lines = result.stdout.strip().split('\n')
    
    # The first line is "List of devices attached"
    devices = [line.split('\t')[0] for line in lines[1:] if '\tdevice' in line]
    
    if len(devices) == 0:
        print("Error: No devices attached. Please connect your phone, enable USB Debugging, and authorize this computer.")
        sys.exit(1)
    elif len(devices) > 1:
        print(f"Warning: Multiple devices attached {devices}. This script will use the default one.")
        print("If it fails, please disconnect other devices.")

def trigger_shutter():
    """Send Volume Up keyevent via ADB to trigger the shutter."""
    try:
        # Keycode 24 is Volume Up, which triggers the shutter in most camera apps including Google Camera
        subprocess.run(["adb", "shell", "input", "keyevent", "24"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"\nError executing adb command: {e}")
        sys.exit(1)

def print_countdown(seconds, message=""):
    """Prints a live countdown timer."""
    for remaining in range(int(seconds), 0, -1):
        sys.stdout.write(f"\r{message} {remaining} seconds remaining...     ")
        sys.stdout.flush()
        time.sleep(1)
    sys.stdout.write(f"\r{message} Done!                      \n")
    sys.stdout.flush()

def main():
    parser = argparse.ArgumentParser(description="Astrophotography Timelapse Intervalometer via ADB")
    parser.add_argument("--interval", type=int, default=280, help="Interval between shots in seconds (default: 280s, approx 4.5 mins)")
    parser.add_argument("--count", type=int, default=10, help="Total number of photos to take (default: 10)")
    parser.add_argument("--delay", type=int, default=10, help="Initial delay before the first shot in seconds (default: 10s)")
    
    args = parser.parse_args()

    print("==================================================")
    print("      Pixel 9 Pro Astrophotography Timelapse      ")
    print("==================================================")
    print(f"Total Shots: {args.count}")
    print(f"Interval:    {args.interval} seconds (~{args.interval/60:.1f} minutes)")
    total_time = args.count * args.interval
    print(f"Est. Total Time: {datetime.timedelta(seconds=total_time)}")
    print("==================================================")
    
    print("\nChecking ADB connection...")
    check_adb()
    print("Device found and ready.\n")
    
    input("Press Enter to start the sequence (or Ctrl+C to abort)...")
    print("")
    
    if args.delay > 0:
        print_countdown(args.delay, "Initial delay:")
        
    for i in range(1, args.count + 1):
        timestamp = datetime.datetime.now().strftime("%H:%M:%S")
        print(f"\n[{timestamp}] Taking photo {i}/{args.count}...")
        
        trigger_shutter()
        
        # Don't wait after the very last shot
        if i < args.count:
            print_countdown(args.interval, f"Waiting for next shot ({args.interval}s):")
            
    print("\n==================================================")
    print("Timelapse sequence complete!")
    print("==================================================")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\nTimelapse sequence aborted by user.")
        sys.exit(0)
