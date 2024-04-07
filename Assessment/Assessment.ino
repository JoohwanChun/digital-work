#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SparkFun_TMP117.h> //TEACHER COMMENTS what about the openLog library that handles the sdcard?
#include <SparkFun_TMP117_Registers.h>
#include <SparkFun_LPS25HB_Arduino_Library.h> //TEACHER COMMENTS this library is for the sensor we are using, so im not sure about this TMP117 code you have below?!

const int chipSelect = 10; // CS pin for the SD card module

TMP117 sensorTMP; // Create an object of the TMP117 class

// Define your sensor's I2C address
const int sensorAddress = 0x00; // Replace 0x00 with the actual address

// Define sensor readings variables
float sensorReading1, sensorReading2, sensorReading3;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  
  // Initialize I2C communication
  Wire.begin();
  //*****************************************************************************
  // Initialize SD card //TEACHER COMMENTS what else is it doing?
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  
  Serial.println("SD card initialized successfully.");
  
  // Create and open a file for data logging
  File dataFile = SD.open("data.csv", FILE_WRITE);
  
  // Check if the file opened successfully //TEACHER COMMENTS what does it do if it doesn't? explain this code more 
  if (!dataFile) {
    Serial.println ("Error opening data file!");
    return;
  }
  
  // Write headers to the CSV file //TEACHER COMMENTS what are reading1 2 and 3? the LPS25HB sensor we are using gives temperature and pressure readings...
  dataFile.println("Time,Reading1,Reading2,Reading3");
  
  // Close the file
  dataFile.close();

  // Initialize the TMP117 sensor ***********************************************
  if (!sensorTMP.begin())
  {
    Serial.println("TMP117 sensor not detected!");
    while (1);
  }
  
  Serial.println("TMP117 sensor initialized successfully.");
  
  // Initialize the LPS25HB sensor ***********************************************
  if (!sensor.init())
  {
    Serial.println("LPS25HB sensor not detected!");
    while (1);
  }
  
  Serial.println("LPS25HB sensor initialized successfully.");
}

void loop() {
  // Read sensor data
  readSensorData();
  
  // Log sensor data to SD card
  logDataToSD();
  
  // Delay for some time before taking the next reading
  delay(1000); // Adjust as needed //TEACHER COMMENTS do we need a delay at all?
}

void readSensorData() {
  // Read data from TMP117 sensor
  sensorReading1 = sensorTMP.readTempC(); //TEACHER COMMENTS why are we looking at temp twice?
  
  // Read data from LPS25HB sensor
  sensorReading2 = sensor.readPressureMillibars(); //TEACHER COMMENTS are these methods you can call? they don't look like what we might see in the example code?
  sensorReading3 = sensor.readTempC();
}

//TEACHER COMMENTS what does this method do? explain in a big comment 
void logDataToSD() {
  // Open the data file in append mode
  File dataFile = SD.open("data.csv", FILE_WRITE);
  
  // Check if the file opened successfully 
  if (datafile) {
    //Get current time
    unsigned long currentTime = millis();

    //Write data to the file
    dataFile.print(currentTime);
    dataFile.print(",");
    dataFile.print(sensorReading1);
    dataFile.print(",");
    dataFile.print(sensorReading2);
    dataFile.print(",");
    dataFile.println(sensorReading3);

    //Close the file
    dataFile.close();

    Serial.println("Data logged successfully.");
  } else {
    Serial.println("Error opening data file for logging!"); //TEACHER COMMENTS are these the words you would use?
  }
}
  



