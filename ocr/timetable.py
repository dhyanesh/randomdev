import easyocr
import cv2
import pandas as pd

def parse_timetable(image_path):
    """Parses a handwritten timetable image and converts it to a spreadsheet.

    Args:
        image_path (str): Path to the timetable image.

    Returns:
        pd.DataFrame: The parsed timetable as a pandas DataFrame.
    """

    # Load the image
    img = cv2.imread(image_path)

    # Perform OCR
    reader = easyocr.Reader(['en'])  # Replace 'en' with the appropriate language
    result = reader.readtext(img)

    # Extract timetable data (adjust parsing logic based on your timetable format)
    lines = result
    timetable_data = []

    for box in result:
        print(box[1])
        # Parse each line to extract relevant information (e.g., day, time, subject)
        # You might need to use regular expressions or other parsing techniques
        # based on the specific format of your timetable
        # day, time, subject = line.split()  # Example parsing for a simple format
        # timetable_data.append([day, time, subject])

    # Create a pandas DataFrame from the extracted data
    df = pd.DataFrame(timetable_data, columns=['Day', 'Time', 'Subject'])

    return df

# Example usage
image_path = '/Users/dhyanesh/Downloads/timetable.jpeg'
timetable_df = parse_timetable(image_path)

# Save the DataFrame as a spreadsheet (adjust file format as needed)
#timetable_df.to_excel('timetable.xlsx', index=False)
