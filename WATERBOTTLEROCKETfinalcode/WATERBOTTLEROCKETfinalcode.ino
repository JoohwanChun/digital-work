//2DIGT - 22493 Joohwan Chun
//Libraries
#include <SparkFun_LPS25HB_Arduino_Library.h>        // Include the LPS25HB sensor library
#include <Wire.h>                                    // Include the Wire library for I2C communication
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
  initialiseSystem();  // Initialise the system
}

void loop() {
  readSensorData();   // Read sensor data
  logDataToSD(true);  // Log data to SD card with debug information ('true' indicates debug mode)

  delay(50);  // Wait for 50 millis
}

void initialiseSystem() {
  Serial.begin(9600);  // Initialise serial communication at 9600 baud rate
  Wire.begin();        // Initialise I2C communication
  ptSensor.begin();    // Initialise the pressure and temperature sensor
  sensorLog.begin();   // Initialise the OpenLog

  if (!ptSensor.isConnected()) {              // Check if the sensor is not connected
    Serial.println("PT sensor not working");  // Alert the user that the sensor is not working
    while (1)
      ;  // Halt the program

    // Append a file on the SD card and write the header
    sensorLog.append(LOG_FILE);
    sensorLog.println(HEADER);
    sensorLog.syncFile();           // Ensure the data is written to the SD card
    Serial.println("Setup done!");  // Indicate that setup is complete
  }
}
// Read actual data from the LPS25HB sensor
void readSensorData() {
  pressure = ptSensor.getPressure_hPa();         // Get pressure in hPa
  temperature = ptSensor.getTemperature_degC();  // Get temperature in degrees Celsius
}

//Log the data to SD card
void logDataToSD(bool debug) {
  unsigned long currentTime = millis();  // Get the current time in milliseconds since the program started

  if (debug) {
    logDataToSerial(currentTime);  // Log data to the serial monitor
  }

  logDataToFile(currentTime);  // Log data to the SD card
}

//Log the data to the serial monitor include the current time
void logDataToSerial(unsigned long currentTime) {
  Serial.print("Pressure in hPa: ");
  Serial.print(pressure);                  // Print the pressure reading in hPa
  Serial.print(", Temperature (degC): ");  // Print the temperature reading in degrees Celsius
  Serial.print(temperature);
  Serial.print(", Current time since the program started: ");
  Serial.println(currentTime);                  // Print the pressure reading in hPa
  Serial.println("Data logged successfully.");  // Indicate that data logging was successful
}


// Log data to SD card will be using the currentTime from the millis method
void logDataToFile(unsigned long currentTime) {
  sensorLog.print(pressure);  // Log pressure data
  sensorLog.print(", ");
  sensorLog.print(temperature);  // Log temperature data
  sensorLog.print(", ");
  sensorLog.println(currentTime);  // Log current time
  sensorLog.syncFile();            // Ensure the data is written to the SD card
}