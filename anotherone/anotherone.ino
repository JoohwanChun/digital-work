//libraries
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Wire.h>
OpenLog myLog; //Create instance
LPS25HB PTSensor; // Create an object of the LPS25HB class

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  PTSensor.begin(); // Begin links an I2C port and I2C address to the sensor, sets an I2C speed, begins I2C on the main board, and then sets default settings
  myLog.begin(); //Open connection to OpenLog (no pun intended)

  if (PTSensor.isConnected() == false)  {
    Serial.println("LPS25HB disconnected. Reset the board to try again.");     // Alert the user that the device is disconnected 
  

   
    myLog.append("Vlog.txt"); 
   myLog.println("This is recorded to the default log file");
    myLog.syncFile();
    while (1);
    Serial.println("Done!");
  }
}

void loop()
{
  Serial.print("Pressure in hPa: ");
  Serial.print(PTSensor.getPressure_hPa()); // Get the pressure reading in hPa
  Serial.print(", Temperature (degC): ");
  Serial.println(PTSensor.getTemperature_degC()); // Get the temperature in degrees C


 // myLog.print("Pressure in hPa: ");
  Serial.print(PTSensor.getPressure_hPa()); // Get the pressure reading in hPa
  Serial.print(", ");
  Serial.println(PTSensor.getTemperature_degC()); 
  delay(40); // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
}