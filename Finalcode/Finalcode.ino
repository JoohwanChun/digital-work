//2DIGT - 22493 Joohwan Chun 
#include <SparkFun_LPS25HB_Arduino_Library.h>  // Include the LPS25HB sensor library
#include <Wire.h>                              // Include the Wire library for I2C communication
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"  // Include the OpenLog library

OpenLog sensorLog;  // Create an instance of the OpenLog class
LPS25HB ptSensor;   // Create an instance of the LPS25HB class

// Constants for file names
const char* LOG_FILE = "VLOG.TXT";
const char* HEADER = "Temp, pressure, time";

// Variables to store simulated sensor readings
float sensorReading1;
float sensorReading2;
float sensorReading3;

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  Wire.begin();        // Initialize I2C communication
  ptSensor.begin();    // Initialize the pressure and temperature sensor
  
  sensorLog.begin();   // Initialize the OpenLog

  if (!ptSensor.isConnected()) {  // Check if the sensor is connected
    Serial.println("PT sensor not working");  // Alert the user that the sensor is not working
    while (1);  // Halt the program if the sensor is not connected
  }

  // Append a file on the SD card and write the header
  sensorLog.append(LOG_FILE);
  sensorLog.println(HEADER);
  sensorLog.syncFile();  // Ensure the data is written to the SD card
  Serial.println("Setup done!");  // Indicate that setup is complete

  // Seed the random number generator
  randomSeed(analogRead(0));
}

void loop() {
  readSensorData();  // Read sensor data
  logDataToSD(true);  // Log data to SD card with debug information ('true' indicates debug mode)

  delay(40);  // Wait for 40 ms (maximum update rate of the sensor is 25 Hz)
}

void readSensorData() {
  // Generate random data for the TMP117 sensor (simulating temperature in Celsius)
  sensorReading1 = random(200, 300) / 10.0;

  // Generate random data for the LPS25HB sensor
  sensorReading2 = random(950, 1050);  // Simulating pressure in hPa
  sensorReading3 = random(200, 300) / 10.0;  // Simulating temperature in Celsius
}

void logDataToSD(bool debug) {
  unsigned long currentTime = millis();  // Get the current time in milliseconds since the program started

  if (debug) {
    // If in debug mode, print data to the serial monitor
    Serial.print("Pressure in hPa: ");
    Serial.print(sensorReading2);  // Print the pressure reading in hPa
    Serial.print(", Temperature (degC): ");
    Serial.println(sensorReading3);  // Print the temperature reading in degrees Celsius

    // Log data to SD card
    sensorLog.print(sensorReading2);  // Log pressure data
    sensorLog.print(", ");
    sensorLog.print(sensorReading3);  // Log temperature data
    sensorLog.print(", ");
    sensorLog.println(currentTime);  // Log current time
    sensorLog.syncFile();  // Ensure the data is written to the SD card
    Serial.println("Data logged successfully.");  // Indicate that data logging was successful
  } else {
    // If not in debug mode, only log data to SD card
    sensorLog.print(sensorReading2);  // Log pressure data
    sensorLog.print(", ");
    sensorLog.print(sensorReading3);  // Log temperature data
    sensorLog.print(", ");
    sensorLog.println(currentTime);  // Log current time
    sensorLog.syncFile();  // Ensure the data is written to the SD card
  }
}
