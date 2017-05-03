/*
  This example provides the load cell output in Kg. 
  Please run calibration sketch before to get the calibration_factor for your specific load cell setup.

 This example code uses bogde's HX711 library, released under a GNU GENERAL PUBLIC LICENSE https://github.com/bogde/HX711
*/

#include "HX711.h"

#define calibration_factor -292500 //This value is obtained using the Calibration sketch

#define DOUT  9
#define CLK  8

HX711 scale(DOUT, CLK);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  scale.set_scale(calibration_factor); 
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

void loop() {
  Serial.print("Weight: ");
  Serial.print(scale.get_units()*0.453592, 3); // 0.453592 is used for converting lbs to Kg 
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
}
