//2DIGT - 22493 Joohwan Chun
//Libraries
#include <SparkFun_LPS25HB_Arduino_Library.h>  // Include the LPS25HB sensor library
#include <Wire.h>                              // Include the Wire library for I2C communication
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"  // Include the OpenLog library

OpenLog sensorLog;  // Create an instance of the OpenLog class
LPS25HB ptSensor;   // Create an instance of the LPS25HB class

// Constants for file names and headers
const char* LOG_FILE = "VLOG.TXT";
const char* HEADER = "Temp, pressure, time";

// Variables to store sensor readings
float temperature;
float pressure;

void setup() {
  initialiseSystem();  // Initialize the system
}

void loop() {
  readSensorData();  // Read sensor data
  logDataToSD(true);  // Log data to SD card with debug information ('true' indicates debug mode)
  
  // Generate a random delay between 20 and 60 ms
  int randomDelay = random(10, 1000);
  Serial.println(randomDelay);  //Print the time of delay on the serial monitor
  delay(randomDelay);  // Wait for a random period of time between 10 and 1000 ms
}

void initialiseSystem() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  Wire.begin();        // Initialize I2C communication
  ptSensor.begin();    // Initialize the pressure and temperature sensor
  sensorLog.begin();   // Initialize the OpenLog

  if (!ptSensor.isConnected()) {  // Check if the sensor is not connected
    Serial.println("PT sensor not working");  // Alert the user that the sensor is not working
    while (1);  // Halt the program

  // Append a file on the SD card and write the header
  sensorLog.append(LOG_FILE);
  sensorLog.println(HEADER);
  sensorLog.syncFile();  // Ensure the data is written to the SD card
  Serial.println("Setup done!");  // Indicate that setup is complete

  randomSeed(analogRead(0));  // Seed the random number generator
}

void readSensorData() {
  // Read actual data from the LPS25HB sensor
  pressure = ptSensor.getPressure_hPa();  // Get pressure in hPa
  temperature = ptSensor.getTemperature_degC();  // Get temperature in degrees Celsius
}

void logDataToSD(bool debug) {
  unsigned long currentTime = millis();  // Get the current time in milliseconds since the program started

  if (debug) {
    logDataToSerial();  // Log data to the serial monitor
  }

  logDataToFile(currentTime);  // Log data to the SD card
}

void logDataToSerial() {
  Serial.print("Pressure in hPa: ");
  Serial.print(pressure);  // Print the pressure reading in hPa
  Serial.print(", Temperature (degC): ");
  Serial.println(temperature);  // Print the temperature reading in degrees Celsius
  Serial.println("Data logged successfully.");  // Indicate that data logging was successful
}

void logDataToFile(unsigned long currentTime) {
  // Log data to SD card
  sensorLog.print(pressure);  // Log pressure data
  sensorLog.print(", ");
  sensorLog.print(temperature);  // Log temperature data
  sensorLog.print(", ");
  sensorLog.println(currentTime);  // Log current time
  sensorLog.syncFile();  // Ensure the data is written to the SD card
}