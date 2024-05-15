//libraries
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Wire.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"
OpenLog sensorLog;     //Create instance
LPS25HB PTSensor;  // Create an object of the LPS25HB class

void setup() {
  Serial.begin(9600);
  Wire.begin();
  PTSensor.begin();  // Begin links an I2C port and I2C address to the sensor, sets an I2C speed, begins I2C on the main board, and then sets default settings
  sensorLog.begin();     //Open connection to OpenLog (no pun intended)

  if (PTSensor.isConnected() == false) {
    Serial.println("PT sensor not working");  // Alert the user that the device is disconnected
    while (1)
      ;
  }


  sensorLog.append("Vlog.txt");
  sensorLog.println("Temp, pressure, time");
  sensorLog.syncFile();
  Serial.println("setup done!");
}

void loop() {

  // Read sensor data
  readSensorData();

  logDataToSD(true);  //t = debug f = launching rocket

  delay(40);          // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
}

void readSensorData() {
  // Read data from TMP117 sensor
  sensorReading1 = sensorTMP.readTempC();
  
  // Read data from LPS25HB sensor
  sensorReading2 = sensor.readPressureMillibars();
  sensorReading3 = sensor.readTempC();
}

void logDataToSD(bool debug) {
  //Get current time
  unsigned long currentTime = millis();
  if (debug) {
    Serial.print("Pressure in hPa: ");
    Serial.print(PTSensor.getPressure_hPa());  // Get the pressure reading in hPa
    Serial.print(", Temperature (degC): ");
    Serial.println(PTSensor.getTemperature_degC());  // Get the temperature in degrees C


    // sensorLog.print("Pressure in hPa: ");
    sensorLog.print(PTSensor.getPressure_hPa());  // Get the pressure reading in hPa
    sensorLog.print(", ");
    sensorLog.println(PTSensor.getTemperature_degC());
    sensorLog.print(", ");
    sensorLog.println(currentTime);
    sensorLog.syncFile();
    Serial.println("Data logged successfully.");
  } else {
    sensorLog.print(PTSensor.getPressure_hPa());  // Get the pressure reading in hPa
    sensorLog.print(", ");
    sensorLog.println(PTSensor.getTemperature_degC());
    sensorLog.print(", ");
    sensorLog.println(currentTime);
    sensorLog.syncFile();
  }
}
