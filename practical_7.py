import gspread
import random
from oauth2client.service_account import ServiceAccountCredentials
from datetime import datetime
import time

# Define the scope and authenticate with Google
scope = ["https://spreadsheets.google.com/feeds", "https://www.googleapis.com/auth/drive"]
creds = ServiceAccountCredentials.from_json_keyfile_name('Iot123.json', scope)
client = gspread.authorize(creds)

# Open the Google Spreadsheet by title or by key
spreadsheet = client.open("IoT123")  # or use .open_by_key("your_spreadsheet_key")

# Select the sheet to work with (e.g., the first sheet)
sheet = spreadsheet.sheet1

# Define headers
headers = ["Date", "Time", "Temperature (°C)", "Humidity (%)"]
sheet.append_row(headers)

# Uploading date, time, temperature, and humidity using a loop
for _ in range(10):  # Adjust the range as needed
    date = datetime.now().strftime("%Y-%m-%d")
    time_now = datetime.now().strftime("%H:%M:%S")
    temperature = round(random.uniform(20.0, 35.0), 2)  # Random temperature between 20 and 35°C
    humidity = round(random.uniform(30.0, 70.0), 2)  # Random humidity percentage between 30% and 70%
    sheet.append_row([date, time_now, temperature, humidity])
    time.sleep(1)  # Sleep to avoid hitting API limits

print("Data uploaded successfully!")
