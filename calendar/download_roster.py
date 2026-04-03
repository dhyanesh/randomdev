import json
import sys
from google.cloud import storage
# Assuming roster_generator_cp.py is in the same directory or accessible in the python path
from roster_generator_cp import download_json_from_gcs

if __name__ == '__main__':
    bucket_name = "trilife-duty-roster-files"
    blob_name = "2026/1/roster.json"
    
    roster_data = download_json_from_gcs(bucket_name, blob_name)
    
    if roster_data:
        json.dump(roster_data, sys.stdout, indent=4)
    else:
        sys.stderr.write("Failed to download roster for January 2026.\n")
        sys.exit(1)
