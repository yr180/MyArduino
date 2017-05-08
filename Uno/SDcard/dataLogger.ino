/*
 This example logs data from a LM35 temperature
 sensor to an SD card using the SD library.

 The circuit:
 * LM35 on A0
 * SD card attached to SPI bus as follows:
   * MOSI - pin 11
   * MISO - pin 12
   * CLK - pin 13
   * CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 */

#include <SPI.h>
#include <SD.h>

#define ADC_REF 4540   // reference voltage in mV
const int chipSelect = 4;

void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    return;
  }
  
  Serial.println("card initialized.");
}

void loop() 
{
  String dataString = "";
  
  int reading = analogRead(A0);
  LM35 = (ADC_REF*reading/1024)/10;  //Conversion for temperature in °C
  dataString = String(LM35) + " °C";

  File dataFile = SD.open("datalog.txt", FILE_WRITE);  //Open existing file or create one for iniitial iteration

  if (dataFile) 
  {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  
  delay(10000);                      //Update every 10 seconds
}
