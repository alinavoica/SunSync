# SunSync
![image](https://github.com/user-attachments/assets/e21c13fe-f865-4402-9c5f-1577b03b1637)
![image](https://github.com/user-attachments/assets/6043ef24-9256-46a2-87c0-cbb184c19471)

### **Code Breakdown:**

1. **Wi-Fi Connection:**
   - Connects to the Wi-Fi network using the SSID `"B100"` and an empty password.
   - Waits until the Wi-Fi connection is established.

2. **Fetching Sunrise Data:**
   - Sends an HTTP GET request to the Open-Meteo API to fetch sunrise times for the specified location (`latitude: 44.43, longitude: 26.14`, which corresponds to Bucharest, Romania).
   - Parses the JSON response and extracts the sunrise times for several days.
   - Stores the extracted sunrise times in the `ora` array and prints them to the serial monitor.

3. **Displaying Data on LEDs and 7-Segment Display:**
   - Uses an array `nr` to define the segment states for displaying numbers (0-9).
   - The function `afisareOre(String a)` controls the 7-segment display to show the hour and minute.
   - The function `prelucrare(String aux)` alternates between displaying the extracted sunrise times and turning off the display at intervals.

4. **LED Control:**
   - The function `stingereLeduri()` turns off all LEDs.
   - The function `aprindereLeduri(int i)` turns on a specific LED corresponding to the day index (from 0 to 6).
   - After retrieving and processing the sunrise data, LEDs are turned on one by one for each day, and the respective sunrise time is displayed on the 7-segment display.

5. **Execution Flow:**
   - After setup, the sunrise times for the upcoming days are displayed sequentially, with the corresponding LED lighting up for each day.
   - The `loop()` function is empty, meaning the program runs only once during `setup()` and then stops.

### **Summary of Functionality:**
- Connects to Wi-Fi.
- Fetches sunrise times from the Open-Meteo API.
- Displays the extracted sunrise times on a 7-segment display.
- Lights up specific LEDs corresponding to different days.
- Turns off all LEDs after displaying the information.

This could be part of a weather-related project, such as an electronic clock displaying daily sunrise times.

