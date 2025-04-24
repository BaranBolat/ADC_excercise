/*  
  Baran Bolat
  20.04.2025
  ADC_Converter
*/

#include <Arduino.h>

#define valuePin A0 

void setup() 
{
  Serial.begin(9600); 
}

void loop() 
{
  int value = analogRead(valuePin); // read value of pin A0
  float voltage = value * (5.0 / 1023.0); // value in voltage

  Serial.print("Potentiometer analog value = ");
  Serial.print(voltage); 
  Serial.println(" V");

  delay(500); // wait 500ms
}

